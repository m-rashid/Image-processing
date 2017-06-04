#include "Image.h"
#include <fstream>
#include <sstream>
using namespace std;

namespace RSHMUS001 {

    //Default constructor
    Image::Image () {

        width = 0;
        height = 0;
        data = nullptr;

    }

    //Constructor used for testing purposes
    Image::Image(int w, int h, unsigned char * data_test) : width(w), height(h) {
      data.reset(data_test);
    }

    //Destructor
    Image::~Image () {

        data = nullptr;
        width = 0;
        height = 0;

    }

    //Copy constructor
    Image::Image (const Image & rhs) : width(rhs.width), height(rhs.height){

        //Deep copy the data
        unsigned char* temp = new unsigned char[width*height];
        for (int i=0; i<width*height; i++) {
          temp[i] = rhs.data[i];
        }
        data.reset(temp);

    }

    //Move constructor
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

    //Copy assignment operator
    Image & Image::operator = (const Image & rhs) {

        if(this != &rhs) {
            width = rhs.width;
            height = rhs.height;
            unsigned char* temp = new unsigned char[width*height];
            for (int i=0; i<width*height; i++) {
              temp[i] = rhs.data[i];
            }
            data.reset(temp);
        }
        return *this;

    }

    //Move assignment operator
    Image & Image::operator = (Image && rhs) {

        if(this != &rhs) {
            width = rhs.width;
            height = rhs.height;
            data = move(rhs.data);
        }

        return *this;
    }

    //+ operator overload for adding two images
    Image Image::operator + (const Image & rhs) {

        //Check if the two images are of the same size
        if ((this->height != rhs.height) || (this->width != rhs.width)) {
            cerr << "Images are different sizes" << endl;
            exit(1);
        }
        Image result(*this);  //use this image to write the output
        Image::iterator img1_begin = result.begin();
        Image:iterator img1_end = result.end();
        Image::iterator img2_begin = rhs.begin();

        while (img1_begin != img1_end) {

            int sum = *img1_begin + *img2_begin; //add the two pixel values

            //clamp to 255
            if (sum > 255) {
                sum = 255;
            }
            *img1_begin = sum;
            ++img1_begin;
            ++img2_begin;
        }

        return result;

    }

    //- operator overload for subtracting two images
    Image Image::operator - (const Image & rhs) {

        //Check if the two images are of the same size
        if ((height != rhs.height) || (width != rhs.width)) {
            cerr << "Images are different sizes" << endl;
            exit(1);
        }
        Image result(*this);
        Image::iterator img1_begin = result.begin();
        Image:iterator img1_end = result.end();
        Image::iterator img2_begin = rhs.begin();

        while (img1_begin != img1_end) {

            int diff = *img1_begin - *img2_begin; //subtract the two pixel values

            //clamp to 255
            if (diff > 255) {
                diff = 255;
            }
            *img1_begin = diff;
            ++img1_begin;
            ++img2_begin;
        }

        return result;

    }

    //! operator overload for inverting an image
    Image Image::operator ! () {

        Image::iterator begin = this -> begin();
        Image::iterator end = this -> end();

        while (begin != end) {
            *begin = 255 - *begin; //Invert
            ++begin;

        }

        return *this;

    }

    /// operator overload for masking this image with rhs
    Image Image::operator / (const Image & rhs) {

        //Check if the two images are of the same size
        if ((height != rhs.height) || (width != rhs.width)) {
            cerr << "Images are different sizes" << endl;
            exit(1);
        }

        Image result(*this);
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

    //* operator overload for thresholding this image with f
    Image Image::operator * (int f) {

        Image result(*this);
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

    istream & operator >> (istream & is, Image & img) {
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

                //Extract height and width
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

        //read the whole chunk of image data
        is.read((char*)(&(img.data[0])), size);
        return is;
    }

    ostream & operator << (ostream & os, const Image & img) {

        os << "P5" << endl << "#This is the resultant image" << endl;
        os << img.height << " " << img.width << endl;
        os << "255" << endl;

        //write the whole chunk of image data
        os.write((char*)&img.data[0], img.height*img.width);
        return os;

    }

    //load image data from file
    void Image::load (string filename) {

        ifstream fin (filename.c_str(), ios::in|ios::binary);
        if (!fin){
            cerr << "File open failed!" << endl;
            exit(1);
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
        width = Ncols;
        height = Nrows;
        int size = Ncols * Nrows;
        data.reset(new unsigned char[size]);
        skipws(fin);
        fin.read((char*)(&(data[0])), size);
        //cout << "width: "<<width<<endl;
        //cout << "height: " << height<<endl;
        cout << "load successful!" << endl;
        fin.close();

    }


    //save image data to file
    void Image::save(string filename) {

        ofstream fout(filename.c_str(), ios::out|ios::binary);
        if (!fout){
            cerr << "File open failed!" << endl;
            exit(1);

        }

        fout << "P5" << endl << "#This is the resultant image" << endl;
        fout << to_string(Image::height) << " " << to_string(Image::width) << endl;
        fout << "255" << endl;

        fout.write((char*)&data[0], height*width);
        cout << "Save successful!" << endl;
        fout.close();

    }

    int Image::getHeight () {
      return height;
    }

    int Image::getWidth () {
      return width;
    }


    Image::iterator Image::begin() const {
        return iterator (data.get());
    }

    Image::iterator Image::end() const {
        return iterator (data.get() + (width*height));
    }

    //== operator overload for testing purposes
    bool Image::operator == (const Image & rhs) {
      if ((width != rhs.width) || (height != rhs.height) ) {
        return false;
      }

      Image m1 (*this);
      Image::iterator m1_begin= m1.begin();
      Image::iterator m1_end = m1.end();
      Image::iterator rhs_begin = rhs.begin();

      while (m1_begin != m1_end) {
        if (*m1_begin != *rhs_begin) {
          return false;
        }
        ++m1_begin;
        ++rhs_begin;
      }

      return true;
    }

}
