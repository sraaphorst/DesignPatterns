/**
 * Gives the appearance of working with an object you are used to working with, even though the object might not have
 * been created.
 */

#include <iostream>
#include <memory>
#include <string>


struct Image {
    virtual void draw() = 0;
};

/// Problem here: we don't actually need to load the bitmap until we are drawing it.
/// Suppose, however, that we are applying the open-closed principle and cannot modify the Bitmap class.
struct Bitmap : Image {
    Bitmap(const std::string filename) {
        std::cout << "Loading bitmap from " << filename << std::endl;
    }

    void draw() override {
        std::cout << "Drawing bitmap" << std::endl;
    }
};

/// So we create a lazy virtual bitmap with the exact same interface as Bitmap.
/// It uses a pointer to a Bitmap under the hood, but doesn't load the Bitmap until necessary.
struct LazyBitmap : Image {
private:
    std::string filename;
    std::unique_ptr<Bitmap> bmp{nullptr};
public:
    LazyBitmap(const std::string &filename) : filename(filename) {}

    void draw() override {
        if (!bmp)
            bmp = std::make_unique<Bitmap>(filename);
        bmp->draw();
    }
};


int main() {
    Bitmap bm{"bitmap.bmp"};
    LazyBitmap lbm{"lazybitmap.bmp"};

    std::cout << "Drawing bitmap.bmp:" << std::endl;
    bm.draw();
    std::cout << std::endl;

    std::cout << "Drawing lazybitmap.bmp:" << std::endl;
    lbm.draw();
}