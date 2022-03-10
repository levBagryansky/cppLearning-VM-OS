#include <iostream>

using namespace std;

void sortAB(int* pa, int* pb)
{
    if (*pa < *pb)
    {
        int buf = *pa;
        *pa = *pb;
        *pb = buf;
    }
}

int main()
{
    int a, b;
    cin >> a >> b;

    if (a == b)
    {
        cout << a;
        return 0;
    }

    sortAB(&a, &b);

    int c = a % b;
    int buf;

    while (c != 0)
    {
        a = b;
        b = c;
        c = a % b;
    }

    cout << b;

    return 0;
}