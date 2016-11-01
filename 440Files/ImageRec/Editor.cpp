//
// Created by Andrew Morris on 11/20/15.
//
#include <math.h>
#include <vector>
#include "Editor.h"

#define WHITE 255
#define BLACK 0
#define KTHRESH 35

struct accumulator { // TO BE USED BY HOUGH TRANSFORM
    int counter; // pixels intersection counter
    vector<int> x;  // x coordinate
    vector<int> y;  // y coordinate
    accumulator() {counter=0;}
};

accumulator pixels[1281][91];

Editor::Editor() {

}

void Editor::Gauss(Image &Dest, Image &Source) {
    int rows = 1024;
    int cols = 768;

    for (int i = 1; i < cols - 1; i++) {

        for (int j = 1; j < rows - 1; j++) {
            int left, right, top, bottom;
            int tl, tr, bl, br;
            int currentPixel;

            currentPixel = (int)(4 * Source.myfile.image_ptr[i][j]);

            left = (int)(2 * Source.myfile.image_ptr[i - 1][j]);
            right = (int)(2 * Source.myfile.image_ptr[i + 1][j]);
            top = (int)(2 * Source.myfile.image_ptr[i][j + 1]);
            bottom = (int)(2 * Source.myfile.image_ptr[i][j - 1]);

            tl = (int)(Source.myfile.image_ptr[i - 1][j + 1]);
            tr = (int)(Source.myfile.image_ptr[i + 1][j + 1]);
            bl = (int)(Source.myfile.image_ptr[i - 1][j - 1]);
            br = (int)(Source.myfile.image_ptr[i - 1][j + 1]);

            Dest.myfile.image_ptr[i][j] = (left + right + top + bottom + tl + tr + bl + br + currentPixel) / 16;

        }//End of rows
    }//End of cols

}

void Editor::Histogram(Image &Dest, Image &Source) {
    int rows = 1024;
    int cols = 768;
    int currentPixel = 0;

    int H[256];

    for (int i = 0; i < 256; i++) {
        H[i] = 0;
    }
    //Build HistoGram
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {

           currentPixel = (int)(Source.myfile.image_ptr[i][j]);
           H[currentPixel] += 1;
        }//End of rows
    }//End of cols

    //Cumulative Histogram
    for (int i = 1; i < 256; i++) {
        H[i] = H[i] + H[i - 1];
    }

    //Normalize
    for (int i = 0; i < 256; i++) {
        H[i] = H[i]*255 / (rows * cols);
        if (H[i] > 255 || H[i] < 0) {
            cout << "INVALID HISTOGRAM VALUE!!!!"<< " " << H[i] << endl;
        }
    }

    //Reassign values
    for (int i = 0; i < cols ; i++) {
        for (int j = 0; j < rows ; j++) {

            currentPixel = (int)(Source.myfile.image_ptr[i][j]);

            Dest.myfile.image_ptr[i][j] = H[currentPixel];
        }//End of rows
    }//End of cols
}

void Editor::Kirsch(Image &Dest, Image &Source) {
    int rows = 1024;
    int cols = 768;

    for (int i = 0; i < cols; i++) {

        for (int j = 0; j < rows; j++) {
            int left, right, top, bottom;
            int tl, tr, bl, br;
            int LeftDifference, UpDifference, ToBottomLeftDifference, ToBottomRightDifference;

            Dest.myfile.image_ptr[i][j] = 255;

            if ((i > 4)&&(i < cols - 5) && (j > 4)&&(j < rows-5)) {

                left = (int) Source.myfile.image_ptr[i - 1][j];
                right = (int) Source.myfile.image_ptr[i + 1][j];
                top = (int) Source.myfile.image_ptr[i][j + 1];
                bottom = (int) Source.myfile.image_ptr[i][j - 1];

                tl = (int) (Source.myfile.image_ptr[i - 1][j + 1]);
                tr = (int) (Source.myfile.image_ptr[i + 1][j + 1]);
                bl = (int) (Source.myfile.image_ptr[i - 1][j - 1]);
                br = (int) (Source.myfile.image_ptr[i - 1][j + 1]);

                LeftDifference = abs((left + tl + bl) - (right + tr + br));

                if (LeftDifference > KTHRESH) {
                    Dest.myfile.image_ptr[i][j] = 0;
                }

                UpDifference = abs((bl + br + bottom) - (tl + tr + top));

                if (UpDifference > KTHRESH) {
                    Dest.myfile.image_ptr[i][j] = 0;
                }

                ToBottomRightDifference = abs((top + left + tl) - (bottom + right + br));

                if (ToBottomRightDifference > KTHRESH) {
                    Dest.myfile.image_ptr[i][j] = 0;
                }

                ToBottomLeftDifference = abs((top + right + tr) - (bottom + left + bl));

                if (ToBottomLeftDifference > KTHRESH) {
                    Dest.myfile.image_ptr[i][j] = 0;
                }
            }

        }//End of rows
    }//End of cols
}

