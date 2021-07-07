#include <iostream>

using namespace std;
int main() {
    int a; int b;
    cin >> a >> b;
    a++;
    a /= 2;
    a *= 2;
    int i = a;
    while (i >= a && i <= b) {
        cout << i << ' ';
        i += 2;
    }
    return 0;
}
