//I made a lot of changes to spelling, grammar, indentation and spacing
// but I didn't make a comment at each instance because it was annoying 
// and didn't seem necessary -AY

/**
@file CatPicApp.cpp
CSE 274
@author Katie Lackey

Include which requirements your program satisfys here -AY
This program satisfys the following requirements: 
A.1 (rectangle), A.2 (circle), A.3 (line), A.
B.1 (blur)
C - draws mickey mouse
D - saves to a file "lackeykn.png"
E.5 (annimation: mickey mouse moves across the screen)
	E.6 (mouse event: triangles appear where mouse is clicked)

*/
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"
#include "cinder/Rand.h"

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
	//surface area that will have the shapes on it
	Surface* mySurface_; 

	//an int used to make objects move
	int draw_offset;

	//int variables for the mouse interaction method
    int tr_randSize;
    int tr_x;
    int tr_y;

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

	//Rectangle method that draws a rectangle.	
	void CreateRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);

	//Method draws a line on the screen,
	void drawLine(uint8_t*pixels, int length, int ptOneh, int ptTwo);

	//There the circle methods draw circles in the shape on mickey mouse.
	void drawCircles(uint8_t* dataArray, int x, int y, int r);
	void drawCircle2(uint8_t* dataArray, int x, int y, int r);
	void drawCircle3(uint8_t* dataArray, int x, int y, int r);

	//Method makes a bunch of lines
	void makeLine(uint8_t* dataArray, int x0, int y0, int x1, int y1);

	//Method blurs the edges of the shapes
	void selectiveBlur(uint8_t* blur_pattern);

	//Method clears the screen each time it is ran by painting it white first. 
		//Then the shapes are painted ontop if it.
	void clear(uint8_t* dataArray);

	//Method draws a rectangle
	void drawTriangle(uint8_t* dataArray, int sideLength, int pointX,int pointY);
};

/**This menthod clears the screen each time it
is ran so that the screen goes white. The objects 
are then painted over the white screen.
*/
void CatPicApp::clear(uint8_t* dataArray){
	//Changed some values here so that the method would clear out the whole 
	// screen and get rid of the little gray edges -AY
	for ( int y=0; y <= kAppHeight-1; y++){	//changed y from 10 to 0 -AY	
		for ( int x = 0; x <= kAppWidth-1; x++) { //changed x from 20 to 0 -AY
			dataArray [3* (x+y*kSurfaceSize)]=225;			
			dataArray [3* (x+y*kSurfaceSize)+1]=225;			
			dataArray [3* (x+y*kSurfaceSize)+2]=225;					
		}		
	}
}

/** This method creates the rectangle.
It takes in 4 variables to create the rectangle
filles requirement A.1
@param dataArray is pixels in the array
@param x1 is the starting coordinate of x
@param y1 is the starting coordinate of y
@param x2 is the ending coordinate of x
@param y2 is the ending coordinate of y
*/
void CatPicApp::CreateRectangle(uint8_t* dataArray, int x1, int y1, int x2, int y2){
	//inital variables that create the start and end points of the rectangle 
	int startx = (x1 < x2) ? x1 : x2;
	int endx = (x1 < x2) ? x2 : x1;
	int starty = (y1 < y2) ? y1 : y2;
	int endy = (y1 < y2) ? y2 : y1;
	//x1 y1
		//x2 y1
	//checking the boundary 
	if(endx < 0) return; 
	if(endy < 0) return; 
	if(startx >= kAppWidth) return;
	if(starty >= kAppHeight) return;
	if(endx >= kAppWidth) endx = kAppWidth-1;
	if(endy >= kAppHeight) endy = kAppHeight-1;

	//making the rectangle
	for ( int y=starty; y <= endy; y++){		
		for ( int x = startx; x <= endx; x++) {		
			dataArray [3* (x+y*kSurfaceSize)]=20;			
			dataArray [3* (x+y*kSurfaceSize)+1]=40;			
			dataArray [3* (x+y*kSurfaceSize)+2]=30;					
		}		
	}
}

