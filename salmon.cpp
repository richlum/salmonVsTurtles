#include <cmath>
#include <iostream>
#include "salmon.hpp"
#include "utils.hpp"
#include <cstdio>
#include "bubble.hpp"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


#define DEBUG true

Salmon::Salmon():
x_(100.0), y_(100.0), rotation_(0.0), advanced_(false),
lastx_(100.0), lasty_(100.0),jaw_angle_(0.0),lastrotation_(0.0),
collided_(false), length_(70.0), width_(20.0), isAlive_(true) {
    
    setColour();

}

void Salmon::reset() {
    advanced_ = false;
    isAlive_ = true;
    collided_ = false;
    rotation_ = 0.0;
	jaw_angle_ = 0.0;
    setColour();

    // Position salmon slightly left of centre of viewport.
    double viewport[4];
    glGetDoublev(GL_VIEWPORT, viewport);
    double window_w = viewport[2];
    double window_h = viewport[3];

    x_ = window_w / 3;
    y_ = window_h / 2;
	updatelastxy();

}



void Salmon::setAdvanced(bool advanced){
	
	if (advanced != advanced_){
	
		advanced_= advanced;
	}
}

void Salmon::updatelastxy(){
	lastx_ = x_;
	lasty_ = y_;
}

void Salmon::setColour() {
    
    // Salmon colour defaults to 'salmon-ish.'
    colour_[0] = 0.98;
    colour_[1] = 0.20;
    colour_[2] = 0.04;
    colour_[3] = 1.0;
}

bool Salmon::isAlive() const {
    return isAlive_;
}

bool Salmon::hasCollided() const {
    return collided_;
}

// rotate what ever x y input to an equivalent x y component along
// salmon frame of reference.
// eg a vertical salmon will move up when right arrow is pressed
void to_rotated_coord(double x, double y, double rotation,  double *newx, double *newy){
		*newx = (x*cos(rotation*M_PI/180.0)) - (y*sin(rotation*M_PI/180.0));
		*newy = (x*sin(rotation*M_PI/180.0)) + (y*cos(rotation*M_PI/180.0));
}

void Salmon::collisionmove(double x, double y) {
    
	lastx_ = x_;
	lasty_ = y_;
	
	x_ += x;
	y_ += y;
	
}



void Salmon::move(double x, double y) {
    
    if (!isAlive_ || collided_) {
        return;
    }

	lastx_ = x_;
	lasty_ = y_;
	if (advanced_){
		// movement should be along salmon axis 
		double newx, newy;
		to_rotated_coord(x, y, rotation_, &newx, &newy);
		if (DEBUG) printf("new xy = (%f, %f) \n", newx, newy);
		x_ += newx;
		y_ += newy;
	}else{
		x_ += x;
		y_ += y;
	}

	////do bounding box check to see if salmon is hitting window bounds
	double viewport[4];
    glGetDoublev(GL_VIEWPORT, viewport);
    double window_w = viewport[2];
    double window_h = viewport[3];

	if ( ((getXcoordinate() - length_) <= 0)){
		x_ = length_+abs(x);
		lastx_ = length_;
	};
	if (	((getXcoordinate() + length_) >= window_w) ){
		x_ = window_w - length_ - abs(x);
		lastx_ = window_w;
	};
	if(	((getYcoordinate() - width_) <= 0 ) ){
		y_ = width_ +abs(y);
		lasty_ = width_;
	};
	if ( ((getYcoordinate() + width_) > window_h) ) {
		y_ = window_h - width_ - abs(y);
		lasty_ = window_h-width_;
	};

}


int Salmon::getXcoordinate() const {
		return x_;
}

int Salmon::getYcoordinate() const {
		return y_;
}



void Salmon::setCollided(bool collided)
{
    collided_ = collided;
    // @@@@@@@@@@
    //
    // @@@@@@@@@@
};

void Salmon::rotate(double angle) {

	if (isAlive_ && !collided_) {

		lastrotation_ = rotation_;
		rotation_ += angle;
		updatelastxy();
	}
}

void Salmon::setRandomColour() {
    
    // @@@@@@@@@@
    // Give the salmon a random colour here.
    // @@@@@@@@@@
	colour_[0] = randf();
    colour_[1] = randf();
    colour_[2] = randf();
    colour_[3] = 1.0;
}

// this calculates a bunch of stuff but doesnt actually do anything

void Salmon::update() {

    if (collided_ || !isAlive_) {
        return;
    }
 
    // Get window width.
    double viewport[4];
    glGetDoublev(GL_VIEWPORT, viewport);
    double window_w = viewport[2];
    double window_h = viewport[3];

    // Evaluate trig quantities based on salmon's rotation.
    double sinR = sin(rotation_*M_PI/180.0);
    double cosR = cos(rotation_*M_PI/180.0);
    double offset = length_/4.0;
    double vRadius = width_/2.0 + fabs(cosR)*offset;
    double hRadius = width_/2.0 + fabs(sinR)*offset;

	

}

