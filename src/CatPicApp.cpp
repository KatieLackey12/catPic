/**
@file CatPicApp.cpp
CSE 274
@author Katie Lackey
*/
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
	void prepareSettings(Settings* settings);
private:
	//Brightness of the screen
	//float brightness;
	int tint;
	//surface area that will have the shapes on it
	Surface* mySurface_; 

	//the variables for the drawCircle method
	struct circleData{
		int x;
		int y;
		int r;
	};
	//width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kSurfaceSize=1024;
//Rectangle method that draws a rectangle onto the screen.	
void CreateRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
//void drawLine(uint8_t*pixels, int lineStart, int line_width, int line_height);
//Method draws a circle onto the screen.
void drawCircles(uint8_t* dataArray, int x, int y, int r);
//Method makes a bunch of lines on the screen
void makeLine(uint8_t* dataArray, int x0, int y0, int x1, int y1);
//Method make a copy of the rectangle already created
void copyRectangle(uint8_t* dataArray, int x_width, int y_height, int x_origin, int y_origin, int y_original_rect);


};
/** This method creates the rectangle that apprears on the screen when ran.
It makes in 4 variables to create the rectangle
*/
void CatPicApp::CreateRectangle(uint8_t* dataArray, int x1, int y1, int x2, int y2){
	//inital variables that create the start and end points of the rectangle 
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

	//making the rectangle
	for ( int y=10; y <= endy; y++){		
		for ( int x = 20; x <= endx; x++) {		
			dataArray [3* (x+y*kSurfaceSize)]=20;			
			dataArray [3* (x+y*kSurfaceSize)+1]=40;			
			dataArray [3* (x+y*kSurfaceSize)+2]=30;					
		}		
	}
}
/*void CatPicApp::drawLine(uint8_t*dataArray, int lineStart, int line_width, int line_height){
	//making a line
	int lineLength =32;
	if((lineStart + line_width)<=kAppWidth){

	for(int i= lineLength; i<=line_height;i++){
		for(int j=lineStart; j<=line_width;j++){
		dataArray[3*(lineStart + lineLength*(kSurfaceSize))];
		dataArray[3*(lineStart + lineLength*(kSurfaceSize))+1];
		dataArray[3*(lineStart + lineLength*(kSurfaceSize))+2];
		}
	}
}
}*/
void CatPicApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}
void CatPicApp::setup(){
	mySurface_=new Surface(kSurfaceSize, kSurfaceSize, false);
	
	//brightness = .1;
	//tint =.1;
	
}

void CatPicApp::mouseDown( MouseEvent event )
{
}
/**This method draws a circle on the screen when ran.
Three variables are taken in during this method to create the circle.
*/
void CatPicApp::drawCircles(uint8_t* dataArray, int center_x, int center_y, int r){
	if(r<=0) return;	
	for (int y=center_y-r; y<=center_y+r; y++){		
		for (int x=center_x-r; x<=center_x+r; x++) {
			if(y<0 || x<0 || x>= kAppWidth || y>= kAppHeight) 
				continue;
			int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(distanceFromCenter <=r){
				int offset = 3*(x+y*kSurfaceSize);
			dataArray[offset] = dataArray[offset]/2;			
			dataArray[offset] = dataArray[offset]/2;			
			dataArray[offset] = dataArray[offset]/2;					
		}
		}
	}
}
/**This method creates and copy of the inital rectangle.
*/
void CatPicApp::copyRectangle(uint8_t* dataArray, int x_width, int y_height, int x_origin, int y_origin, int y_original_rect){
	int offSet = (y_origin - y_original_rect);
	if((x_width < kAppWidth) && ((y_height + y_origin) < kAppHeight)){
	for(int i = y_origin; i<= (y_height + y_origin); i++){
		for(int j= x_origin; j<= (x_origin + x_width); j++){
			dataArray[3*(i+j*kSurfaceSize)] = dataArray[3*(i +(j-offSet)*kSurfaceSize)];
			dataArray[3*(i+j*kSurfaceSize)] = dataArray[3*(i +(j-offSet)*kSurfaceSize+1)];
			dataArray[3*(i+j*kSurfaceSize)] = dataArray[3*(i +(j-offSet)*kSurfaceSize)+2];
		}
	}
}
}
/**This method makes a few line segmenst that go across the screen
when ran.
*/
void CatPicApp:: makeLine(uint8_t* dataArray, int x0, int y0, int x1, int y1){
	int x, offset;
	float dy, dx, y, m;
	dy = y1-y0;
	dx = x1-x0;
	m = dy/dx;//find the midpoint
	y = y0;

	for(x = x0; x <= x1; x++){
		offset = 3 *(x + (y*kSurfaceSize));

		dataArray[offset]=225;
		dataArray[offset+1]=0;
		dataArray[offset+2]=0;
		y = y+m; 
	}
}

/**The update() method updates the program before it is ran each
time. Anything  that you want to appear when ran must be declared here.
*/
void CatPicApp::update(){
	uint8_t* dataArray = (*mySurface_).getData();
	//needed to draw the application on the screen
	CreateRectangle(dataArray, 200,100,200,100);
	//drawLine(dataArray,40,30,10);
	drawCircles(dataArray, 500, 300, 100);
	makeLine(dataArray, 0, 0, 300, 500);
	copyRectangle(dataArray,200,100,100,300,100); 
	//brightness = brightness + .01;
	//if(brightness>1)
		//brightness=0;
	//tint = tint +.2;
}

void CatPicApp::draw(){

	//Clear the surface with a green color
	gl::clear(Color(0,3,5));
	////Draw the surface
	gl::draw(*mySurface_);
	// clear out the window with black
	//gl::clear( Color( .01, 2, .01 ) ); 
	//tint;

}

CINDER_APP_BASIC( CatPicApp, RendererGl )

	