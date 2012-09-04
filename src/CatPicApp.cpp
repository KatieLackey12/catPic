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
	//surface area that will have the shapes on it
	Surface* mySurface_; 

	//the variables for the drawCircle method
	struct circleData{
		int x;
		int y;
		int r;
	};
	//uint8_t* my_blur_pattern_;
	//width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kSurfaceSize=1024;
//Rectangle method that draws a rectangle onto the screen.	
void CreateRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
void drawLine(uint8_t*pixels, int length, int ptOneh, int ptTwo);
//Method draws a circle onto the screen.
void drawCircles(uint8_t* dataArray, int x, int y, int r);
void drawCircle2(uint8_t* dataArray, int x, int y, int r);
void drawCircle3(uint8_t* dataArray, int x, int y, int r);
//Method makes a bunch of lines on the screen
void makeLine(uint8_t* dataArray, int x0, int y0, int x1, int y1);
//Method make a copy of the rectangle already created
void copyRectangle(uint8_t* dataArray, int x_width, int y_height, int x_origin, int y_origin, int y_original_rect);
//Method blurs the edges of the shapes
void selectiveBlur(uint8_t* blur_pattern);
//void drawAccident(uint8_t* pixels, int center_x, int center_y, int r);
//Method clears the screen each time it is rain by painting it white first. Then the shapes are painted ontop if it.
void clear(uint8_t* dataArray);

};

void CatPicApp::clear(uint8_t* dataArray){
	//making the rectangle
	for ( int y=10; y <= kAppHeight-1; y++){		
		for ( int x = 20; x <= kAppWidth-1; x++) {		
			dataArray [3* (x+y*kSurfaceSize)]=225;			
			dataArray [3* (x+y*kSurfaceSize)+1]=225;			
			dataArray [3* (x+y*kSurfaceSize)+2]=225;					
		}		
	}

}
/** This method creates the rectangle that apprears on the screen when ran.
It makes in 4 variables to create the rectangle
filles requirement 1
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
/*This method draws a straight line when the program is ran. 
fills requirement 1
*/
void CatPicApp::drawLine(uint8_t*dataArray, int length, int ptOne, int ptTwo){
	//making a line
	int x = ptOne;
	int y = ptTwo;
	for(int i=0; i<= length; i++){
		dataArray [3*(x+(y*kSurfaceSize))]=0;
		dataArray [3*(x+(y*kSurfaceSize))+1]=0;
		dataArray [3*(x+(y*kSurfaceSize))+2]=0;

		x=x+1;
		y=y+1;
	}
}
void CatPicApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}


