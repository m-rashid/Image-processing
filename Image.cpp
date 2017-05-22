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

        if ((this -> height != rhs.height) && (this -> width != rhs.width)) {
            cerr << "Images are different sizes" << endl;
            return 1;
        }
        Image result = *this;
        Image::iterator img1_begin = this -> begin();
        Image:iterator img1_end = this -> end();
        Image::iterator img2_begin = rhs.begin();
        Image::iterator res_begin = result.begin();

        while (img1_begin != img1_end) {

            int sum = *img1_begin + *img2_begin;
            if (sum > 255) {
                sum = 255;
            }
            *res_begin = sum;
            ++img1_begin;
            ++img2_begin;
            ++res_begin;
        }

        return result;

    }

    

    Image::iterator Image::begin() const {
        return iterator (data.get());
    }

    Image::iterator Image::end() const {
        return iterator (data.get() + (width*height));
    }


}
