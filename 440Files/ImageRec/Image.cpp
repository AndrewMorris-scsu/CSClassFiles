#include "Image.h"

using namespace std;

Image::Image(char parentFilename[], char myFilename[]) {
    ifstream infile;
    bmpBITMAP_FILE ParentFile;
    infile.open(parentFilename, ios::in | ios::binary);
    cout << "Loading bitmap" << endl;
    Load_Bitmap_File(ParentFile, infile);
    cout << "about to copy" << endl;
    Copy_Image(ParentFile, this->myfile);
    cout << "Done copying" << endl;
    strncpy(this->myFilename, myFilename,79 );
    cout << "File name is :" << myFilename << endl;
}

Image::~Image () {
    Remove_Image(myfile);
}

void Image::open_input_file( ifstream &in_file ) {
    char in_file_name[80];

    cout << "Enter the name of the file" << endl
        << "which contains the bitmap: ";
    cin  >> in_file_name;

    in_file.open(in_file_name, ios::in | ios::binary);
    if (!in_file)
        cerr << "Error opening file\a\a\n", exit(101);

    return;
}

//================ Assemble_Integer ========================
int Image::Assemble_Integer (unsigned char bytes[])
{
    int an_integer;

    an_integer =
        int(bytes[0])
        + int(bytes[1]) * 256
        + int(bytes[2]) * 256*256
        + int(bytes[3]) * 256*256*256;
    return an_integer;
}

//============= Display_FileHeader =======================
//

void Image::Display_FileHeader(bmpFILEHEADER &fileheader)
{
    cout << "bfType:        "  << fileheader.bfType[0]
    << fileheader.bfType[1]
    << "\n";

    cout << "bfSize:        "
        << Assemble_Integer(fileheader.bfSize) << "\n";
    cout << "bfReserved:     "
        << Assemble_Integer(fileheader.bfReserved) << "\n";
    cout << "bfOffbits:      "
        << Assemble_Integer(fileheader.bfOffbits) << "\n";
}

//================ Display_InfoHeader ======================
//

void Image::Display_InfoHeader(bmpINFOHEADER &infoheader)
{
    cout << "\nThe bmpInfoHeader contains the following:\n";
    cout << "biSize:          "
        << Assemble_Integer(infoheader.biSize)   << "\n";
    cout << "biWidth:         "
        << Assemble_Integer(infoheader.biWidth)  << "\n";
    cout << "biHeight:        "
        << Assemble_Integer(infoheader.biHeight) << "\n";
    cout << "biPlanes:        "
        << int(infoheader.biPlanes[0])  +
        int(infoheader.biPlanes[1]) * 256          << "\n";

    cout << "biBitCount:      "
        << int(infoheader.biBitCount[0])  +
        int(infoheader.biBitCount[1])   * 256       << "\n";
    cout << "biCompression:   "
        << Assemble_Integer(infoheader.biCompression)<<"\n";
    cout << "biSizeImage:     "
        << Assemble_Integer(infoheader.biSizeImage) << "\n";
    cout << "biClrUsed:       "
        << Assemble_Integer(infoheader.biClrUsed)   << "\n";
    cout << "biClrImportant:  "
        << Assemble_Integer(infoheader.biClrImportant)<<"\n";

}

//==================== Calc_Padding ========================
//

int Image::Calc_Padding(int pixel_width)
{
    // Each scan line must end on a 4 byte boundry.
    // Threfore, if the pixel_width is not evenly divisible
    // by 4, extra bytes are added (either 1 - 3 extra bytes)

    int remainder = 0;
    int padding = 0;

    remainder = pixel_width % 4;
    //cout << "\nPixel width: " << pixel_width << "\n";
    //cout << "Remainder:     " << remainder << "\n";

    switch (remainder)
    {
        case 0:	padding = 0;
            break;
        case 1: padding = 3;
            break;
        case 2: padding = 2;
            break;
        case 3: padding = 1;
            break;
        default: cerr << "Error:  Padding was set to "
            << padding << "\n";
            exit(101);
    }

    //cout << "Padding determined: " << padding << "\n";

    return padding;
}

//================== load_Bitmap_File ======================
//
void Image::Load_Bitmap_File( bmpBITMAP_FILE &image, ifstream &fs_data)
{


    int bitmap_width;
    int bitmap_height;

    int padding = 0;
    long int cursor1; // used to navigate through the
                      // bitfiles

    fs_data.read(( char *) &image.fileheader,
                 sizeof(bmpFILEHEADER));
    //fs_data.seekg(14L);
    fs_data.read(( char *) &image.infoheader,
                 sizeof(bmpINFOHEADER));

    fs_data.read(( char *) &image.palette   ,
                 sizeof(bmpPALETTE));	// this will need to
                                       // be dynamic, once
                        // the size of the palette can vary

    bitmap_height = Assemble_Integer(image.infoheader.biHeight);
    bitmap_width = Assemble_Integer(image.infoheader.biWidth);
    padding = Calc_Padding(bitmap_width);

    // allocate a 2 dim array
    image.image_ptr = new byte_t*[bitmap_height];
    for (int i=0; i < bitmap_height; i++)
        image.image_ptr[i] = new byte_t[bitmap_width];

    cursor1 = Assemble_Integer(image.fileheader.bfOffbits);
    fs_data.seekg(cursor1);  //move the cursor to the
                            // beginning of the image data

    //load the bytes into the new array one line at a time
    for (int i=0; i<bitmap_height; i++)
    {
        fs_data.read(( char *) image.image_ptr[i],
                     bitmap_width);
        // insert code here to read the padding,
        // if there is any
    }

    fs_data.close();  //close the file
    // (consider replacing with a function w/error checking)
}

