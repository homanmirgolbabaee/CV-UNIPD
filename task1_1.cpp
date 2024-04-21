#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    // Check for proper argument usage
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }

    // Load the image in grayscale
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }

    // Otsu's thresholding
    cv::Mat otsuImg;
    double otsuThreshold = cv::threshold(image, otsuImg, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    
    // Validate if Otsu's thresholding was successful
    if (otsuThreshold == 0) {
        std::cerr << "Otsu's thresholding failed!" << std::endl;
        return -1;
    }

    // Morphological closing to enhance the cracks
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 6));
    cv::Mat closingOtsuImg;
    cv::morphologyEx(otsuImg, closingOtsuImg, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 2);

    // Save or show the result
    cv::imwrite("segmented_cracks_otsu.png", closingOtsuImg);
    cv::imshow("Segmented Cracks with Otsu's", closingOtsuImg);
    cv::waitKey(0);

    return 0;
}
