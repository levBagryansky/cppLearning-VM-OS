#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {
    vector<string> arr = {"", "", ""};
    cin >> arr[0] >> arr[1] >> arr[2];

    string min = arr[0];
    for (auto item: arr)
    {
        if (min > item)
            min = item;
    }

    cout << min;
}
