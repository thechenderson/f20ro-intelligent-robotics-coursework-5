#!/bin/bash

# load optional flags
REBUILD=0
DEBUG=0
while [ ! $# -eq 0 ]
do
	case "$1" in
		--help | -h)
			echo "By default, this makes build directories, then runs cmake and make for you."
            echo "    -r  --rebuild    to clean all and rebuild"
            echo "    -d  --debug      make debug builds instead of optimised release builds"
			exit
			;;
		--rebuild | -r)
			REBUILD=1
			;;
		--debug | -d)
			DEBUG=1
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
        if [ $DEBUG == 1 ]; then
            echo "Setting cmake to build DEBUG (slow, allows debugging)"
            cmake -DCMAKE_BUILD_TYPE=Debug ..
            
        else
            echo "Setting cmake to build RELEASE (fast, no debug)"
            cmake ..
        fi
        make

        # go back to src
        cd ../..
    fi
 
done