/**This method draws a traingle
fills reguirment B.1
@param dataArray is the pixels
@param sideLength is the length of each traingle side
@param pointX is one of the traingle points
@param pointY is antoehr traingle point
*/
void CatPicApp::drawTriangle(uint8_t* dataArray, int sideLength, int pointX,int pointY){
	if((pointX<=kAppWidth)&&((pointX + sideLength) <= kAppWidth)){

		int x = pointX;
		int y = pointY;

		for(int side1=0; side1<= sideLength; side1++){
			dataArray[3*(x+y*kSurfaceSize)] =0;
			dataArray[3*(x+y*kSurfaceSize)+1] =0;
			dataArray[3*(x+y*kSurfaceSize)+2] =225;
			x=x+1;
			y=y+1;
		}
		for(int side1=0; side1<= sideLength*2; side1++){
			dataArray[3*(x+y*kSurfaceSize)] =0;
			dataArray[3*(x+y*kSurfaceSize)+1] =0;
			dataArray[3*(x+y*kSurfaceSize)+2] =225;
			x=x-1;
		}
		for(int side1=0; side1<= sideLength; side1++){
			dataArray[3*(x+y*kSurfaceSize)] =0;
			dataArray[3*(x+y*kSurfaceSize)+1] =0;
			dataArray[3*(x+y*kSurfaceSize)+2] =225;
			x=x+1;
			y=y-1;
		}
	}
}

/*This method draws a straight line. 
fills requirement A.3
@param dataArray are the pixels
@param length is the length of the line
@param ptOne is a point on the line
@param ptTwo is another point on the line
*/
void CatPicApp::drawLine(uint8_t*dataArray, int length, int ptOne, int ptTwo){
	int x = ptOne;
	int y = ptTwo;
	for(int i=0; i<= length; i++){
		dataArray [3*(x+(y*kSurfaceSize))]=0;
		dataArray [3*(x+(y*kSurfaceSize))+1]=0;
		dataArray [3*(x+(y*kSurfaceSize))+2]=0;

		x+=1; //changed from x=x+1 -AY
		y+=1; //changed from y=y+1 -AY
	}
}

void CatPicApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

/**This method draws a circle.
Three variables are taken in during this method to create the circle.
This circle is also used to create part of the mickey mouse outline.
fills requirement A.2 and also helps fill the picture requirement 
@Param dataArray are the pixels
@param center_x is the center x coordinate 
@param center_y is the center y coordinate
@param r is the radius of the cirlce 
*/
void CatPicApp::drawCircles(uint8_t* dataArray, int center_x, int center_y, int r){
	if(r<=0) return;

	for (int y=center_y-r; y<=center_y+r; y++){		
		for (int x=center_x-r; x<=center_x+r; x++) {
			if(y<0 || x<0 || x>= kAppWidth || y>= kAppHeight) 
				continue;
			int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(distanceFromCenter <=r){
				int equation = 3*(x+y*kSurfaceSize);
				dataArray[equation] = 50;			
				dataArray[equation+1] = 30;			
				dataArray[equation+2] = 102;					
			}
		}
	}
}

/*This circle is used to create part of the mickey mouse outline
helps fill the picture requirement  
@Param dataArray are the pixels
@param center_x is the center x coordinate 
@param center_y is the center y coordinate
@param r is the radius of the cirlce 
*/
void CatPicApp:: drawCircle2(uint8_t* dataArray, int center_x, int center_y, int r){
	if(r<=0) return;	
	for (int y=center_y-r; y<=center_y+r; y++){		
		for (int x=center_x-r; x<=center_x+r; x++) {
			if(y<0 || x<0 || x>= kAppWidth || y>= kAppHeight) 
				continue;
			int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(distanceFromCenter <=r){
				int offset = 3*(x+y*kSurfaceSize);
				dataArray[offset] = 50;			
				dataArray[offset+1] = 30;			
				dataArray[offset+2] = 102;					
			}
		}
	}
}

/*This method is used to creat part of the mickey mouse outline.
Helps fill the picture requirement 
@Param dataArray are the pixels
@param center_x is the center x coordinate 
@param center_y is the center y coordinate
@param r is the radius of the cirlce 
*/
void CatPicApp:: drawCircle3(uint8_t* dataArray, int center_x, int center_y, int r){
	if(r<=0) return;	
	for (int y=center_y-r; y<=center_y+r; y++){		
		for (int x=center_x-r; x<=center_x+r; x++) {
			if(y<0 || x<0 || x>= kAppWidth || y>= kAppHeight) 
				continue;
			int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(distanceFromCenter <=r){
				int offset = 3*(x+y*kSurfaceSize);
				dataArray[offset] = 50;			
				dataArray[offset+1] = 30;			
				dataArray[offset+2] = 102;					
			}
		}
	}
}

