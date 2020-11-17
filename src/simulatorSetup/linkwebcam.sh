#!/bin/bash
gnome-terminal -- bash -c "yarpdev --device opencv_grabber --name /test/video; exec bash"
gnome-terminal -- bash -c "yarp connect /test/video /icubSim/texture/screen; exec bash"

