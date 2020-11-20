#include <stdio.h>
/* Get all OS and signal processing YARP classes */
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
using namespace yarp::os;
using namespace yarp::sig;
int main() {
 Network yarp; // set up yarp
 // make a port for reading images
 BufferedPort<ImageOf<PixelRgb> > imagePort;
imagePort.open("/tutorial/image/in"); // give the port a name
 while (1) {
 ImageOf<PixelRgb> *image = imagePort.read(); // read an image
 if (image!=NULL) { // check we actually got something
 printf("We got an image of size %dx%d\n", image->width(), image->height());
 }
 }
 return 0;
}
