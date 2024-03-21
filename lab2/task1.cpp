#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // Check if an image name was provided
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <ImageName>" << std::endl;
        return 1;
    }

    // Construct the path to the input image within the "/images" directory
    std::string imageName = argv[1];
    std::string imagePath = "Images/" + imageName;

    // Load the image
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    // Show the loaded image
    cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original Image", image);
    cv::waitKey(0); // Wait for a key press

    // Convert the image to grayscale
    cv::Mat imageGray;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);

    // Construct the path for saving the grayscale image
    // Extract the file name without extension
    size_t lastindex = imageName.find_last_of(".");
    std::string rawName = imageName.substr(0, lastindex);
    std::string grayImagePath = "/images/" + rawName + "_grayscale.jpg";

    // Save the grayscale image
    cv::imwrite(grayImagePath, imageGray);

    // Optionally, show the grayscale image
    cv::namedWindow("Grayscale Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Grayscale Image", imageGray);
    cv::waitKey(0); // Wait for a key press

    return 0;
}
