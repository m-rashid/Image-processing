#include "Image.h"

using namespace std;

namespace RSHMUS001 {

    Image::Image () {

        width = 0;
        height = 0;
        data = nullptr;

    }

    Image::~Image () {

        data = nullptr;
        width = 0;
        height = 0;

    }

    Image::Image (const Image & rhs) : width(rhs.width), height(rhs.height), data(new unsigned char(*rhs.data)) {}

    Image::Image (Image && rhs) : width(rhs.width), height(rhs.height), data(move(rhs.data)) {

        data = nullptr;

    }

    Image & Image::operator = (const Image & rhs) {

        if(this != rhs) {
            width = rhs.width;
            height = rhs.height;
            data.reset(new int (*rhs.data));
        }
        return *this;

    }

    Image & Image::operator = (Image && rhs) {

        if(this != rhs) {
            width = rhs.width;
            hieght = rhs.height;
            data = move(rhs.data);
        }

        return *this;
    }

    Image & operator + (const Image & rhs) {



    }

    Image::iterator Image::begin() const {
        return iterator (data.get());
    }

    Image::iterator Image::end() const {
        return iterator (data.get() + (width*height));
    }
}
