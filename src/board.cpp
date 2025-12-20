#include "board.hpp"

#include <random>
#include <chrono>

using namespace std;

Board::Board(size_t width, size_t height, size_t circles) {
    this->width = width;
    this->height = height;

    this->circles = vector<Coord>(circles);

    grid = vector<vector<bool>>(width, vector<bool>(height, false));
}

bool Board::randomize(double probability) {
    std::uniform_real_distribution<double> unif(0, 1);
    std::default_random_engine re;
    re.seed(std::chrono::system_clock::now().time_since_epoch().count());
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            grid[i][j] = unif(re) < probability;
        }
    }

    // Djikstra to check if the board is valid
    vector<bool> prev(height, false);
    vector<bool> cur(height, false);
    for (size_t i = 0; i < height; i++) {
        prev[i] = !grid[width - 1][i];
    }
    for (int i = width - 2; i >= 0; i--) {
        for (int j = 0; j < height; j++) {
            bool toTop = j > 0 ?
                prev[j - 1] : false;
            bool toFront = prev[j];
            bool toBottom = j < height - 1 ?
                prev[j + 1] : false;

            cur[j] = !grid[i][j] &&
                (toTop || toFront || toBottom);
        }
        prev = cur;
    }

    return cur[height / 2];
}

void Board::generate(double probability) {
    while (!randomize(probability)) {
        continue;
    }
    for (size_t i = 0; i < circles.size(); i++) {
        circles[i].x = 0;
        circles[i].y = height / 2;
    }
}

Eigen::VectorXd Board::toVector() {
    Eigen::VectorXd vector(width * height);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            size_t coords = (i * height) + j;
            vector(coords) = grid[i][j] ? 1 : 0;
        }
    }

    return vector;
}

vector<vector<bool>> Board::obstacles() {
    return grid;
}
