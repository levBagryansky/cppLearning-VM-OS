#include <iostream>
#include <map>

#include "TextEditor-impl.h"

int main() {
    std::string path = "../Tests/lord_of_rings.txt";
    //std::string path = "../Tests/lord_of_rings.txt";

    TextEditor te;
    te.Upload(path);
    te.DumpStatistics();
    std::cout << "-------------------------------------------------------------" << std::endl;

    int num_of_dc = 10;

    Dictionary *dictionaries = new Dictionary[num_of_dc];
    for (int i = 0; i < num_of_dc - 1; ++i) {
        dictionaries[i].SetLen(i + 2);
    }
    dictionaries[num_of_dc - 1].SetLen(num_of_dc  + 1, 25);

    for (int i = 0; i < num_of_dc; ++i) {
        dictionaries[i].Update(path);
        std::cout << "Count of dictionaries[" << i << "] = " << dictionaries[i].Length() <<
            ", collisions = " << dictionaries[i].GetCollisions() << std::endl;
    }

}