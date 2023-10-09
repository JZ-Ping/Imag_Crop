// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()

TEST(test_mat_init_corner){

  Image *img = new Image; // create a Matrix in dynamic memory
  stringstream ins;
  ins << "P3\n1 1\n255\n";
  ins << "0 0 230 \n";

  Image_init(img, ins);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).r, 0);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).g, 0);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).b, 230);

  delete img;
}

TEST(test_mat_init){

  Image *img = new Image; // create a Matrix in dynamic memory
  stringstream ins;
  ins << "P3\n2 2\n255\n";
  ins << "0 0 230 1 4 139\n";
  ins << "39 19 123 33 12 204\n";

  Image_init(img, ins);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).r, 0);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).g, 0);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).b, 230);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 1).r, 1);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 1).g, 4);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 1).b, 139);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 0).r, 39);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 0).g, 19);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 0).b, 123);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).r, 33);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).g, 12);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).b, 204);

  delete img;
}


TEST(test_height_width){
  Image *img = new Image; // create an Image in dynamic memory
  
  Image_init(img, 189, 268);
  //Initialize an image

  ASSERT_EQUAL(Image_width(img), 189);
  ASSERT_EQUAL(Image_height(img), 268);
  //Test if width and height are assigned

  delete img; // delete the Image
}

TEST(test_set_get_pixel){
  Image *img = new Image; // create an Image in dynamic memory
  Image_init(img, 2, 2);
  //Initialize an image
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).r, 255);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).g, 0);  
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).b, 0);
  //Check first pixel
  ASSERT_EQUAL(Image_get_pixel(img, 0, 1).r, 0);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 1).g, 255);  
  ASSERT_EQUAL(Image_get_pixel(img, 0, 1).b, 0);
  //Check second pixel
  ASSERT_EQUAL(Image_get_pixel(img, 1, 0).r, 0);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 0).g, 0);  
  ASSERT_EQUAL(Image_get_pixel(img, 1, 0).b, 255);
  //Check third pixel
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).r, 255);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).g, 255);  
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).b, 255);
  //Check fourth pixel
  delete img; // delete the Image
}

TEST(test_image_fill){
  Image *img = new Image; // create an Image in dynamic memory
  
  const int width = 299;
  const int height = 138;

  Image_init(img, width, height);
  //Initialize an image
  const Pixel myPix = {117, 219, 192};
  //Customize a pixel, somewhere cyan, and fill it with Image_fill
  Image_fill(img, myPix);

  //Image_print(img, cout);

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      ASSERT_EQUAL(Image_get_pixel(img, i, j).r, 117);
      ASSERT_EQUAL(Image_get_pixel(img, i, j).g, 219);  
      ASSERT_EQUAL(Image_get_pixel(img, i, j).b, 192);
    }
  }
  //Check if all pixels are filled

  delete img; // delete the Image
}

TEST(test_image_fill_corner){
  Image *img = new Image; // create an Image in dynamic memory
  
  const int width = 1;
  const int height = 1;

  Image_init(img, width, height);
  //Initialize an image
  const Pixel myPix = {0, 0, 255};
  //Customize a pixel, somewhere cyan, and fill it with Image_fill
  Image_fill(img, myPix);

  //Image_print(img, cout);

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      ASSERT_EQUAL(Image_get_pixel(img, i, j).r, 0);
      ASSERT_EQUAL(Image_get_pixel(img, i, j).g, 0);  
      ASSERT_EQUAL(Image_get_pixel(img, i, j).b, 255);
    }
  }
  //Check if all pixels are filled

  delete img; // delete the Image
}

TEST_MAIN() // Do NOT put a semicolon here
