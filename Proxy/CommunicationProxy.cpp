#include <iostream>
#include <string>


struct Pingable {
    virtual std::wstring ping(const std::wstring &message) = 0;
};

struct Pong : Pingable {
    std::wstring ping(const std::wstring &message) override {
        return message + L" pong";
    }
};

void tryit(Pingable &p) {
    std::wcout << p.ping(L"ping") << std::endl;
}

int main() {
    Pong pong;
    for (size_t i = 0; i < 3; ++i)
        tryit(pong);
}