void Editor::FillIn(Image &Dest, Image & Source) {
    int rows = 1024;
    int cols = 768;
    //Copy the Source to Dest.
    for (int i = 0; i < cols; i++) {

        for (int j = 0; j < rows; j++) {
            Dest.myfile.image_ptr[i][j] = Source.myfile.image_ptr[i][j];

        }//End of rows
    }//End of cols


    for (int i = 1; i < cols - 1; i++) {

        for (int j = 1; j < rows - 1; j++) {
            if (Source.myfile.image_ptr != 0) {
                int left, right, top, bottom;
                int tl, tr, bl, br;
                int currentPixel;
                int surrounding[8];

                left = (int) (Source.myfile.image_ptr[i - 1][j]);
                right = (int) (Source.myfile.image_ptr[i + 1][j]);
                top = (int) (Source.myfile.image_ptr[i][j + 1]);
                bottom = (int) (Source.myfile.image_ptr[i][j - 1]);

                tl = (int) (Source.myfile.image_ptr[i - 1][j + 1]);
                tr = (int) (Source.myfile.image_ptr[i + 1][j + 1]);
                bl = (int) (Source.myfile.image_ptr[i - 1][j - 1]);
                br = (int) (Source.myfile.image_ptr[i - 1][j + 1]);

                surrounding[0] = left;
                surrounding[1] = right;
                surrounding[2] = top;
                surrounding[3] = bottom;
                surrounding[4] = tl;
                surrounding[5] = tr;
                surrounding[6] = bl;
                surrounding[7] = br;

                int count = 0;
                for (int k = 0; i < 8; i++) {   //Get a count of all edge elements.
                    if (surrounding[k] == 0) {
                        count++;
                    }
                }
                if (count >= 6) {
                    Dest.myfile.image_ptr[i][j] = 0;
                }
            }
            else {
                Dest.myfile.image_ptr[i][j] = 0;
            }
        }//End of rows
    }//End of cols
}

