//#include <fstream>
#include <cstring>
//#include <cmath>
#include "bmplib.h"
#include "bmplib.cpp"

#define test_cases int t; cout << "Enter the n of test cases: "; cin >> t ; while(t--)
#define fin "\n"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];

void loadImage();

void saveImage();

void doSomethingForImage();

char options();

void imageProcessor(char option);

void black_and_white();

void invert();

void merge();

void flip();

void rotate();

void darken_and_lighten();

void detect_edges();  // unfinished

void enlarge();

void shrink();

void shuffle();

void mirror();

void blur();

void crop();

void skew_horizontal(); // unfinished

void skew_vertical(); // unfinished

int main() {
    test_cases {
        loadImage();
        doSomethingForImage();
        saveImage();
    }
    return 0;
}

//_________________________________________
void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void loadImage2() {
    char imageFileName2[100];

    // Get gray scale image file name
    cout << "Enter the source of the second image file name: ";
    cin >> imageFileName2;

    // Add to it .bmp extension and load image
    strcat(imageFileName2, ".bmp");
    readGSBMP(imageFileName2, image2);
}

//_________________________________________
void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void doSomethingForImage() {
    char c = options();
    imageProcessor(c);
}

//_________________________________________
char options() {
    char option;

    cout << "Options:" << fin;
    cout << "1- Black and white image" << fin;
    cout << "2- Invert image" << fin;
    cout << "3- Merge images" << fin;
    cout << "4- Flip image" << fin;
    cout << "5- Rotate image" << fin;
    cout << "6- Darken and lighten image" << fin;
    cout << "7- Detect image edges" << fin;
    cout << "8- Enlarge image" << fin;
    cout << "9- Shrink image" << fin;
    cout << "a- Mirror image" << fin;
    cout << "b- Shuffle image" << fin;
    cout << "c- Blur image" << fin;
    cout << "d- Crop image" << fin;
    cout << "e- Skew horizontally" << fin;
    cout << "f- Skew vertically" << fin;

    cout << "Choice: ";
    cin >> option;

    return option;
}

//_________________________________________
void imageProcessor(char option) {
    switch (option) {
        case '1':
            black_and_white();
            break;

        case '2':
            invert();
            break;

        case '3':
            merge();
            break;

        case '4':
            flip();
            break;

        case '5':
            rotate();
            break;

        case '6':
            darken_and_lighten();
            break;

        case '7':
            detect_edges();
            break;

        case '8':
            enlarge();
            break;

        case '9':
            shrink();
            break;

        case 'a':
            mirror();
            break;

        case 'b':
            shuffle();
            break;

        case 'c':
            blur();
            break;

        case 'd':
            crop();
            break;

        case 'e':
            skew_horizontal();
            break;

        case 'f':
            skew_vertical();
            break;

        default:
            return;
    }
}

// output an image in black and white only
void black_and_white() {
    // convert light shades to white
    for (auto &i: image) {
        for (unsigned char &j: i) {
            if (j > 127)
                // convert light shades to white
                j = 255;
            else
                // convert dark shades to black
                j = 0;
        }
    }
}

// invert the colors of the image
void invert() {
    for (auto &i: image) {
        for (unsigned char &j: i) {
            // invert the color
            j = 255 - j;
        }
    }
}

// merge 2 images together
void merge() {
    // take the second image entered from the user
    loadImage2();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // calculate the average of the 2 pixels in the same position
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

//flip the image horizontally or vertically
void flip() {
    cout << "Flip image (h)orizontally or (v)ertically?" << fin;
    char choice; //direction
    cin >> choice;
    // Flip horizontally
    if (tolower(choice) == 'h') {
        unsigned char temp; // Temporary variable for pixel swapping
        for (auto &i: image) {
            for (int j = 0; j < SIZE / 2; ++j) {
                temp = i[j];
                i[j] = i[SIZE - 1 - j];
                i[SIZE - 1 - j] = temp;
                // Swap pixels between the left and right sides of the row to achieve horizontal flip
            }
        }
        // Flip vertically
    } else {
        unsigned char temp;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                temp = image[j][i];
                image[j][i] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = temp;
                // Swap pixels between the top and bottom sides of the column to achieve vertical flip
            }
            }
        }
    }

// rotate the image clockwise based on the user's input by (90 ,180 , 270) degrees
void rotate() {
    cout << "Do you want to rotate the image clockwise by: a) 90  b) 180  c) 270" << fin;
    char choice;
    cin >> choice;
    int n_times = 0; // Variable to store the number of times to rotate (90 degrees per rotation)

    // Determine the number of rotations based on the user's choice
    switch (choice) {
        case 'a':
            n_times = 1; // Rotate 90 degrees
            break;
        case 'b':
            n_times = 2; // Rotate 180 degrees
            break;
        case 'c':
            n_times = 3; // Rotate 270 degrees
            break;
        default:
            cout << "Enter a valid choice" << fin;
            rotate();
    }

    // Perform the specified number of rotations
    while (n_times--) {
        // Iterate through each pixel in the original image
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                // Rotate the pixel clockwise by 90 degrees and store it in a temporary image (image3)
                image3[SIZE - 1 - j][i] = image[i][j];
            }
        }

        // Copy the rotated image (image3) back to the original image
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image3[i][j];
            }
        }
    }
}


