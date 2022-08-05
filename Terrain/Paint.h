#pragma once
#include "glm/glm.hpp"
#include "freeglut.h"
using namespace glm;
class Paint {
public:
	Paint();
	void mouseEvent(int btn, int state, int x, int y);
	void mouseMovement(int x, int y);
	void PaintSet(int pic_width, int pic_height, int pane_width, int pane_height, unsigned char* picture);
private:
	bool lmb_down;
	vec2 lmb_down_coor;
	int pic_width;
	int pic_height;
	int pane_width;
	int pane_height;
	int pen_size;
	unsigned char* picture;
};