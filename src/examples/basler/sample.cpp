#include <iostream>
#include "sample.h"
#include "../../utils/utils.h"

using namespace std;

void dgtl::example::basler::update( void ) {


  // Start the grabbing of c_countOfImagesToGrab images.
  // The camera device is parameterized with a default configuration which
  // sets up free-running continuous acquisition.
  CameraInstance.StartGrabbing(NoofImagesToGrab);

  // This smart pointer will receive the grab result data.
  Pylon::CGrabResultPtr GrabResultPtr;

  // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
  // when c_countOfImagesToGrab images have been retrieved.
  while (CameraInstance.IsGrabbing()) {
    // Wait for an image and then retrieve it. A timeout of TimeoutMs ms is used.
    CameraInstance.RetrieveResult(TimeoutMs, GrabResultPtr, Pylon::TimeoutHandling_ThrowException);

    // Image grabbed successfully?
    if (GrabResultPtr->GrabSucceeded()) {
      const uint8_t *ImageBuffer = (uint8_t *) GrabResultPtr->GetBuffer();
      Pixels.setFromPixels(ImageBuffer, GrabResultPtr->GetWidth(), GrabResultPtr->GetHeight(), OF_PIXELS_UYVY);
			YUV2RGB(Pixels);
      Frame.setFromPixels(Pixels);
    } else {
      cout << "Error: " << GrabResultPtr->GetErrorCode() << " " << GrabResultPtr->GetErrorDescription() << endl;
    }
  }
}

void dgtl::example::basler::draw( void ) {
  Frame.draw(0, 0);
}

dgtl::example::basler::basler( void ) : 
  Factory(Pylon::CTlFactory::GetInstance()),
  CameraInstance(Factory.CreateFirstDevice()),
  NoofImagesToGrab(5), TimeoutMs(1000) {

  try {
    cout << "Using device " << CameraInstance.GetDeviceInfo().GetModelName() << endl;
    // The parameter MaxNumBuffer can be used to control the count of buffers
    // allocated for grabbing. The default value of this parameter is 10.
    CameraInstance.MaxNumBuffer = 5;
  } catch (const Pylon::GenericException &e) {
    cout << e.what();
  }
}