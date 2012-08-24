#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPicApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
private:
	float brightness;
};

void CatPicApp::setup()
{
	brightness = .1;
}

void CatPicApp::mouseDown( MouseEvent event )
{
}

void CatPicApp::update()
{
	brightness = brightness + .01;
	if(brightness>1){
		brightness=0;
	}
}

void CatPicApp::draw()
{
	// clear out the window with black
	gl::clear( Color( brightness, 2, brightness ) ); 
}

CINDER_APP_BASIC( CatPicApp, RendererGl )

	