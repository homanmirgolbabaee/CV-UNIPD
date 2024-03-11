#include <opencv2/opencv.hpp>
#include <iostream>

// Function to set a specific channel to 0
void setChannelToZero(cv::Mat &image, int channelIndex) {
    if (image.channels() == 3 && channelIndex >= 0 && channelIndex < 3) {
        std::vector<cv::Mat> channels;
        cv::split(image, channels); // Split the image into its 3 channels
        channels[channelIndex] = cv::Mat::zeros(image.rows, image.cols, CV_8UC1); // Set the specified channel to 0
        cv::merge(channels, image); // Merge the channels back
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <ImagePath>\n";
        std::cerr << "Error: Image filename shall be provided as a command-line argument." << std::endl;
        return -1;
    }

    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR); // Ensuring the image is loaded as a color image

    if (image.empty()) {
        std::cerr << "Error loading the image. Check if the filename is correct." << std::endl;
        return -1;
    }

    std::cout << "Number of channels in the image: " << image.channels() << std::endl;

    // Checking and manipulating the image based on the number of channels
    if (image.channels() == 3) {
        // Example: Setting the first channel (Blue in BGR) to zero
        setChannelToZero(image, 0); // Try changing this to 1 or 2 for Green or Red channels

        std::cout << "After setting one channel to 0." << std::endl;
    }

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", image);

    char keyPressed = static_cast<char>(cv::waitKey(0));
    std::cout << "Key pressed: " << keyPressed << std::endl;

    return 0;
}

