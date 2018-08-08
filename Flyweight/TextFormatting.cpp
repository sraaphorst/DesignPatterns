#include <iostream>
#include <string>
#include <vector>

class FormattedText {
private:
    std::string plain_text;

    /// Extremely efficient way of determining which characters are caps: bool array for each char.
    /// We should just be able to operate on the idea of ranges.
    bool *caps;

public:
    FormattedText(const std::string &plain_text) : plain_text(plain_text) {
        caps = new bool[plain_text.length()];
        memset(caps, 0, plain_text.length());
    }

    ~FormattedText() {
        delete[] caps;
    }

    void capitalize(int start, int end) {
        for (int i=start; i <= end; ++i)
            caps[i] = true;
    }

    friend std::ostream &operator<<(std::ostream &os, const FormattedText &text) {
        std::string s;
        for (int i=0; i < text.plain_text.length(); ++i) {
            auto c = text.plain_text[i];
            s += text.caps[i] ? toupper(c) : c;
        }
        return os << s;
    }
};

class BetterFormattedText {
public:
    /// In this example, it is the TextRange that is the flyweight.
    /// Instead of having huge boolean array, we have a small list of ranges.
    /// We could add bold, italics, etc.
    struct TextRange {
        int start, end;
        bool capitalize;

        bool covers(int pos) const {
            return pos >= start && pos <= end;
        }
    };

    TextRange &get_range(int start, int end) {
        formatting.emplace_back(TextRange{start, end});
        return formatting.back();
    }

    BetterFormattedText(const std::string &plain_text) : plain_text(plain_text) {}


    friend std::ostream &operator<<(std::ostream &os, const BetterFormattedText &text) {
        std::string s;

        for (int i=0; i < text.plain_text.length(); ++i) {
            auto c = text.plain_text[i];
            for (const auto &rng: text.formatting) {
                if (rng.covers(i))
                    c = toupper(c);
            }
            s += c;
        }
        return os << s;
    }

private:
    std::string plain_text;
    std::vector<TextRange> formatting;

};

int main() {
    FormattedText ft {"This is a brave new world."};
    ft.capitalize(10, 15);
    std::cout << ft << std::endl;

    BetterFormattedText bft {"This is a really brave new world."};
    bft.get_range(10, 21).capitalize = true;
    std::cout << bft << std::endl;
}