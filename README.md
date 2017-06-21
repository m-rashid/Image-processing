*******************************************************************************  
                          PGM IMAGE MANIPULATOR  
*******************************************************************************  
  
GETTING STARTED  

After unpacking the tarball, you will find the following files:  
Image.h        -  Header file containing the structure for Image class  
Image.cpp      -  Definitions for the functions declared in the header file  
                  Represents and Image, and contains various operator overloads  
                  for Image operations (see below)  
/Test/Test.cpp -  Utility for performing unit tests on various code sections.  
driver.cpp     -  Driver file containing the main() method to run the program  
Makefile       -  Utility for compiling, linking and creating the executable  
  
COMPILING  
  
Navigate to the project source folder. Run 'make' in the terminal.  
An executable named 'imageops' is created  
  
  
RUNNING  
  
cd into the project folder. Execute the following command to run the program:  
  ./imageops <option> <output file name (prefix only)>  
  
./imageops         : Name of the executable  
<output file name> : Prefix of the output image file  
<option>           : Could be one of the following operations performed on  
                     images I1 and I2  
  
                    -a I1 I2  
                    add the pixel values of I1 to I2  
  
                    -s I1 I2  
                    subtract pixel values of I2 from I1  
  
                    -i I1  
                    invert I1  
   
                    -l I1 I2  
                    mask I1 with I2  
  
                    -t I1 f  
                    threshold I1 with integer value of f  
  
To perform unit testing:  
  
cd into /Test  
run make  
An executable named 'test' is created.  
Execute './test' in the terminal to run the unit test program  
  
NOTE:  
The test cases are carefully written to cover the iterator inner class,  
constructors and all operator overloads, including copy/move assignment.  
These are specified in the comments.  
  
Please ensure that the input/output file names given as command-line parameters  
do not contain the extension (prefix only!)  

