#!/bin/bash
gnome-terminal -- /bin/bash -c "yarpserver; exec bash"
gnome-terminal -- /bin/bash -c "iCub_SIM; exec bash"
gnome-terminal -- /bin/bash -c "yarpview -name /view/left; exec bash"
sleep 1 
gnome-terminal -- /bin/bash -c "yarp connect /icubSim/cam/left /yarpview/img:i;"
sleep 1 
gnome-terminal -- /bin/bash -c "yarpdev --device opencv_grabber --name /test/video; exec bash"
sleep 2 
gnome-terminal -- /bin/bash -c "yarp connect /test/video /icubSim/texture/screen;"
sleep 1 
gnome-terminal -- /bin/bash -c "./../applyLinearFilter/build/applyLinearFilter"
gnome-terminal -- /bin/bash -c "yarpview -name /view/Sobel_edges; exec bash"
sleep 1 
gnome-terminal -- /bin/bash -c "yarp connect /test/video /imageProc/edgeDetection/in;"
gnome-terminal -- /bin/bash -c "yarp connect /imageProc/edgeDetection/out /view/Sobel_edges;"