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

    Image & Image::operator + (const Image & rhs) {

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

    Image & Image::operator - (const Image & rhs){

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

            int sum = *img1_begin - *img2_begin;
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

    Image & Image::operator ! (){

        //Image result = *this;
        Image::iterator begin = this -> begin();
        Image::iterator end = this -> end();

        while (begin != end) {
            *begin = 255 - *begin;
            ++begin;

        }

        return *this;

    }

    Image & Image::operator / (const Image & rhs) {

        if ((this -> height != rhs.height) && (this -> width != rhs.width)) {
            cerr << "Images are different sizes" << endl;
            return 1;
        }

        Image result = *this;
        Image::iterator img1_begin = this -> begin();
        Image:iterator img1_end = this -> end();
        Image::iterator mask_begin = rhs.begin();
        Image::iterator res_begin = result.begin();

        while (img1_begin != img1_end) {

            if (*mask_begin != 255){
                *res_begin = 0;
            }
            ++img1_begin;
            ++mask_begin;
            ++res_begin;
        }

        return result;

    }

    Image & Image::operator * (int f) {

        Image result = *this;
        Image::iterator res_begin = result.begin();
        Image::iterator res_end = result.end();

        while (res_begin != res_end) {
            if (*res_begin > f) {
                *res_begin = 255;
            }
            else {
                *res_begin = 0;
            }

            ++res_begin;
        }

        return result;
    }

    istream & Image::operator >> (istream & is, Image & img) {
        /*Header Format:
         * P5
         * #Comment line (can be more than one)
         * NRows Ncols
         * 255
         * binary_data_block */

        string line;
        int Nrows, Ncols;
        getline (is, line);
        while (line != '255') {
            if (line!='P5' || line.at(0)!='#') {
                istreamstream iss(line);
                ss >> Nrows;
                ss >> Ncols;
            }

            getline (is, line);
        }
        img.width = Ncols;
        img.height = Nrows;
        int size = Ncols * Nrows;
        img.data = std::unique_ptr<unsigned char[]>(new unsigned char[size]);
        is >> ws;
        is.read((char*)(&(img.data[0])), size);
        return is;
    }

    ostream & operator << (ostream & os, const Image & img) {

        os << "P5" << endl << "#This is the resultant image" << endl
        os << img.height << " " << img.width << endl;
        os << "255" << endl;

        os.write((char*)&img.data[0], img.height*img.width);
        return os;

    }

    Image::iterator Image::begin() const {
        return iterator (data.get());
    }

    Image::iterator Image::end() const {
        return iterator (data.get() + (width*height));
    }


}
