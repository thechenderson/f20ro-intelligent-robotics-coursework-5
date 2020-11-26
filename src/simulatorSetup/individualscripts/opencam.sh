#!/bin/bash
gnome-terminal -- bash -c "yarpview --name /view/left; exec bash"
sleep 1
gnome-terminal -- bash -c "yarp connect /icubSim/cam/left /view/left; exec bash"