void CatPicApp::mouseDown( MouseEvent event )
{
}
/**This method draws a circle on the screen when ran.
Three variables are taken in during this method to create the circle.
This circle is also used to create part of the mickey mouse outline.
fills requirement 1 and also helps fill the picture requirement 
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
//This circle is used to create part of the mickey mouse outline
//helps fill the picture requirement  
void CatPicApp:: drawCircle2(uint8_t* dataArray, int center_x, int center_y, int r){
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
//This method is used to creat part of the mickey mouse outline.
//Helps fill the picture requirement 
void CatPicApp:: drawCircle3(uint8_t* dataArray, int center_x, int center_y, int r){
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
fills requirement 1
*/
void CatPicApp::copyRectangle(uint8_t* dataArray, int x_width, int y_height, int x_origin, int y_origin, int y_original_rect){
	int offSet = (y_origin - y_original_rect);
	if((x_width < kAppWidth) && ((y_height + y_origin) < kAppHeight)){
	for(int i = y_origin; i<= (y_height + y_origin); i++){
		for(int j= x_origin; j<= (x_origin + x_width); j++){
			dataArray[3*(i+j*kSurfaceSize)] = dataArray[3*(i +(j-offSet)*kSurfaceSize)]=10;
			dataArray[3*(i+j*kSurfaceSize)] = dataArray[3*(i +(j-offSet)*kSurfaceSize+1)]=20;
			dataArray[3*(i+j*kSurfaceSize)] = dataArray[3*(i +(j-offSet)*kSurfaceSize)+2]=0;
		}
	}
}
}
/**This method is a blue method and it blues the edges of the shapes
to make the look less crsip.
fills requirement 2
*/
void CatPicApp::selectiveBlur(uint8_t* blur_pattern){
	float kernel[9] = 
	{ 1/9.0,1/9.0,1/9.0,
	1/9.0,1/9.0,1/9.0,
	1/9.0,1/9.0,1/9.0};
	for(int y=1; y<= kAppHeight-1; y++){
		for (int x=1; x<= kAppWidth-1; x++){
			int totalR = 0;
			int totalG =0;
			int totalB=0;
			for(int innerY=y-1; innerY <= y+1; innerY++){
				for(int innerX=x-1; innerX <= x+1; innerX++){
				//calculate offset for innerX and innerY
					totalR = totalR + blur_pattern[3*(innerY+innerX*kSurfaceSize)];
					totalG = totalG + blur_pattern[3*(innerY+innerX*kSurfaceSize)+1];
					totalB = totalB + blur_pattern[3*(innerY+innerX*kSurfaceSize)+2];
				}
			}
			blur_pattern[3*(y+x*kSurfaceSize)]=totalR/9;
			blur_pattern[3*(y+x*kSurfaceSize)+1]=totalG/9;
			blur_pattern[3*(y+x*kSurfaceSize)+2]=totalB/9;
		}//calculate the offset for y and x
	}
	kernel[9];
}

/**This method makes a few line segmenst that go across the screen
when ran. It is a bunch of dots that a alligned very close to each other to
look like a line.
fills requirement 1
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

/*void CatPicApp::drawAccident(uint8_t* pixels, int center_x, int center_y, int r){
	//Bounds test
	if(r <= 0) return;
	
	int r2 = r*r;
	for(int y=center_y-r; y<=center_y+r; y++){
		for(int x=center_x-r; x<=center_x+r; x++){
			//Bounds test, to make sure we don't access array out of bounds
			if(y < 0 || x < 0 || x >= kAppWidth || y >= kAppHeight) continue;
			
			int dist = (x-center_x)*(x-center_x) + (y-center_y)*(y-center_y);
			if(dist <= r2){
				if((dist/49)%2 == 0){
					int offset = 3*(x + y*kSurfaceSize);
					pixels[offset] = 0;
					pixels[offset+1] = 0;
					pixels[offset+2] = 225;
				}
			}
		}
	}
}*/

/**The update() method updates the program before it is ran each
time. Anything  that you want to appear when ran must be declared here.
*/
void CatPicApp::update(){
	
	uint8_t* dataArray = (*mySurface_).getData();
	//needed to draw the application on the screen

	//Clear the screen
	clear(dataArray);

	CreateRectangle(dataArray, 200,100,200,100);
	drawLine(dataArray,80,600,400);
	drawCircles(dataArray, 260, 190, 80);
	drawCircle2(dataArray, 400,400,180);
	drawCircle3(dataArray, 550, 195, 80);
	makeLine(dataArray, 0, 0, 300, 500);
	copyRectangle(dataArray,200,100,200,100,100);
	selectiveBlur(dataArray);
	//brightness = brightness + .01;
	//if(brightness>1)
		//brightness=0;
	//tint = tint +.2;
	//if(frame_number_ == 0){
		writeImage("lackeykn.png",*mySurface_);
}
void CatPicApp::setup(){
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,false);
	//brightness = .1;
	//tint =.1;
	
}
void CatPicApp::draw(){

	//Clear the surface with a green color
	gl::clear(Color(0,3,5));
	////Draw the surface
	gl::draw(*mySurface_);
	// clear out the window with black
	//gl::clear( Color( .01, 2, .01 ) ); 

}

CINDER_APP_BASIC( CatPicApp, RendererGl )

	