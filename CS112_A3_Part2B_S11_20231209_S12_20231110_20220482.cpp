/*File name : CS112_A3_Part2B_S11_20231209_S12_20231110_20220482.cpp
  purpose: This program takes an image from the user and apply different filters on it

  Authors: 1- Ali Radwan Farouk Ahmad - id:20231110 - section:12  - He did filter 2 (Black and White), filter 5 (Flip Image), filter 8 (Crop),
           filter 11 (Resize) and filter 13 (Sunlight)

           2- Yousef Hassan Abdelgawad Hassan - id:20231209 - section:11 - He did filter 3 (Invert Image), filter 6 (Rotate Image),
           filter 9 (Adding a Frame to the Picture), filter 12 (Blur), filter 17 (Infrared)

           3- Abdallah Tarek Eid Mohamed - id: 20220482 - section:12 - He did filter 1 (Grayscale Conversion), filter 4 (Merge),
           filter 7 (Darken and Lighten Image), filter 16 (Purpler filter)

           Yousef and Abdallah collaborated on filter 10 (Detect Image Edges)

  GitHub repository link:  https://github.com/AliRadwan1/Assignment3

  System Diagram link: https://drive.google.com/file/d/1xwLBQWYXGitOqVcExf5WPYaslM38Yqug/view?usp=drive_link
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cctype>
#include <sstream>
#include "Image_Class.h"

using namespace std;

// Function to check if the input is digit
static bool alldigit(string num) //Checks if the input is a number
{
    if (num.empty())
    {
        return false;
    }
    int start = 0;
    if (num[0] == '-')
    {
        start = 1;
    }
    for (int i = start; i < num.size(); i++)
    {
        if (!isdigit(num[i]))
        {
            return false;
        }
    }
    return true;
}
// Function to check if the input is postive number
bool isPositiveInteger(const string& str)
{
    for (char c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return !str.empty();
}
bool isFloat(const string& str) {
    istringstream iss(str);
    float f;
    // Try to extract a float from the string
    iss >> noskipws >> f;
    // Check if the entire string was consumed and if there are no other characters left
    // Also check if the next character is the end of file (EOF)
    return iss.eof() && !iss.fail() && iss.peek() == EOF;
}
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
// Function to check the format of the image name input
string formatCheck(string name)
{
    while (true)
    {
        getline(cin, name);
        string extension_check;
        if (name.size() >= 4)
        {
            extension_check = name.substr(name.size() - 4);
            if (extension_check == ".jpg" || extension_check == ".bmp" || extension_check == ".png" || extension_check == ".tga")
                break;
        }
        cout << "Enter a valid name with extension (.jpg/.bmp/.png/.tga): ";
    }
    return name;
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


//// Ali Radwan Farouk Ahmad's filtrs

// The Black and white filtr
void black_and_white(Image& image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0; // Initialize average value
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k); // Accumulate pixel values
            }
            avg /= 3; // Calculate average
            if (avg > 127)
            {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
            else
            {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// The  Flip (Mirror) filtr
void mirror(Image& image)
{
    while (true)
    {
        string mirror_choice1;
        cout << "Which way do you want to flip it:\n1) Horizontally\n2) Vertically\nChoose(1/2): ";
        getline(cin, mirror_choice1);
        string mirror_choice = valid_input(mirror_choice1);

        if (mirror_choice == "1")
        {
            // Vertical mirror
            for (int i = 0; i < image.width / 2; i++)
            {
                for (int j = 0; j < image.height; j++)
                {
                    swap(image(i, j, 0), image(image.width - 1 - i, j, 0));
                    swap(image(i, j, 1), image(image.width - 1 - i, j, 1));
                    swap(image(i, j, 2), image(image.width - 1 - i, j, 2));
                }
            }
            break;
        }
        else if (mirror_choice == "2")
        {
            // Horizontal mirror
            for (int i = 0; i < image.width; i++)
            {
                for (int j = 0; j < image.height / 2; j++)
                {
                    swap(image(i, j, 0), image(i, image.height - 1 - j, 0));
                    swap(image(i, j, 1), image(i, image.height - 1 - j, 1));
                    swap(image(i, j, 2), image(i, image.height - 1 - j, 2));
                }
            }
            break;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");

}
// The Sun effect fiter
void SunEffect(Image& image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            image(i, j, 0) = min(255, image(i, j, 0) + 50);
            image(i, j, 1) = min(255, image(i, j, 1) + 50);
            image(i, j, 2) = image(i, j, 2) / 1.25;
            for (int k = 0; k < 2; k++)
            {
                image(i, j, k) = max(0, image(i, j, k) - 20);
            }
        }
    }
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    //and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// The Crop filter
void Croping(Image& image)
{
    string widstart, widend, heistart, heiend;
    int t = 1;
    while (true)
    {
        if (t == 1) // Checks if the width of the start pixel is a positve number
        {
            cout << "Enter the first width pixel: ";
            cin >> widstart;
            if (alldigit(widstart))
            {
                if (stoi(widstart) > 0)
                    t++;
                else
                {
                    cout << "Please enter a positive number" << endl;
                    continue;
                }
            }
        }
        if (t == 2)// Checks if the width of the end pixel is a positve number
        {
            cout << "Enter the end of width pixel: ";
            cin >> widend;
            if (alldigit(widend))
            {
                if (stoi(widend) > 0)
                    t++;
                else
                {
                    cout << "Please enter a positive number" << endl;
                    continue;
                }
            }
        }
        if (t == 3)// Checks if the Height of the start pixel is a positve number
        {
            cout << "Enter the first height pixel: ";
            cin >> heistart;
            if (alldigit(heistart))
            {
                if (stoi(heistart) > 0)
                    t++;
                else
                {
                    cout << "Please enter a positive number" << endl;
                    continue;
                }
            }
        }
        if (t == 4)// Checks if the Height of the end pixel is a positve number
        {
            cout << "Enter the end of height pixel: ";
            cin >> heiend;
            if (alldigit(heiend))
            {
                if (stoi(heiend) > 0)
                    t++;
                else
                {
                    cout << "Please enter a positive number" << endl;
                    continue;
                }
            }
        }
        // Checks if the place of the photo that the user inputs is in the image not out of range
        if (stoi(widstart) < 0 || stoi(widend) > image.width || stoi(heistart) < 0 || stoi(heiend) > image.height || stoi(widstart) >= stoi(widend) || stoi(heistart) >= stoi(heiend))
        {
            cerr << "Error: Invalid crop region coordinates." << endl;
            t = 1;
        }
        if (t == 5)
            break;
    }

    int cropWidth = stoi(widend) - stoi(widstart), cropHeight = stoi(heiend) - stoi(heistart);
    // Creat a new image
    Image cropped(cropWidth, cropHeight);
    // Crop the part of the image wanted into the new image
    for (int y = 0; y < cropWidth; ++y)
    {
        for (int x = 0; x < cropHeight; ++x)
        {
            cropped(y, x, 0) = image(y + stoi(widstart), x + stoi(heistart), 0);
            cropped(y, x, 1) = image(y + stoi(widstart), x + stoi(heistart), 1);
            cropped(y, x, 2) = image(y + stoi(widstart), x + stoi(heistart), 2);
        }
    }
    image = cropped;
    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
}
// The Resize filter
void Resize(Image& image)
{
    int newWidth, newHeight;
    string resized_width, resized_height;
    string choice;
    while (true)
    {
        cout << "Do you want to:\n[1] Enter the new size\n[2] Enter a ratio to resize\nEnter your choice (1/2): ";
        getline(cin, choice);
        if (choice == "1")
        {
            while (true) { // Checks if input is a positive int
                cout << "Enter the new width: ";
                getline(cin, resized_width);
                if (!isPositiveInteger(resized_width) || stoi(resized_width) == 0) {
                    cout << "Please enter a positive integer." << endl;
                    continue;
                }
                break;
            }

            while (true) {// Checks if input is a positive int
                cout << "Enter the new height: ";
                getline(cin, resized_height);
                if (!isPositiveInteger(resized_height) || stoi(resized_height) == 0) {
                    cout << "Please enter a positive integer." << endl;
                    continue;
                }
                break;
            }
            newWidth = stoi(resized_width);
            newHeight = stoi(resized_height);
            break;
        }
        else if (choice == "2")
        {
            string Rat_w, Rat_h;
            int ratio_w = 0, ratio_h = 0; // Initialize ratio_w and ratio_h
            while (true)
            {
                cout << "Enter the Ratio of width to use in percentage (without %): ";
                getline(cin, Rat_w);
                if (!isFloat(Rat_w) || stoi(Rat_w) == 0)
                {
                    cout << "Please enter a positive number." << endl;
                    continue;
                }
                cout << "Enter the Ratio of height to use in percentage (without %): ";
                getline(cin, Rat_h);
                if (!isFloat(Rat_h) || stoi(Rat_h) == 0)
                {
                    cout << "Please enter a positive number." << endl;
                    continue;
                }
                ratio_w = stoi(Rat_w); // Assign value to ratio_w
                ratio_h = stoi(Rat_h); // Assign value to ratio_h
                break;
            }
            // Cast to double to avoid loss of data in calculations
            newWidth = static_cast<unsigned int>((image.width * ratio_w) / 100.0);
            newHeight = static_cast<unsigned int>((image.height * ratio_h) / 100.0);
            break;
        }

        else
        {
            cout << "Please enter a valid choice" << endl;
        }
    }
    // Calculate scaling factors
    float scaleX = static_cast<float>(image.width) / newWidth;
    float scaleY = static_cast<float>(image.height) / newHeight;
    // Create a new image to store the resized image
    Image resizedImage(newWidth, newHeight);

    // Resize the image
    for (int i = 0; i < newWidth; ++i)
    {
        for (int j = 0; j < newHeight; ++j)
        {
            // Calculate corresponding coordinates in the original image
            int srcX = static_cast<int>(i * scaleX);
            int srcY = static_cast<int>(j * scaleY);
            // Map the pixel from the original image to the resized image
            for (int c = 0; c < 3; ++c)
            {
                resizedImage(i, j, c) = image(srcX, srcY, c);
            }
        }
    }
    image = resizedImage;

    cout << "The filter has been applied successfully\n";
    // Save the image after applying the filter to a file named "test.png"
    // and open it using the default image viewer
    image.saveImage("test.png");
    system("test.png");
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

// Function to save the image
void save_image(Image& image, string image_name) {
    while (true) {
        cout << "How do you want to save your image?\n";
        cout << "[1] Save the image on the same file name\n";
        cout << "[2] Save the image and change file name\n";
        cout << "Please enter your choice between 1-2: ";
        string choice2;
        getline(cin, choice2);
        string choice = valid_input(choice2);
        if (choice == "1") { // saves the image on the same file name
            cout << "Image has been saved successfully\n";
            image.saveImage(image_name);
            system(image_name.c_str());
            break;
        }
        else if (choice == "2") { // saves the image as copy with a new file name
            string save_name;
            cout << "Name the image file with the extention (.png, .tga, .jpg, .bmp) to save it : ";
            save_name = formatCheck("");
            image.saveImage(save_name);
            cout << "Image has been saved successfully\n";
            system(save_name.c_str());
            break;
        }
        else {
            cout << "Invalid choice\n";
            continue;
        }
    }
}

int main()
{
    string image_name;

    Image image;
    while (true)
    { // Checks if the image the user entered exists and with the extension
        cout << "Please enter the name of the image file with extension (.png, .tga, .jpg, .bmp)\n";
        getline(cin, image_name);
        try {
            image.loadNewImage(image_name);
            break;
        }
        catch (invalid_argument&) {
        }
    }

    while (true)
    { // Displaying the options
        cout << "-------------------------------------------------------------------------------------------\n";
        cout << "Welcome to Baby Photoshop Program\n";
        cout << "Choose the filter you want\n";
        cout << "[1] Grayscale Conversion\n[2] Black and White\n[3] Invert Image\n[4] Merge Images\n[5] Flip Image\n";
        cout << "[6] Rotate Image\n[7] Darken and Lighten Image\n[8] Crop Images\n[9] Adding a Frame to the Picture\n";
        cout << "[10] Detect Image Edges\n[11] Resizing Images\n[12] Blur Images\n";
        cout << "[13] Sun Effect\n[14] Purple Effect\n[15] Infrared Filter\n";
        cout << "[16] Save The Image\n[17] Upload New Image\n[18] EXIT\n";
        cout << "Please enter your choice: ";
        string choice1;
        getline(cin, choice1);
        cout << "-------------------------------------------------------------------------------------------\n";
        string choice = valid_input(choice1);
        if (choice == "1") // Applying Gray filter
        {
            grayscale_conversion(image);
        }
        else if (choice == "2") // Applying Black and White filter
        {
            black_and_white(image);
        }
        else if (choice == "3") // Applying Invert colors filter
        {
            invert_image(image);
        }
        else if (choice == "4") // Applying merge filter
        {
            string image1_name;

            Image image2;
            while (true)
            { // Checks if the image the user entered exists and with the extension
                cout << "Please enter the name of the second image file with extension (.png, .tga, .jpg, .bmp)\n";
                getline(cin, image1_name);
                try {
                    image2.loadNewImage(image1_name);
                    break;
                }
                catch (invalid_argument&) {
                }
            }
            while (true) {

                cout << "Choose an option:\n";
                cout << "[1] Resize both images to the largest width and height.\n";
                cout << "[2] Merge the common area of the smaller width and height.\n";
                cout << "Enter your option: ";
                string option;
                string option1;
                getline(cin, option1);
                option = valid_input(option1);
                if (option == "1") {
                    mergeImages(image, image2);
                    break;
                }
                else if (option == "2") {
                    Image mergedImage(min(image.width, image2.width), min(image.height, image2.height));
                    mergeCommonArea(image, image2, mergedImage);
                    break;
                }
                else {
                    cout << "Invalid choice\n";
                }
            }

        }
        else if (choice == "5") // Applying flip filter
        {
            mirror(image);
        }
        else if (choice == "6") // Applying rotate filter
        {
            rotate_image(image);
        }
        else if (choice == "7") // Applying Darken and Lighten filter
        {
            adjustBrightness(image);
        }
        else if (choice == "8") // Applying Crop
        {
            Croping(image);
        }
        else if (choice == "9") // Applying frame filter
        {
            while (true) {
                cout << "What type of frame do you want?\n";
                cout << "[1] Normal Frame\n[2] Fancy Frame\n";
                cout << "Please enter your choice: ";
                string option;
                string option1;
                getline(cin, option1);
                option = valid_input(option1);
                if (option == "1") {
                    normal_frame(image);
                    break;
                }
                else if (option == "2") {
                    fancy_frame(image);
                    break;
                }
                else {
                    cout << "Invalid choice\n";
                }
            }
        }
        else if (choice == "10") // Applying Edge detect filter
        {
            edge_detect(image);
        }
        else if (choice == "11") // Applying Resize filter
        {
            Resize(image);
        }
        else if (choice == "12") // Applying Blur filter
        {
            blur_filter(image);
        }
        else if (choice == "13") // Applying Sun Effect filter
        {
            SunEffect(image);
        }
        else if (choice == "14") // Applying Purple Effect filter
        {
            PurpleFilter(image);
        }
        else if (choice == "15") // Applying Infrared filter
        {
            infrared_filter(image);
        }
        else if (choice == "16") // Save the image
        {
            save_image(image, image_name);
        }
        else if (choice == "17") // Upload a new image
        {
            while (true)
            { // Asks the user if he wants to save the image he was working on
                cout << "Do you want to save the save the current image before loading a new one?\n";
                cout << "[1] YES\n";
                cout << "[2] NO\n";
                cout << "please enter your choice: ";
                string option1;
                getline(cin, option1);
                string option = valid_input(option1);
                if (option == "1")  // Save the image
                {
                    save_image(image, image_name); // Saveing the image
                    while (true) // Uploading the new image
                    {
                        Image image2;
                        cout << "Please enter the name of the image file with extension (.png, .tga, .jpg, .bmp)\n";
                        getline(cin, image_name);
                        try {
                            image2.loadNewImage(image_name);
                            image = image2;
                            break;
                        }
                        catch (invalid_argument&) {
                        }
                    }
                    break;
                }
                else if (option == "2") // Uploads the new image without saveing the old one
                {
                    while (true)
                    {
                        Image image2;
                        cout << "Please enter the name of the image file with extension (.png, .tga, .jpg, .bmp)\n";
                        getline(cin, image_name);
                        try {
                            image2.loadNewImage(image_name);
                            // Update image dimensions and copy rotated pixels
                            image = image2;
                            break;
                        }
                        catch (invalid_argument&) {
                        }
                    }
                    break;
                }
                else {
                    cout << "Invalid choice\n";
                    continue;
                }
            }
        }
        else if (choice == "18") // Exit the program
        {
            while (true)
            { // Asks the user if he want to save
                cout << "DO you want to save the image before exiting the program?\n";
                cout << "[1] YES\n[2] NO\n";
                cout << "Please enter your choice: ";
                string user_choice1;
                getline(cin, user_choice1);
                string user_choice = valid_input(user_choice1);
                if (user_choice == "1") // YES
                {
                    save_image(image, image_name); // Save the image
                    cout << "Thanks for using our program\n";
                    cout << "Exiting...\n";
                    break; // Close the program
                }
                else if (user_choice == "2") // NO
                {
                    cout << "Thanks for using our program\n";
                    cout << "Exiting...\n";
                    break; // Close the program
                }
                else
                {
                    cout << "Invalid choice\n";
                    continue;
                }
            }
            break;
        }
        else // Invalid input
        {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
    }
    return 0;
}