#include "ParkingSpaceDetector.h"

ParkingSpaceDetector::ParkingSpaceDetector() {}

std::vector<cv::RotatedRect> ParkingSpaceDetector::detectParkingSpaces(const cv::Mat& image) {
    cv::Mat preprocessed = preprocessImage(image);
    cv::Mat edges;
    cv::Canny(preprocessed, edges, 50, 150);
    std::vector<cv::Vec4i> lines = detectLines(edges);
    std::vector<cv::Point2f> intersections = findIntersections(lines);
    return formParkingSpaces(intersections);
}

cv::Mat ParkingSpaceDetector::preprocessImage(const cv::Mat& image) {
    cv::Mat gray, blurred;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
    return blurred;
}

std::vector<cv::Vec4i> ParkingSpaceDetector::detectLines(const cv::Mat& edges) {
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 10);
    return lines;
}

std::vector<cv::Point2f> ParkingSpaceDetector::findIntersections(const std::vector<cv::Vec4i>& lines) {
    std::vector<cv::Point2f> intersections;
    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = i + 1; j < lines.size(); j++) {
            cv::Point2f pt;
            if (lineIntersection(lines[i], lines[j], pt)) {
                intersections.push_back(pt);
            }
        }
    }
    return intersections;
}

std::vector<cv::RotatedRect> ParkingSpaceDetector::formParkingSpaces(const std::vector<cv::Point2f>& intersections) {
    std::vector<cv::RotatedRect> parkingSpaces;
    // This is a simplified implementation. In a real scenario, you'd need a more sophisticated
    // algorithm to group intersections into parking spaces.
    for (size_t i = 0; i < intersections.size(); i += 4) {
        if (i + 3 < intersections.size()) {
            std::vector<cv::Point2f> corners(intersections.begin() + i, intersections.begin() + i + 4);
            cv::RotatedRect rect = cv::minAreaRect(corners);
            parkingSpaces.push_back(rect);
        }
    }
    return parkingSpaces;
}

bool ParkingSpaceDetector::lineIntersection(cv::Vec4i line1, cv::Vec4i line2, cv::Point2f& intersection) {
    cv::Point2f p1(line1[0], line1[1]), p2(line1[2], line1[3]);
    cv::Point2f p3(line2[0], line2[1]), p4(line2[2], line2[3]);

    float d = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    if (std::abs(d) < 1e-5) return false;

    float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / d;
    float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / d;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        intersection.x = p1.x + t * (p2.x - p1.x);
        intersection.y = p1.y + t * (p2.y - p1.y);
        return true;
    }

    return false;
}