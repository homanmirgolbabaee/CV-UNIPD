#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Load the image
    cv::Mat image = cv::imread("Garden.jpg"); // Make sure to use the correct path for the image
    if(image.empty()) {
        std::cout << "Could not read the image: Garden.jpg" << std::endl;
        return 1;
    }
    
    // Display the original image
    cv::imshow("Original Image", image);
    cv::waitKey(0); // Wait for a keystroke in the window

    // Convert to grayscale
    cv::Mat imageGray;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    
    // Save the grayscale image
    cv::imwrite("Garden_grayscale.jpg", imageGray);
    
    std::cout << "The image has been converted to grayscale and saved as Garden_grayscale.jpg" << std::endl;
    
    return 0;
}
