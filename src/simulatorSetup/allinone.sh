#!/bin/bash
gnome-terminal -- bash -c "yarpserver; exec bash"
gnome-terminal -- bash -c "iCub_SIM; exec bash"
gnome-terminal -- bash -c "yarpview -name /view/left; exec bash"
sleep 1
gnome-terminal -- bash -c "yarp connect /icubSim/cam/left /yarpview/img:i;"
sleep 1
gnome-terminal -- bash -c "yarpdev --device opencv_grabber --name /test/video; exec bash"
sleep 2
gnome-terminal -- bash -c "yarp connect /test/video /icubSim/texture/screen;"
