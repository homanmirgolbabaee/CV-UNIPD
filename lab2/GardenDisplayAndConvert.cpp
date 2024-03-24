#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Function to resize an image while maintaining its aspect ratio
Mat resizeMaintainingAspectRatio(const Mat& src, int targetWidth, int targetHeight) {
    Mat resized;
    double aspectRatio = static_cast<double>(src.cols) / static_cast<double>(src.rows);
    int width, height;

    if (src.cols > src.rows) {
        // Landscape orientation
        width = targetWidth;
        height = static_cast<int>(targetWidth / aspectRatio);
    } else {
        // Portrait orientation
        height = targetHeight;
        width = static_cast<int>(targetHeight * aspectRatio);
    }

    // Perform the resizing
    resize(src, resized, Size(width, height));
    return resized;
}

int main() {
    // Load the image
    Mat image = imread("../Images/Garden.jpg");
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Prepare the image for display
    Mat displayImage = resizeMaintainingAspectRatio(image, 600, 400); // Adjust target size as needed
    // Display the original image in an appropriate size
    imshow("Original Image", displayImage);
    waitKey(0);

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Save the grayscale image
    imwrite("Garden_grayscale.jpg", grayImage);

    // Prepare the grayscale image for display
    Mat displayGrayImage = resizeMaintainingAspectRatio(grayImage, 600, 400); // Adjust target size as needed
    // Display the grayscale image in an appropriate size
    imshow("Grayscale Image", displayGrayImage);
    waitKey(0);

    return 0;
}
