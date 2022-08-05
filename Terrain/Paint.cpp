#include "Paint.h"
Paint::Paint(){
	lmb_down = false;
	lmb_down_coor = vec2(0.f, 0.f);
	pic_width = 0;
	pic_height = 0;
	pane_width = 0;
	pane_height = 0;
	pen_size = 10;
	picture = 0;
}
void Paint::PaintSet(int pic_width0, int pic_height0, int pane_width0, int pane_height0, unsigned char* picture0) {
	pic_width = pic_width0;
	pic_height = pic_height0;
	pic_height = pic_height0;
	pane_width = pane_width0;
	pane_height = pane_height0;
	picture = picture0;
}

void Paint::mouseEvent(int btn, int state, int x, int y) {
	switch (state) {
	case GLUT_UP:
		lmb_down = false;
		break;
	case GLUT_DOWN:
		lmb_down = true;
		break;
	}
}

void Paint::mouseMovement(int x, int y) {
	if (lmb_down == true) {
		if (x < pane_width && y< pane_height){
			int x_pic = float(x) * (float(pic_width) / float(pane_width));
			int y_pic = float(pic_height) - float(y) * (float(pic_height) / float(pane_height));
			for (int dy = -pen_size; dy <= pen_size; dy++) {
				if (y_pic + dy < 0 || y_pic + dy >= pic_height)break;
				for (int dx = -pen_size; dx <= pen_size; dx++) {
					if (x_pic + dx < 0 || x_pic + dx >= pic_width)break;
					for (int a = 0; a < 3; a++) {
						picture[((y_pic+dy) * pic_width + (x_pic+dx)) * 3 + a] = 255;
					}
				}
			}
		}
	}
}