#include "TextEditor.h"

bool CorrectSymbol(char c) {
    return ((c >= 'a' && c <= 'z') || c == '-' || c == ' ');
}

std::string* FilterWord(std::string* p_word) {  // filters to normal word
    std::string& word = *p_word;
    for (int i = static_cast<int>(word.length() - 1); i >= 0; --i) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] += 'a' - 'A';
        }
    }

    int i = static_cast<int>(word.length() - 1);
    while (i >= 0 && !CorrectSymbol(word[i])) {
        word.erase(i, 1);
        i--;
    }

    i = 0;
    while (word.length() > 0 && !CorrectSymbol(word[i])) {
        i++;
    }
    word.erase(0, i);

    for (size_t j = 0; j < word.length(); ++j) {
        if (!((word[j] >= 'a' && word[j] <= 'z') || word[j] == '-')) {
            word = "";
            break;
        }
    }
    return p_word;
}

int Levenshtein(const std::string& str1, const std::string& str2) {
    if (str1.size() > str2.size()) {
        return Levenshtein(str2, str1);
    }

    const int min_size = str1.size();
    const int max_size = str2.size();
    std::vector<int> lev_dist(min_size + 1);

    for (int i = 0; i <= min_size; ++i) {
        lev_dist[i] = i;
    }

    for (int j = 1; j <= max_size; ++j) {
        int previous_diagonal = lev_dist[0];
        int previous_diagonal_save;
        ++lev_dist[0];

        for (int i = 1; i <= min_size; ++i) {
            previous_diagonal_save = lev_dist[i];
            if (str1[i - 1] == str2[j - 1]) {
                lev_dist[i] = previous_diagonal;
            } else {
                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]),
                                       previous_diagonal) +
                              1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }

    return lev_dist[min_size];
}

Dictionary::Dictionary(int min_len, int max_len)
    : min_len_(min_len), max_len_(max_len) {}

Dictionary::Dictionary(int len) : min_len_(len), max_len_(len) {}

void Dictionary::SetLen(int len) { max_len_ = min_len_ = len; }

void Dictionary::SetLen(int min_len, int max_len) {
    min_len_ = min_len;
    max_len_ = max_len;
}

void Dictionary::Update(const std::string& path) {
    std::ifstream ifstream{path};
    std::string next_word;
    while (ifstream >> next_word) {
        FilterWord(&next_word);
        if (next_word.length() <= max_len_ && next_word.length() >= min_len_) {
            AddKey(next_word);
        }
    }

    ifstream.close();
    // std::cout << "Updating, len = " << min_len_ << " count = " << Length() <<
    // std::endl;
}

void Dictionary::AddKey(const std::string& key) {
    if (2 * count_ >= capacity_) {
        Resize();
    }

    size_t index = HashFunction(key);
    size_t i = 0;

    // Looking for empty cell or cell with the same key
    while (data_[index].value != -1) {
        if (data_[index].key == key) {
            break;
        }
        i++;
        index = (index + const_val1 * i + const_val2 * i * i) % capacity_;
    }

    if (data_[index].value == -1) {
        data_[index].key = key;
        data_[index].value = 1;
        count_++;
    } else {
        data_[index].value++;
    }
}

const std::string& Dictionary::BestWord(const std::string& word) {
    int min_dist = INT32_MAX;
    size_t min_dist_pos = 0;
    int min_dist_frequency = 0;
    for (size_t i = 0; i < capacity_; ++i) {
        if (data_[i].value > 0) {
            int dist = Levenshtein(word, data_[i].key);
            if (dist < min_dist ||
                (dist == min_dist && min_dist_frequency < data_[i].value)) {
                min_dist = Levenshtein(word, data_[i].key);
                min_dist_pos = i;
                min_dist_frequency = data_[i].value;
            }
        }
    }
    return data_[min_dist_pos].key;
}
