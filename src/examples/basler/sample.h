#pragma once

#include <pylon/PylonIncludes.h>
#include "ofMain.h"
#include "def.h"

namespace dgtl {
namespace example {
class basler : public ofBaseApp {
public:
  basler( void );

  void update( void ) final;
  void draw( void ) final;

private:
  Pylon::CTlFactory &Factory;
  Pylon::CInstantCamera CameraInstance;
  ofImage Frame;
  ofPixels Pixels;
  uint
    NoofImagesToGrab,
    TimeoutMs;
};
}
}