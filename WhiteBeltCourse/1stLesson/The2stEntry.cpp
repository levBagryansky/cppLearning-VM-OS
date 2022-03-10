#include <iostream>

using namespace std;

int main(){
    int c = 'f';
    int numEntry = 2;

    string str;
    cin >> str;
    int i = 0; // счетчик символов
    int k = 0; // счиетчик вхождений
    while (i < str.size() && k < numEntry)
    {
        if (str[i] == c)
            k++;
        i++;
    }

    if (k == 2)
    {
        cout << --i;
    }
    else if (k == 1)
    {
        cout << -1;
    }
    else if (k == 0)
    {
        cout << -2;
    }

    return 0;  
};
