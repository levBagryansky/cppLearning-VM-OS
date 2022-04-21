#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <thread>
#include <vector>
#include <sstream>
#include "Dictionary.h"

const int MAX_WORD_LEN = 20;

class TextEditor final {
   public:
    explicit TextEditor(uint num_of_tables = 10);
    ~TextEditor();

    void Upload(const std::string& path);
    void DumpStatistics() const;
    bool HaveWord(const std::string& word) const;
    void EditWord(std::string *p_str) const;
    void EditVectorRange(std::vector<std::string> *p_vector, size_t start, size_t range_len) const;
    void EditText(const std::string& wrong_text_path, const std::string& correct_text_path, int n_threads = 100) const;

   private:
    uint num_of_tables_;
    Dictionary* tables_;

    size_t GetSuitableDictionary(size_t word_len) const;
};

#endif //TEXTEDITOR_H