
#include "def.h"
#include "examples/gui/sample.h"
#include "examples/basler/sample.h"

int main( int argc, char* argv[] ) {
  ofSetupOpenGL(1366, 768, OF_WINDOW);// <-------- setup the GL context  
  Pylon::PylonInitialize();

  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:

  //ofRunApp(new dgtl::example::gui());
  ofRunApp(new dgtl::example::basler());

  Pylon::PylonTerminate(); 
  return 0;
}
