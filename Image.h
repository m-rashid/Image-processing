//
// Created by Mustafa on 14/05/2017.
//

#ifndef _IMAGE_H
#define _IMAGE_H

namespace  RSHMUS001 {

    class Image {

    private:
        int width, height;
        std::unique_ptr<unsigned char[]> data;

    public:
        Image ();                   //default constructor;
        ~Image ();                  //destructor
        Image (const Image & rhs);  //copy constructor
        Image (Imsge && rhs);       //move constructor

        /* Overloading operators */
        Image & operator = (const Image & rhs); //copy assignment
        Image & operator = (Image && rhs);      //move assignment
        Image & operator + (const Image & rhs); //addition
        Image & operator - (const Image & rhs); //subtraction
        Image & operator ! (void);              //invert
        Image & operator / (const Image & rhs); //mask
        Image & operator * (int f);             //threshold with f
        friend std::ostream & operator << (std::ostream & os, const Image & img);   //input assignment
        friend std::istream & operator >> (std::istream & is, Image & img);         //output assignment

        
    };

}

#endif //_IMAGE_H
