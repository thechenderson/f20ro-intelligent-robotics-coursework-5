#!/bin/bash

#Start yarpserver
gnome-terminal -- /bin/bash -c "yarpserver; exec bash"

#Start iCubSim
gnome-terminal -- /bin/bash -c "iCub_SIM; exec bash"

#Create a new yarpview for robot's perspective
gnome-terminal -- /bin/bash -c "yarpview -name /view/left; exec bash"
sleep 1 
gnome-terminal -- /bin/bash -c "yarp connect /icubSim/cam/left /yarpview/img:i;"
sleep 1 

#Set up virtual simulator screen to display video from webcam
gnome-terminal -- /bin/bash -c "yarpdev --device opencv_grabber --name /test/video; exec bash"
sleep 2 
gnome-terminal -- /bin/bash -c "yarp connect /test/video /icubSim/texture/screen;"
sleep 1

#Apply linear filter to new yarpview
gnome-terminal -- /bin/bash -c "./../applyLinearFilter/build/applyLinearFilter"
gnome-terminal -- /bin/bash -c "yarpview -name /view/Sobel_edges; exec bash"
sleep 1 
gnome-terminal -- /bin/bash -c "yarp connect /test/video /imageProc/edgeDetection/in;"
gnome-terminal -- /bin/bash -c "yarp connect /imageProc/edgeDetection/out /view/Sobel_edges;"