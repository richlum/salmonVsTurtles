#ifndef TURTLE_H
#define TURTLE_H

#define MAXIMUM_RADIUS 30
#define MAXIMUM_TURTLE_MOMENTUM 5

class Salmon; // Forward declaration

class Turtle {
    
private:
    // Location of the centre of the turtle.
    double x_, y_;
    
    // The shell colour of the turtle.
    float shell_[4];
    
    // Size of the turtle
    double radius_;
    
    // Tracks if the turtle is still alive; will be removed when not alive.
    bool isAlive_;
    
    // Tracks if the turtle has collided with the salmon.
    bool collided_;

	static int collisionlights[6];
    static int currentlight;

public:
    
    // Constructor: initializes default values
    Turtle();
    
    // Constructor: specified location
    Turtle(int xCoordinate, int yCoordinate);
    
    // Sets the colour of the turtle.
    void setColour();
    
    // Returns if the turtle is still alive.
    bool isAlive() const;
    
    // Move the turtle by the given amount in each coordinate direction.
    void move(double x, double y);
    
    // Performs physics updates, colliding with the given salmon.
    void update(Salmon &salmon);
    
    // Sets up the turtle's light.
    void setupLight();
    
    // Draw the turtle.
    void draw();
};

#endif
