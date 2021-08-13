#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output ("output.txt");
    if (input) {
        string line;
        while (getline(input, line)) {
            //cout << line << endl;
            output << line << endl;
        }
    }
    else{
        cout << "File was not found" << endl;
    }
    return 0;
}
