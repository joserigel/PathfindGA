#include "training.hpp"

#include <Eigen/Dense>
#include <iostream>

Training::Training(size_t width, size_t height, size_t peripheral, size_t horizon, size_t instances
        ) : instances(instances), scores(instances), _peripheral(peripheral), _horizon(horizon) { 
   nets.reserve(instances); 
   for (int i = 0; i < instances; i++) {
       nets.emplace_back(peripheral, horizon);
   }
}

void Training::train(size_t instance, Board& board) {
    Eigen::VectorXd input = board.toVector(instance, _peripheral, _horizon);
    Eigen::VectorXd output = nets[instance].feed(input);

    int direction = 0;
    double confidence = output(1);
    if (output(0) > confidence) {
        direction = -1;
        confidence = output(0);
    }

    if (output(2) > confidence) {
        direction = 1;
        confidence = output(1);
    }
    switch(direction) {
        case -1:
            cout << "L";
            break;
        case 0:
            cout << "F";
            break;
        case 1:
            cout << "R";
            break;
    }
    bool valid = board.moveCircle(instance, direction);
    
    /**
     * Currently the scoring is very simple
     * Add 1 if it can proceed
     *
     */
    if (valid) {
        scores[instance]++;
    } 
}

void Training::tick(Board& board) {
    trainingThreads.clear();
    trainingThreads.reserve(instances);
    for (int i = 0; i < instances; i++) {
        trainingThreads.emplace_back(&Training::train, this, i, std::ref(board));
    }

    for (int i = 0; i < instances; i++) {
        trainingThreads[i].join();
    }
}

void Training::clear() {
    for (auto& score : scores) {
        score = 0;
    }
}

void Training::pickAndMutate(double rate) {
    size_t bestIdx = 0;
    size_t maxScore = scores[0];
    for (int i = 1; i < scores.size(); i++) {
        if (scores[i] > maxScore) {
            maxScore = scores[i];
            bestIdx = i;
        }
    }
    cout << "bestNet: "<< bestIdx << ", score: " << maxScore << endl;
    NeuralNet bestNet = nets[bestIdx];
    for (int i = 0; i < nets.size(); i++) {
        nets[i] = bestNet; 
        nets[i].mutate(rate);
    }
}


