#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cctype>
#include "Image_Class.h"

using namespace std;

// Function to delete spaces if user inputs them
string valid_input(string user_choice) {
    string user_choice1 = "";
    for (char a : user_choice) {
        if (isspace(a)) {
            continue;
        }
        else {
            user_choice1 += a;
        }
    }
    return user_choice1;
}

//// Abdallah Tarek Eid Mohamed's filtrs

// The Grayscaling filtr
void grayscale_conversion(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// The merge filter
void resizeImage(Image& sourceImage, Image& resizedImage, int targetWidth, int targetHeight) {
    float scaleX = static_cast<float>(sourceImage.width) / targetWidth;      // this is made to resize the source Image to match target Width and heihgt
    float scaleY = static_cast<float>(sourceImage.height) / targetHeight;

    for (int i = 0; i < targetWidth; ++i) {
        for (int j = 0; j < targetHeight; ++j) {
            int srcX = static_cast<int>(i * scaleX);
            int srcY = static_cast<int>(j * scaleY);

            for (int c = 0; c < 3; ++c) {
                resizedImage.setPixel(i, j, c, sourceImage.getPixel(srcX, srcY, c));
            }
        }
    }
}

void mergeImages(Image& image, Image& image2) {
    int largerWidth = max(image.width, image2.width);   // merge two images 1 adn 2
    int largerHeight = max(image.height, image2.height);

    Image resizedImage1(largerWidth, largerHeight);
    Image resizedImage2(largerWidth, largerHeight);

    resizeImage(image, resizedImage1, largerWidth, largerHeight);
    resizeImage(image2, resizedImage2, largerWidth, largerHeight);

    Image mergedImage(largerWidth, largerHeight);

    for (int y = 0; y < largerHeight; ++y) {
        for (int x = 0; x < largerWidth; ++x) {
            for (int c = 0; c < 3; ++c) {
                unsigned char pixel1 = resizedImage1.getPixel(x, y, c);
                unsigned char pixel2 = resizedImage2.getPixel(x, y, c);
                mergedImage.setPixel(x, y, c, (pixel1 + pixel2) / 2);
            }
        }
    }

    image = mergedImage;
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}

void mergeCommonArea(Image& image, Image& image2, Image& mergedImage) {
    int commonWidth = min(image.width, image2.width);              // this is made to merge the common area of image1 and image2
    int commonHeight = min(image.height, image2.height);

    for (int y = 0; y < commonHeight; ++y) {
        for (int x = 0; x < commonWidth; ++x) {
            for (int c = 0; c < 3; ++c) {
                unsigned char pixel1 = image.getPixel(x, y, c);
                unsigned char pixel2 = image2.getPixel(x, y, c);
                mergedImage.setPixel(x, y, c, (pixel1 + pixel2) / 2);
            }
        }
    }
    image = mergedImage;
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// The purple filter
void PurpleFilter(Image& image) {
    for (int j = 0; j < image.height; ++j) {
        for (int i = 0; i < image.width; ++i) {
            // Adjust color channels to emphasize purple
            image(i, j, 0) = min(255, static_cast<int>(image(i, j, 0) * 1.5)); // Increase red component
            image(i, j, 1) = image(i, j, 1) / 2; // Reduce green component
            image(i, j, 2) = min(255, static_cast<int>(image(i, j, 2) * 1.5)); // Increase blue component
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// The Darken and Lighten Image
void adjustBrightness(Image& image) {
    string choice;
    string choice1;
    float factor;
    while (true) {
        cout << "Do you want to make the image brighter or darker? ";// Ask user if they want to make the image brighter or darker
        cout << "[1] Brighter\n[2] Darker\n";
        cout << "Please enter your choice: ";
        getline(cin, choice1);
        choice = valid_input(choice1);
        if (choice == "1") {
            factor = 1.5;
            break;
        }
        else if (choice == "2") {
            factor = 0.5;
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }
    // looping through each pixel in the image
    for (int j = 0; j < image.height; ++j) {
        for (int i = 0; i < image.width; ++i) {
            for (int c = 0; c < image.channels; ++c) {
                // this is made to get the current pixel value
                int pixelValue = image(i, j, c);

                pixelValue = static_cast<int>(pixelValue * factor);

                pixelValue = max(0, min(255, pixelValue));
                // this is made to update the pixel value
                image(i, j, c) = static_cast<unsigned char>(pixelValue);
            }
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// The edge detect filter
void edge_detect(Image& image) {
    cout << "This might take few seconds\n";
    // Step 1: Convert the image to grayscale
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            // Calculate the grayscale value using standard weights for RGB channels
            unsigned avg = round((image(i, j, 0) * 0.299) +
                (image(i, j, 1) * 0.587) +
                (image(i, j, 2) * 0.114));

            // Set all three channels (R, G, B) to the grayscale value
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = avg;
            }
        }
    }
    // Sobel operator kernels
    int horizontal_kernel[3][3] = { {-1, 0, 1},
                                    {-2, 0, 2},
                                    {-1, 0, 1} };
    int vertical_kernel[3][3] = { {1, 2, 1},
                                  {0, 0, 0},
                                  {-1, -2, -1} };

    // Create a copy of the image to hold the Sobel results
    Image sobel_image = image;

    // Step 2: Apply Sobel operator to detect edges
    for (int i = 1; i < image.width - 1; i++) {
        for (int j = 1; j < image.height - 1; j++) {
            for (int k = 0; k < 3; k++) {
                int sum_horizontal = 0;
                int sum_vertical = 0;

                // Compute horizontal and vertical sums using Sobel kernels
                for (int m = -1; m <= 1; m++) {
                    for (int n = -1; n <= 1; n++) {
                        sum_horizontal += horizontal_kernel[m + 1][n + 1] * image(i + m, j + n, k);
                        sum_vertical += vertical_kernel[m + 1][n + 1] * image(i + m, j + n, k);
                    }
                }

                // Calculate magnitude of the gradient
                double magnitude = (sqrt(pow(sum_horizontal, 2) + pow(sum_vertical, 2))) / 2;

                // Thresholding
                if (magnitude > 70) { // Adjust threshold value as needed
                    sobel_image(i, j, k) = 0; // black (edge detected)
                }
                else {
                    sobel_image(i, j, k) = 255; // white (no edge detected)
                }
            }
        }
    }
    image = sobel_image;
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}

int main() {

    return 0;
}

