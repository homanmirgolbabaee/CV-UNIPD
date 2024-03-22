#include "ImageFilters.h"

int main() {
    cv::Mat img = cv::imread("puppy.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Failed to open image" << std::endl;
        return -1;
    }

    // Apply and display results for median filter and gaussian smoothing
    auto medianFiltered = medianFilter(img, 5); // Example usage
    showResizedWindow("Median Filtered", medianFiltered);

    auto gaussianSmoothed = gaussianSmoothing(img, 5, 1.5); // Example sigma values
    showResizedWindow("Gaussian Smoothed", gaussianSmoothed);

    // Histogram Equalization
    auto histEqualized = histogramEqualization(img);
    showResizedWindow("Histogram Equalized", histEqualized);

    cv::waitKey(0);
    return 0;
}