void Editor::Thinning(Image &Dest, Image &Source) {
    int modulo = 0;

    int rows = 1024;
    int cols = 768;
    int finalPoints[768][1024];
    int contourPoints[768][1024];

    int I = 0, F = 0, C = 0;

    //parse original image to get a count of all edge elements.
    for (int i = 0; i < cols; i++) {

        for (int j = 0; j < rows; j++) {

            int currentPixel;

            currentPixel = (int)(Source.myfile.image_ptr[i][j]);
            if (currentPixel == 0) {
                I++;
            }
            Dest.myfile.image_ptr[i][j] = WHITE;
            finalPoints[i][j] = 0;
            contourPoints[i][j] = 0;
        }//End of rows
    }//End of cols
    //Done accumulating edge elements from source image and initializing line image.
    int rounds = 0;
    while (true && rounds < 20) {
        //cout << "Abs(f - i) == " << abs(F - I) << endl;
        if(abs(F - I) < 24)  {
           return;
        }

        for (int i = 1; i < cols - 1; i++) {

            for (int j = 1; j < rows - 1; j++) {
                bool Contour = false;
                bool Final = false;

                if ((int)Source.myfile.image_ptr[i][j] == 0) {   //Current pixel is an edge element,
                                                            // we need not bother otherwise.
                    int left, right, top, bottom;
                    int tl, tr, bl, br;
                    int currentPixel;

                    currentPixel = (int) Source.myfile.image_ptr[i][j];

                    left = (int) Source.myfile.image_ptr[i - 1][j];
                    right = (int) Source.myfile.image_ptr[i + 1][j];
                    top = (int) Source.myfile.image_ptr[i][j + 1];
                    bottom = (int) Source.myfile.image_ptr[i][j - 1];

                    tl = (int) Source.myfile.image_ptr[i - 1][j + 1];
                    tr = (int) Source.myfile.image_ptr[i + 1][j + 1];
                    bl = (int) Source.myfile.image_ptr[i - 1][j - 1];
                    br = (int) Source.myfile.image_ptr[i - 1][j + 1];

                    /**
                     * We will want to mark the current pixel as a contour point or
                     * final point. Final points are considered in the following situations.
                     * modulo = 0; b1, b2
                     * modulo = 1; b3, b4
                     * modulo = 2; b1, b4
                     * modulo = 3; b2, b3
                     */

                    switch (modulo) {
                        case 0: {
                            if (bottom == WHITE ) {
                                Contour = true;

                            }
                            //B1
                            if ((bottom == BLACK) &&
                                (right == WHITE && bl == WHITE) &&
                                (tl == BLACK || top == BLACK || tr == BLACK ) ) {
                                Final = true;
                            }
                            //B2
                            if ((right == BLACK) &&
                                (tr == WHITE && bottom == WHITE) &&
                                (tl == BLACK || left == BLACK || bl == BLACK ) ) {
                                Final = true;
                            }
                            break;
                        }
                        case 1: {
                            if (top == WHITE) {
                                Contour = true;
                            }
                            //B3
                            if ((top == BLACK) &&
                                (tr == WHITE && left == WHITE) &&
                                (bl == BLACK || bottom == BLACK || br == BLACK ) ) {
                                Final = true;
                            }

                            //B4
                            if ((left == BLACK) &&
                                (bl == WHITE && top == WHITE) &&
                                (tr == BLACK || right == BLACK || br == BLACK ) ) {
                                Final = true;
                            }

                            break;
                        }
                        case 2: {
                            if (left == WHITE) {
                                Contour = true;

                            }
                            //B1
                            if ((bottom == BLACK) &&
                                (right == WHITE && bl == WHITE) &&
                                (tl == BLACK || top == BLACK || tr == BLACK ) ) {
                                Final = true;
                            }
                            //B4
                            if ((left == BLACK) &&
                                (bl == WHITE && top == WHITE) &&
                                (tr == BLACK || right == BLACK || br == BLACK ) ) {
                                Final = true;
                            }
                            break;
                        }
                        case 3: {
                            if (right == WHITE) {
                                Contour = true;

                            }

                            //B2
                            if ((right == BLACK) &&
                                (tr == WHITE && bottom == WHITE) &&
                                (tl == BLACK || left == BLACK || bl == BLACK ) ) {
                                Final = true;
                            }
                            //B3
                            if ((top == BLACK) &&
                                (tr == WHITE && left == WHITE) &&
                                (bl == BLACK || bottom == BLACK || br == BLACK ) ) {
                                Final = true;
                            }
                            break;
                        }
                    }
                    //Regardless of previous operations, if the following are true, the pixel is a final point.
                    if ((left == WHITE && right == WHITE) &&
                        ( tl == BLACK || top == BLACK  || tr == BLACK ) &&
                        ( bl == BLACK || bottom == BLACK || br == BLACK) ) {         //a1
                        Final = true;
                    }
                    else if ((top == WHITE && bottom == WHITE) &&
                            (tl == BLACK || left == BLACK || bl == BLACK) &&
                            (tr == BLACK || right == BLACK || br == BLACK) ) {    //a2
                        Final = true;
                    }
                    else if ((tl == WHITE && br == WHITE ) &&
                            (left == BLACK || bl == BLACK || bottom == BLACK ) &&
                            (top == BLACK || tr == BLACK || right == BLACK ) ) {    //a3
                        Final = true;
                    }
                    else if ((tr == WHITE && bl == WHITE ) &&
                            ( left == BLACK || tl == BLACK || top == BLACK) &&
                            ( bottom == BLACK || br == BLACK || right == BLACK ) ) {    //a4
                        Final = true;
                    }

                    if (Final) {
                        Dest.myfile.image_ptr[i][j] = BLACK;
                        if(finalPoints[i][j] == 0) {

                            finalPoints[i][j] = 1;
                            F++;
                        }


                    } else {

                        if (Contour) {
                            Source.myfile.image_ptr[i][j] = WHITE;
                            if (contourPoints[i][j] == 0) {

                                contourPoints[i][j] = 1;
                                C++;
                            }
                        }
                    }

                }

            }//End of rows
        }//End of cols
        I = I - C + F;
        //F= F + finalpoints(I)
        //if (F == I) return;

        //C = countourPointsi(I)
        //i = (i + 1) % 4
        modulo = (modulo + 1) % 4;
        ++rounds;
    }
}

