#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include "a1.hpp"
#include "salmon.hpp"
#include "turtle.hpp"
#include "utils.hpp"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define DEBUG 1

// Positioning state.
int window_w, window_h;

// The salmon, turtles, and river current speed.
Salmon salmon;
std::list<Turtle *> turtles;
//int current = -5;
int current = 0;
int lightNo = 3;

typedef enum {BASIC,ADVANCED} gamemode_t;
gamemode_t mode = BASIC;

// @@@@@@@@@@
// Put any other global state variables you need here.
// e.g., keyboard state, mouse state....

// last mouse position for rotation tracking
int mousex=0;
int mousey=0;
int mouseXdisplacement=0;

// initial response rate to salmon direction change
double vert_change = 15;
double horz_change = 15;
// @@@@@@@@@@

void setup_lighting(void) {

	// Turn on lighting, and two local lights.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);

	// Set the intensity of the global ambient light.
	float ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	// Set up the diffuse intensities of the local light source.
	float diffuse[][4] = { 0.8, 0.8, 0.8, 1, 0.2, 0.2, 0.2, 1, };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse[0]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse[1]);

	// Move the light near the top corner of the window.
	float light_positions[][4] = { 0, 1, 2, 0, // From above-left
			0, -5, 0, 0, // From below
			};
	glLightfv(GL_LIGHT0, GL_POSITION, light_positions[0]);
	glLightfv(GL_LIGHT1, GL_POSITION, light_positions[1]);
}

