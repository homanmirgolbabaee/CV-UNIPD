#include <opencv2/opencv.hpp>
#include <string>

// Function to apply Canny edge detection and display the result
void on_trackbar(int, void* userData) {
    // Retrieve user data
    cv::Mat* img = reinterpret_cast<cv::Mat*>(userData);

    // Retrieve trackbar values
    int lowerThreshold = cv::getTrackbarPos("Lower Threshold", "Edges");
    int upperThreshold = cv::getTrackbarPos("Upper Threshold", "Edges");

    // Apply Canny edge detection
    cv::Mat edges;
    cv::Canny(*img, edges, lowerThreshold, upperThreshold);

    // Display the result
    cv::imshow("Edges", edges);
}

int main() {
    // Load the image
    cv::Mat img = cv::imread("street_scene.png");
    if (img.empty()) {
        std::cerr << "Error: Unable to open the image file." << std::endl;
        return -1;
    }

    // Create a window
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Edges", cv::WINDOW_AUTOSIZE);

    // Display the original image
    cv::imshow("Original", img);

    // Create the trackbars
    int lowerThreshold = 50;
    int upperThreshold = 150;
    cv::createTrackbar("Lower Threshold", "Edges", &lowerThreshold, 255, on_trackbar, &img);
    cv::createTrackbar("Upper Threshold", "Edges", &upperThreshold, 255, on_trackbar, &img);

    // Call the function to initialize the display
    on_trackbar(0, &img);

    // Wait for the user to exit
    cv::waitKey(0);
    return 0;
}
