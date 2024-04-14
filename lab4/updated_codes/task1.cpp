#include <opencv2/opencv.hpp>
#include <string>

// Struct to hold image and trackbar values
struct UserData {
    cv::Mat img;
    int lowerThreshold;
    int upperThreshold;
};

// Function to apply Canny edge detection and display the result
void on_trackbar(int, void* userData) {
    // Retrieve user data
    UserData* data = static_cast<UserData*>(userData);

    // Retrieve trackbar values
    int lowerThreshold = data->lowerThreshold;
    int upperThreshold = data->upperThreshold;

    // Apply Canny edge detection
    cv::Mat edges;
    cv::Canny(data->img, edges, lowerThreshold, upperThreshold);

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
    UserData data = {img, lowerThreshold, upperThreshold};
    cv::createTrackbar("Lower Threshold", "Edges", &data.lowerThreshold, 255, on_trackbar, &data);
    cv::createTrackbar("Upper Threshold", "Edges", &data.upperThreshold, 255, on_trackbar, &data);

    // Call the function to initialize the display
    on_trackbar(0, &data);

    // Wait for the user to exit
    cv::waitKey(0);
    return 0;
}

