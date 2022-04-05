#include "TextEditor.h"

TextEditor::TextEditor(uint num_of_tables) : num_of_tables_(num_of_tables) {
    tables_ = new Dictionary[num_of_tables_];
    for (uint i = 0; i < num_of_tables_ - 1; ++i) {
        tables_[i].SetLen(i + 2);
    }
    tables_[num_of_tables_ - 1].SetLen(num_of_tables_ + 1, MAX_WORD_LEN);
}

TextEditor::~TextEditor() { delete[] tables_; }

void TextEditor::Upload(const std::string& path) {
    std::ifstream ifstream{path};
    std::string next_word;
    while (ifstream >> next_word) {
        FilterWord(&next_word);
        size_t index_gictionary = GetSuitableDictionary(next_word.length());
        if (index_gictionary <= num_of_tables_) {
            tables_[index_gictionary].AddKey(next_word);
        }
    }

    ifstream.close();
}

void TextEditor::DumpStatistics() const {
    for (uint i = 0; i < num_of_tables_; ++i) {
        std::cout << "Count of tables[" << i << "] = " << tables_[i].Length()
                  << ", collisions = " << tables_[i].GetCollisions()
                  << std::endl;
    }
}

bool TextEditor::HaveWord(const std::string& word) const {
    size_t index_dictionary = GetSuitableDictionary(word.length());
    if (GetSuitableDictionary(word.length()) >= num_of_tables_) {
        return false;
    }
    return tables_[index_dictionary].HaveKey(word);
}

void TextEditor::EditWord(
    std::string* p_str) const {  // example: "{(_:cit{__}" --> "{(_:cat{__}"
    size_t first_letter_pos = 0;
    size_t last_letter_pos = (*p_str).length() - 1;
    while (first_letter_pos < (*p_str).length() &&
           !CorrectSymbol((*p_str)[first_letter_pos])) {
        first_letter_pos++;
    }
    while (!CorrectSymbol((*p_str)[last_letter_pos]) &&
           last_letter_pos >= first_letter_pos) {
        last_letter_pos--;
    }

    std::string word = (*p_str).substr(first_letter_pos,
                                       last_letter_pos - first_letter_pos + 1);
    bool capital = (word[0] >= 'A' && word[0] <= 'Z');
    FilterWord(&word);

    if (!HaveWord(word) &&
        GetSuitableDictionary(word.length()) <= num_of_tables_) {
        word = tables_[GetSuitableDictionary(word.length())].BestWord(word);
    }
    if (capital) {
        word[0] += 'A' - 'a';
    }

    (*p_str).replace(first_letter_pos, last_letter_pos - first_letter_pos + 1,
                     word);
}

void TextEditor::EditVectorRange(std::vector<std::string>* p_vector,
                                 size_t start, size_t range_len) const {
    for (size_t i = start; i < start + range_len; ++i) {
        EditWord(&((*p_vector)[i]));
    }
}

void TextEditor::EditText(const std::string& wrong_text_path,
                          const std::string& correct_text_path,
                          int n_threads) const {
    std::vector<std::string> buf;
    std::ifstream ifstream(wrong_text_path);
    std::ofstream ofstream(correct_text_path);
    if (!ifstream.is_open() || !ofstream.is_open()) {
        std::cout << "File is not opened" << std::endl;
    }

    std::string line;
    std::string str;
    while (!ifstream.eof()) {
        std::getline(ifstream, line);
        std::stringstream line_stream;
        line_stream << line;
        while (line_stream >> str) {
            buf.push_back(str);
        }
        buf.back().push_back('\n');
    }
    ifstream.close();

    std::vector<std::thread> threads(n_threads);
    int i;
    for (i = 0; i < n_threads - 1; ++i) {
        threads[i] =
            std::thread(&TextEditor::EditVectorRange, this, &buf,
                        buf.size() / n_threads * i, buf.size() / n_threads);
    }
    threads[i] = std::thread(&TextEditor::EditVectorRange, this, &buf,
                             buf.size() / n_threads * i,
                             buf.size() - (buf.size() / n_threads * i));

    for (auto& th : threads) {
        th.join();
    }

    for (const auto& word : buf) {
        if (!word.empty()) {
            if (word.back() != '\n') {
                ofstream << word << ' ';
            } else {
                ofstream << word;
            }
        }
    }
    ofstream.close();
}

size_t TextEditor::GetSuitableDictionary(size_t word_len) const {
    if (word_len < 2 || word_len > MAX_WORD_LEN) {
        return SIZE_MAX;
    }
    if (word_len < num_of_tables_ + 2) {
        return word_len - 2;
    }
    return num_of_tables_ - 1;
}