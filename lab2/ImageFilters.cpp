#include "ImageFilters.h"

// Implement the maxFilter function
cv::Mat maxFilter(const cv::Mat& src, int kernelSize) {
    cv::Mat dst;
    if (kernelSize % 2 == 0) {
        std::cerr << "Kernel size must be odd!" << std::endl;
        return src; // Returning the original image
    }
    // Apply max filtering
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
    cv::dilate(src, dst, kernel);
    return dst;
}

// Implement the minFilter function
cv::Mat minFilter(const cv::Mat& src, int kernelSize) {
    cv::Mat dst;
    if (kernelSize % 2 == 0) {
        std::cerr << "Kernel size must be odd!" << std::endl;
        return src; // Returning the original image
    }
    // Apply min filtering
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
    cv::erode(src, dst, kernel);
    return dst;
}

// Implement the showResizedWindow function
void showResizedWindow(const std::string& winname, const cv::Mat& img, int width, int height) {
    cv::Mat resizedImg;
    cv::resize(img, resizedImg, cv::Size(width, height)); // Resize the image
    cv::imshow(winname, resizedImg); // Show the resized image in a window
}
