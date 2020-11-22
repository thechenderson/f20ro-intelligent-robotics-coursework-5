#!/bin/bash
#Script used to build all of the C++ files before use in the simulator


gnome-terminal -- /bin/bash -c "cd ../applyLinearFilter/build ; cmake ..; cd ../../arMarkers/build ; cmake .. ; exec bash"