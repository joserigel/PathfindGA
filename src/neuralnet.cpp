#include "neuralnet.hpp"

#include <random>
#include <chrono>

Eigen::VectorXd NeuralNet::ReLU(Eigen::VectorXd& input) {
    Eigen::VectorXd output = input;
    for (int i = 0; i < output.rows(); i++) {
        output(i) = output(i) >= 0 ? output(i) : 0; 
    }

    return output;
}

NeuralNet::NeuralNet(const NeuralNet& other) noexcept {
   layers = std::vector<Eigen::MatrixXd>(other.layers.size());
   for (int i = 0; i < other.layers.size(); i++) {
        layers[i] = other.layers[i];
   }
}

NeuralNet::NeuralNet(NeuralNet&& other) noexcept :
    layers(other.layers) {
}

NeuralNet& NeuralNet::operator=(NeuralNet& other) {
    this->layers = other.layers;
    return *this;
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
    re.seed(std::chrono::system_clock::now()
            .time_since_epoch().count());
    for (int i = 0; i < layersCount; i++) {
        for (int row = 0; row < layers[i].rows(); row++) {
            for (int col = 0; col < layers[i].cols(); col++) {
                layers[i](row, col) = unif(re);
            }
        }
    }
}

void NeuralNet::mutate(double rate) {
    std::uniform_real_distribution<double> unif(-rate, rate);
    std::default_random_engine re;
    re.seed(std::chrono::system_clock::now().
            time_since_epoch().count());

    for (int i = 0; i < layers.size(); i++) {
        for (int row = 0; row < layers[i].rows(); row++) {
            for (int col = 0; col < layers[i].cols(); col++) {
                layers[i](row, col) += unif(re);
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
