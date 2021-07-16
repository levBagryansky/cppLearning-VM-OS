/*
Слова называются анаграммами друг друга, если одно из них можно получить
 перестановкой букв в другом. Например, слово «eat» можно получить
 перестановкой букв слова «tea», поэтому эти слова являются анаграммами
 друг друга. Даны пары слов, проверьте для каждой из них, являются ли
 слова этой пары анаграммами друг друга.
 */

#include <iostream>
#include <map>

using namespace std;

map<char, int> BuildCharCounters(const string& word);

int main()
{
    int N; cin >> N;
    string word1;
    string word2;

    for (int i = 0; i < N; ++i) {
        cin >> word1;
        cin >> word2;

        if (BuildCharCounters(word1) == BuildCharCounters(word2))
            cout << "YES";
        else
            cout << "NO";

        cout << endl;
    }
    return 0;
}

map<char, int> BuildCharCounters(const string& word)
{
    map<char, int> result;
    for (char c: word)
        result[c]++;
    return result;
}
