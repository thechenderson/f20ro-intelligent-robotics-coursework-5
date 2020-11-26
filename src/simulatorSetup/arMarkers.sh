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

#Apply ar marker search on new yarpview
gnome-terminal -- /bin/bash -c "./../arMarkers/build/arMarkers"
gnome-terminal -- /bin/bash -c "yarpview --name /view/arMarkers; exec bash"
sleep 2
gnome-terminal -- /bin/bash -c "yarp connect /icubSim/cam/left /imageProc/image/in;"
sleep 2
gnome-terminal -- /bin/bash -c "yarp connect /imageProc/image/out /view/arMarkers;"