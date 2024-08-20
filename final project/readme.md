deadline : 14/07/2024 - 14 july 2024

'''bash
dataset : https://drive.google.com/drive/folders/1dzNrhDpc2DXRqmQgbO5l2WMjzfhMdxVn
'''

AD\mirghom49577@dei-cv-002:~/Desktop/parking-lot-management/build$ make
[ 12%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/main.cpp.o
[ 25%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/ParkingSpaceDetector.cpp.o
/home/local/mirghom49577/Desktop/parking-lot-management/src/ParkingSpaceDetector.cpp: In member function ‘std::vector<cv::Point_<float> > ParkingSpaceDetector::findIntersections(const std::vector<cv::Vec<int, 4> >&)’:
/home/local/mirghom49577/Desktop/parking-lot-management/src/ParkingSpaceDetector.cpp:32:21: error: ‘segmentIntersection’ is not a member of ‘cv’
   32 |             if (cv::segmentIntersection(
      |                     ^~~~~~~~~~~~~~~~~~~
make[2]: *** [CMakeFiles/ParkingLotManagement.dir/build.make:90: CMakeFiles/ParkingLotManagement.dir/src/ParkingSpaceDetector.cpp.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:83: CMakeFiles/ParkingLotManagement.dir/all] Error 2
make: *** [Makefile:91: all] Error 2
