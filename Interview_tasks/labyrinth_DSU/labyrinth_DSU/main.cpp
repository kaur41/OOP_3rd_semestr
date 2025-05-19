#include "D://OOP_3rd_semestr/lib_DSU/DSU.h"
#include "D://OOP_3rd_semestr//D_Massive/DMassiv.h"

class MazeGen {
private:
    int rows, cols;
    DMassiv<bool> horizon_walls;
    DMassiv<bool> vertical_walls;

    int toIndex(int i, int j) const {
        return i * cols + j;
    }

    void shuffleWalls(char* types, int* i_coords, int* j_coords, int count) {
        for (int k = count - 1; k > 0; k--) {
            int rand_index = rand() % (k + 1);
            char temp_type = types[k];
            types[k] = types[rand_index];
            types[rand_index] = temp_type;
            int temp_i = i_coords[k];
            i_coords[k] = i_coords[rand_index];
            i_coords[rand_index] = temp_i;
            int temp_j = j_coords[k];
            j_coords[k] = j_coords[rand_index];
            j_coords[rand_index] = temp_j;
        }
    }

public:
    MazeGen(int r, int c) : rows(r), cols(c) {
        horizon_walls = DMassiv<bool>((rows - 1) * cols, true);
        vertical_walls = DMassiv<bool>(rows * (cols - 1), true);
        srand(GetTickCount());
    }

    void generate() {
        DSU dsu(rows * cols);
        int vertical_wall_count = rows * (cols - 1);
        int horizontal_wall_count = (rows - 1) * cols;
        int total_walls = vertical_wall_count + horizontal_wall_count;
        char* wall_types = new char[total_walls];
        int* i_coords = new int[total_walls];
        int* j_coords = new int[total_walls];
        int index = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols - 1; j++) {
                wall_types[index] = 'V';
                i_coords[index] = i;
                j_coords[index] = j;
                index++;
            }
        }

        for (int i = 0; i < rows - 1; i++) {
            for (int j = 0; j < cols; j++) {
                wall_types[index] = 'H';
                i_coords[index] = i;
                j_coords[index] = j;
                index++;
            }
        }

        shuffleWalls(wall_types, i_coords, j_coords, total_walls);

        for (int k = 0; k < total_walls; k++) {
            char type = wall_types[k];
            int i = i_coords[k];
            int j = j_coords[k];

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

        delete[] wall_types;
        delete[] i_coords;
        delete[] j_coords;
    }

    void print() {
        for (int j = 0; j < cols; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int i = 0; i < rows; i++) {
            printf("|");
            for (int j = 0; j < cols - 1; j++) {
                printf("   ");
                if (vertical_walls.data()[i * (cols - 1) + j]) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
            printf("   |\n");

            if (i < rows - 1) {
                for (int j = 0; j < cols; j++) {
                    printf("+");
                    if (horizon_walls.data()[i * cols + j]) {
                        printf("---");
                    }
                    else {
                        printf("   ");
                    }
                }
                printf("+\n");
            }
        }

        for (int j = 0; j < cols; j++) {
            printf("+---");
        }
        printf("+\n");
    }
};

int main() {
    int rows, cols;
    printf("Enter maze dimensions (rows cols): ");
    scanf("%d %d", &rows, &cols);

    MazeGen maze(rows, cols);
    maze.generate();
    maze.print();

    system("pause");
    return 0;
}