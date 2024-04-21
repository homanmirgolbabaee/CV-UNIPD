#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    // Check if the image path has been passed as a command-line argument
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <Image_Path>" << std::endl;
        return -1;
    }

    // Load the image in grayscale mode
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if(image.empty()) {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }

    // Apply Otsu's thresholding to binarize the image
    cv::Mat otsuImg;
    cv::threshold(image, otsuImg, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);

    // Morphological closing to enhance the cracks
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 6));
    cv::Mat closedImg;
    cv::morphologyEx(otsuImg, closedImg, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 2);

    // Save and/or display the result
    cv::imwrite("segmented_cracks_otsu.png", closedImg);
    cv::imshow("Segmented Cracks with Otsu's", closedImg);
    cv::waitKey(0);

    return 0;
}
