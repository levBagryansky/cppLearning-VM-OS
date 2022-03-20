#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <thread>
#include <vector>
#include <sstream>
#include "Dictionary.h"

const int MAX_WORD_LEN = 20;

class TextEditor{
   public:
    explicit TextEditor(uint num_of_tables = 10);
    ~TextEditor();

    void Upload(const std::string& path);
    void DumpStatistics();
    bool HaveWord(const std::string& word);
    void EditWord(std::string *p_str);
    void EditVectorRange(std::vector<std::string> *p_vector, size_t start, size_t range_len);
    void EditText(const std::string& wrong_text, const std::string& correct_text, int n_threads = 100);

   private:
    uint num_of_tables_;
    Dictionary* tables_;
};

#endif //TEXTEDITOR_H