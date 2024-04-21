#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    // Load the image
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if(image.empty()) {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }

    // Adaptive Threshold
    cv::Mat thresholdImg;
    cv::adaptiveThreshold(image, thresholdImg, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 
                          cv::THRESH_BINARY_INV, 11, 2);

    // Morphological opening to remove noise
    cv::Mat kernelNoise = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    cv::Mat openingImg;
    cv::morphologyEx(thresholdImg, openingImg, cv::MORPH_OPEN, kernelNoise);

    // Dilation to enhance the cracks
    cv::Mat kernelDilation = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 6));
    cv::Mat dilatedImg;
    cv::dilate(openingImg, dilatedImg, kernelDilation);

    // Save or show the result
    cv::imwrite("segmented_cracks.png", dilatedImg);
    cv::imshow("Segmented Cracks", dilatedImg);
    cv::waitKey(0);

    return 0;
}
