#include "neuralnet.hpp"

#include <random>

Eigen::VectorXd NeuralNet::ReLU(Eigen::VectorXd& input) {
    Eigen::VectorXd output = input;
    for (int i = 0; i < output.rows(); i++) {
        output(i) = output(i) >= 0 ? output(i) : 0; 
    }

    return output;
}

NeuralNet::NeuralNet(NeuralNet& other) {
   layers = std::vector<Eigen::MatrixXd>(other.layers.size());
   for (int i = 0; i < other.layers.size(); i++) {
        layers[i] = other.layers[i];
   }
}

NeuralNet::NeuralNet(size_t boardWidth, size_t boardHeight) {
    const int layersCount = 4;
    const int inputSize = boardWidth * boardHeight;
    layers.reserve(layersCount);

    layers.push_back(Eigen::MatrixXd(128, inputSize));
    layers.push_back(Eigen::MatrixXd(256, 128));
    layers.push_back(Eigen::MatrixXd(128, 256));
    layers.push_back(Eigen::MatrixXd(3, 128));
    
    double lowerBound = -1.0;
    double upperBound = 1.0;
    std::uniform_real_distribution<double> unif(lowerBound, upperBound);
    std::default_random_engine re;
    for (int i = 0; i < layersCount; i++) {
        for (int row = 0; row < layers[i].rows(); row++) {
            for (int col = 0; col < layers[i].cols(); col++) {
                layers[i](row, col) = unif(re);
            }
        }
    }
}

Eigen::VectorXd NeuralNet::feed(Eigen::VectorXd input) {
    for (Eigen::MatrixXd& layer : layers) {
        input = layer * input;
        input = ReLU(input);
    }
    return input;
}
