#include <iostream>
#include <map>

#include "TextEditor-impl.h"

int main() {
    std::string path = "../Tests/lord_of_rings.txt";
    TextEditor te;
    te.Upload(path);

    te.EditText("../Texts/to_edit.txt", "../Texts/correct.txt", 2);
}