// Called by GLUT at the start of the session, and when the window is reshaped.
void reshape(int w, int h) {

	window_w = w;
	window_h = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Z range must be big enough to encompass salmon and turtles.
	glOrtho(0, w, 0, h, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setup_lighting();

	salmon.reset();
}

// Called by GLUT when you move the mouse.
void mouse_move(int x, int y) {
	double degPerPixel = 0.5;
	double angle=0.0;
	// @@@@@@@@@@
	// Use mouse movements to rotate the salmon.
	// Compare the current and previous mouse coordinates and use
	// the displacement to set the amount of rotation.
	if ((mousex > 0)&&(mousey>0)){
		// further right is larger. add diff since last report to displacment
		mouseXdisplacement = ( x - mousex);
		angle = mouseXdisplacement * degPerPixel;  
		if (angle < 15)  // limit impact of edge entries
			salmon.rotate(angle);	
		// rotate is an accumulator, only feed it deltas.
	}
	//  position for mouse history
	mousex = x;
	mousey = y;
	
	// @@@@@@@@@@

}

// Called by GLUT when you press a key on the keyboard.
void keyboard(unsigned char key, int x, int y) {

	// Reset the salmon by pressing 'r'.
	// Increase and decrease the current with the '>' and '<' keys.
	switch (key) {
	case 'r':
	case 'R':  //reset : remove all turtles and start over
		// @@@@@@@@@@
		// Do something or call a function here
		salmon.reset();
		turtles.clear();
		current = -5;
		glDisable(GL_LIGHT2);
		// @@@@@@@@@@
		break;
	case '>':
		decreaseCurrent(true);
		break;
	case '<':
		decreaseCurrent(false);
		break;
	case 'a':
	case 'A':	//advance mode
		mode=ADVANCED;
		salmon.setAdvanced(true);
		salmon.updatelastxy();
		break;
	case 'b':
	case 'B':	//basic mode
		mode=BASIC;
		salmon.setAdvanced(false);
		salmon.updatelastxy();
		break;
		// @@@@@@@@@@
		// Toggle between advanced mode and basic mode here by detecting
		// non-arrow key presses here.  You can detect any other key press
		// events here, and use them however you like.
	case 'q':
	case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case 't':
		salmon.rotation_ = 30;
		break;
	case 's':
		salmon.rotation_ = 45;
		break;
	default:
		if (DEBUG) printf("unrecognized key (%c)\n",key);
		break;

	}
}

// Change the current.
void decreaseCurrent(bool increase) {
	if (increase && (current < 0))
		current++;
	else if (!increase)
		current--;
	// trying to increase from neg to beyond zero should do nothing
	
}

void print_specialKeyName(int key){
	switch (key){
	case GLUT_KEY_F1:
		printf("F1 function key.");
		break;
	case GLUT_KEY_F2:
		printf("F2 function key.");
		break;
	case GLUT_KEY_F3:
		printf("F3 function key.");
		break;
	case GLUT_KEY_F4:
		printf("F4 function key.");
		break;
	case GLUT_KEY_F5:
		printf("F5 function key.");
		break;
	case GLUT_KEY_F6:
		printf("F6 function key.");
		break;
	case GLUT_KEY_F7:
		printf("F7 function key.");
		break;
	case GLUT_KEY_F8:
		printf("F8 function key.");
		break;
	case GLUT_KEY_F9:
		printf("F9 function key.");
		break;
	case GLUT_KEY_F10:
		printf("F10 function key.");
		break;
	case GLUT_KEY_F11:
		printf("F11 function key.");
		break;
	case GLUT_KEY_F12:
		printf("F12 function key.");
		break;
	case GLUT_KEY_LEFT:
		printf("Left directional key.");
		break;
	case GLUT_KEY_UP:
		printf("Up directional key.");
		break;
	case GLUT_KEY_RIGHT:
		printf("Right directional key.");
		break;
	case GLUT_KEY_DOWN:
		printf("Down directional key.");
		break;
	case GLUT_KEY_PAGE_UP:
		printf("Page up directional key.");
		break;
	case GLUT_KEY_PAGE_DOWN:
		printf("Page down directional key.");
		break;
	case GLUT_KEY_HOME:
		printf("Home directional key.");
		break;
	case GLUT_KEY_END:
		printf("End directional key.");
		break;
	case GLUT_KEY_INSERT:
		printf("Inset directional key.");
		break;
	default:
		printf("unknown key.");
		break;
	}
	printf("\n");

}


// Called by GLUT when you release a key on the keyboard.
void keyboardup(unsigned char key, int x, int y) {

	// @@@@@@@@@@
	// Detect non-arrow key releases here.

	// @@@@@@@@@@
}






// Called by GLUT when you press a special key on the keyboard.
void keyboardSpecial(int key, int x, int y) {

	// @@@@@@@@@@
	// Detect arrow key presses here.
	switch (key){
	case GLUT_KEY_LEFT :
		salmon.move(-horz_change,0);
		break;
	case GLUT_KEY_UP :
		salmon.move(0,vert_change);// glut co-ord 0,0 at upper left
		break;
	case GLUT_KEY_RIGHT :
		salmon.move(horz_change,0);
		break;
	case GLUT_KEY_DOWN :
		salmon.move(0,-vert_change);
		break;
	default:
		if (DEBUG) {
			printf("unhandled special key %d\n", key);
			print_specialKeyName(key);
			// home end ins and fn keys
		}
		break;
	}
	if (mode != ADVANCED){
		switch (key){
			case GLUT_KEY_RIGHT :
			case GLUT_KEY_LEFT :
				horz_change+=10;
				break;
			case GLUT_KEY_DOWN :
			case GLUT_KEY_UP :
				vert_change+=10;// glut co-ord 0,0 at upper left
				break;
			default:
				if (DEBUG) {
					printf("unhandled special key %d\n", key);
					print_specialKeyName(key);
					// home end ins and fn keys
				}
				break;
		}
	}
	if (DEBUG){
		printf("SALMON POSITION= (%d,%d)\n",
				salmon.getXcoordinate(),salmon.getYcoordinate());
	}
	// @@@@@@@@@@
}
// Called by GLUT when you release a special key on the keyboard.
void keyboardSpecialUp(int key, int x, int y) {
	// x y mouse wrt window co-ordinate when special key pressed
	// @@@@@@@@@@
	// Detect arrow key releases here.
	switch (key){
	case GLUT_KEY_LEFT :

		break;
	case GLUT_KEY_UP :

		break;
	case GLUT_KEY_RIGHT :

		break;
	case GLUT_KEY_DOWN :

		break;
	default:
		if (DEBUG){
			printf("unhandled special keyup %d\n", key);
			print_specialKeyName(key);
		}
		break;
	}

	if (mode != ADVANCED){
		switch (key){
			case GLUT_KEY_RIGHT :
			case GLUT_KEY_LEFT :
				horz_change = 10;
				break;
			case GLUT_KEY_DOWN :
			case GLUT_KEY_UP :
				vert_change = 10;
				break;
			default:
				if (DEBUG) {
					printf("unhandled special key %d\n", key);
					print_specialKeyName(key);
					// home end ins and fn keys
				}
				break;
		}
	}
	// @@@@@@@@@@
}

// Called by GLUT when we need to redraw the screen.
void display(void) {

	// Clear the buffer we will draw into.
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Initialize the modelview matrix.
	glLoadIdentity();

	// Disable all remaining lights.
	for (int i = lightNo; i < GL_MAX_LIGHTS; ++i) {
		glDisable(GL_LIGHT0 + i);
	}

	// Draw a blue river background grid.
	glNormal3f(0, 0, 1);
	const int res = 40;
	for (int x = 0; x <= window_w; x += res) {
		glBegin(GL_QUAD_STRIP);
		for (int y = 0; y <= window_h; y += res) {
			double gradient = (double) y / (double) window_h;
			glColor3f(gradient * 0.74, 0.69 + gradient * 0.25,
					0.9 + gradient * 0.08);
			glVertex3f(x, y, -20);
			glVertex3f(x + res, y, -20);
		}
		glEnd();
	}

	// Draw the salmon.
	salmon.draw();

	// Draw the turtles.
	std::list<Turtle *>::iterator turtle;
	for (turtle = turtles.begin(); turtle != turtles.end(); turtle++) {
		(*turtle)->draw();
	}

	// Make the buffer we just drew into visible.
	glutSwapBuffers();
}

// Called by GLUT on a timer for every frame of animation.
// We are responsible for setting the argument that is passed to this function.
void animate(int last_frame = 0) {

	// @@@@@@@@@@
	// Control the movement of the salmon here based on arrow key states.
		// this is being done from registered glutSpecialFunc which updates 
		// salmon position info, which just need to draw here.
	// @@@@@@@@@@

	// Find collisions between turtles and the salmon (naive).
	std::list<Turtle *>::iterator turtle;
	for (turtle = turtles.begin(); turtle != turtles.end(); turtle++) {
		(*turtle)->update(salmon);
	}

	// Randomly generate some new turtles upstream.
	if (randf() < 0.01) {
		turtles.push_back(new Turtle(window_w, randf() * window_h));
	}

	// Delete turtles who have swum downstream out of the window.
	turtle = turtles.begin();
	while (turtle != turtles.end()) {
		if (!(*turtle)->isAlive()) {
			delete *turtle;
			turtle = turtles.erase(turtle);
		} else {
			turtle++;
		}
	}

	// Update the salmon's properties.
	salmon.update();

	// Signal that the window should be redrawn.  - calls function registered by glutDisplayFunc
	glutPostRedisplay();

	// Schedule the next frame.
	int current_time = glutGet(GLUT_ELAPSED_TIME);
	int next_frame = last_frame + 1000 / 30;
	glutTimerFunc(MAX(0, next_frame - current_time), animate, current_time);
}

//do something when the mouse pointer enters or leaves the window
void mouse_inout(int state){
	if (DEBUG){
		if (state == GLUT_LEFT ){
			printf("mouse left window\n");
		}else if (state == GLUT_ENTERED){
			printf("mouse entered window\n");
		}
	}
	//reset mouse history for rotation
	mousex=0;
	mousey=0;

}



int Turtle::collisionlights[] = {GL_LIGHT2 ,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7} ;
int Turtle::currentlight = 0;

int main(int argc, char *argv[]) {

	// Initialize random seed.
	srand(time(NULL));

	// Initialize GLUT and open a window.
	glutInit(&argc, argv);  // command line args are window system dependent
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(900, 600);  // can override --geometry WxH+X+Y cmd args
	glutCreateWindow(argv[0]);

	// Register callbacks for GLUT events.
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMotionFunc(mouse_move);
	glutPassiveMotionFunc(mouse_move);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);

	// @@@@@@@@@@
	// Register your callbacks here.
	//eg glutEntryFunc  if we want notification when mouse enters/leaves our window
	glutEntryFunc(mouse_inout);
	glutSpecialFunc(keyboardSpecial);
	glutSpecialUpFunc(keyboardSpecialUp);
	glutPassiveMotionFunc(mouse_move);
	// @@@@@@@@@@

	// Schedule the first animation callback ASAP.(0 ms wait time, function to call, 0 parm for animate
	glutTimerFunc(0, animate, 0);

	// Pass control to GLUT.
	glutMainLoop();

	return 0;
}

