#include "board.hpp"

#include <random>
#include <chrono>

using namespace std;

vector<vector<bool>> Board::obstacles() {
    return _obstacles;
}

vector<Coord> Board::circles() {
    return _circles;
}

size_t Board::width() {
    return _width;
}

size_t Board::height() {
    return _height;
}

Eigen::VectorXd Board::toVector(size_t circle) {
    Eigen::VectorXd vector(_width * _height);

    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            size_t coords = (i * _height) + j;
            vector(coords) = _obstacles[i][j] ? 1 : 0;
        }
    }

    size_t circleX = _circles[circle].x;
    size_t circleY = _circles[circle].y;

    size_t coordCircle = (circleX * _height) + circleY;
    vector(coordCircle) = 2;
    return vector;
}

Board::Board(size_t width, size_t height, size_t circles) {
    this->_width = width;
    this->_height = height;

    this->_circles = vector<Coord>(circles);

    _obstacles = vector<vector<bool>>(
            width, vector<bool>(height, false));
}

bool Board::randomize(double probability) {
    std::uniform_real_distribution<double> unif(0, 1);
    std::default_random_engine re;
    re.seed(std::chrono::system_clock::now()
            .time_since_epoch().count());

    for (size_t i = 0; i < _width; i++) {
        for (size_t j = 0; j < _height; j++) {
            _obstacles[i][j] = unif(re) < probability;
        }
    }

    // Djikstra to check if the board is valid
    vector<bool> prev(_height, false);
    vector<bool> cur(_height, false);
    for (size_t i = 0; i < _height; i++) {
        prev[i] = !_obstacles[_width - 1][i];
    }
    for (int i = _width - 2; i >= 0; i--) {
        for (int j = 0; j < _height; j++) {
            bool toTop = j > 0 ?
                prev[j - 1] : false;
            bool toFront = prev[j];
            bool toBottom = j < _height - 1 ?
                prev[j + 1] : false;

            cur[j] = !_obstacles[i][j] &&
                (toTop || toFront || toBottom);
        }
        swap(prev, cur); 
    }

    return prev[_height / 2];
}

void Board::generate(double probability) {
    while (!randomize(probability)) {
        continue;
    }
    for (size_t i = 0; i < _circles.size(); i++) {
        _circles[i].x = 0;
        _circles[i].y = _height / 2;
    }
}

void Board::reset() {
    for (int i = 0; i < _circles.size(); i++) {
        _circles[i].x = 0;
        _circles[i].y = _height / 2;
    }
}

bool Board::moveCircle(size_t circle, int direction) {
    assert(direction >= -1 && direction <= 1);
    Coord coord = _circles[circle];

    if (coord.x == _width - 1) {
        return false;
    }
    bool toTop = coord.y > 0 ? 
        !_obstacles[coord.x + 1][coord.y - 1] : false;
    bool toFront = !_obstacles[coord.x + 1][coord.y];
    bool toBottom = coord.y < _height - 1 ?
        !_obstacles[coord.x + 1][coord.y + 1] : false;

    bool isValid = (direction == -1 && toTop) ||
        (direction == 0 && toFront) ||
        (direction == 1 && toBottom);
    
    if (direction == -1 && toTop) {
        _circles[circle].x++;
        _circles[circle].y--;
    } else if (direction == 0 && toFront) {
        _circles[circle].x++;
    } else if (direction == 1 && toBottom) {
        _circles[circle].x++;
        _circles[circle].y++;
    }

    return isValid;
}
