#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <thread>
#include <vector>
#include "Dictionary-impl.h"

class TextEditor{
   public:
    TextEditor(uint num_of_tables = 10);
    ~TextEditor();

    void Upload(const std::string& path);
    void DumpStatistics();

   private:
    uint num_of_tables_;
    Dictionary* tables_;
};

TextEditor::TextEditor(uint num_of_tables): num_of_tables_(10) {
    tables_ = new Dictionary[num_of_tables_];
    for (int i = 0; i < num_of_tables_ - 1; ++i) {
        tables_[i].SetLen(i + 2);
    }
    tables_[num_of_tables_ - 1].SetLen(num_of_tables_ + 1, 25);
}

TextEditor::~TextEditor() {
    delete[] tables_;
}

void TextEditor::Upload(const std::string& path) {
    std::vector<std::thread> threads(num_of_tables_);
    for (int i = 0; i < num_of_tables_; ++i) {
        threads[i] = std::thread(&Dictionary::Update, &tables_[i], path);
        //tables_[i].Update(path);
    }

    for(auto& th: threads){
        th.join();
    }

}

void TextEditor::DumpStatistics() {
    for (int i = 0; i < num_of_tables_; ++i) {
        std::cout << "Count of tables[" << i << "] = " << tables_[i].Length() <<
            ", collisions = " << tables_[i].GetCollisions() << std::endl;
    }
}

#endif //TEXTEDITOR_H
