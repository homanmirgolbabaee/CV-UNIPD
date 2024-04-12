#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

int main() {
    // Load the image
    cv::Mat img = cv::imread("street_scene.png");
    if (img.empty()) {
        std::cerr << "Error loading the image" << std::endl;
        return -1;
    }

    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Reduce noise with Gaussian blur
    cv::GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);

    // Vector to store the circles
    std::vector<cv::Vec3f> circles;

    // Apply the Hough Transform to find the circles
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 8, 100, 30, 1, 30); // Change these parameters as needed

    // Draw the circles detected
    for (size_t i = 0; i < circles.size(); i++) {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        // Circle center
        cv::circle(img, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);

        // Circle outline
        cv::circle(img, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }

    // Show your results
    cv::namedWindow("Hough Circle Transform Demo", cv::WINDOW_AUTOSIZE);
    cv::imshow("Hough Circle Transform Demo", img);

    cv::waitKey(0);
    return 0;
}
