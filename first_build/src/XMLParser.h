#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

struct ParkingSpace {
    int id;
    bool occupied;
    cv::RotatedRect rect;
};

class XMLParser {
public:
    static std::vector<ParkingSpace> parseXML(const std::string& xmlPath);
};

#endif // XML_PARSER_H