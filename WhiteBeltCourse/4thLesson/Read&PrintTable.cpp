/*
  В первой строке файла input.txt записаны два числа N и M. Далее в файле
  находится таблица из N строк и M столбцов, представленная в формате CSV
  (comma-separated values). Такой формат часто используется для текстового
  представления таблиц с данными: в файле несколько строк, значения из
  разных ячеек внутри строки отделены друг от друга запятыми.  Ваша задача
  — вывести данные на экран в виде таблицы. Формат таблицы:

1)  размер ячейки равен 10,

2)  соседние ячейки отделены друг от друга пробелом,

3)  последняя ячейка в строке НЕ оканчивается пробелом,

4)  последняя строка НЕ оканчивается символом перевода строки.
 Гарантируется, что в таблице будет ровно N строк и M столбцов,
 значение каждой из ячеек — целое число.
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

vector<vector<int>> readMatrix(ifstream& stream);
void printMatrix (const vector<vector<int>>& matrix);

int main() {
    ifstream input("input.txt");

    vector<vector<int>> m = readMatrix(input);

    printMatrix(m);
    return 0;
}

vector<vector<int>> readMatrix(ifstream& stream){
    int x_size;
    int y_size;
    stream >> y_size;
    stream >> x_size;

    vector<vector<int>> result(y_size, vector<int>(x_size));
    for (int y = 0; y < y_size; ++y) {
        for (int x = 0; x < x_size; ++x) {
            stream.ignore(1);
            stream >> result[y][x];
        }
    }

    return result;
}

void printMatrix (const vector<vector<int>>& matrix){
    for (int y = 0; y < matrix.size() - 1; ++y) {
        for (int x = 0; x < matrix[0].size() - 1; ++x) {
            cout << setw(10) << matrix[y][x] << ' ';
        }
        cout << setw(10) << matrix[y][matrix[0].size() - 1];
        cout << endl;
    }

    for (int x = 0; x < matrix[0].size(); ++x) {
        cout << setw(10) << matrix[matrix.size() - 1][x] << ' ';
    }
}