void Editor::windowNoiseReduction(Image &Dest, Image &Source, int winSize) {
    int rows = 1024;
    int cols = 768;

    //Copy the Source to Dest.
    for (int i = 0; i < cols; i++) {

        for (int j = 0; j < rows; j++) {
        Dest.myfile.image_ptr[i][j] = Source.myfile.image_ptr[i][j];

        }//End of rows
    }//End of cols

    //Begining noise reduction
    for (int i = winSize/2 - 1  ; i < cols - winSize/2 ; i++) {

        for (int j = winSize/2 - 1 ; j < rows - winSize/2 ; j++) {
            //cout << "i = " << i << " J = " << j << endl;
            int left, right, top, bottom;
            int tl, tr, bl, br;
            int currentPixel;


            //search the perimeter of the window for a line,
            // if a line exists on the perimeter, move on to the next
            // pixel.
            bool perimeterEdge = false;
            for (int y = i - (winSize/2) + 1; y < i + (winSize/2) ; y++) {
                for (int x = j - (winSize/2) + 1  ; x < j + (winSize/2) ; x++) {
                    //cout << "y = " << y << " x = " << x << endl;
                    /*if (Source.myfile.image_ptr[y][x] == 0) {
                        cout << "x";
                    }
                    else {
                        cout << "o";
                    }
                     */
                    if (    y == i - (winSize/2) + 1 || x == j - (winSize/2) + 1 ||
                            y == i + (winSize/2) - 1 || x == j + (winSize/2) - 1  )
                    {   //Only check outside of the window.
                        if ((int)Source.myfile.image_ptr [y][x] == 0) {
                            perimeterEdge = true;
                        }
                    }
                }
                //cout << endl;
            }

            if (perimeterEdge == false) {           //Erase all pixels within the window,
                //cout << "Above was deleted";// because no border elements were found..
                for (int y = i - (winSize/2) + 1; y < i + (winSize/2) ; y++) {
                    for (int x = j - (winSize/2) + 1; x < j + (winSize/2) ; x++) {

                        Dest.myfile.image_ptr[y][x] = 255;
                    }
                }
            }
            //cout << endl;
        }//End of rows
    }//End of cols
}

void Editor::Hough_Transform(Image &Dest, Image &Source) {
    int rows = 768;
    int cols = 1024;
    int currentPixel;

    int votes = 0;

    // Analyze the input image first
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {
            // Check for each edge pixels
            currentPixel = (int) (Source.myfile.image_ptr[i][j]);
            Dest.myfile.image_ptr[i][j] = 255; // Initialize final image
            // If the currentPixel is an edge
            if (currentPixel == 0) { // BLACK (There is a macro for this too)

                int theta_inc = 2; // Determines the quantization of theta

                // Determine the parametric representations of individual pixel
                for (int theta = 0; theta <= 180; theta += theta_inc) {

                    // d = xsin(theta) + ycos(theta)
                    // d is a perpendicular distance from (0,0) to the line
                    // Theta is angle betn the perpendicular and the horizontal axis
                    int d = round((i * sin(theta)) + (j * cos(theta)));
                    d = abs(d);
                    //cout << "The perpend dist is : " << d << "\n";
                    int quotient = round (theta/theta_inc);
                    //cout << "The quotient is : " << quotient << "\n";
                    pixels[d][quotient].counter += 1;
                    pixels[d][quotient].x.push_back(i);
                    pixels[d][quotient].y.push_back(j);
                } // for

                //Dest.myfile.image_ptr[i][j] = 0; // Writing to output file
            } // DONE ANALYZING CURRENTPIXEL (if block)
        } // Rows
    } // Cols

    // Analyze the accumulator array to draw out Hough lines
    for (int i = 0; i < 1281; i++) {
        for (int j = 0; j < 91; j++) {
            if (pixels[i][j].counter > 0) {
                int votes = pixels[i][j].counter;
                int xval = pixels[i][j].x[0];
                int yval = pixels[i][j].y[0];
                //cout << "The votes for pixel at [" << xval << " , " << yval << "] is: " << votes << "\n";
            }
        }
    }

    /**
     * Print out the pixels with the voted amount.
     */
    for (int i = 0; i < 1281; i++) {
        for (int j = 0; j < 91; j++) {

            if (pixels[i][j].counter > 140) {
                //If we will consider this to be a line.
                //Print out all of the pixels that voted for this line.

                for (int k = 0; k < pixels[i][j].counter; k++) {
                    Dest.myfile.image_ptr[ pixels[i][j].x.at(k) ][ pixels[i][j].y.at(k) ] = 0;
                }

            }
        }
    }
}// Hough_Transform