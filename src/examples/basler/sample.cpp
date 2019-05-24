#include <iostream>
#include "sample.h"
#include "../../utils/utils.h"

using namespace std;

void dgtl::example::basler::update( void ) {
  // Start the grabbing of c_countOfImagesToGrab images.
  // The camera device is parameterized with a default configuration which
  // sets up free-running continuous acquisition.

	for (uint i = 0; i < CameraInstances.GetSize(); i++) {

	  // This smart pointer will receive the grab result data.
	  Pylon::CGrabResultPtr GrabResultPtr;
	  
	  // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
	  // when c_countOfImagesToGrab images have been retrieved.
		int n = 1;
		while (n-- > 0) {
			// Wait for an image and then retrieve it. A timeout of TimeoutMs ms is used.
			CameraInstances.RetrieveResult(TimeoutMs, GrabResultPtr, Pylon::TimeoutHandling_ThrowException);

			int cameraContextValue = GrabResultPtr->GetCameraContext();

			// Image grabbed successfully?
			if (GrabResultPtr->GrabSucceeded()) {
				const uint8_t *ImageBuffer = (uint8_t *)GrabResultPtr->GetBuffer();
				//auto t = GrabResultPtr->GetPixelType();
				Pixels.setFromPixels(ImageBuffer, GrabResultPtr->GetWidth(), GrabResultPtr->GetHeight(), OF_PIXELS_YUY2);
				YUV2RGB(Pixels);
				Frame[cameraContextValue].setFromPixels(Pixels);
			}
			else {
				cerr << "Error: " << GrabResultPtr->GetErrorCode() << " " << GrabResultPtr->GetErrorDescription() << endl;
			}
		}
	}
}

void dgtl::example::basler::draw( void ) {
  Frame[0].draw(0, 0);
	Frame[1].draw(500, 0);
}

dgtl::example::basler::basler( void ) : 
  Factory(Pylon::CTlFactory::GetInstance()),
  NoofImagesToGrab(4), TimeoutMs(1000) {

	// Get all attached devices and exit application if no device is found.
	Pylon::DeviceInfoList_t devices;
	if (Factory.EnumerateDevices(devices) == 0)
		throw RUNTIME_EXCEPTION("No camera present.");

	// Initialize cameras
	CameraInstances.Initialize(std::min<size_t>(2, devices.size()));

	for (uint i = 0; i < CameraInstances.GetSize(); i++) {
		CameraInstances[i].Attach(Factory.CreateDevice(devices[i]));
		cout << "Using device " << CameraInstances[i].GetDeviceInfo().GetModelName() << endl;
	}

  try {
    // The parameter MaxNumBuffer can be used to control the count of buffers
    // allocated for grabbing. The default value of this parameter is 10.
		for (uint i = 0; i < CameraInstances.GetSize(); i++)
      CameraInstances[i].MaxNumBuffer = NoofImagesToGrab;
		CameraInstances.StartGrabbing();
  } catch (const Pylon::GenericException &e) {
    cout << e.what();
  }
}