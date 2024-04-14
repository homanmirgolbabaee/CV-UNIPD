#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

// Function to draw filled polygon between two strongest lines
void fillBetweenLines(cv::Mat& img, std::vector<cv::Vec2f> lines) {
    if (lines.size() < 2) return; // Check if we have at least two lines

    // Assuming the lines are somewhat parallel, find the points where they intersect the image borders
    // Then draw a filled polygon between them
    cv::Point points[4];
    for (int i = 0; i < 2; i++) {
        float rho = lines[i][0], theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        points[i*2] = cv::Point(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
        points[i*2 + 1] = cv::Point(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));
    }

    // Sort points based on their x coordinates
    std::sort(points, points + 4, [](cv::Point a, cv::Point b) {
        return a.x < b.x;
    });

    // Draw the polygon
    cv::fillConvexPoly(img, points, 4, cv::Scalar(0, 0, 255));
}

int main() {
    // Load the image
    cv::Mat img = cv::imread("street_scene.png");
    if (img.empty()) {
        std::cerr << "Error: Unable to open the image file." << std::endl;
        return -1;
    }

    // Convert the image to grayscale
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Detect edges using Canny
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 150);

    // Use Hough transform to detect lines
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edges, lines, 1, CV_PI / 180, 200); // You might need to adjust the last parameter (threshold) based on the image

    // Draw the filled area between the two strongest lines
    fillBetweenLines(img, lines);

    // Save and show the result
    cv::imwrite("task3_result.png", img);
    cv::imshow("Detected Lines", img);
    cv::waitKey(0);

    return 0;
}
