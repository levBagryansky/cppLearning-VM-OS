#include <iostream>
#include <vector>

using namespace std;
int main() {
    int n;
    cin >> n;
    if (n == 0)
    {
        cout << 0;
        return 0;
    }

    vector<int> arr;
    while(n > 0)
    {
        arr.push_back(n % 2);
        n /= 2;
    }

    int len = arr.size();

    for (int i = len - 1; i >= 0 ; i--)
    {
        cout << arr[i];
    }
    return 0;
}