// 2 options for the image brightness
void darken_and_lighten() {
    cout << "a) Darken  b) Lighten ?" << fin;
    char choice;
    cin >> choice;

    // Iterate through each pixel in the image
    for (auto &i : image) {
        for (unsigned char &j : i) {
            if (choice == 'a') {
                // If the user chooses to darken, reduce the pixel intensity by dividing by 2
                j /= 2;
            }
            if (choice == 'b') {
                // If the user chooses to lighten, increase the pixel intensity by dividing by 2 and adding 127
                j = (j / 2) + 127;
            }
        }
    }
}

//const int EDGE_THRESHOLD = 200; // Adjust this threshold to control sensitivity
void detect_edges() {
//    // Create a temporary image to store the edge-detected result
//    unsigned char tempImage[SIZE][SIZE];
//
//    // Define Sobel kernels for horizontal and vertical edge detection
//    int sobelHorizontal[3][3] = {{-1, 0, 1},
//                                 {-2, 0, 2},
//                                 {-1, 0, 1}};
//    int sobelVertical[3][3] = {{-1, -2, -1},
//                               {0,  0,  0},
//                               {1,  2,  1}};
//
//    for (int y = 1; y < SIZE - 1; y++) {
//        for (int x = 1; x < SIZE - 1; x++) {
//
//        }
//    }
//    // Copy the edge-detected image back to the original image
//    for (int y = 0; y < SIZE; y++) {
//        for (int x = 0; x < SIZE; x++) {
//            image[y][x] = tempImage[y][x];
//        }
//    }
}

// enlarge the chosen quarter of image to a 256x256 image
// This function allows the user to enlarge a specific quarter of the image based on their choice.

void enlarge() {
    cout << "Which quarter do you want to enlarge: a) 1   b) 2   c) 3   d) 4 " << fin;
    char choice;
    cin >> choice;

    if (tolower(choice) == 'a') {
        for (int i = 0; i < 128; ++i) {
            for (int j = 0; j < 128; ++j) {
                // Calculate the coordinates in the enlarged image (image3)
                int x = i * 2;
                int y = j * 2;

                // Enlarge the pixel from the top-left quarter
                image3[x][y] = image[i][j];
                image3[x][y + 1] = image[i][j];
                image3[x + 1][y] = image[i][j];
                image3[x + 1][y + 1] = image[i][j];
            }
        }
        // copy the enlarged image back to the original image.
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image3[i][j];
            }
        }
    }

    // Continue similar logic for the other quarters (b, c, d)...

    // If the user chooses 'b', 'c', or 'd', the appropriate quarter is enlarged.
}


// shrink the image to (1/2 , 1/3 , 1/4)
void shrink() {
    cout << "Do you want to shrink to a) 1/2  b) 1/3  c) 1/4" << fin;
    char choice;
    cin >> choice;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image3[i][j] = image[i][j];
            image[i][j] = 255;
        }
    }
    int row = 0;
    int column;
    if (tolower(choice) == 'a') { // reduce the image to 1/2
        // row = 0;
        for (int i = 0; i < SIZE - 2; i += 2) {
            column = 0;
            for (int j = 0; j < SIZE - 2; j += 2) {
                image[row][column] = (image3[i][j] + image3[i][j + 1] + image3[i + 1][j] + image3[i + 1][j + 1]) / 4;
                column++;
            }
            row++;
        }
    } else if (tolower(choice) == 'b') { // reduce image to 1/3
        // row = 0; //take the average of 9 adjacent pixels together
        for (int i = 0; i < SIZE - 2; i += 3) {
            column = 0;
            for (int j = 0; j < SIZE - 2; j += 3) {
                image[row][column] =
                        (image3[i][j] + image3[i + 1][j] + image3[i + 2][j] + image3[i + 1][j] + image3[i + 1][j + 1] +
                         image3[i + 1][j + 2] + image3[i + 2][j] + image3[i + 2][j + 1] + image3[i + 2][j + 2]) / 9;
                column++;
            }
            row++;
        }
    } else if (tolower(choice) == 'c') { // reduce the image to 1/4
        // row = 0; //take the average of 4 adjacent pixels together for two times
        for (int i = 0; i < SIZE - 2; i += 2) {
            column = 0;
            for (int j = 0; j < SIZE - 2; j += 2) {
                image[row][column] = (image3[i][j] + image3[i + 1][j] + image3[i][j + 1] + image3[i + 1][j + 1]) / 4;
                column++;
            }
            row++;
        }
        row = 0;
        for (int i = 0; i < SIZE - 2; i += 2) {
            column = 0;
            for (int j = 0; j < SIZE - 2; j += 2) {
                image[row][column] = (image[i][j] + image[i + 1][j] + image[i][j + 1] + image[i + 1][j + 1]) / 4;
                column++;
            }
            row++;
        }
    }
}

