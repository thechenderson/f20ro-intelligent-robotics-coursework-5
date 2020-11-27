#include <stdio.h> 
#include <unistd.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <string>

using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;

std::string facePositionTopic = "/idk/facePositionTopic";

int main() {
	Network yarp; //useless
	BufferedPort<Bottle> target_bottle;
	target_bottle.open("iKinGazeControler/xd:i");
	
	//Property options of robotHead
	Property options1;
	options1.put("device","remote_controlboard");
	options1.put("remote","/icubSim/head");
	options1.put("local","/gaze_adb/client");
	PolyDriver robotHead(options1);
	if (!robotHead.isValid()) {
	  	printf("Cannot connect to the creppy head\n");
		return 1;
	}
	
	//Property options of iKinGazeCtrl
	Property options0;
	options0.put("device","gazecontrollerclient");
	options0.put("remote","/iKinGazeCtrl");
	options0.put("local","/client/gaze");
	PolyDriver clientGazeCtrl(options0);
	IGazeControl *igaze=NULL;
	if (clientGazeCtrl.isValid()) {
	   clientGazeCtrl.view(igaze);
	}

	//Set to velocity part
	IControlMode *con;
	IPositionControl *pos;
	IVelocityControl *vel;
	robotHead.view(pos);
	robotHead.view(con);
	//Checking robot connection
	if (pos==NULL || con==NULL) {
		printf("Cannot get interface to robot head\n");
		robotHead.close();
		return 1;
	}
	
	//Setting joints to Velocity
	int joints = 5;
	//pos->getAxes(&joints);
	Vector setpoints;
	setpoints.resize(joints);
	for(int i = 0; i <= joints; i++) {
		con->setControlMode(i, VOCAB_CM_VELOCITY);
	}
	vel->velocityMove(setpoints.data());
	
	Bottle& b = target_bottle.prepare();
	b.addDouble(3.0);
	b.addDouble(0.0);
	b.addDouble(0.25);
	target_bottle.write();
	while (1) { // repeat forever
	}
	clientGazeCtrl.close();
}
