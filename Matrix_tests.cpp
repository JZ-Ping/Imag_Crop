// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <sstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) { //Passed

  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  //Fill the matrix with value

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  //Assert if all elements are correctly assigned

  delete mat; // delete the Matrix
}


TEST(test_fill_corner) { //Passed

  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 1;
  const int height = 1;
  const int value = -15;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, value);
  //Fill the 1x1 matrix with value

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  //Assert if all elements are correctly assigned

  delete mat; // delete the Matrix
}

TEST(test_matrix_at){
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 2;
  const int height = 2;
  const int val1 = -2;
  const int val2 = -4;
  Matrix_init(mat, height, width);
  *Matrix_at(mat, 0, 0) = val1;
  *Matrix_at(mat, 0, 1) = val2;
  *Matrix_at(mat, 1, 0) = val1;  
  *Matrix_at(mat, 1, 1) = val2;
  //Set the values to the matrix with 

  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), val1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), val2);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 0), val1);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 1), val2);
  delete mat; // delete the Matrix
}


// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(test_fill_border_basic) { //Passed

  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  const int value2 = 15;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat, value2);
  //Fill the matrix with value, then the border with value2

  for(int r = 1; r < height-1; ++r){
    for(int c = 1; c < width-1; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  //Check if correctly assigned in the center

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      if(r==0 || c==0 || r==(height-1) || c==(width-1)){
//        cout<<*Matrix_at(mat, r, c)<<" "<<r<<" "<<c<<endl;
        ASSERT_EQUAL(*Matrix_at(mat, r, c), value2);
      }
    }
  }
  //Check if correctly assigned around the border

  delete mat; // delete the Matrix
}

TEST(test_height_width) { //Passed
  cout<<"test_height_width"<<endl;
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 192;
  const int height = 389;
  const int value = 42;
  Matrix_init(mat, 192, 389);
  Matrix_fill(mat, value);
  ASSERT_EQUAL(width, Matrix_width(mat));
  ASSERT_EQUAL(height, Matrix_height(mat));

  delete mat; // delete the Matrix
}

TEST(test_matrix_min_max) { 

  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 5;
  //const int height = 3;
  const int value = 42;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, value);
  const int row1[] = {1, 7, 9, 2, -4};
  const int row2[] = {4, 19, 0, -23, -11};
  const int row3[] = {28, -5, 18, 39, -29};  

  for(int c = 0; c < width; ++c){
    *Matrix_at(mat, 0, c) = row1[c];
    //Matrix_print(mat,cout);
  }
  for(int c = 0; c < width; ++c){
    *Matrix_at(mat, 1, c) = row2[c];
    //Matrix_print(mat,cout);
  }
  for(int c = 0; c < width; ++c){
    *Matrix_at(mat, 2, c) = row3[c];
    //Matrix_print(mat,cout);
  }
  //Assign the three rows with values

  //Matrix_print(mat,cout);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 5), -4);
  //Matrix_print(mat,cout);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 5), -23);
  //Matrix_print(mat,cout);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 5), -29);
  //Matrix_print(mat,cout);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 5), 4);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 5), 3);  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 5), 4);
  ASSERT_EQUAL(Matrix_max(mat), 39);
  //Check if mininum and maximums are correct

  delete mat; // delete the Matrix
}

TEST(test_matrix_min_max_corner) { 

  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 2;
  const int height = 2;
  const int value = 15;
  Matrix_init(mat, height, width);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 2), 15);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 2), 15);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 2), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 2), 0);  
  ASSERT_EQUAL(Matrix_max(mat), 15);

  delete mat; // delete the Matrix
}

TEST(test_matrix_min_max_corner_2) { 

  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 1;
  const int height = 1;
  const int value = 13;
  Matrix_init(mat, height, width);
  Matrix_fill(mat, value);
  //Initialize a 1x1 matrix

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 1), 13);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 1), 0);
  ASSERT_EQUAL(Matrix_max(mat), 13);
  //Test the min max for 1x1 matrix

  delete mat; // delete the Matrix
}

TEST(test_matrix_row_column){
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 3;
  const int height = 5;
  const int value = 17;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(Matrix_column(mat, Matrix_at(mat, r, c)), c);
      ASSERT_EQUAL(Matrix_row(mat, Matrix_at(mat, r, c)), r);      
    }
  }
  delete mat; // delete the Matrix 
}

TEST(test_matrix_print_corner) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 5;
  //const int height = 3;
  const int value = 42;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, value);
  const int row1[] = {1, 7, 9, 2, -4};
  const int row2[] = {4, 19, 0, -23, -11};
  const int row3[] = {28, -5, 18, 39, -29};  

  for(int c = 0; c < width; ++c){
    *Matrix_at(mat, 0, c) = row1[c];
    //Matrix_print(mat,cout);
  }
  for(int c = 0; c < width; ++c){
    *Matrix_at(mat, 1, c) = row2[c];
    //Matrix_print(mat,cout);
  }
  for(int c = 0; c < width; ++c){
    *Matrix_at(mat, 2, c) = row3[c];
    //Matrix_print(mat,cout);
  }
  ostringstream expected;
  expected << "5 3\n"
           << "1 7 9 2 -4 \n"
           << "4 19 0 -23 -11 \n"
           << "28 -5 18 39 -29 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
