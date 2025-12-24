#ifndef __TRAINING_HPP__
#define __TRAINING_HPP__

#include "neuralnet.hpp"
#include "board.hpp"

#include <vector>
#include <thread>

using namespace std;

class Training {
    private:
        size_t instances;
        size_t _peripheral;
        size_t _horizon;
        vector<thread> trainingThreads;
        vector<double> scores;
        vector<NeuralNet> nets;

        void train(size_t instance, Board& board);
    public:
        Training(size_t width, size_t height, size_t peripheral, size_t horizon, size_t instances);

        void tick(Board& board);
        void pickAndMutate(double rate);
        void clear();
};

#endif /* __TRAINING_HPP__ */
