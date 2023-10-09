// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"
#include <string>
using namespace std;

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  assert(0 < width && width <= MAX_MATRIX_WIDTH); 
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);

  img->width = width; //modifies pointer struct
  img->height = height;
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  string fileType;
  int maxValue = 1;
  int width = 1;
  int height = 1;

  is >> fileType >> width >> height >> maxValue;
  img->width = width;
  img->height = height;

  Matrix_init(&img->red_channel, img->width, img->height);
  Matrix_init(&img->green_channel, img->width, img->height);
  Matrix_init(&img->blue_channel, img->width, img->height);
  
  for (int r = 0; r < img->height; ++r) {
    for (int c = 0; c < img->width; ++c) {
      int* ptrR = Matrix_at(&img->red_channel, r , c);
      int* ptrG = Matrix_at(&img->green_channel, r , c);
      int* ptrB = Matrix_at(&img->blue_channel, r , c);
      is >> *ptrR >> *ptrG >> *ptrB;
    }
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3" << '\n';
  os << img->width << ' ' << img->height << '\n';
  os << 255 << '\n';

  for (int r = 0; r < img->height; ++r) {
    for (int c = 0; c < img->width; ++c) {
      const int *ptrR = Matrix_at(&img->red_channel, r , c);
      const int *ptrG = Matrix_at(&img->green_channel, r , c);
      const int *ptrB = Matrix_at(&img->blue_channel, r , c);
      os << *ptrR << ' ';
      os << *ptrG << ' ';
      os << *ptrB << ' ';
    }
    os << '\n';
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  // get the respective R, G, B value from the matrices 
  const int* ptrR = Matrix_at(&img->red_channel, row, column);
  const int* ptrG = Matrix_at(&img->green_channel, row, column);
  const int* ptrB = Matrix_at(&img->blue_channel, row, column); 

  // declare new Pixel type variable to catch the result
  Pixel pix;
  pix.r = *ptrR;
  pix.g = *ptrG;
  pix.b = *ptrB;

  return pix;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  // unbundling the color input
  int R = color.r;
  int G = color.g;
  int B = color.b;

  // get the respective R, G, B value from the matrices 
  int* ptrR = Matrix_at(&img->red_channel, row, column);
  int* ptrG = Matrix_at(&img->green_channel, row, column);
  int* ptrB = Matrix_at(&img->blue_channel, row, column); 

  // over write the old RGB with the new ines from color
  *ptrR = R;
  *ptrG = G;
  *ptrB = B;  
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  // unbundling the color input
  int R = color.r;
  int G = color.g;
  int B = color.b;

  Matrix_fill(&img->red_channel, R);
  Matrix_fill(&img->green_channel, G);
  Matrix_fill(&img->blue_channel, B);
}
