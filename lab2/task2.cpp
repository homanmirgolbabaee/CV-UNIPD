#include <opencv2/opencv.hpp>
#include "ImageFilters.h"

int main() {
    cv::Mat img = cv::imread("Garden_grayscale.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Image not found!" << std::endl;
        return -1;
    }

    // Apply max and min filters with various kernel sizes
    std::vector<int> kernelSizes = {3, 5, 7}; // Example sizes
    for (int size : kernelSizes) {
        cv::Mat maxFiltered = maxFilter(img, size);
        cv::Mat minFiltered = minFilter(img, size);

        // Display the original and filtered images using the showResizedWindow function
        // For the original image, it might make sense to only show it once, not in the loop
        if (size == kernelSizes.front()) { // Only display the original image once, at the beginning
            showResizedWindow("Original Image", img);
        }

        // For filtered images, display them with their corresponding kernel size mentioned
        showResizedWindow("Max Filtered (Kernel Size " + std::to_string(size) + ")", maxFiltered);
        showResizedWindow("Min Filtered (Kernel Size " + std::to_string(size) + ")", minFiltered);
    }

    cv::waitKey(0); // Wait for a key press to close the windows
    return 0;
}
