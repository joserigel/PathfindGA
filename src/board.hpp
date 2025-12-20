#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <stddef.h>
#include <vector>
#include <Eigen/Dense>

using namespace std;

class Board {
    private:
        size_t width;
        size_t height;

        size_t x;
        size_t y;

        vector<vector<bool>> board;
    public:
        Board(size_t width, size_t height);

        void generate(double probability);
        Eigen::VectorXd toVector();
        vector<vector<bool>> data();
};

#endif /* __BOARD_HPP__ */
