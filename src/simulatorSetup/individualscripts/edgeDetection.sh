#!/bin/bash
gnome-terminal -- /bin/bash -c "./../../applyLinearFilter/build/applyLinearFilter"
gnome-terminal -- /bin/bash -c "yarpview -name /view/Sobel_edges; exec bash"
sleep 1 
gnome-terminal -- /bin/bash -c "yarp connect /test/video /imageProc/edgeDetection/in;"
gnome-terminal -- /bin/bash -c "yarp connect /imageProc/edgeDetection/out /view/Sobel_edges;"