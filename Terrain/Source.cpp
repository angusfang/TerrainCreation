#include "glew.h"
#include "freeglut.h"
#include "glm\glm.hpp"
#include "myCommon.h"
#include "ViewManager.h"
#include <iostream>
using namespace std;
using namespace glm;
ViewManager camera;
struct glo_var {
	GLuint program = 0;
	GLuint texture_ID = 0;
	GLuint VBO_ID = 0;
	GLuint VAO_ID = 0;
	int wheel = 10;
	int lr = 10;
	int ud = 10;
	mat4 view_matrix = mat4(1.f);
	mat4 rotate_matrix = mat4(1.f);
	float aspect =0.f;
}glo;
struct win_var {
	GLuint program = 0;
	GLuint texture_ID = 0;
	GLuint VBO_ID = 0;
	GLuint VAO_ID = 0;
}win;
const float ver[] = {
	-1.f, -1.f, 0.f, 0.f, 0.f,
	0.0f, 1.f, 0.f, 0.5f, 1.f,
	1.f, -1.f, 0.f, 1.f, 0.f
};

char** loadShaderSource(const char* file) {
	FILE* fp;
	errno_t err = fopen_s(&fp, file, "rb");
	if (err) {
		cout << "load fail" << endl;
	}
	else {
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* src = new char[len + 1];
		fread(src, sizeof(char), len, fp);
		src[len] = '\0';
		char** srcp = new char* [1];
		srcp[0] = src;
		return srcp;
	}

}
void freeShaderSource(char** srcp) {
	delete[] srcp[0];
	delete[] srcp;
}
void shaderLog(GLuint shader) {
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		GLchar* infoLog = new GLchar[logLen + 1];
		glGetShaderInfoLog(shader, logLen, &logLen, infoLog);
		infoLog[logLen] = '\0';
		cout << infoLog << endl;
		delete[] infoLog;
	}
}
void renderScene(void)
{


	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(glo.program);
	glBindTexture(GL_TEXTURE_2D, glo.texture_ID);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	mat4 p = camera.GetProjectionMatrix(glo.aspect);
	mat4 v = camera.GetViewMatrix();
	mat4 mv = v * camera.GetModelMatrix();
	glUseProgram(glo.program);
	glUniformMatrix4fv(glGetUniformLocation(glo.program, "p"), 1, false, &p[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(glo.program, "mv"), 1, false, &mv[0][0]);
	glDrawArrays(GL_PATCHES, 0, 3);

	glDisable(GL_DEPTH_TEST);
	glUseProgram(win.program);
	glBindTexture(GL_TEXTURE_2D, glo.texture_ID);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glutSwapBuffers();

}
void myMouse(int btn, int state, int x, int y) {
	camera.mouseEvents(btn, state, x, y);
	if (state == GLUT_DOWN) {
		switch (btn) {
		case GLUT_LEFT_BUTTON:
			std::cout << "left click at: (" << x << ", " << y << ")\n";
			break;
		case GLUT_RIGHT_BUTTON:
			std::cout << "right click at: (" << x << ", " << y << ")\n";
			break;
		case GLUT_MIDDLE_BUTTON:
			std::cout << "middle click at: (" << x << ", " << y << ")\n";
			break;
		case 3:  //mouse wheel scrolls

			glo.wheel += 1;
			std::cout << glo.wheel;
			glUniform1i(glGetUniformLocation(glo.program, "wheel"), glo.wheel);
			break;
		case 4:
			glo.wheel = glo.wheel - 1 >= 0 ? glo.wheel - 1 : glo.wheel;
			std::cout << glo.wheel;
			glUniform1i(glGetUniformLocation(glo.program, "wheel"), glo.wheel);
			break;
		default:
			break;
		}
	}
	glutPostRedisplay();
}
void myMotion(int x, int y) {
	camera.mouseMoveEvent(x, y);
	cout << x <<"," << y << endl;
	glo.view_matrix = translate(mat4(1.f), vec3((float)x, (float)y, 0.f));
	cout << glo.view_matrix[3].x << "," << glo.view_matrix[3].y << "$$" << endl;
	glutPostRedisplay();
}
void myReshape(int width, int height) {

	glViewport(0, 0, width, height);
	camera.SetWindowSize(width, height);
	glo.aspect = (float)width / (float)height;
}
void myMenu(int id) {
	switch (id) {
	case 0:
		glClearColor(1., 1., 0., 1.);
		break;
	case 1:
		glClearColor(0., 1., 1., 1.);
		break;
	case 2:
		exit(0);
	}
	glutPostRedisplay();
}
void myKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		glo.lr += 1;
		glo.rotate_matrix = rotate(mat4(1.), deg2rad(-10.f), vec3(0.f, 1.f, 0.f))*glo.rotate_matrix;
		glUseProgram(glo.program);
		glUniform1i(glGetUniformLocation(glo.program, "lr"), glo.lr);
		break;
	case GLUT_KEY_RIGHT:
		glo.lr -= 1;
		glo.rotate_matrix = rotate(glo.rotate_matrix, deg2rad(+10.f), vec3(0.f, 1.f, 0.f));
		glUseProgram(glo.program);
		glUniform1i(glGetUniformLocation(glo.program, "lr"), glo.lr);
		break;
	case GLUT_KEY_UP:
		glo.ud += 1;
		glo.rotate_matrix = rotate(glo.rotate_matrix, deg2rad(-10.f), vec3(1.f, 0.f, 0.f));
		glUseProgram(glo.program);
		glUniform1i(glGetUniformLocation(glo.program, "ud"), glo.ud);
		break;
	case GLUT_KEY_DOWN:
		glo.ud -= 1;
		glo.rotate_matrix = rotate(glo.rotate_matrix, deg2rad(10.f), vec3(1.f, 0.f, 0.f));
		glUseProgram(glo.program);
		glUniform1i(glGetUniformLocation(glo.program, "ud"), glo.ud);
		break;
		
	}
	glutPostRedisplay();
}
void My_Mouse_Moving(int x, int y) {
	camera.mouseMoveEvent(x, y);
	glutPostRedisplay();
}
void My_Keyboard(unsigned char key, int x, int y)
{
	camera.keyEvents(key);

	printf("Key %c is pressed at (%d, %d)\n", key, x, y);
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 480);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("07");

	glewInit();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
	GLuint tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char** v_source = loadShaderSource("assets/vertex.vs.glsl");
	char** tcs_source = loadShaderSource("assets/tcs.glsl");
	char** tes_source = loadShaderSource("assets/tes.glsl");
	char** f_source = loadShaderSource("assets/fragment.fs.glsl");
	glShaderSource(vs, 1, v_source, NULL);
	glShaderSource(tcs, 1, tcs_source, NULL);
	glShaderSource(tes, 1, tes_source, NULL);
	glShaderSource(fs, 1, f_source, NULL);
	freeShaderSource(v_source);
	freeShaderSource(tcs_source);
	freeShaderSource(tes_source);
	freeShaderSource(f_source);
	glCompileShader(vs);
	glCompileShader(tcs);
	glCompileShader(tes);
	glCompileShader(fs);
	cout << "vs" << endl;
	shaderLog(vs);
	cout << "tcs" << endl;
	shaderLog(tcs);
	cout << "tes" << endl;
	shaderLog(tes);
	cout << "fs" << endl;
	shaderLog(fs);
	glo.program = glCreateProgram();
	glAttachShader(glo.program, vs);
	glAttachShader(glo.program, tcs);
	glAttachShader(glo.program, tes);
	glAttachShader(glo.program, fs);
	glLinkProgram(glo.program);
	glUseProgram(glo.program);

	v_source = loadShaderSource("assets/win.vs.glsl");
	f_source = loadShaderSource("assets/win.fs.glsl");
	glShaderSource(vs, 1, v_source, NULL);
	glShaderSource(fs, 1, f_source, NULL);
	freeShaderSource(v_source);
	freeShaderSource(f_source);
	glCompileShader(vs);
	glCompileShader(fs);
	cout << "vs" << endl;
	shaderLog(vs);
	cout << "fs" << endl;
	shaderLog(fs);
	win.program = glCreateProgram();
	glAttachShader(win.program, vs);
	glAttachShader(win.program, fs);
	glLinkProgram(win.program);

	//glGenBuffers(1, &glo.VBO_ID);
	//glBindBuffer(GL_ARRAY_BUFFER, glo.VBO_ID);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW);
	glGenVertexArrays(1, &glo.VAO_ID);
	glBindVertexArray(glo.VAO_ID);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float)*3));
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	TextureData texture_data = Load_jpg("assets/map.jpg");
	glGenTextures(1, &glo.texture_ID);
	glBindTexture(GL_TEXTURE_2D, glo.texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, texture_data.width, texture_data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glUniform1i(glGetUniformLocation(glo.program, "lr"), glo.lr);
	glUniform1i(glGetUniformLocation(glo.program, "ud"), glo.ud);
	
	//register
	glutDisplayFunc(renderScene);
	glutReshapeFunc(myReshape);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutSpecialFunc(myKeyboard);
	glutPassiveMotionFunc(My_Mouse_Moving);
	glutKeyboardFunc(My_Keyboard);

	int N_menu_main = glutCreateMenu(myMenu);
	glutSetMenu(N_menu_main);
	glutAddMenuEntry("00", 0);
	glutAddMenuEntry("01", 1);
	glutAddMenuEntry("Exit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();//enters the GLUT event processing loop.  
	return 0;
}
