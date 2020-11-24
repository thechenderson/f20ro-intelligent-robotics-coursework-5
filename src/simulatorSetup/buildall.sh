#!/bin/bash
#Script used to build all of the C++ files before use in the simulator


gnome-terminal -- /bin/bash -c "mkdir ../applyLinearFilter/build ; cd ../applyLinearFilter/build ; cmake ..; make ; mkdir ../../arMarkers/build ; cd ../../arMarkers/build ; cmake .. ; make ; mkdir ../../faceDetection/build ; cd ../../faceDetection/build ; cmake .. ; make ; mkdir ../../detect_markers/build ; cd ../../detect_markers/build ; cmake .. ; make ; exec bash"