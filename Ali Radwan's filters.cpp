#include <iostream>
#include <string>
#include<cmath>
#include<algorithm>
#include "Image_Class.h"

using namespace std;

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
string formatCheck(string name)
{
    while (true)
    {
        getline(cin, name);
        string extention_check;
        if (name.size() >= 4)
        {
            for (int i = name.size() - 4; i < name.size(); i++)
            {
                extention_check += name[i];
            }
            if (extention_check != ".jpg" && extention_check != ".bmp" && extention_check != ".png" && extention_check != ".tga")
            {
                cout << "Specify extension (.jpg/.bmp/.png/.tga) and use only lowercase letters: ";
                continue;
            }
            else
                break;
        }
        else
        {
            cout << "Enter a valid name" << endl;
            extention_check = "";
        }
    }
    return name;
}
bool isPositiveInteger(const string& str)
{
    for (char c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return !str.empty();
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
string getValidImageName()
{
    string name;
    while (true)
    {
        cout << "Please enter the image name (with extension .jpg, .bmp, .png, .tga): ";
        getline(cin, name);
        string extension = name.substr(name.find_last_of('.') + 1);
        if (extension == "jpg" || extension == "bmp" || extension == "png" || extension == "tga")
        {
            return name;
        }
        cout << "Invalid extension. Please try again." << endl;
    }
}
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


int main()
{
    
    return 0;
}
