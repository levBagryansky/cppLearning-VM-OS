#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <thread>
#include <vector>
#include "Dictionary-impl.h"

const int MAX_WORD_LEN = 20;

class TextEditor{
   public:
    TextEditor(uint num_of_tables = 10);
    ~TextEditor();

    void Upload(const std::string& path);
    void DumpStatistics();
    bool HaveWord(const std::string& word);
    void EditWord(std::string& word);

   private:
    uint num_of_tables_;
    Dictionary* tables_;
};

TextEditor::TextEditor(uint num_of_tables): num_of_tables_(10) {
    tables_ = new Dictionary[num_of_tables_];
    for (int i = 0; i < num_of_tables_ - 1; ++i) {
        tables_[i].SetLen(i + 2);
    }
    tables_[num_of_tables_ - 1].SetLen(num_of_tables_ + 1, MAX_WORD_LEN);
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

bool TextEditor::HaveWord(const std::string &word) {
    if (word.length() < 2 || word.length() > MAX_WORD_LEN){
        return false;
    }
    if (word.length() < num_of_tables_ + 2){
        return tables_[word.length() - 2].HaveKey(word);
    }
    return tables_[num_of_tables_ - 1].HaveKey(word);
}

void TextEditor::EditWord(std::string &word) {
    char first_sym = word[0];
    char last_sym = word[word.length() - 1];
    FilterWord(word);

    if (!HaveWord(word)){
        //code..
    }

    if(first_sym > 'A' && first_sym < 'Z'){
        word[0] += 'a' - 'A';
    }
    if(last_sym == '.' || last_sym ==)
}

#endif //TEXTEDITOR_H
