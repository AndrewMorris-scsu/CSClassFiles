#include <iostream>
#include <cstdlib>
#include "Image.h"
#include "Editor.h"


using namespace std;

int main()
{
    Editor edit;

    char filename1[80] = "first.bmp";
    char filename2[80] = "second.bmp";
    char filename3[80] = "third.bmp";
    char filename4[80] = "fourth.bmp";
    char filename5[80] = "fifth.bmp";
    char filename6[80] = "sixth.bmp";
    char filename7[80] = "seventh.bmp";
    char filename8[80] = "eighth.bmp";
    char filename9[80] = "ninth.bmp";
    char filename10[80] = "tenth.bmp";
    char filename11[80] = "eleventh.bmp";
    char filename12[80] = "twelth.bmp";
    char filename13[80] = "thirteenth.bmp";
    char filename14[80] = "fourteenth.bmp";
    char FillIN[80] = "FilledIn.bmp";

    char tempName[] = "template.bmp";

    //cout << "Enter the name of the new file you would like to create" << endl;
    //cin >> filename1;
    Image Old(tempName, filename1);

    //cout << "Enter the name of the new file for Histogram Equalization" << endl;
    //cin >> filename2;
    Image Histo(tempName, filename2);
    //edit.Histogram(Histo, Old);


    //cout << "Enter the name of the new file you would like to create for initial smoothing" << endl;
    //cin >> filename3;
    Image Smooth1(tempName, filename3);
    cout << "Starting Gauss" << endl;
    edit.Gauss(Smooth1, Histo);


    //cout << "Enter the name of the new file for second smoothing" << endl;
    //cin >> filename4;
    Image DoubleSmooth(tempName, filename4);
    edit.Gauss(DoubleSmooth, Smooth1);


    //cout << "Enter the name of the file you want for the edge drawing" << endl;
    //cin >> filename5;
    Image Edge(tempName, filename5);
    edit.Kirsch(Edge, DoubleSmooth);


    //cout << "Enter the name of the file for the line drawing" << endl;
    //cin >> filename6;

    //Add fill in method here.




    //cout << "Enter the name of the file for the REDUCED line drawing" << endl;
    //cin >> filename7;
    Image NoiseReduc(tempName, filename6);

    edit.windowNoiseReduction(NoiseReduc, Edge , 11);

    //cout << "Enter the name of the file for the REDUCED line drawing" << endl;
    //cin >> filename8;
    Image DoubleNoiseReduc(tempName, filename7);

    edit.windowNoiseReduction(DoubleNoiseReduc,NoiseReduc, 25);

    Image Fillin(tempName, FillIN);
    edit.FillIn(Fillin, DoubleNoiseReduc);

    Image Line(tempName, filename8);

    edit.Thinning(Line, Fillin);

    Image Huff(tempName,filename9);

    edit.Hough_Transform(Huff, Fillin);

    Image HuffNoise1(tempName, filename10);

    edit.windowNoiseReduction(HuffNoise1, Huff, 15);

    Image Huff2(tempName, filename11);

    edit.Hough_Transform(Huff2, HuffNoise1);

    Image HuffNoise2(tempName, filename12);

    edit.windowNoiseReduction(HuffNoise2, Huff2, 11);

    Image HuffNoise3(tempName, filename13);

    edit.windowNoiseReduction(HuffNoise3, HuffNoise2, 25);

    Image HuffNoise4(tempName, filename14);

    edit.windowNoiseReduction(HuffNoise4, HuffNoise3, 50);


    Old.Save_Bitmap_File();
    Histo.Save_Bitmap_File();
    Smooth1.Save_Bitmap_File();
    DoubleSmooth.Save_Bitmap_File();
    NoiseReduc.Save_Bitmap_File();
    DoubleNoiseReduc.Save_Bitmap_File();
    Edge.Save_Bitmap_File();
    Line.Save_Bitmap_File();
    Huff.Save_Bitmap_File();
    HuffNoise1.Save_Bitmap_File();
    Huff2.Save_Bitmap_File();
    HuffNoise2.Save_Bitmap_File();
    HuffNoise3.Save_Bitmap_File();
    HuffNoise4.Save_Bitmap_File();
    Fillin.Save_Bitmap_File();

    return 0;
}

