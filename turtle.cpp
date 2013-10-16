#include <cmath>
#include <iostream>
#include "turtle.hpp"
#include "salmon.hpp"
#include "utils.hpp"
#include <cstdio>

extern int current, lightNo;

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif



Turtle::Turtle():
radius_(40), isAlive_(true), collided_(false) {
    
    double viewport[4];
    glGetDoublev(GL_VIEWPORT, viewport);
    double window_w = viewport[2];
    double window_h = viewport[3];
    
    y_ = randf() * window_h;
    x_ = window_w;
    setColour();
}

Turtle::Turtle(int xCoordinate, int yCoordinate):
x_(xCoordinate), y_(yCoordinate), radius_(40),
isAlive_(true), collided_(false) {

    setColour();
}

void Turtle::setColour() {
    
    shell_[0] = 0.01;
    shell_[1] = 0.62;
    shell_[2] = 0.08;
    shell_[3] = 1.0;
}

bool Turtle::isAlive() const {
    return isAlive_;
}

void Turtle::move(double x, double y) {
    
    if (!isAlive_ || collided_) {
        return;
    }
    x_ += x;
    y_ += y;
}

void Turtle::update(Salmon &salmon) {

    if (!isAlive_ || collided_) {
        return;
    }
    
    // Move the turtle with the current.
    move(current, 0);
    
    // Get window width.
    double viewport[4];
    glGetDoublev(GL_VIEWPORT, viewport);
    double window_w = viewport[2];
    double window_h = viewport[3];
    
    // Passof the screen (the left wall) and die.
    if (x_ < 0) {
        isAlive_ = false;
    }
    
	//
    // Impact with salmon (naive).
	//
    int salmon_x_ = salmon.getXcoordinate();
    int salmon_y_ = salmon.getYcoordinate();
    
    double distance = sqrt( pow((x_ - salmon_x_), 2) + pow((y_ - salmon_y_), 2) );
    if (distance <= 2.0 * radius_) {
		//salmon.move(-4,0);
        collided_ = true;
        setupLight();
        salmon.setCollided(true);
		salmon.setRandomColour();
		salmon.emitbubble();
		salmon.collisionmove(-4,0);
    }
}

void Turtle::setupLight() {
	// since we locate lights over turtle, make sure 
	// our frame of reference is what we expect
	glPushMatrix();
	glLoadIdentity();
	printf("turtle collision %f %f\n",x_,y_);

	GLfloat lightposition[] = {x_, y_, 20.0, 0.0};
	GLfloat direction[] = {0.0, 0.0, 1.0};
	GLfloat cutoffangle[] = {55.0};
	GLfloat ambient[] = {.30,.30,.30,1.0};
	GLfloat diffuse[] = {.4,.4,.4,1};
	glLightfv(collisionlights[currentlight], GL_AMBIENT, ambient);    // set the light color
	glLightfv(collisionlights[currentlight], GL_POSITION, lightposition);  // set the light source position over the turtle
	// turns down harshness of light on collision but harder to visually verify they are working
	//glLightfv(collisionlights[currentlight], GL_SPOT_DIRECTION, direction); // point the light directly at turtle
	//glLightfv(collisionlights[currentlight], GL_SPOT_CUTOFF, cutoffangle);  // narrow the light beam
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glEnable(collisionlights[currentlight]);
	glEnable(GL_LIGHTING);
	//glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	if (currentlight <5)
		currentlight++;
	else
		currentlight =0;

}

