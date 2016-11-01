#ifndef IMAGE_H
#define IMAGE_H

#include "ImageStructs.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>


using namespace std;

class Image
{
public:
    Image(char[], char[]);
    ~Image();
    bmpBITMAP_FILE myfile;
    char myFilename[80];

    //Methods FROM EDITBMP.cpp
    void open_input_file (ifstream &in_file);
    int Assemble_Integer(unsigned char bytes[]);
    void Display_FileHeader(bmpFILEHEADER &fileheader);
    void Display_InfoHeader(bmpINFOHEADER &infoheader);
    int Calc_Padding(int pixel_width);

    void Display_Bitmap_File(bmpBITMAP_FILE &image);
   void Copy_Image(bmpBITMAP_FILE &image_orig, bmpBITMAP_FILE &image_copy);
    void Remove_Image(bmpBITMAP_FILE &image);
    void Save_Bitmap_File();
    void Open_Output_File(ofstream &out_file);

private:
        void Load_Bitmap_File(bmpBITMAP_FILE &image, ifstream &infile);


};

#endif // IMAGE_H
