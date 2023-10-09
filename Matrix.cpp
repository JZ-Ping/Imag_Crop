// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  assert(0 < width && width <= MAX_MATRIX_WIDTH); 
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);
  mat->width = width; //modifies pointer struct
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  os << mat->width << ' ' << mat->height << '\n';
  for (int i = 0; i < mat->height; ++i) { 
    // double for loop to print out the matrix row by row
    for (int j = 0; j < mat->width; ++j) {
      os << mat->data[j+(i*mat->width)] << ' '; 
    } 
    os << '\n'; //Only change line at the end of each row
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  return mat->width;  // just return width
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  //assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  //assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  return mat->height;  // just return height
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH);
  assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  assert(ptr >= Matrix_at(mat,0, 0) &&
    ptr <= Matrix_at(mat, (mat->height - 1), (mat->width - 1))); 
  // verify that pointer points to element inside the matrix

  int row = (int)(ptr - Matrix_at(mat,0, 0)) / mat->width; 
  // divide the ptr by width and get the integer part of the result, 
  // which is the row number
  return row;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  assert(ptr >= Matrix_at(mat,0, 0) && 
    ptr <= Matrix_at(mat, (mat->height - 1), (mat->width - 1))); 
  // verify that pointer points to element inside the matrix

  int column = (ptr - Matrix_at(mat,0, 0)) % mat->width; 
  // divide the ptr by height and the integer part of the result is the column number
  return column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column. 
int* Matrix_at(Matrix* mat, int row, int column) {
  //assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH);
  //assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  assert(0 <= row && row < Matrix_height(mat)); 
  assert(0 <= column && column < Matrix_width(mat));

  int location = (row * mat->width) + column; 
  // calculate the position of the element in the matrix, 
  // if the matrix is just a long, single line vector
  int* ptr = &mat->data[location]; // pointer
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
 // assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
 // assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  //assert(0 <= row && row < Matrix_height(mat)); 
  //assert(0 <= column && column < Matrix_width(mat));

  int location = (row * mat->width) + column; 
  // calculate the position of the element in the matrix,
  // if the matrix is just a long, single line vector
  const int* ptr = &(mat->data[location]); // pointer
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  //assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  //assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  /*for (int i = 0; i < mat->height; ++i) { 
    // double for loop to treverse through each element in the matrix row by row
    for (int j = 0; j < mat->width; ++j) {
      mat->data[(i*mat->width)+j] = value;
    } 
  }*/
  for (int i = 0; i < (mat->width * mat->height); ++i) {
    mat->data[i] = value;
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  // set the first row to value
  for (int i = 0; i < mat->width; ++i) {
    mat->data[i] = value;
  }
  // set the last row to value
  for (int i = (mat->width * (mat->height - 1));
    i <= (mat->width * mat->height - 1); ++i) {
    mat->data[i] = value;
  }
  // set the first column to value
  for (int i = 0; i <= (mat->height * mat->width - mat->width); i += mat->width) {
    mat->data[i] = value;
  }
  // set the last column to value
  for (int i = (mat->width - 1); 
    i <= (mat->height * mat->width - 1); i += mat->width) {
    mat->data[i] = value;
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  int max_element = mat->data[0];
  for (int i = 0; i < (mat->width * mat->height); ++i) {
    if (mat->data[i] > max_element) {
      max_element = mat->data[i];
    }
  }
  return max_element;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row, 
    int column_start, int column_end) {
  //assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  //assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int index_start = row * mat->width + column_start; // inclusive
  int index_end = row * mat->width + column_end; 
  // exclusive, exclude the element AT index_end

  int min_element = mat->data[index_start];
  int column = column_start; 

  // note that the element at Index_end is excluded
  for (int i = index_start; i < index_end; ++i) { // find minimum element function
    if (mat->data[i] < min_element) {
      min_element = mat->data[i];
    }
  }

  for (int i = index_start; i < index_end; ++i) { // locate first occuring minimum element
    if (mat->data[i] != min_element) {
      column += 1;
    }else{
      return column;
    }
  }
  return 0;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row, 
    int column_start, int column_end) {
  assert(0 < mat->width && mat->width <= MAX_MATRIX_WIDTH); 
  assert(0 < mat->height && mat->height <= MAX_MATRIX_HEIGHT);
  assert(0 <= row && row < Matrix_height(mat)); // more conditions, potential problem
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int index_start = row * mat->width + column_start; // inclusive
  int index_end = row * mat->width + column_end;
  // exclusive, exclude the element AT index_end

  int min_element = mat->data[index_start];

  // note that the element at Index_end is excluded
  for (int i = index_start; i < index_end; ++i) { // find minimum element function
    if (mat->data[i] < min_element) {
      min_element = mat->data[i];
    }
  }

  return min_element; // just the above function without the locate leftest column part
}