void Turtle::draw() {
    
    // Setup transformation matrix for the turtle
    
    glPushMatrix();
    glTranslatef(x_, y_, -10);
    glNormal3f(0, 0, 1);
    
    glNormal3f(0, 0, 1);
    
    // Turtle shell.
    glColor4fv(shell_);
    glBegin(GL_POLYGON);
	if (collided_){
		glMaterialfv(GL_FRONT, GL_EMISSION,shell_);
	}
    for (double i = 0; i < M_PI; i += M_PI / 12)
        glVertex3f(cos(i) * radius_, sin(i) * radius_, 0.0);
    glEnd();
	GLfloat none[] = { 0,0,0,1};
    glMaterialfv(GL_FRONT, GL_EMISSION, none);
    // Turtle body, tail, legs, and head.
    float skin_[] = { 0.73, 0.59, 0.27, 1.0};
    glColor4fv(skin_);

    glBegin(GL_TRIANGLES);
    
    glVertex3f(-radius_ - 5, 10, 0);
    glVertex3f(-radius_ - 5, 20, 0);
    glVertex3f((-radius_ - 40), 15, 0);

    glVertex3f(-radius_ - 5, 10, 0);
    glVertex3f(-radius_ - 5, 0, 0);
    glVertex3f((-radius_ - 40), 5, 0);

    glVertex3f(-radius_ - 5, 10, 0);
    glVertex3f(-radius_ - 5, 0, 0);
    glVertex3f((-radius_ - 40), 5, 0);
    
    glEnd();

    glPushMatrix();
    glScalef(1, 0.15, 0.0);
    glBegin(GL_POLYGON);
    for (double i = 4.0 * M_PI / 6.0; i < 2 * M_PI; i += M_PI / 12)
        glVertex3f(cos(i) * radius_, sin(i) * radius_, 0.0);
    glEnd();
    glPopMatrix();

    glBegin(GL_TRIANGLES);
    
    glVertex3f(-radius_ - 5, 11, 0);
    glVertex3f(radius_ + 5, 0, 0);
    glVertex3f(-radius_ - 5, 0, 0);
    
    glVertex3f(-radius_ + 5, 0, 0);
    glVertex3f(-radius_ + 35, 0, 0);
    glVertex3f(-radius_ + 30, -25, 0);
    
    glVertex3f(20, 0, 0);
    glVertex3f(40, 0, 0);
    glVertex3f(40, -25, 0);
    
    glVertex3f(38, 10, 0);
    glVertex3f(40, 0, 0);
    glVertex3f(50, 15, 0);
    
    glEnd();
    
    glPushMatrix();
    glTranslatef(-radius_ - 10, 10, 0);
    glScalef(1, 0.5, 0.0);
    glBegin(GL_POLYGON);
    for (double i = -M_PI / 2.0; i < M_PI / 2.0; i += M_PI / 12)
        glVertex3f(cos(i) * 20, sin(i) * 20, 0.0);
    glEnd();
    glPopMatrix();
    
    // Turtle lowlights.
    glColor4fv(shell_);
    
    glBegin(GL_TRIANGLES);
    
    glVertex3f(-radius_ + 25, 5, 0);
    glVertex3f(-radius_ + 34, -7, 0);
    glVertex3f(-radius_ + 30, -25, 0);
    
    glVertex3f(15, -2, 0);
    glVertex3f(40, -10, 0);
    glVertex3f(40, -25, 0);
    
    glEnd();
    
    float lowlights_[] = { 0.17, 0.49, 0.27, 1.0 };
    glColor4fv(lowlights_);
    
    glBegin(GL_TRIANGLES);
    
    glVertex3f(-30, 10, 0);
    glVertex3f(-30, 5, 0);
    glVertex3f(40, 0, 0);
    
    glEnd();
    
    // Eyes and frowning eyebrows.
    glPushMatrix();
    glTranslatef(-radius_ - 10, 20, 0);
    const float white[] = {1.0, 1.0, 1.0, 1.0};
    glColor4fv(white);
    glNormal3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (double i = 0.0; i < 2 * M_PI; i += M_PI / 6)
        glVertex3f(cos(i) * 6, sin(i) * 6, 0.0);
    glEnd();
    const float black[] = {0.0, 0.0, 0.0, 1.0};
    glColor4fv(black);
    glNormal3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (double i = 0.0; i < 2 * M_PI; i += M_PI / 6)
        glVertex3f(cos(i) * 2, sin(i) * 2, 0.0);
    glEnd();
    glTranslatef(10, 0, 0);
    glColor4fv(white);
    glNormal3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (double i = 0.0; i < 2 * M_PI; i += M_PI / 6)
        glVertex3f(cos(i) * 6, sin(i) * 6, 0.0);
    glEnd();
    glColor4fv(black);
    glNormal3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (double i = 0.0; i < 2 * M_PI; i += M_PI / 6)
        glVertex3f(cos(i) * 2, sin(i) * 2, 0.0);
    glEnd();
    glPopMatrix();
    
    glBegin(GL_TRIANGLES);
    glVertex3f(-radius_ - 5, 23, 0);
    glVertex3f(-radius_ - 15, 30, 0);
    glVertex3f(-radius_ - 15, 25, 0);
    
    glVertex3f(-radius_ - 5, 23, 0);
    glVertex3f(-radius_ + 5, 30, 0);
    glVertex3f(-radius_ + 5, 25, 0);
    glEnd();

    // Restore the transformation matrix.
    glPopMatrix();
}