//============== Display_Bitmap_File =======================
//
void Image::Display_Bitmap_File(bmpBITMAP_FILE &image)
{
    int bitmap_width = 0;
    int bitmap_height = 0;

    Display_FileHeader(image.fileheader);
    Display_InfoHeader(image.infoheader);

    //display the palatte here too, perhaps.

    bitmap_height = Assemble_Integer(image.infoheader.biHeight);
    bitmap_width = Assemble_Integer(image.infoheader.biWidth);

    for (int i=0; i < 1; i++)
    {
        for (int j=0; j < bitmap_width; j++)
            cout << int(image.image_ptr[i][j]);
        cout << "\n\nNew Line\n\n";
    }
}

//=============== Copy_Image ===============================

void Image::Copy_Image(bmpBITMAP_FILE &image_orig,
                bmpBITMAP_FILE &image_copy)
{
    int height, width;
    cout << "Starting copy" << endl;
    image_copy.fileheader = image_orig.fileheader;
    image_copy.infoheader = image_orig.infoheader;
    image_copy.palette    = image_orig.palette;

    height = Assemble_Integer(image_copy.infoheader.biHeight);
    width = Assemble_Integer(image_copy.infoheader.biWidth);

    image_copy.image_ptr = new byte_t*[height];

    for (int i=0; i < height; i++)
        image_copy.image_ptr[i] = new byte_t[width];

    //load the bytes into the new array one byte at a time
    for (int i=0; i<height; i++)
    {
        for (int j=0; j < width; j++)
            image_copy.image_ptr[i][j] =
                image_orig.image_ptr[i][j];
    }
}

//================== Remove_Image ==========================
//
void Image::Remove_Image(bmpBITMAP_FILE &image)
{
    int height = 0;
    int width = 0;

    height = Assemble_Integer(image.infoheader.biHeight);
    width =  Assemble_Integer(image.infoheader.biWidth);

    //once the palette is dynamic, must delete the memory
    // allocated for the palatte here too

    // delete the dynamic memory
    for (int i = 0; i < height; i++)
        delete [] image.image_ptr[i];
    delete [] image.image_ptr;

    image.fileheader.bfType[0] = 'X';  // just to mark it as
    image.fileheader.bfType[1] = 'X';  // unused.
    // Also, we may wish to initialize all the header
    // info to zero.
}

//================== Save_Bitmap_File ======================
//
void Image::Save_Bitmap_File()
{
    ofstream fs_data;

    int width;
    int height;
    int padding = 0;
    long int cursor1 = 0;	// used to navigate through the
                        // bitfiles

    height = Assemble_Integer(this->myfile.infoheader.biHeight);
    width = Assemble_Integer(this->myfile.infoheader.biWidth);

    Open_Output_File(fs_data);

    fs_data.write ((char *) &this->myfile.fileheader,
                   sizeof(bmpFILEHEADER));
    if (!fs_data.good())
    {
        cout << "\aError 101 writing bitmapfileheader";
        cout << " to file.\n";
        exit (101);
    }

    fs_data.write ((char *) &this->myfile.infoheader,
                   sizeof(bmpINFOHEADER));
    if (!fs_data.good())
    {
        cout << "\aError 102 writing bitmap";
        cout << " infoheader to file.\n";
        exit (102);
    }

    fs_data.write ((char *) &this->myfile.palette,
                   sizeof(bmpPALETTE));
    if (!fs_data.good())
    {
        cout << "\aError 103 writing bitmap palette to";
        cout << "file.\n";
        exit (103);
    }
    //this loop writes the image data
    for (int i=0; i< height; i++)
    {
        for (int j=0; j<width; j++)
        {
            fs_data.write((char *) &this->myfile.image_ptr[i][j],
                          sizeof(byte_t));
            if (!fs_data.good())
            {
                cout << "\aError 104 writing bitmap data";
                cout << "to file.\n";
                exit (104);
            }
        }
    }

    fs_data.close();
}

//================== Open_Output_File ===================
//
void Image::Open_Output_File(ofstream &out_file)
{


    out_file.open(this->myFilename, ios::out | ios::binary);
    if (!out_file)
    {
        cout << "\nCannot open " << myFilename << endl;
        exit(101);
    }

    return;
}
