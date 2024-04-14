
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

cv::Mat detectWhiteMarkings(const cv::Mat& input) {
    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // Use Canny edge detector
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 150);

    // Check edge orientation and colors close to edge points
    cv::Mat orientation, magnitude;
    cv::Mat sobel_x, sobel_y;
    cv::Sobel(gray, sobel_x, CV_32F, 1, 0);
    cv::Sobel(gray, sobel_y, CV_32F, 0, 1);
    cv::cartToPolar(sobel_x, sobel_y, magnitude, orientation, true);


    // Threshold for white color in grayscale
    double white_thresh = 100;

    // Mask of white markings (initially all zeros)
    cv::Mat white_markings = cv::Mat::zeros(edges.size(), edges.type());

    // Iterate over the edges
    for (int y = 0; y < edges.rows; ++y) {
        for (int x = 0; x < edges.cols; ++x) {
            if (edges.at<unsigned char>(y, x) > 0) {
                // If the edge point is bright enough and the orientation is roughly horizontal
                if (gray.at<unsigned char>(y, x) > white_thresh && std::abs(orientation.at<float>(y, x) - 90) < 10) {
                    white_markings.at<unsigned char>(y, x) = 255;
                }
            }
        }
    }

    return white_markings;
}

int main() {
    // Load the image
    cv::Mat img = cv::imread("street_scene.png");
    if (img.empty()) {
        std::cerr << "Error: Unable to open the image file." << std::endl;
        return -1;
    }

    // Detect white markings on the road
    cv::Mat white_markings = detectWhiteMarkings(img);

    // Create a window and display the result
    cv::namedWindow("White Markings", cv::WINDOW_AUTOSIZE);
    cv::imshow("White Markings", white_markings);

    // Wait for the user to exit
    cv::waitKey(0);
    return 0;
}
