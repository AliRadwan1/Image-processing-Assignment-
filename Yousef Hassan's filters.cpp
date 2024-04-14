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

//// Yousef Hassan Abdelgawad Hassan's filters

// The Rotation filter
void rotate_image(Image& image) {
    while (true) {
        // Display rotation options
        cout << "[1]  Rotate 90 degrees\n[2]  Rotate 180 degrees\n[3]  Rotate 270 degrees\n";
        cout << "Please enter your choice: ";
        string choice1;
        getline(cin, choice1);
        string choice = valid_input(choice1);
        if (choice == "1") {
            // Rotate the image 90 degrees clockwise
            Image image2(image.height, image.width);
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        // Rotate pixel values
                        image2(image.height - 1 - j, i, k) = image(i, j, k);
                    }
                }
            }
            // Update image dimensions and copy rotated pixels
            image = image2;
            cout << "The filter has been applied successfully\n";
            // Save the image after applying the filter to a file named "test.png"
            // and open it using the default image viewer
            image.saveImage("test.png");
            system("test.png");
            break;
        }
        else if (choice == "2") {
            // Rotate the image 180 degrees clockwise
            Image image2(image.width, image.height);
            for (int i = (image.width - 1); i >= 0; i--) {
                for (int j = (image.height - 1); j >= 0; j--) {
                    for (int k = 0; k < 3; k++) {
                        // Rotate pixel values
                        image2(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                    }

                }
            }
            // Update image dimensions and copy rotated pixels
            image = image2;
            cout << "The filter has been applied successfully\n";
            // Save the image after applying the filter to a file named "test.png"
            // and open it using the default image viewer
            image.saveImage("test.png");
            system("test.png");
            break;

        }
        else if (choice == "3") {
            // Rotate the image 270 degrees clockwise
            Image image2(image.height, image.width);
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        // Rotate pixel values
                        image2(j, image.width - 1 - i, k) = image(i, j, k);
                    }
                }
            }
            // Update image dimensions and copy rotated pixels
            image = image2;
            cout << "The filter has been applied successfully\n";
            // Save the image after applying the filter to a file named "test.png"
            // and open it using the default image viewer
            image.saveImage("test.png");
            system("test.png");
            break;
        }
        else {
            // Handle invalid input
            cout << "Invalid input. please only enter your choice from 1-3\n";
            continue;
        }
    }
}
// The Invert colors filtr
void invert_image(Image& image)
{
    // Invert the image pixels colors horizontally and vertically
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                // Invert color values
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// Function to apply a frame to an image
void normal_frame(Image& image) {
    // Variables to store the user's choice and the color values for the frame
    string choice1, choice;
    int Rvalue, Gvalue, Bvalue;

    // Continuously prompt the user for their choice of frame color
    while (true) {
        cout << "What is the color of the frame you want?\n";
        cout << "[1] Determining an average color\n";
        cout << "[2] Red\n";
        cout << "[3] Green\n";
        cout << "[4] Blue\n";
        cout << "[5] Yellow\n";
        cout << "[6] Silver\n";
        cout << "[7] Black\n";
        cout << "Please enter your choice between 1-7: ";
        getline(cin, choice1);

        // Validate the user's input choice
        choice = valid_input(choice1);

        // Determine the color values for the frame based on the user's choice
        if (choice == "1") {
            // Calculate the average color of the image
            int sum1 = 0, sum2 = 0, sum3 = 0;
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    sum1 += image(i, j, 0); // Sum of red channel
                    sum2 += image(i, j, 1); // Sum of green channel
                    sum3 += image(i, j, 2); // Sum of blue channel
                }
            }
            // Calculate the average color values
            Rvalue = sum1 / (image.height * image.width);
            Gvalue = sum2 / (image.height * image.width);
            Bvalue = sum3 / (image.height * image.width);
            break;
        }
        else if (choice == "2") {
            // Red frame
            Rvalue = 255;
            Gvalue = 0;
            Bvalue = 0;
            break;
        }
        else if (choice == "3") {
            // Green frame
            Rvalue = 0;
            Gvalue = 128;
            Bvalue = 0;
            break;
        }
        else if (choice == "4") {
            // Blue frame
            Rvalue = 0;
            Gvalue = 0;
            Bvalue = 255;
            break;
        }
        else if (choice == "5") {
            // Yellow frame
            Rvalue = 255;
            Gvalue = 255;
            Bvalue = 0;
            break;
        }
        else if (choice == "6") {
            // Silver frame
            Rvalue = 192;
            Gvalue = 192;
            Bvalue = 192;
            break;
        }
        else if (choice == "7") {
            // Black frame
            Rvalue = 0;
            Gvalue = 0;
            Bvalue = 0;
            break;
        }
        else {
            // If the choice is invalid, prompt the user again
            cout << "Invalid choice.\n";
        }
    }

    // Calculate frame dimensions based on the image size
    int frame_width = (4 * image.width) / 100;
    int frame_height = (4 * image.height) / 100;
    int frame_avg = (frame_width + frame_height) / 2;

    // Create a new image with the frame
    int m = image.width + (2 * frame_avg);
    int n = image.height + (2 * frame_avg);
    Image image2(m, n);

    // Loop through the new image to apply the frame
    for (int i = 0; i < image2.width; i++) {
        for (int j = 0; j < image2.height; j++) {
            // Check if the current pixel is within the frame region
            if ((i < frame_avg) || (j < frame_avg) || i >= (image2.width - frame_avg) || j >= (image2.height - frame_avg)) {
                // Set the pixel color to the chosen frame color
                image2(i, j, 0) = Rvalue;
                image2(i, j, 1) = Gvalue;
                image2(i, j, 2) = Bvalue;
            }
            else {
                // Copy the original image pixel values to the new image within the non-frame region
                for (int k = 0; k < 3; k++) {
                    image2(i, j, k) = image(i - frame_avg, j - frame_avg, k);
                }
            }
        }
    }

    // Update the original image with the new image that includes the frame
    image = image2;
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// Function to apply a fancy frame to an image
void fancy_frame(Image& image) {
    // Variables to store the user's choice and the color values for the frame
    string choice1, choice;
    int Rvalue, Gvalue, Bvalue;

    // Continuously prompt the user for their choice of frame color
    while (true) {
        cout << "What is the color of the frame you want?\n";
        cout << "[1] Determining an average color\n";
        cout << "[2] Red\n";
        cout << "[3] Green\n";
        cout << "[4] Blue\n";
        cout << "[5] Yellow\n";
        cout << "[6] Silver\n";
        cout << "[7] Black\n";
        cout << "Please enter your choice between 1-7: ";
        getline(cin, choice1);

        // Validate the user's input choice
        choice = valid_input(choice1);

        // Determine the color values for the frame based on the user's choice
        if (choice == "1") {
            // Calculate the average color of the image
            int sum1 = 0, sum2 = 0, sum3 = 0;
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    sum1 += image(i, j, 0); // Sum of red channel
                    sum2 += image(i, j, 1); // Sum of green channel
                    sum3 += image(i, j, 2); // Sum of blue channel
                }
            }
            // Calculate the average color values
            Rvalue = sum1 / (image.height * image.width);
            Gvalue = sum2 / (image.height * image.width);
            Bvalue = sum3 / (image.height * image.width);
            break;
        }
        else if (choice == "2") {
            // Red frame
            Rvalue = 255;
            Gvalue = 0;
            Bvalue = 0;
            break;
        }
        else if (choice == "3") {
            // Green frame
            Rvalue = 0;
            Gvalue = 128;
            Bvalue = 0;
            break;
        }
        else if (choice == "4") {
            // Blue frame
            Rvalue = 0;
            Gvalue = 0;
            Bvalue = 255;
            break;
        }
        else if (choice == "5") {
            // Yellow frame
            Rvalue = 255;
            Gvalue = 255;
            Bvalue = 0;
            break;
        }
        else if (choice == "6") {
            // Silver frame
            Rvalue = 192;
            Gvalue = 192;
            Bvalue = 192;
            break;
        }
        else if (choice == "7") {
            // Black frame
            Rvalue = 0;
            Gvalue = 0;
            Bvalue = 0;
            break;
        }
        else {
            // If the choice is invalid, prompt the user again
            cout << "Invalid choice.\n";
        }
    }

    // Calculate the dimensions of the outer frame
    int frame_width = (3 * image.width) / 100;
    int frame_height = (3 * image.height) / 100;
    int frame_avg = (frame_width + frame_height) / 2;

    // Calculate the dimensions of the inner frame
    int fm_w = (2 * image.width) / 100;
    int fm_h = (2 * image.height) / 100;
    int fm_avg = (fm_w + fm_h) / 2;

    // Calculate the dimensions of the new image (original image plus frames)
    int m = image.width + (2 * frame_avg) + (2 * fm_avg);
    int n = image.height + (2 * frame_avg) + (2 * fm_avg);
    Image image2(m, n);

    // Loop through the new image to apply the frames
    for (int i = 0; i < image2.width; i++) {
        for (int j = 0; j < image2.height; j++) {
            // Check if the current pixel is within the outer frame region
            if ((i < frame_avg) || (j < frame_avg) || i >= (image2.width - frame_avg) || j >= (image2.height - frame_avg)) {
                // Set the pixel color to the chosen frame color
                image2(i, j, 0) = Rvalue;
                image2(i, j, 1) = Gvalue;
                image2(i, j, 2) = Bvalue;
            }
            // Check if the current pixel is within the inner frame region
            else if (i < (fm_avg + frame_avg) || j < (fm_avg + frame_avg) || i >= (image2.width - (fm_avg + frame_avg)) || j >= (image2.height - (fm_avg + frame_avg))) {
                // Set the pixel color of the inner frame to white (255, 255, 255)
                for (int k = 0; k < 3; k++) {
                    image2(i, j, k) = 255;
                }
            }
            // Otherwise, copy the original image pixel values within the non-frame region
            else {
                for (int k = 0; k < 3; k++) {
                    image2(i, j, k) = image(i - (frame_avg + fm_avg), j - (frame_avg + fm_avg), k);
                }
            }
        }
    }

    // Calculate the size of the overlap between the inner and outer frames
    int sum = frame_avg + fm_avg;

    // Apply a white corner decoration to the image
    for (int i = 0; i < sum; i++) {
        for (int j = 0; j < sum; j++) {
            for (int k = 0; k < 3; k++) {
                // Top-left, top-right, bottom-left, and bottom-right corners
                image2(i, j, k) = 255;
                image2(i, image2.height - 1 - j, k) = 255;
                image2(image2.width - 1 - i, j, k) = 255;
                image2(image2.width - 1 - i, image2.height - 1 - j, k) = 255;
            }
        }
    }

    // Update the original image with the new image that includes the frames
    image = image2;
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// Function to apply an infrared filter to an image
void infrared_filter(Image& image) {
    // Step 1: Convert the image to grayscale by averaging the RGB values of each pixel
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned avg = 0;
            // Calculate the average of the RGB channels for the current pixel
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);
            }
            avg /= 3; // Average the RGB values

            // Set all three color channels (R, G, B) to the average value (grayscale)
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = avg;
            }
        }
    }

    // Step 2: Apply an infrared filter effect
    // Loop through each pixel of the image
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            // Modify the color channels based on the infrared filter effect
            for (int k = 0; k < 3; k++) {
                if (k == 0) {
                    // Set the red channel to the maximum value (255)
                    image(i, j, k) = 255;
                }
                else {
                    // Invert the green and blue channels by subtracting their value from 255
                    image(i, j, k) = 255 - image(i, j, k);
                }
            }
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// Function to apply a blur filter to an image
void blur_filter(Image& image) {
    int radius;

    // Ask the user for the desired level of blur
    while (true) {
        cout << "What level of blur do you want?\n";
        cout << "[1] Light\n[2] Medium\n[3] Heavy\n";
        string choice1;
        string choice;
        cout << "Please enter your choice: ";
        getline(cin, choice1);
        choice = valid_input(choice1);

        // Determine the blur radius based on the user's choice
        if (choice == "1") {
            radius = round(0.01 * (image.width + image.height));
            break;
        }
        else if (choice == "2") {
            radius = round(0.02 * (image.width + image.height));
            break;
        }
        else if (choice == "3") {
            radius = round(0.04 * (image.width + image.height));
            break;
        }
        else {
            cout << "Invalid input\n";
        }
    }

    cout << "This might take few seconds\n";

    // Create a 3D vector to store the summed area table for the image
    vector<vector<vector<int>>> table(image.height, vector<vector<int>>(image.width, vector<int>(image.channels)));

    // Compute the summed area table (integral image) for the image
    // Initialize the top-left corner of the table with the image's pixel values
    for (int k = 0; k < 3; k++) {
        table[0][0][k] = image(0, 0, k);
    }

    // Fill in the first row of the summed area table
    for (int i = 1; i < image.width; i++) {
        for (int k = 0; k < 3; k++) {
            table[0][i][k] = image(i, 0, k) + table[0][i - 1][k];
        }
    }

    // Fill in the first column of the summed area table
    for (int j = 1; j < image.height; j++) {
        for (int k = 0; k < 3; k++) {
            table[j][0][k] = image(0, j, k) + table[j - 1][0][k];
        }
    }

    // Fill in the rest of the summed area table using the previously calculated values
    for (int i = 1; i < image.width; i++) {
        for (int j = 1; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                table[j][i][k] = image(i, j, k) + table[j - 1][i][k] + table[j][i - 1][k] - table[j - 1][i - 1][k];
            }
        }
    }

    // Apply the box blur filter to the image
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            // Calculate the region of interest around the current pixel based on the blur radius
            int min_horizontal = max(i - radius, 0);
            int max_horizontal = min(i + radius, image.width - 1);
            int min_vertical = max(j - radius, 0);
            int max_vertical = min(j + radius, image.height - 1);

            // Calculate the area of the matrix (number of pixels in the region of interest)
            int matrix_area = (max_horizontal - min_horizontal + 1) * (max_vertical - min_vertical + 1);

            // Apply the blur filter to each color channel (RGB) based on the sum of the pixels in the region of interest
            for (int k = 0; k < 3; k++) {
                int sum1;
                int sum2 = 0;
                int sum3 = 0;
                int sum4 = 0;
                sum1 = table[max_vertical][max_horizontal][k];

                if (min_horizontal > 0) {
                    sum2 = table[max_vertical][min_horizontal - 1][k];
                }

                if (min_vertical > 0) {
                    sum3 = table[min_vertical - 1][max_horizontal][k];
                }

                if (min_vertical > 0 && min_horizontal > 0) {
                    sum4 = table[min_vertical - 1][min_horizontal - 1][k];
                }
                int sum = sum1 - sum2 - sum3 + sum4;

                // Calculate the average and set the pixel value in the image
                image(i, j, k) = round(double(sum) / matrix_area);
            }
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}


int main() {

    return 0;
}

