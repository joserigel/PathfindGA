#ifndef __NEURAL_NET_HPP__
#define __NEURAL_NET_HPP__

#include <Eigen/Dense>
#include <vector>

class NeuralNet {
    private:
        size_t _peripheral;
        size_t _horizon;
        std::vector<Eigen::MatrixXd> layers;
        Eigen::VectorXd ReLU(Eigen::VectorXd& input);

    public:
        NeuralNet(size_t peripheral, size_t horizon);
        NeuralNet(const NeuralNet& other) noexcept;
        NeuralNet(NeuralNet&& other) noexcept;
        NeuralNet& operator=(NeuralNet& other);
        
        Eigen::VectorXd feed(Eigen::VectorXd input);
        void mutate(double rate); 
};

#endif /*  __NEURAL_NET_HPP__ */
