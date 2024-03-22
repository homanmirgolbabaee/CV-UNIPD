#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Load the image
    Mat image = imread("Images/Garden.jpg");
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Display the original image
    imshow("Original Image", image);
    waitKey(0);

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Save the grayscale image
    imwrite("Garden_grayscale.jpg", grayImage);

    // Display the grayscale image
    imshow("Grayscale Image", grayImage);
    waitKey(0);

    return 0;
}