/**This method blurs the edges of the shapes
fills requirement B.1
*/
void CatPicApp::selectiveBlur(uint8_t* blur_pattern){
	for(int y=1; y <= kAppHeight-1; y++){
		for (int x=1; x <= kAppWidth-1; x++){
			int totalR = 0;
			int totalG = 0;
			int totalB = 0;
			for(int innerY=y-1; innerY <= y+1; innerY++){
				for(int innerX=x-1; innerX <= x+1; innerX++){
					totalR = totalR + blur_pattern[3*(innerY+innerX*kSurfaceSize)];
					totalG = totalG + blur_pattern[3*(innerY+innerX*kSurfaceSize)+1];
					totalB = totalB + blur_pattern[3*(innerY+innerX*kSurfaceSize)+2];
				}
			}
			blur_pattern[3*(y+x*kSurfaceSize)]=totalR/9.0;
			blur_pattern[3*(y+x*kSurfaceSize)+1]=totalG/9.0;
			blur_pattern[3*(y+x*kSurfaceSize)+2]=totalB/9.0; //changed these from 9 to 9.0 -AY
		}
	}
}

/**This method makes a few line segmenst that go across the screen
It is a bunch of dots that are alligned very close to each other to look like a line.
fills requirement A.3
@param dataArray are the pixels
@param ptX0 is the staring x coordinate 
@param ptY0 is the staring y coordinate
@param ptX1 is the ending x coordinate
@param ptY1 is the ending y coordinate
*/
void CatPicApp:: makeLine(uint8_t* dataArray, int ptX0, int ptY0, int ptX1, int ptY1){
	int x, offset;
	float dy, dx, y, midPt;
	dy = ptY1 - ptY0;	
	dx = ptX1 - ptX0;	
	midPt = dy / dx;	
	y = ptY0;

	for(x = ptX0; x <= ptX1; x++){
		offset = 3 *(x + (y*kSurfaceSize));
		dataArray[offset]=225;
		dataArray[offset+1]=0;
		dataArray[offset+2]=0;
		y = y+midPt; 
	}
}

/**This method allows for interaction with the user while the 
project is being ran. This fills one of the last section requirements
*/
void CatPicApp::mouseDown( MouseEvent event ){	
	
	tr_randSize = Rand::randInt(0, 300);	
	tr_x = event.getX();	
	tr_y = event.getY();
}

/**The update() method updates the program before it is ran each
time. Anything  that you want to appear when ran must be declared here.
*/
void CatPicApp::update(){
	//needed to draw the application on the screen
	uint8_t* dataArray = (*mySurface_).getData();

	//Clear the screen
	clear(dataArray);
	
	//allows objects to move. This fills one of the last sections requirements 
	draw_offset+=10; //changed from draw_offset=draw_offset+10;
    drawCircles(dataArray, 260+draw_offset, 190+draw_offset, 80);
    drawCircle2(dataArray, 400+draw_offset, 400+draw_offset, 180);
    drawCircle3(dataArray, 550+draw_offset, 195+draw_offset, 80);

	CreateRectangle(dataArray, 10, 10, 100, 100);
    drawLine(dataArray, 80, 600, 50); //changed value from 400 to 50 to make line more visable -AY
    makeLine(dataArray, 0, 0, 300, 500);
    selectiveBlur(dataArray);
	drawTriangle(dataArray, 60, 120, 140);
	
	//draw a triangle with a mouse click, another mouse click redraws the triangle elsewhere
	drawTriangle(dataArray, tr_randSize, tr_x, tr_y);
	//Moved this so that the triangles draw on top instead of behind the surface -AY
	
	writeImage("lackeykn.png",*mySurface_);
}

//This method sets up the program
void CatPicApp::setup(){
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,false);
	draw_offset=0;
	tr_randSize=140;
    tr_x=60;
    tr_y=120;
}

//Everything is drawn in this method. Without this method nothing would get drawn on the screen.
void CatPicApp::draw(){

	//Clear the surface with a green color
	gl::clear(Color(0,3,5));

	////Draw the surface
	gl::draw(*mySurface_);

	//setting a timer so that the mickey face moves every second.
	Timer t;
    t.start();
    while(t.getSeconds() < 1.00){
    }
    t.stop();
}

CINDER_APP_BASIC( CatPicApp, RendererGl )

	