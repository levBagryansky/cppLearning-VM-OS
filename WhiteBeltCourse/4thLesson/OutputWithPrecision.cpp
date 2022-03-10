#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    cout << fixed << setprecision(3);
    // числа нужно выводить с точностью до 3х знаков после запяттй
    ifstream input ("input.txt");
    string line;
    double number;
    while (getline(input, line)){
        number = atof(line.c_str());
        cout << number << endl;
    }
    return 0;
}
