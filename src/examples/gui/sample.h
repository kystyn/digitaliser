#pragma once

#include "ofMain.h"
#include "ofxGui.h"

namespace dgtl {
namespace example {
  class gui : public ofBaseApp {
  public:
    void setup();
    void update();
    void draw();
    
    void exit();
  
    void keyPressed( int Key );
    void keyReleased( int Key );
    void mouseMoved( int X, int Y );
    void mouseDragged( int X, int Y, int Button );
    void mousePressed( int X, int Y, int Button );
    void mouseReleased (int X, int Y, int Button );
    void mouseEntered( int X, int Y );
    void mouseExited( int X, int Y );
    void windowResized( int W, int H );
    void dragEvent( ofDragInfo DragInfo );
    void gotMessage( ofMessage Msg );
  
    void circleResolutionChanged( int &circleResolution );
    void ringButtonPressed();
  
    bool Hide;
  
    ofxFloatSlider Radius;
    ofxColorSlider Color;
    ofxVec2Slider Center;
    ofxIntSlider CircleResolution;
    ofxToggle Filled;
    ofxButton TwoCircles;
    ofxButton RingButton;
    ofxLabel ScreenSize;
  
    ofxPanel Panel;
  
    ofSoundPlayer Ring;
  };
} /* end of 'example' namespace */
} /* end of 'dgtl' namespace */

