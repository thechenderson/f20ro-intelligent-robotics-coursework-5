#!/bin/bash

# load optional flags
REBUILD=0
while [ ! $# -eq 0 ]
do
	case "$1" in
		--help | -h)
			echo "Use --rebuild to clean all and rebuild - default does not clean."
			exit
			;;
		--rebuild | -r)
			REBUILD=1
			;;
	esac
	shift
done

#  perform builds!
#  first go to src folder
cd ..
for dir in */; do 
    # skip folders that don't have projects that we want to build
    if [ $dir = "simulatorSetup/" ] || [ $dir = "examplePrograms/" ]; then
        echo $dir " ignored"
        continue;
    else
        echo "building " $dir
        
        # remove / character from the end of $dir before using in mkdir
        if [ $REBUILD == 1 ]; then
            echo "Cleaning up before building"
            rm -r ${dir%?}/build

        else
            echo "Building without deleting existing build directory first."
        
        fi
        mkdir ${dir%?}/build
        cd ${dir%?}/build
        cmake ..
        make

        # go back to src
        cd ../..
    fi
 
done
