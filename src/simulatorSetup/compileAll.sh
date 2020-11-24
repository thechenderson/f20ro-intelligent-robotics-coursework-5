#!/bin/bash
#  go to src folder
cd ..
for dir in */; do 
    # skip folders that don't have projects that we want to build
    if [ $dir = "simulatorSetup/" ] || [ $dir = "examplePrograms/" ]; then
        echo $dir " ignored"
        continue;
    else
        echo "building " $dir
        
        # remove / character from the end of $dir before using in mkdir
        rm -r ${dir%?}/build
        mkdir ${dir%?}/build
        cd ${dir%?}/build
        cmake ..
        make

        # go back to src
        cd ../..
    fi
 
done
