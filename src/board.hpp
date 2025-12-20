#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <stddef.h>
#include <vector>
#include <Eigen/Dense>

using namespace std;

class Board {
    private:
        struct Coord {
            size_t x;
            size_t y;
        };

        size_t width;
        size_t height;

        vector<Coord> circles;
        vector<vector<bool>> grid;

        bool randomize(double probability);
    public:
        Board(size_t width, size_t height, size_t circles);

        void generate(double probability);
        Eigen::VectorXd toVector();
        vector<vector<bool>> obstacles();
};

#endif /* __BOARD_HPP__ */
