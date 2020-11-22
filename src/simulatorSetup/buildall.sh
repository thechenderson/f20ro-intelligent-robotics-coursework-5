#!/bin/bash
#Script used to build all of the C++ files before use in the simulator


gnome-terminal -- /bin/bash -c "mkdir ../applyLinearFilter/build ; cd ../applyLinearFilter/build ; cmake ..; mkdir ../../arMarkers/build ; cd ../../arMarkers/build ; cmake .. ; exec bash"