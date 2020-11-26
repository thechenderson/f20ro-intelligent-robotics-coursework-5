 #include <stdio.h> 
 #include <yarp/os/all.h>
 #include <yarp/sig/all.h>
 #include <yarp/dev/all.h>
 using namespace yarp::os;
 using namespace yarp::sig;
 using namespace yarp::dev;
 int main() {
   Network yarp; // set up yarp
   BufferedPort<Vector> targetPort;
   targetPort.open("/lookAtTarget/in");
   Network::connect("/faceDetection/out","/lookAtTarget/in");
   Network::connect("/imageProc/image/out","/lookAtTarget/in");

   Property options;
   options.put("device", "remote_controlboard");
   options.put("local", "/tutorial/motor/client");
   options.put("remote", "/icubSim/head");
   PolyDriver robotHead(options);
   if (!robotHead.isValid()) {
     printf("Cannot connect to robot head\n");
     return 1;
   }
   IPositionControl *pos;
   IVelocityControl *vel;
   IEncoders *enc;
   IControlMode *con;
   robotHead.view(pos);
   robotHead.view(vel);
   robotHead.view(enc);
   robotHead.view(con);
   if (pos==NULL || vel==NULL || enc==NULL  || con==NULL) {
     printf("Cannot get interface to robot head\n");
     robotHead.close();
     return 1;
   }
   int jnts = 0;
      pos->getAxes(&jnts);
      Vector setpoints;
      setpoints.resize(jnts);
      for(int i = 0; i<=jnts; i++)
	   con->setControlMode(i, VOCAB_CM_VELOCITY);
      vel->velocityMove(setpoints.data());
    
      while (1) { // repeat forever
        Vector *target = targetPort.read();  // read a target
        if (target!=NULL) { // check we actually got something
           printf("We got a vector containing");
           for (size_t i=0; i<target->size(); i++) {
             printf(" %g", (*target)[i]);
           }
           printf("\n");
    
           double x = (*target)[0];
           double y = (*target)[1];
           double conf = (*target)[2];
    
           x -= 320/2;
           y -= 240/2;
    
           double vx = x*0.1;
           double vy = -y*0.1;
    
           // prepare command
           for (int i=0; i<jnts; i++) {
             setpoints[i] = 0;
           }
    
           if (conf>0.5) {
             setpoints[3] = vy;
             setpoints[4] = vx;
           } else {
             setpoints[3] = 0;
             setpoints[4] = 0;
           }
        } else {
             setpoints[3] = 0;
             setpoints[4] = 0;
        }
        vel->velocityMove(setpoints.data());
	yarp::os::Time::delay(0.01);
      }
      return 0;
    }
