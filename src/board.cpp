#include "board.hpp"

#include <random>
#include <chrono>

Board::Board(size_t width, size_t height) {
    this->width = width;
    this->height = height;

    board = vector<vector<bool>>(width, vector<bool>(height, false));
}

void Board::generate(double probability) {
    std::uniform_real_distribution<double> unif(0, 1);
    std::default_random_engine re;
    re.seed(std::chrono::system_clock::now().time_since_epoch().count());
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            board[i][j] = unif(re) < probability;
        }
    }

    // Djikstra to check if the board is valid
    vector<bool> possibleToProceed(height, false);
    for (size_t i = 0; i < height; i++) {
        possibleToProceed[i] = !board[width - 1][i];
    }
    for (int i = width - 2; i >= 0; i--) {
        for (int j = 0; j < height; j++) {
            bool toTop = j > 0 ?
                possibleToProceed[j - 1] : false;
            bool toFront = possibleToProceed[j];
            bool toBottom = j < height - 1 ?
                possibleToProceed[j + 1] : false;

            possibleToProceed[i] = !board[i][j] &&
                (toTop || toFront || toBottom);
        }
    }

    x = 0;
    y = height / 2;

    if (!possibleToProceed[height / 2]) {
        generate(probability);
    }
}

Eigen::VectorXd Board::toVector() {
    Eigen::VectorXd vector(width * height);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            size_t coords = (i * height) + j;
            vector(coords) = board[i][j] ? 1 : 0;
        }
    }
    vector((x * height) + y) = 2;

    return vector;
}

vector<vector<bool>> Board::data() {
    return board;
}
