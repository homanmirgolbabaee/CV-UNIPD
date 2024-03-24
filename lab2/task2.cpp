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


    // Show the histogram of the original image
    plotHistogram(img, "Histogram Before Equalization");

    // Apply histogram equalization
    cv::Mat histEqualized;
    cv::equalizeHist(img, histEqualized);

    // Show the histogram of the equalized image
    plotHistogram(histEqualized, "Histogram After Equalization");

    // Optionally, show the images themselves for comparison
    cv::imshow("Original Image", img);
    cv::imshow("Equalized Image", histEqualized);


    cv::waitKey(0);
    return 0;
}
