
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

// Function to remove a specified color channel
void removeColorChannel(cv::Mat &image, int channelIndex) {
    if (image.channels() == 3 && channelIndex >= 0 && channelIndex < 3) {
        std::vector<cv::Mat> channels(3);
        // Split the image into its 3 channels
        cv::split(image, channels);
        // Set the specified channel to zero
        channels[channelIndex] = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);
        // Merge the channels back into the image
        cv::merge(channels, image);
    }
}

int main(int argc, char** argv) {
    // Safety check on argc to ensure an image filename is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <ImagePath>\n";
        std::cerr << "Error: Image filename shall be provided as a command-line argument." << std::endl;
        return -1; // Return an error code
    }

    // Load the image from the provided filename
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR); // Ensure image is read in color

    // Safety check on the loaded image
    if (image.empty()) {
        std::cerr << "Error loading the image. Check if the filename is correct." << std::endl;
        return -1; // Return an error code
    }

    // Print the number of channels
    std::cout << "Number of channels in the image: " << image.channels() << std::endl;

    // Remove a color channel based on the task requirement
    // For the task, you can modify this to 0, 1, or 2 to remove the Blue, Green, or Red channel respectively
    int channelToRemove = 1; // Example: remove the Blue channel
    removeColorChannel(image, channelToRemove);
    std::cout << "Removed channel index: " << channelToRemove << " (0: Blue, 1: Green, 2: Red in BGR format)" << std::endl;

    // Display the modified image
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow("Display window", image); // Show our modified image inside it.

    // Wait for a keystroke in the window and save it into a char variable
    char keyPressed = static_cast<char>(cv::waitKey(0)); // Wait for any key press
    std::cout << "Key pressed: " << keyPressed << std::endl;

    return 0;
}

