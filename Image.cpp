#include "Image.h"
#include <fstream>
#include <sstream>
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

    Image::Image (const Image & rhs) : width(rhs.width), height(rhs.height){

        unsigned char* temp = new unsigned char[width*height];
        for (int i=0; i<width*height; i++) {
          temp[i] = rhs.data[i];
        }
        data.reset(temp);

    }

    Image::Image (Image && rhs) : width(rhs.width), height(rhs.height) {

      unsigned char* temp = new unsigned char[width*height];
      for (int i=0; i<width*height; i++) {
        temp[i] = rhs.data[i];
      }
      data.reset(temp);

      //maintain state of newly created object
      rhs.data = nullptr;
      rhs.width = 0;
      rhs.height = 0;
    }

    Image & Image::operator = (const Image & rhs) {

        if(!(this == rhs)) {
            width = rhs.width;
            height = rhs.height;
            data.reset(new int (*rhs.data));
        }
        return *this;

    }

    Image & Image::operator = (Image && rhs) {

        if(this != rhs) {
            width = rhs.width;
            height = rhs.height;
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

    Image & Image::operator - (const Image & rhs) {

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

    Image & Image::operator ! () {

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

    istream & Image::operator >> (std::istream & is, Image & img) {
        /*Header Format:
         * P5
         * #Comment line (can be more than one)
         * NRows Ncols
         * 255
         * binary_data_block */

        string line;
        int Nrows, Ncols;
        getline (is, line);
        while (line != "255") {
            if (line!="P5" || line.at(0)!='#') {
                istringstream iss(line);
                iss >> Nrows;
                iss >> Ncols;
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

    void Image::load (string filename) {

        ifstream fin (filename.c_str(), ios::binary);
        if (!fin){
            cerr << "File open failed!" << endl;
        }

        string line;
        int Nrows, Ncols;
        getline (fin, line);
        while (line != "255") {
            if (line!="P5" || line.at(0)!='#') {
                istringstream iss(line);
                iss >> Nrows;
                iss >> Ncols;
            }

            getline (fin, line);
        }
        Image::width = Ncols;
        Image::height = Nrows;
        int size = Ncols * Nrows;
        Image::data = std::unique_ptr<unsigned char[]>(new unsigned char[size]);
        fin >> ws;
        fin.read((char*)(&(Image::data[0])), size);
        fin.close();

    }


    void Image::save(string filename) {

        ofstream fout(filename.c_str(), ios::binary);
        if (!fout){
            cerr << "File open failed!" << endl;
        }

        fout << "P5" << endl << "#This is the resultant image" << endl;
        fout << Image::height << " " << Image::width << endl;
        fout << "255" << endl;

        fout.write((char*)&Image::data[0], Image::height*Image::width);
        fout.close();

    }


    Image::iterator Image::begin() const {
        return iterator (data.get());
    }

    Image::iterator Image::end() const {
        return iterator (data.get() + (width*height));
    }


}
