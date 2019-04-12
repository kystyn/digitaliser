#include <pylon/PylonIncludes.h>

#include "def.h"
#include "examples/gui/sample.h"

static const int
  NoofImagesToGrab = 5,
  TimeoutMs = 5000;

int main( int argc, char* argv[] ) {
  ofSetupOpenGL(1366, 768, OF_WINDOW);// <-------- setup the GL context
  
  auto & Factory = Pylon::CTlFactory::GetInstance();
  Pylon::PylonInitialize();
  try {
    Pylon::CInstantCamera InstantCamera(Factory.CreateFirstDevice());
    cout << "Using device " << InstantCamera.GetDeviceInfo().GetModelName() << endl;

    // The parameter MaxNumBuffer can be used to control the count of buffers
    // allocated for grabbing. The default value of this parameter is 10.
    InstantCamera.MaxNumBuffer = 5;

    // Start the grabbing of c_countOfImagesToGrab images.
    // The camera device is parameterized with a default configuration which
    // sets up free-running continuous acquisition.
    InstantCamera.StartGrabbing(NoofImagesToGrab);

    // This smart pointer will receive the grab result data.
    Pylon::CGrabResultPtr GrabResultPtr;

    // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
    // when c_countOfImagesToGrab images have been retrieved.
    while (InstantCamera.IsGrabbing()) {
      // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
      InstantCamera.RetrieveResult(TimeoutMs, GrabResultPtr, Pylon::TimeoutHandling_ThrowException);

      // Image grabbed successfully?
      if (GrabResultPtr->GrabSucceeded()) {
          // Access the image data.
          cout << "SizeX: " << GrabResultPtr->GetWidth() << endl;
          cout << "SizeY: " << GrabResultPtr->GetHeight() << endl;
          const uint8_t *ImageBuffer = (uint8_t *) GrabResultPtr->GetBuffer();
          cout << "Gray value of first pixel: " << (uint32_t) ImageBuffer[0] << endl << endl;
      }
      else {
          cout << "Error: " << GrabResultPtr->GetErrorCode() << " " << GrabResultPtr->GetErrorDescription() << endl;
      }
    }
  } catch (const Pylon::GenericException &e) {
  }

  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:
  ofRunApp(new dgtl::example::gui());

  Pylon::PylonTerminate(); 
  return 0;
}
