deadline : 14/07/2024 - 14 july 2024

'''bash
dataset : https://drive.google.com/drive/folders/1dzNrhDpc2DXRqmQgbO5l2WMjzfhMdxVn
'''



AD\mirghom49577@dei-cv-002:~/Desktop/parking-lot-management/build$ make
[ 12%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/main.cpp.o
[ 25%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/ParkingSpaceDetector.cpp.o
[ 37%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/OccupancyClassifier.cpp.o
[ 50%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/CarSegmentation.cpp.o
[ 62%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/TopViewVisualizer.cpp.o
[ 75%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/PerformanceEvaluator.cpp.o
[ 87%] Building CXX object CMakeFiles/ParkingLotManagement.dir/src/XMLParser.cpp.o
/home/local/mirghom49577/Desktop/parking-lot-management/src/XMLParser.cpp:2:10: fatal error: tinyxml2.h: No such file or directory
    2 | #include <tinyxml2.h>
      |          ^~~~~~~~~~~~
compilation terminated.
make[2]: *** [CMakeFiles/ParkingLotManagement.dir/build.make:160: CMakeFiles/ParkingLotManagement.dir/src/XMLParser.cpp.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:83: CMakeFiles/ParkingLotManagement.dir/all] Error 2
make: *** [Makefile:91: all] Error 2
