#include "ImageFilters.h"

// Include this header for histogram functions
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// Declare the filtering functions
cv::Mat maxFilter(const cv::Mat& src, int kernelSize);
cv::Mat minFilter(const cv::Mat& src, int kernelSize);


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

// Implement medianFilter using OpenCV's medianBlur
cv::Mat medianFilter(const cv::Mat& src, int kernelSize) {
    cv::Mat dst;
    cv::medianBlur(src, dst, kernelSize);
    return dst;
}

// Implement gaussianSmoothing using OpenCV's GaussianBlur
cv::Mat gaussianSmoothing(const cv::Mat& src, int kernelSize, double sigmaX, double sigmaY) {
    cv::Mat dst;
    cv::GaussianBlur(src, dst, cv::Size(kernelSize, kernelSize), sigmaX, sigmaY);
    return dst;
}

// Task 5 and 6 related to histogram are more complex to implement directly here due to the plotting.
// However, you can perform histogram equalization directly.
cv::Mat histogramEqualization(const cv::Mat& src) {
    cv::Mat dst;
    cv::equalizeHist(src, dst);
    return dst;
}




void calculateHistogram(const cv::Mat& src, cv::Mat& hist, int histSize = 256) {
    // Set the ranges (for B,G,R channels, if applicable)
    float range[] = {0, 256};
    const float* histRange[] = {range};

    // Calculate the histogram
    cv::calcHist(&src, 1, 0, cv::Mat(), hist, 1, &histSize, histRange, true, false);

    // Normalize the result to [0, 255]
    cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX);
}




// New implementation for plotHistogram
void plotHistogram(const cv::Mat& src, const std::string& title) {
    
    // Number of bins
    int histSize = 256;
    float range[] = {0, 256}; //the upper boundary is exclusive
    const float* histRange = {range};
    bool uniform = true, accumulate = false;
    cv::Mat hist;

    // Calculate the histogram for the grayscale image
    calcHist(&src, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

    // Create an image to display the histogram
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0,0,0));

    // Normalize the result to [0, histImage.rows]
    normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    // Draw for each channel
    for(int i = 1; i < histSize; i++) {
        line(histImage, cv::Point(bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1))),
             cv::Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
             cv::Scalar(255, 0, 0), 2, 8, 0);
    }

    // Display
    cv::imshow(title, histImage); 
}


