#ifndef __BUBBLE_H__
#define __BUBBLE_H__

class Bubble{
private:
	double x_, y_;
	double scale_;
	double riserate_;
	static int count;
	double diam_;
	double blend_;
public:
	Bubble(double x,double y);
	~Bubble();
	bool isOutOfBound();
	void draw();
	void up();
	static int bubblecount();
	double getX();
	double getY();
};




#endif
