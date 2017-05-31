#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"
#include "../Image.h"

using namespace RSHMUS001;
using namespace std;

TEST_CASE ("Constructors and operator overloads", "[Overloading]") {

  unsigned char* data_test1 = new unsigned char[12];
  unsigned char* data_test2 = new unsigned char[12];

  for (int i=0; i<6; i++) {
    data_test1[i] = 80 + i + 10;
    data_test2[i] = 255;
  }

  for (int i=6; i<12; i++) {
    data_test1[i] = 80 - (i+10);
    data_test2[i] = 0;
  }

  Image m1 (3, 4, data_test1);
  Image m2 (!m1);
  Image u1 (3, 4, data_test2);

  SECTION ("Threshold") {
    Image test_mask (m1 * 80);
    REQUIRE (m1 == u1);
  }

  






}