//randomly emit 1 to 10 bubbles
void Salmon::emitbubble(){
	if (advanced_ ){
		int qty = 1+(rand() % 10);
		for(int i = 0; i<qty;i++){
			bubble = new Bubble(x_,y_);
			bubbles.push_back(bubble);
		}
	}
}
void Salmon::draw() {

    if (!isAlive_) {
        return;
    }   
 
    // Setup transformation matrix for the salmon.
    glPushMatrix();

    // @@@@@@@@@@
	// There are several different tasks to complete here:
    // - Use glTranslate to set the position of the salmon.
    // - Use glRotate to set the rotation of the salmon.
	// - Set the colour of the salmon.
    // @@@@@@@@@@
	double deltax = x_ - lastx_;
	double deltay = y_ - lasty_;
	
	glTranslatef(x_, y_, 0);
	glRotatef(rotation_,0,0,1);

    // We are now in a coordinate system with 0,0,0 at the centre of the salmon.
    // DRAW IT!
    
    // Salmon body (main body colour).
    glNormal3f(0, 0, 1);
    glColor4fv(colour_);
    glBegin(GL_POLYGON); //Naive.  Why are triangles better?
    glVertex3f(53.0, -20.0, 0);
    glVertex3f(53.0, 18.0, 0);
    glVertex3f(25.0, 40.0, 0);
    glVertex3f(-10.0, 40, 0);
    glVertex3f(-30.0, 35, 0);
    glVertex3f(-60.0, 20, 0);
    glVertex3f(-70.0, 15, 0);
    glVertex3f(-80.0, 12, 0);
    glVertex3f(-80.0, -10, 0);
    glVertex3f(-60.0, -15, 0);
    glEnd();
    
    // Salmon tail (sans fins).
    glBegin(GL_TRIANGLES);
    
    glVertex3f(-80.0, 12, 0);
    glVertex3f(-130.0, 30, 0);
    glVertex3f(-80.0, -10, 0);
    
    glVertex3f(-80.0, 12, 0);
    glVertex3f(-130.0, -30, 0);
    glVertex3f(-80.0, -10, 0);
    glEnd();
    
    // Salmon belly, dorsal fins, and contours (lighter).
    float belly_[] = { 0.98, 0.45, 0.04, 1.0 };
    glColor4fv(belly_);
    glPushMatrix();
    glScalef(1, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (double i = (6.8 / 6 ) * M_PI; i < 1.9 * M_PI; i += M_PI / 6) {
        glVertex3f(cos(i) * (1.2 * length_), sin(i) * length_, 0.0);
    }
    glEnd();
    glPopMatrix();
    
    glBegin(GL_TRIANGLES);
    
    glVertex3f(-40.0, 25, 0);
    glVertex3f(-70.0, 10, 0);
    glVertex3f(-80.0, 10, 0);
    
    glVertex3f(25.0, -5.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(35.0, 15.0, 0);
    
    glVertex3f(-90.0, 0, 0);
    glVertex3f(-130.0, 30, 0);
    glVertex3f(-110.0, 0, 0);
    
    glVertex3f(-90.0, 0, 0);
    glVertex3f(-130.0, -30, 0);
    glVertex3f(-110.0, 0, 0);
    
    glVertex3f(-60.0, 20, 0);
    glVertex3f(-70.0, 15, 0);
    glVertex3f(-75.0, 22, 0);

    glVertex3f(-10.0, 40, 0);
    glVertex3f(-30.0, 35, 0);
    glVertex3f(-30.0, 60, 0);
    
    glVertex3f(-30.0, 35, 0);
    glVertex3f(-30.0, 60, 0);
    glVertex3f(-50.0, 35, 0);
    
    glVertex3f(-30.0, 35, 0);
    glVertex3f(-40.0, 30, 0);
    glVertex3f(-50.0, 35, 0);
    
    glEnd();
    
    // Green lowlights.
    float lowlights_[] = { 0.17, 0.49, 0.27, 1.0 };
    glColor4fv(lowlights_);
    glBegin(GL_TRIANGLES);
    
    glVertex3f(-85.0, 0, 0);
    glVertex3f(-125.0, -28, 0);
    glVertex3f(-90.0, 0, 0);
    
    glEnd();
    
    // Green highlights.
    float highlights_[] = { 0.37, 0.67, 0.35, 1.0 };
    glColor4fv(highlights_);
    glBegin(GL_TRIANGLES);

    glVertex3f(-90.0, 0, 0);
    glVertex3f(-130.0, 30, 0);
    glVertex3f(-110.0, 0, 0);
    
    glVertex3f(-90.0, 0, 0);
    glVertex3f(-130.0, -30, 0);
    glVertex3f(-110.0, 0, 0);
    
    glEnd();
    
    // Salmon fins (same colour as body to contrast with belly).
    glColor4fv(colour_);
    glBegin(GL_TRIANGLES);
    
    glVertex3f(40.0, -15.0, 0);
    glVertex3f(15.0, -20.0, 0);
    glVertex3f(30.0, -40, 0);
    
    glVertex3f(0.0, -25.0, 0);
    glVertex3f(-20.0, -25.0, 0);
    glVertex3f(-25.0, -35, 0);
    
    glVertex3f(-60.0, -20, 0);
    glVertex3f(-70.0, -15, 0);
    glVertex3f(-75.0, -22, 0);
    
    glEnd();
    
    // Face and top mandible (greenish).
    float face_[] = { 0.37, 0.67, 0.35, 1.0 };
    glColor4fv(face_);
    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    
    glVertex3f(35.0, -5.0, 0);
    glVertex3f(55.0, 17.0, 0);
    glVertex3f(100.0, 10, 0);
    
    glVertex3f(35.0, -5.0, 0);
    glVertex3f(100.0, 10, 0);
    glVertex3f(60.0, -17, 0);

    glVertex3f(100.0, 10, 0);
    glVertex3f(93.0, -5, 0);
    glVertex3f(86.0, 10, 0);
    
    glEnd();
    
    // Lower mandible (darker green).
	if (advanced_){
		glPushMatrix();
		jaw_angle_+=.6;
		if (jaw_angle_ > 15)
			jaw_angle_ = 0.0;
		glRotatef(-jaw_angle_,0.0,0.0,1.0);
	}

	for (std::vector<Bubble*>::iterator it =bubbles.begin(); it!=bubbles.end();){
		Bubble* bubble =(Bubble*) *it ;
		bubble->up();
		bubble->draw();
		double bx = bubble->getX();
		double by = bubble->getY();
		if (bubble->isOutOfBound()){
			delete bubble;
			it = bubbles.erase(it);
			printf("deleting bubble\n");
		}else{
			it++;
		}
	}

    float jaw_[] = { 0.17, 0.49, 0.27, 1.0 };
    glColor4fv(jaw_);
    glBegin(GL_TRIANGLES);
    
    glVertex3f(37.0, -7.0, 0);
    glVertex3f(37.0, -25.0, 0);
    glVertex3f(75.0, -22, 0);
    
    glVertex3f(55.0, -20.0, 0);
    glVertex3f(100.0, -10.0, 0);
    glVertex3f(75.0, -22, 0);
    
    glEnd();
	if (advanced_){
		glPopMatrix();
	}
    // Eye
    glPushMatrix();
    glTranslatef(50, 0, 0);
	// animate eyes when collided, use jaw motion as driver.
	if (advanced_ && collided_){
		glScalef(ceil(jaw_angle_*2.0/15)+1,ceil(jaw_angle_*2.0/15)+1, ceil(jaw_angle_*2.0/15)+1);
	}
    const float white[] = {1.0, 1.0, 1.0, 1.0};
    glColor4fv(white);
    glNormal3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (double i = 0.0; i < 2 * M_PI; i += M_PI / 6)
        glVertex3f(cos(i) * 4, sin(i) * 4, 0.0);
    glEnd();
    glTranslatef(1, 0, 0);
    const float black[] = {0.0, 0.0, 0.0, 1.0};
    glColor4fv(black);
    glNormal3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (double i = 0.0; i < 2 * M_PI; i += M_PI / 6)
        glVertex3f(cos(i) * 2, sin(i) * 2, 0.0);
    glEnd();
    glPopMatrix();

    // Restore the transformation matrix.
    glPopMatrix();
	
	// gliding calculations to give salmon momentum
	double fadefactor = 1.0;  // amount to reduce next momentum increment
	if ((advanced_) && ((abs(deltax) > 0.9) || (abs(deltay)>0.9))){
		double adjdeltax=0.0;
		double adjdeltay=0.0;
		if (deltax>0)
			adjdeltax = deltax - fadefactor;
		if (deltax<0)
			adjdeltax = deltax + fadefactor;
		if (deltay>0)
			adjdeltay = deltay - (fadefactor+.1);
		if (deltay<0)
			adjdeltay = deltay + (fadefactor+.1);

		lastx_ = x_;
		lasty_ = y_;
		x_ = x_ + adjdeltax;
		y_ = y_ + adjdeltay;
	}

}


