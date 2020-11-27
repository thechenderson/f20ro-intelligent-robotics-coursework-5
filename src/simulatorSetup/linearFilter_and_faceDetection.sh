#!/bin/bash

#Start yarpserver
gnome-terminal -- /bin/bash -c "yarpserver; exec bash"

#Start iCubSim
gnome-terminal -- /bin/bash -c "iCub_SIM; exec bash"

#Create a new yarpview for robot's perspective
gnome-terminal -- /bin/bash -c "yarpview --name /view/left; exec bash"
sleep 1 
gnome-terminal -- /bin/bash -c "yarp connect /icubSim/cam/left /view/left;"
sleep 1 

#Set up virtual simulator screen to display video from webcam
gnome-terminal -- /bin/bash -c "yarpdev --device opencv_grabber --name /webcam/video; exec bash"
sleep 2 
gnome-terminal -- /bin/bash -c "yarp connect /webcam/video /icubSim/texture/screen;"
sleep 1

#Throw face boxing up onto new yarpview
gnome-terminal -- /bin/bash -c "./../faceDetection/build/faceDetection"
gnome-terminal -- /bin/bash -c "yarpview --name /view/faces; exec bash"
sleep 2
gnome-terminal -- /bin/bash -c "yarp connect /icubSim/cam/left /faceDetection/in;"
sleep 2
gnome-terminal -- /bin/bash -c "yarp connect /faceDetection/out /view/faces;"

#Apply linear filter to new yarpview
gnome-terminal -- /bin/bash -c "./../applyLinearFilter/build/applyLinearFilter"
gnome-terminal -- /bin/bash -c "yarpview --name /view/Sobel_edges; exec bash"
sleep 2
gnome-terminal -- /bin/bash -c "yarp connect /icubSim/cam/left /imageProc/edgeDetection/in;"
sleep 2
gnome-terminal -- /bin/bash -c "yarp connect /imageProc/edgeDetection/out /view/Sobel_edges;"
