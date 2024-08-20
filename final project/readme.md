deadline : 14/07/2024 - 14 july 2024

'''bash
dataset : https://drive.google.com/drive/folders/1dzNrhDpc2DXRqmQgbO5l2WMjzfhMdxVn
'''


/usr/bin/ld: CMakeFiles/ParkingLotManagement.dir/src/XMLParser.cpp.o: in function `XMLParser::parseXML(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)':
XMLParser.cpp:(.text+0x51): undefined reference to `tinyxml2::XMLDocument::XMLDocument(bool, tinyxml2::Whitespace)'
/usr/bin/ld: XMLParser.cpp:(.text+0x75): undefined reference to `tinyxml2::XMLDocument::LoadFile(char const*)'
/usr/bin/ld: XMLParser.cpp:(.text+0x354): undefined reference to `tinyxml2::XMLDocument::~XMLDocument()'
/usr/bin/ld: XMLParser.cpp:(.text+0x37c): undefined reference to `tinyxml2::XMLDocument::~XMLDocument()'
/usr/bin/ld: CMakeFiles/ParkingLotManagement.dir/src/XMLParser.cpp.o: in function `tinyxml2::XMLNode::FirstChildElement(char const*)':
XMLParser.cpp:(.text._ZN8tinyxml27XMLNode17FirstChildElementEPKc[_ZN8tinyxml27XMLNode17FirstChildElementEPKc]+0x23): undefined reference to `tinyxml2::XMLNode::FirstChildElement(char const*) const'
/usr/bin/ld: CMakeFiles/ParkingLotManagement.dir/src/XMLParser.cpp.o: in function `tinyxml2::XMLNode::NextSiblingElement(char const*)':
XMLParser.cpp:(.text._ZN8tinyxml27XMLNode18NextSiblingElementEPKc[_ZN8tinyxml27XMLNode18NextSiblingElementEPKc]+0x23): undefined reference to `tinyxml2::XMLNode::NextSiblingElement(char const*) const'
/usr/bin/ld: CMakeFiles/ParkingLotManagement.dir/src/XMLParser.cpp.o: in function `tinyxml2::XMLElement::QueryIntAttribute(char const*, int*) const':
XMLParser.cpp:(.text._ZNK8tinyxml210XMLElement17QueryIntAttributeEPKcPi[_ZNK8tinyxml210XMLElement17QueryIntAttributeEPKcPi]+0x27): undefined reference to `tinyxml2::XMLElement::FindAttribute(char const*) const'
/usr/bin/ld: XMLParser.cpp:(.text._ZNK8tinyxml210XMLElement17QueryIntAttributeEPKcPi[_ZNK8tinyxml210XMLElement17QueryIntAttributeEPKcPi]+0x4c): undefined reference to `tinyxml2::XMLAttribute::QueryIntValue(int*) const'
/usr/bin/ld: CMakeFiles/ParkingLotManagement.dir/src/XMLParser.cpp.o: in function `tinyxml2::XMLElement::QueryBoolAttribute(char const*, bool*) const':
XMLParser.cpp:(.text._ZNK8tinyxml210XMLElement18QueryBoolAttributeEPKcPb[_ZNK8tinyxml210XMLElement18QueryBoolAttributeEPKcPb]+0x27): undefined reference to `tinyxml2::XMLElement::FindAttribute(char const*) const'
/usr/bin/ld: XMLParser.cpp:(.text._ZNK8tinyxml210XMLElement18QueryBoolAttributeEPKcPb[_ZNK8tinyxml210XMLElement18QueryBoolAttributeEPKcPb]+0x4c): undefined reference to `tinyxml2::XMLAttribute::QueryBoolValue(bool*) const'
/usr/bin/ld: CMakeFiles/ParkingLotManagement.dir/src/XMLParser.cpp.o: in function `tinyxml2::XMLElement::QueryFloatAttribute(char const*, float*) const':
XMLParser.cpp:(.text._ZNK8tinyxml210XMLElement19QueryFloatAttributeEPKcPf[_ZNK8tinyxml210XMLElement19QueryFloatAttributeEPKcPf]+0x27): undefined reference to `tinyxml2::XMLElement::FindAttribute(char const*) const'
/usr/bin/ld: XMLParser.cpp:(.text._ZNK8tinyxml210XMLElement19QueryFloatAttributeEPKcPf[_ZNK8tinyxml210XMLElement19QueryFloatAttributeEPKcPf]+0x4c): undefined reference to `tinyxml2::XMLAttribute::QueryFloatValue(float*) const'
collect2: error: ld returned 1 exit status
make[2]: *** [CMakeFiles/ParkingLotManagement.dir/build.make:246: ParkingLotManagement] Error 1
make[1]: *** [CMakeFiles/Makefile2:83: CMakeFiles/ParkingLotManagement.dir/all] Error 2
make: *** [Makefile:91: all] Error 2

