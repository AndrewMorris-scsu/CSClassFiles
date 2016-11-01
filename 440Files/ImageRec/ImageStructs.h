#ifndef IMAGESTRUCTS_H
#define IMAGESTRUCTS_H



typedef unsigned char  byte_t;

// The following two structures were adapted from
// http://users.ece.gatech.edu/~slabaugh/personal/c/bmpwrite.html
struct bmpFILEHEADER
{
    byte_t 	bfType[2];  //Bitmap identifier,  Must be "BM"
    byte_t	bfSize[4];
    byte_t       bfReserved[4];
    byte_t       bfOffbits[4];  //specifies the location
                                //(in bytes) in the file of the
               // image data. Should be equal to
               // sizeof(bmpFileHeader + sizeof(bmpInfoHeader)
               //        + sizeof(Palette)
};

struct bmpINFOHEADER
{
    byte_t	biSize[4];    // Size of the bmpInfoHeader,
                              // i.e. sizeof(bmpInfoheader)
    byte_t	biWidth[4];   // Width of bitmap, in pixels
                              // change this if you change
            // the size of the image. see ***** note below

    byte_t  	biHeight[4];  // Height of bitmap, in pixels
                              //change this if you change the
            // size of the image. see ***** note below
    byte_t 	biPlanes[2];  // Should/must be 1.
    byte_t	biBitCount[2]; // The bit depth of the bitmap.
                            // For 8 bit bitmaps, this is 8
    byte_t  	biCompression[4];   // Should be 0 for
                                    // uncompressed bitmaps
    byte_t       biSizeImage[4];    //The size of the padded
                                    // image, in bytes
    byte_t       biXPelsPerMeter[4]; //Horizontal resolution,
                        // in pixels per meter.  Not signif.
    byte_t       biYPelsPermeter[4];  //Vertical resolution,
                                      //as above.
    byte_t       biClrUsed[4];   //Indicates the number of
                                 //colors in the palette.
    byte_t       biClrImportant[4]; //Indicates number of
            //colors to display the bitmap.
        // Set to zero to indicate all colors should be used.
};
            // *****Note (from above) you will have to write
            //         a function to do this.  I have not yet.
struct bmpPALETTE
{
    byte_t	palPalette[1024]; // this will need to be
                   //improved if the program is to scale.
                    // unless we change the palette,
                   // this will do.
};

struct bmpBITMAP_FILE	// note:  this structure may not be
                        // written to file all at once.
                        // the two headers may be written
                        // normally, but the image requires
                        // a write for each line followed
                        //  by a possible 1 - 3 padding bytes.
{
    bmpFILEHEADER	fileheader;
    bmpINFOHEADER	infoheader;
    bmpPALETTE		palette;     //this implementation
        // will not generalize.  Fixed at 256 shades of grey.
    byte_t		**image_ptr; //this points to the
        // image. Allows the allocation of a two dimensional
        // array dynamically
};

#endif // IMAGESTRUCTS_H
