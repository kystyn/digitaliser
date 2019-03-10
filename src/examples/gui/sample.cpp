#include "sample.h"

using namespace dgtl::example;

void gui::setup( void ) {
  ofSetVerticalSync(true);

  // we add this listener before setting up so the initial circle resolution is correct
  CircleResolution.addListener(this, &gui::circleResolutionChanged);
  RingButton.addListener(this, &gui::ringButtonPressed);

  Panel.setup(); // most of the time you don't need a name
  Panel.add(Filled.setup("fill", true));
  Panel.add(Radius.setup("Radius", 140, 10, 300));
  Panel.add(Center.setup("Center", ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
  Panel.add(Color.setup("Color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
  Panel.add(CircleResolution.setup("circle res", 5, 3, 90));
  Panel.add(TwoCircles.setup("two circles"));
  Panel.add(RingButton.setup("Ring"));
  Panel.add(ScreenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));

  Hide = false;

  Ring.load("ring.wav");
}

void gui::exit( void ) {
  RingButton.removeListener(this, &gui::ringButtonPressed);
}

void gui::circleResolutionChanged( int &CircleResolution ) {
  ofSetCircleResolution(CircleResolution);
}

void gui::ringButtonPressed( void ) {
  Ring.play();
}

void gui::update( void ) {
  ofSetCircleResolution(CircleResolution);
}

void gui::draw( void ) {
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    
  if (Filled)
    ofFill();
  else
    ofNoFill();

  ofSetColor(Color);

  if (TwoCircles) {
    ofDrawCircle(Center->x-Radius*.5, Center->y, Radius);
    ofDrawCircle(Center->x+Radius*.5, Center->y, Radius);
  }
  else
    ofDrawCircle((ofVec2f)Center, Radius );
  
  // auto draw?
  // should the Panel control hiding?
  if(!Hide) {
    Panel.draw();
  }
}

void gui::keyPressed( int Key ) {
  switch (Key) {
  case 'h':
    Hide = true - Hide;
    break;
  case 's':
    Panel.saveToFile("settings.xml");
    break;
  case 'l':
    Panel.loadFromFile("settings.xml");
    break;
  case ' ':
    Color = ofColor(255);
    break;
  }
}

void gui::keyReleased( int Key ) {
  
}

void gui::mouseMoved( int X, int Y ) {

}

void gui::mouseDragged( int X, int Y, int Button ) {

}

void gui::mousePressed( int X, int Y, int Button ) {
  
}

void gui::mouseReleased( int X, int Y, int Button ) {
  
}

void gui::mouseEntered( int X, int Y ) {

}

void gui::mouseExited( int X, int Y ) {

}

void gui::windowResized( int W, int H ) {
    ScreenSize = ofToString(W) + "x" + ofToString(H);
}

void gui::gotMessage( ofMessage Msg ) {
  
}

void gui::dragEvent( ofDragInfo DragInfo ) {
  
}
