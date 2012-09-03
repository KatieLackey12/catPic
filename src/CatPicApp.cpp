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
	Surface* mySurface_; 


	struct circleData{
		int x;
		int y;
		int r;
	};
	//deque<rings_info> rings_list_;
	//width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kSurfaceSize=1024;
	
void CreateRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
void drawLine(uint8_t*pixels, int line1_width, int line2_height);
void drawCircles(uint8_t* dataArray, int x, int y, int r);

};
void CatPicApp::CreateRectangle(uint8_t* dataArray, int x1, int y1, int x2, int y2){
	
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
void CatPicApp::drawLine(uint8_t*dataArray, int line1_width, int line2_height){
	//making a line
	for(int i=0; i<=line1_width;i++){
		//for(int i=0; line2_height;i++){
		dataArray[3*i]=10;
		dataArray[3*i+1]=10;
		dataArray[3*i+2]=10;
		//}
}
}

	

void CatPicApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}
void CatPicApp::setup(){
	mySurface_=new Surface(kSurfaceSize, kSurfaceSize, false);
	
	//brightness = .1;

	
}

void CatPicApp::mouseDown( MouseEvent event )
{
}
void CatPicApp::drawCircles(uint8_t* dataArray, int center_x, int center_y, int r){
	if(r<=0) return;	
	//int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x)+(y-center_y)*(y-center_y)));
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
void CatPicApp::update(){
	uint8_t* dataArray = (*mySurface_).getData();
	//needed to draw the application on the screen
	CreateRectangle(dataArray, 200,100,200,100);
	drawLine(dataArray,40,30);
	drawCircles(dataArray, 500, 300, 100);
	
	//brightness = brightness + .01;
	//if(brightness>1)
		//brightness=0;
}

void CatPicApp::draw(){

	//Clear the surface with a green color
	gl::clear(Color(0,3,5));
	//Draw the surface
	gl::draw(*mySurface_);
	// clear out the window with black
	//gl::clear( Color( .01, 2, .01 ) ); 

}

CINDER_APP_BASIC( CatPicApp, RendererGl )

	