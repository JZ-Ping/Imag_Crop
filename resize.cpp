// Project UID af1f95f547e44c8ea88730dfb185559d
#include <iostream>
#include "processing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
  //cout << "Hello World!\n";
  if(argc<4||argc>5){
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     exit(0);
  } 
  string in_fname;
  string out_fname;
  int w_wanted = stoi(argv[3]);
  int h_wanted = stoi(argv[4]);
  in_fname = argv[1];
  out_fname = argv[2];

  //FILE *img_file;
  //img_file = fopen(in_fname, "rb");
  //if(!img_file){
  //}

  ifstream img_file(in_fname, ifstream::in);
  if (!img_file.is_open())
   {
    cout << "Error opening file: " << in_fname << endl;
    exit(0);
   }

  Image* img = new Image;
  Image_init(img, img_file);

  if(w_wanted<=0||w_wanted>img->width||h_wanted<=0||h_wanted>img->height){
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     exit(0);
   }

  seam_carve(img, w_wanted, h_wanted);

  ofstream out_img(out_fname, ofstream::out);
  if (!out_img.is_open())
   {
    cout << "Error opening file: " << out_fname << endl;
    exit(0);
   }
  Image_print(img, out_img);

  out_img.close();
  img_file.close();
  delete img;

  return 0;
}