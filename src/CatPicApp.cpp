#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"


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
	//Brightness of the screen
	//float brightness;
	Surface* mySurface_; 

	//width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;

void CreateRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
};
void CatPicApp::CreateRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2){
	int startx = (x1 < x2) ? x1 : x2;
	int endx = (x1 < x2) ? x2 : x1;
	int starty = (y1 < y2) ? y1 : y2;
	int endy = (y1 < y2) ? y2 : y1;

	//checking the boundary 
	if(endx < 0) return; 
	if(endy < 0) return; 
	if(startx >= kAppWidth) return;
	if(starty >= kAppHeight) return;
	if(endx >= kAppWidth) endx = kAppWidth-1;
	if(endy >= kAppHeight) endy = kAppHeight-1;
}

void CatPicApp::setup(){
	mySurface_=new Surface(kTextureSize, kTextureSize, false);
	
	//brightness = .1;
}

void CatPicApp::mouseDown( MouseEvent event )
{
}

void CatPicApp::update(){
	//needed to draw the application on the screen
	uint8_t* dataArray = (*mySurface_).getData();
	
	
	//brightness = brightness + .01;
	//if(brightness>1)
		//brightness=0;
}

void CatPicApp::draw(){

	//Draw our surface to the screen, using graphics library
	gl::clear(Color(.01,2,.02));
	gl::draw(*mySurface_);
	// clear out the window with black
	//gl::clear( Color( .01, 2, .01 ) ); 

}

CINDER_APP_BASIC( CatPicApp, RendererGl )

	