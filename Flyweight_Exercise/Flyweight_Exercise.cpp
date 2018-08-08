#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

struct Sentence {
private:
    struct WordToken {
        WordToken(const std::string &s) : word{s}, capitalize(false) {}
        const std::string word;
        bool capitalize;

        const std::string str() const {
            if (capitalize) {
                std::string s;
                std::transform(word.cbegin(), word.cend(), std::back_inserter(s), [](const char c) { return toupper(c); });
                return s;
            }
            return word;
        }
    };

    std::vector<WordToken> words;

public:
    Sentence(const std::string &text) {
        std::istringstream iss{text};
        std::transform(std::istream_iterator<std::string>{iss},
                       std::istream_iterator<std::string>{},
                       std::back_inserter(words),
                       [](const std::string &s) {
                            return WordToken{s};
        });
    }

    WordToken &operator[](size_t index) {
        return words[index];
    }

    std::string str() const {
        std::string s;
        bool firstWord = true;
        for (const auto &wt: words) {
            if (!firstWord) s += ' ';
            firstWord = false;
            s += wt.str();
        }
        return s;
    }
};

int main() {
    Sentence sentence{"hello world"};
    sentence[1].capitalize = true;
    std::cout << sentence.str() << std::endl;
}