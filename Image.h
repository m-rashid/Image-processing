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

        class iterator {

        private:
            unsigned char *ptr;
            friend class Image;
            iterator (unsigned char *p) : ptr(p) {};    //construct only via Image class (begin/end)

        public:
            iterator (const iterator & rhs) : ptr(rhs.ptr) {};  //copy constructor

            /* appropriate iterator operator overloading */
            iterator & operator = (const iterator & rhs) {  //copy assignment
                if (this != &rhs){
                    ptr = rhs.ptr;
                }
                return *this;
            }

            iterator & operator ++ (void) {                 //increment
                ptr += 1;
                return *this;
            }

            iterator & operator -- (void) {                 //decrement
                ptr -= 1;
                return *this;
            }

            iterator & operator * (void) {                  //dereference
                return *ptr;
            }

            bool operator == (const iterator & rhs) {       //equality
                return ptr == rhs.ptr;
            }

            bool operator != (const iterator & rhs) {       //inequality
                return ptr != rhs.ptr;
            }

        };

        iterator begin (void) const;
        iterator end (void) const;

    };

}

#endif //_IMAGE_H
