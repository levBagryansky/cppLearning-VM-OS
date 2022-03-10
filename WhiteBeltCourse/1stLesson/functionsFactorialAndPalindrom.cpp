#include <iostream>
#include <vector>

using namespace std;

int Factorial(int x); //calculate factorial
bool IsPalindrom(string str); //check if a word is palindrom
vector<string> PalindromFilter(vector<string> words, int minLength); //filter string
//by palindrom and lengft


int main() {
    return 0;
}

int Factorial(int x)
{
    int result = 1;

    for (int i = 1; i <= x; ++i) {
        result *= i;
    }

    return result;
}

bool IsPalindrom(string str)
{
    int i = 0;
    while (i < str.size())
    {
        if (str[i] != str[str.size() - i - 1])
            return false;
        i++;
    }

    return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength)
{
    vector<string> result;
    for (int i = 0; i < words.size(); ++i) {
        if (words[i].size() >= minLength && IsPalindrom(words[i]))
            result.push_back(words[i]);
    }

    return result;
}