#ifndef A1_H
#define A1_H

void setup_lighting(void);

void setAdvancedMode(void);

void setBasicMode(void);

void reshape(int w, int h);

void mouse_move(int x, int y);

void keyboard(unsigned char key, int x, int y);

void keyboardup(unsigned char key, int x, int y);

void keyboardSpecial(int key, int x, int y);

void keyboardSpecialUp(int key, int x, int y);

void handleKeys(void);

void display(void);

void addTurtle(int x, int y);

void decreaseCurrent(bool increase);

void reset();

#endif
