#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // Safety check on argc to ensure an image filename is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <ImagePath>\n";
        std::cerr << "Error: Image filename shall be provided as a command-line argument." << std::endl;
        return -1; // Return an error code
    }

    // Load the image from the provided filename
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_UNCHANGED);

    // Safety check on the loaded image
    if (image.empty()) {
        std::cerr << "Error loading the image. Check if the filename is correct." << std::endl;
        return -1; // Return an error code
    }

    // If the image is loaded successfully, display it
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow("Display window", image); // Show our image inside it.

    // Wait for a keystroke in the window
    cv::waitKey(0); // Wait for any key press
    return 0;
}
