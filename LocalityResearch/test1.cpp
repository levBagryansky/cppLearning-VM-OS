#include <iostream>

const int NUM_OF_LINE = 100;
const int SIZE_OF_LINE = 1e5;

int main(){
    srand(time(0));
    int** matrix = (int**) calloc(NUM_OF_LINE, sizeof (int*));
    for (int i = 0; i < NUM_OF_LINE; ++i) {
        matrix[i] = (int*) calloc(SIZE_OF_LINE, sizeof (int*));
        for (int j = 0; j < SIZE_OF_LINE; ++j) {
            matrix[i][j] = rand() % 1000;
        }
    }

    long long sum = 0;

    for (int k = 0; k < 500; ++k) {
        for (int i = 0; i < NUM_OF_LINE; ++i) {
            for (int j = 0; j < SIZE_OF_LINE; ++j) {
                sum += matrix[i][j];
            }
        }
        sum = 0;
    }

    for (int i = 0; i < NUM_OF_LINE; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    std::cout << "sum1 = " << sum << std::endl;
}