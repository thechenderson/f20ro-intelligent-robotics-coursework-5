#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <string>

using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;
using namespace std;

int main(int argc, const char **argv)
{

	Network yarp;
	
	//Get the ID of the marker
	BufferedPort<Bottle> target_ID;
	target_ID.open("/wave/markerReceived");
	Network::connect("/marker/markerSend", "/wave/markerReceived");
	Bottle *marker_IDb = target_ID.read();
	string marker_ID = marker_IDb->toString();

	//Options of right arm
	Property options; 
	options.put("device", "remote_controlboard");
	options.put("local", "/tutorial/client");
	options.put("remote", "/icubSim/right_arm");

	PolyDriver robotDev(options);
	if (!robotDev.isValid())
	{
	  printf("Device not available.\n");
	  return 1;
	}

	//Create object to get the data from the right arm
	IPositionControl *pos;
	IEncoders *enc;
	IControlMode *ictrl;
	robotDev.view(pos);
	robotDev.view(enc);
	robotDev.view(ictrl);
	//Values that will be sent and received
	yarp::sig::Vector setpoints;
	yarp::sig::Vector Encoders;

	//Getting joints number of right arm
	int joints = 0;
	setpoints.resize(joints);
	pos->getAxes(&joints);
	
	//Resize vector with the number of joints in the arm
	setpoints.resize(joints);
	Encoders.resize(joints);
	
	//Set right arm joints in Position mode
	for (int i = 0; i < joints; i++)
	{
	  ictrl->setControlMode(i, VOCAB_CM_POSITION); 
	  setpoints[i] = 0;
	}

	//Set joints to raise the arm to the vertical
	pos->positionMove(0, -90);
	pos->positionMove(1, 90);

	while(1) {
		if (marker_ID.compare("42") == 0) {
			//Motion of wave (not the Queen's one)
			if (Encoders[3] >= 80)
				pos->positionMove(3, 40);

			if (Encoders[3] <= 50)
				pos->positionMove(3, 90);

			//Update values of the encoders
			enc->getEncoders(Encoders.data());
		}
	}
}
