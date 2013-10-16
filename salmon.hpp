#ifndef SALMON_H 
#define SALMON_H
#include "bubble.hpp"
#include <vector>

class Turtle; // Forward declaration

class Salmon {
public:
	 double rotation_;
	 //TODO: put this back into private after debugging 

private: 
    // Location of the centre of the salmon.
    double x_, y_;
	// immediately prev value of location
	double lastx_, lasty_;
    // Rotation of the salmon in degrees (around the Z-axis).
   // double rotation_;
	double lastrotation_;
    
    // Tracks if the salmon has collided with an object.
    bool collided_;

    // The surface colour of the salmon.
    float colour_[4];
   
    // Size of the salmon; generally constant.
    double length_, width_;
    
    // Tracks if the salmon is still alive; will be removed when not alive.
    bool isAlive_;
    // tracks if salmon has been put into advanced mode
	bool advanced_;

	double jaw_angle_;

	//TODO: should really not be owned by salmon, move to a1
	std::vector<Bubble*> bubbles;
	Bubble* bubble;

public:

    // Constructor: initializes default values.
    Salmon();   
    
    // Reset the salmon to its initial state.
    void reset();
    
	// set salmon mode to advanced
	void setAdvanced(bool advanced);

    // Sets the salmon's colour.
    void setColour();
 
    // Return if the salmon is still alive.
    bool isAlive() const;

    // Return if the salmon has collided.
    bool hasCollided() const;

    // Move the salmon by the given amount in each coordinate direction.
    void move(double x, double y);
	// allow movement even though collided - no bounding box feature
    void collisionmove(double x, double y);
    // Set collision state.
    void setCollided(bool collided);

    // Rotate the salmon by the given angle (in degrees).
    void rotate(double angle);

    // Change the colour of the salmon body to a random colour.
    void setRandomColour();
    
    // Return the salmon coordinates.
    int getXcoordinate() const;
    int getYcoordinate() const;
    
    // Perform physics updates.
    void update();
    
    // Draw the salmon.
    void draw();

	// frame of ref salmon xy  from window to salmon rotation
	double x_to_salmon_rotation() const;
	double y_to_salmon_rotation() const;
	// salmon rotated xy to window frame co-ordinate
	double x_from_salmon_rotation() const;
	double y_from_salmon_rotation() const;

	// to update lastx lasty to current
	void updatelastxy();

	void emitbubble();
};


#endif
