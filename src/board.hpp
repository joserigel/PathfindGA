#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <stddef.h>
#include <vector>
#include <Eigen/Dense>

using namespace std;

struct Coord {
    size_t x;
    size_t y;
};

class Board {
    private:       
        size_t _width;
        size_t _height;

        vector<Coord> _circles;
        vector<vector<bool>> _obstacles;

        bool randomize(double probability);
    public:
        Board(size_t width, size_t height, size_t circles);

        void generate(double probability);
        Eigen::VectorXd toVector(size_t circle);
        vector<vector<bool>> obstacles();
        vector<Coord> circles();
        bool moveCircle(size_t circle, int direction);
        void reset();
        size_t width();
        size_t height();
};

#endif /* __BOARD_HPP__ */
