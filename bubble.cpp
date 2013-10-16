#include <cstdlib>
#include <GL/glut.h>
#include "bubble.hpp"
#include <cstdio>
#include "utils.hpp"
#include <cmath>

int Bubble::count = 0;

extern int current;

//TODO: fix origination of bubble to take into account salmon rotation


Bubble::Bubble(double x, double y):x_(x),y_(y),
	riserate_(1),scale_(1.0),diam_(5),blend_(0.8){
		count++;
		int size_var = rand() % 10;
		riserate_ = 0.5 + randf();

	
}

Bubble::~Bubble(){
	printf("blend value %f  ,",blend_);
	count--;
	printf("%d bubbles left\n",count);


}

int  Bubble::bubblecount(){
	return count;
}

void Bubble::draw(){
	GLfloat white[] = {1.0, 1.0, 1.0};
	GLfloat param[]={0};
	glGetMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, param);
	GLfloat shine=128;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glLoadIdentity();
	int xpos = 75 + (rand() % 5);
	int ypos = -22 + (rand() % 3);
	glTranslatef(x_+xpos,y_+ypos,0.0);
	glColor4f(.6,.6,.7,blend_);
	glScalef(scale_,scale_,scale_);
	
    glNormal3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (double i = 0.0; i < 2 * M_PI; i += M_PI / 6)
        glVertex3f(cos(i) * 6, sin(i) * 6, 0.0);
    glEnd();
	//glutSolidSphere(diam_,12,12);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, param);
	glDisable(GL_BLEND);
}
	

void Bubble::up(){
	y_ += riserate_ + randf();
	x_ += current/2 + randf();
	scale_ += riserate_/200;
	if (blend_ > .1)
		blend_ -= .0015;
}

double Bubble::getX(){
	return x_;
}

double Bubble::getY(){
	return y_;
}

bool Bubble:: isOutOfBound(){
	double viewport[4];
    glGetDoublev(GL_VIEWPORT, viewport);
    double window_w = viewport[2];
    double window_h = viewport[3];

	if ((y_ - diam_*scale_) > window_h)
		return true;
	else
		return false;
}