#include "XMLParser.h"
#include "tinyxml2.h"  // Change this line


std::vector<ParkingSpace> XMLParser::parseXML(const std::string& xmlPath) {
    std::vector<ParkingSpace> spaces;
    tinyxml2::XMLDocument doc;
    
    if (doc.LoadFile(xmlPath.c_str()) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* parkingElement = doc.FirstChildElement("parking");
        if (parkingElement) {
            for (tinyxml2::XMLElement* spaceElement = parkingElement->FirstChildElement("space");
                 spaceElement;
                 spaceElement = spaceElement->NextSiblingElement("space")) {
                
                ParkingSpace space;
                spaceElement->QueryIntAttribute("id", &space.id);
                spaceElement->QueryBoolAttribute("occupied", &space.occupied);
                
                tinyxml2::XMLElement* rectElement = spaceElement->FirstChildElement("rotatedRect");
                if (rectElement) {
                    float centerX, centerY, width, height, angle;
                    rectElement->FirstChildElement("center")->QueryFloatAttribute("x", &centerX);
                    rectElement->FirstChildElement("center")->QueryFloatAttribute("y", &centerY);
                    rectElement->FirstChildElement("size")->QueryFloatAttribute("w", &width);
                    rectElement->FirstChildElement("size")->QueryFloatAttribute("h", &height);
                    rectElement->FirstChildElement("angle")->QueryFloatAttribute("d", &angle);
                    
                    space.rect = cv::RotatedRect(cv::Point2f(centerX, centerY), cv::Size2f(width, height), angle);
                }
                
                spaces.push_back(space);
            }
        }
    }
    
    return spaces;
}