#include "TextEditor.h"

TextEditor::TextEditor(uint num_of_tables) : num_of_tables_(num_of_tables) {
    tables_ = new Dictionary[num_of_tables_];
    for (uint i = 0; i < num_of_tables_ - 1; ++i) {
        tables_[i].SetLen(static_cast<size_t>(i + 2));
    }
    tables_[num_of_tables_ - 1].SetLen(static_cast<size_t>(num_of_tables_ + 1),
                                       MAX_WORD_LEN);
}

TextEditor::~TextEditor() { delete[] tables_; }

void TextEditor::Upload(const std::string& path) {
    std::vector<std::thread> threads(num_of_tables_);
    for (uint i = 0; i < num_of_tables_; ++i) {
        threads[i] = std::thread(&Dictionary::Update, &tables_[i], path);
    }

    for (auto& th : threads) {
        th.join();
    }
}

void TextEditor::DumpStatistics() {
    for (uint i = 0; i < num_of_tables_; ++i) {
        std::cout << "Count of tables[" << i << "] = " << tables_[i].Length()
                  << ", collisions = " << tables_[i].GetCollisions()
                  << std::endl;
    }
}

bool TextEditor::HaveWord(const std::string& word) {
    if (word.length() < 2 || word.length() > MAX_WORD_LEN) {
        return false;
    }
    if (word.length() < num_of_tables_ + 2) {
        return tables_[word.length() - 2].HaveKey(word);
    }
    return tables_[num_of_tables_ - 1].HaveKey(word);
}

void TextEditor::EditWord(
    std::string& str) {  // example: "{(_:cit{__}" --> "{(_:cat{__}"
    size_t first_letter_pos = 0;
    size_t last_letter_pos = str.length() - 1;
    while (first_letter_pos < str.length() &&
           !CorrectSymbol(str[first_letter_pos])) {
        first_letter_pos++;
    }
    while (!CorrectSymbol(str[last_letter_pos]) &&
           last_letter_pos >= first_letter_pos) {
        last_letter_pos--;
    }

    std::string word =
        str.substr(first_letter_pos, last_letter_pos - first_letter_pos + 1);
    bool capital = (word[0] >= 'A' && word[0] <= 'Z');
    FilterWord(word);

    if (!HaveWord(word)) {
        if (word.length() < num_of_tables_ + 2 && word.length() >= 2) {
            word = tables_[word.length() - 2].BestWord(word);
        } else if (word.length() >= num_of_tables_ + 2) {
            word = tables_[num_of_tables_ - 1].BestWord(word);
        }
    }
    if (capital) {
        word[0] += 'A' - 'a';
    }

    str.replace(first_letter_pos, last_letter_pos - first_letter_pos + 1, word);
}

void TextEditor::EditVectorRange(std::vector<std::string>& vector, size_t start,
                                 size_t range_len) {
    for (size_t i = start; i < start + range_len; ++i) {
        EditWord(vector[i]);
    }
}

void TextEditor::EditText(std::string wrong_text, std::string correct_text,
                          int n_threads) {
    std::vector<std::string> buf;
    std::ifstream ifstream(wrong_text);
    std::ofstream ofstream(correct_text);
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
            std::thread(&TextEditor::EditVectorRange, this, std::ref(buf),
                        buf.size() / n_threads * i, buf.size() / n_threads);
    }
    threads[i] = std::thread(&TextEditor::EditVectorRange, this, std::ref(buf),
                             buf.size() / n_threads * i,
                             buf.size() - (buf.size() / n_threads * i));

    for (auto& th : threads) {
        th.join();
    }

    for (size_t i = 0; i < buf.size(); ++i) {
        if (!buf[i].empty()) {
            if (buf[i].back() != '\n') {
                ofstream << buf[i] << ' ';
            } else {
                ofstream << buf[i];
            }
        }
    }
    ofstream.close();
}
