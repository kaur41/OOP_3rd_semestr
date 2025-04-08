#include "D://OOP_3rd_semestr/lib_DSU/DSU.h"
#include "D://OOP_3rd_semestr//D_Massive/DMassiv.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>
#include <windows.h>

class MazeGen {
private:
    int rows, cols;
    DMassiv<bool> horizon_walls;
    DMassiv<bool> vertical_walls;

    int toIndex(int i, int j) const {
        return i * cols + j;
    }

public:
    MazeGen(int r, int c) : rows(r), cols(c) {
        horizon_walls = DMassiv<bool>((rows - 1) * cols, true);
        vertical_walls = DMassiv<bool>(rows * (cols - 1), true);
        srand(time(nullptr));
    }

    void generate() {
        DSU dsu(rows * cols);
        std::vector<std::pair<char, std::pair<int, int>>> walls;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols - 1; j++) {
                walls.emplace_back('V', std::make_pair(i, j));
            }
        }

        for (int i = 0; i < rows - 1; i++) {
            for (int j = 0; j < cols; j++) {
                walls.emplace_back('H', std::make_pair(i, j));
            }
        }

        std::random_shuffle(walls.begin(), walls.end());

        for (const auto& wall : walls) {
            char type = wall.first;
            int i = wall.second.first;
            int j = wall.second.second;

            if (type == 'H') {
                int cellAbove = toIndex(i, j);
                int cellBelow = toIndex(i + 1, j);
                if (dsu.Find(cellAbove) != dsu.Find(cellBelow)) {
                    horizon_walls.replace(i * cols + j, false);
                    dsu.Union(cellAbove, cellBelow);
                }
            }
            else {
                int cellLeft = toIndex(i, j);
                int cellRight = toIndex(i, j + 1);
                if (dsu.Find(cellLeft) != dsu.Find(cellRight)) {
                    vertical_walls.replace(i * (cols - 1) + j, false);
                    dsu.Union(cellLeft, cellRight);
                }
            }
        }
    }

    void print() {
        for (int j = 0; j < cols; ++j) {
            std::cout << "+---";
        }
        std::cout << "+\n";

        for (int i = 0; i < rows; ++i) {
            std::cout << "|";
            for (int j = 0; j < cols - 1; ++j) {
                std::cout << "   ";
                if (vertical_walls.data()[i * (cols - 1) + j]) {
                    std::cout << "|";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << "   |\n";

            if (i < rows - 1) {
                for (int j = 0; j < cols; ++j) {
                    std::cout << "+";
                    if (horizon_walls.data()[i * cols + j]) {
                        std::cout << "---";
                    }
                    else {
                        std::cout << "   ";
                    }
                }
                std::cout << "+\n";
            }
        }

        for (int j = 0; j < cols; ++j) {
            std::cout << "+---";
        }
        std::cout << "+\n";
    }
};

int main() {
    int rows, cols;
    std::cout << "Enter maze dimensions (rows cols): ";
    std::cin >> rows >> cols;

    MazeGen maze(rows, cols);
    maze.generate();
    maze.print();

    system("pause");
    return 0;

}