// shuffle the 4 quarters of the 4 quarters of the chosen image based on the user's input
void shuffle() {
    cout << "Enter the order of the quarters for the new image " << fin;
    for (int i = 1; i <= 4; ++i) {
        char quarter;
        cin >> quarter;
        int j, k;
        if (quarter < 49 || quarter > 52) {
            cout << "Invalid answer" << fin;
            shuffle();
        }
        //copy to quarter 1
        if (i == 1) {
            for (j = 0; j < 127; ++j) {
                for (k = 0; k < 127; ++k) {
                    if (quarter == '4')
                        image3[j][k] = image[j + 127][k + 127];
                    else if (quarter == '3')
                        image3[j][k] = image[j + 127][k];
                    else if (quarter == '2')
                        image3[j][k] = image[j][k + 127];
                }
            }
        }

            //copy to quarter 2
        else if (i == 2) {
            for (j = 0; j < 127; ++j) {
                for (k = 127; k < SIZE; ++k) {
                    if (quarter == '4')
                        image3[j][k] = image[j + 127][k];
                    else if (quarter == '3')
                        image3[j][k] = image[j + 127][k - 127];
                    else if (quarter == '1')
                        image3[j][k] = image[j][k - 127];
                }
            }
        }

            //copy to quarter 3
        else if (i == 3) {
            for (j = 127; j < SIZE; ++j) {
                for (k = 0; k < 127; ++k) {
                    if (quarter == '4')
                        image3[j][k] = image[j][k + 127];
                    else if (quarter == '2')
                        image3[j][k] = image[j - 127][k + 127];
                    else if (quarter == '1')
                        image3[j][k] = image[j - 127][k];
                }
            }
        }

            //copy to quarter 4
        else if (i == 4) {
            for (j = 127; j < SIZE; ++j) {
                for (k = 127; k < SIZE; ++k) {
                    if (quarter == '3')
                        image3[j][k] = image[j][k - 127];
                    else if (quarter == '2')
                        image3[j][k] = image[j - 127][k];
                    else if (quarter == '1')
                        image3[j][k] = image[j - 127][k - 127];
                }
            }
        }
    }
    //copy to the original image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image3[i][j];
        }
    }
}

// mirror 1/2 of the image There are 4 options (Left 1/2, Right 1/2, Upper 1/2 and Lower 1/2)
// This function allows the user to mirror a specified half of the image based on their choice.

void mirror() {
    cout << "Which half do you want to mirror? a) Left 1/2  b) Right 1/2  c) Upper 1/2  d) Lower 1/2 " << fin;
    char option;
    cin >> option;

    if (option == 'a') {
        //  mirror the left half of the image.
        for (auto &i : image) {
            for (int j = 127; j < SIZE; ++j) {
                i[j] = i[SIZE - 1 - j];
            }
        }
    } else if (option == 'b') {
        //  mirror the right half of the image.
        for (auto &i : image) {
            for (int j = 127; j < SIZE; ++j) {
                i[SIZE - 1 - j] = i[j];
            }
        }
    } else if (option == 'c') {
        //  mirror the upper half of the image.
        for (int i = 127; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[SIZE - 1 - i][j];
            }
        }
    } else if (option == 'd') {
        // mirror the lower half of the image.
        for (int i = 127; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[SIZE - 1 - i][j] = image[i][j];
            }
        }
    } else {
        cout << "Invalid answer, please retry: ";
        mirror();
    }
}


// blur the image
void blur() {
    // image3 is Temporary image to store the blurred result

    for (int x = 1; x < SIZE - 1; x++) {
        for (int y = 1; y < SIZE - 1; y++) {
            int sum = 0;

            // Apply the 3x3 box blur filter
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    sum += image[x + j][y + i];
                }
            }

            // Set the pixel in the temporary image to the average
            image3[x][y] = (sum / 9);
        }
    }

    // Copy the blurred image back to the original image
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            image[x][y] = image3[x][y];
        }
    }
}

// crop the image based on starting point and dimensions entered by the user
void crop() {
    // copy the original image to temporary one and convert the original to white image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image3[i][j] = image[i][j];
            image[i][j] = 255;
        }
    }
    int x, y; // the position of the pixel where I will start to crop
    cout << "Enter the point to start cropping from (x, y): " << fin;
    cin >> x >> y;
    int l, w; // the dimensions of the cropped image
    cout << "Enter the length and width (l, w): ";
    cin >> l >> w;

    // copy the selected region from the original image to the image3
    for (int i = x; i < x + w; ++i) {
        for (int j = y; j < y + l; ++j) {
            image[i][j] = image3[i][j];
        }
    }
}

void skew_horizontal() {}

void skew_vertical() {}