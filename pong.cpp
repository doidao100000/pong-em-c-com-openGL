#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <string>
#include <GLFW/glfw3.h>
#include "stbfont.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;

struct ball {
	int n = 100;
	bool xcolision = true; bool ycolision = true;
	float ang, step, v1xpos, v1ypos, v2xpos, v2ypos;
	float r = 0.01f;
	float xvel;
	float vel = 0.5f;
    float xpos = 0.0f, ypos = 0.0f;
	float create_ball (float delta, float start, bool xcol, int cont) {
		if (start < 2.0f) {
			 xvel = 0.0f;
		}
		else {
			 xvel = 1.0f;
		}

		//movimento

		if (ycolision == true) {
		    ypos += delta * vel;
		}
		if (ycolision == false) {
			ypos += delta * (- vel);
		}
		if (xcol == true) {
			xpos += delta * (-xvel);
		}
		if (xcol == false) {
			xpos += delta * xvel;
		}
		if (ypos >= 1) {
			ycolision = false;
		}
		if (ypos <= -1) {
			ycolision = true;
		}

		
		//desenho

		glColor3f(1.0f, 0.0f, 0.0f);
		ang = 2 * M_PI / n;
		v1xpos = xpos + r * sin(ang);
		v1ypos = ypos + r * cos(ang);

		
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xpos, ypos);
		glVertex2f(v1xpos, v1ypos);
		for (int i = 0; i <= n; i++) {
			step = ang * i;
			v2xpos = xpos + r * sin(step);
			v2ypos = ypos + r * cos(step);
			glVertex2f(v2xpos, v2ypos);
		}
	    glEnd();

		//progressao

		if (cont > 10) {
			vel = 0.9f;
			xvel = 1.0f;
		}
		if (cont > 15) {
			vel = 1.4f;
		}
		if (cont > 20) {
			xvel = 1.2f;
		}
		if (cont > 25) {
			xvel = 1.4f;
		}
		if (cont > 50) {
			xvel = 1.8f;
		}

		return xpos, ypos, r;
	}
};

struct lbar {
	float v1x, v2x, v1y, v2y;
	float lxpos = -0.85f;
	float lypos = 0.0f;
	float lxsize = 0.03f, lysize = 0.2f;
	float vell = 1.0f;
	float creat_bar(float delta, bool lmove, bool lmoveb) {
		v1x = lxpos - lxsize / 2;
		v2x = lxpos + lxsize / 2;
		v1y = lypos + lysize / 2;
		v2y = lypos - lysize / 2;
		
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex2f(v1x, v1y);
			glVertex2f(v2x, v1y);
			glVertex2f(v2x, v2y);
			glVertex2f(v1x, v2y);
		glEnd();

		// movimento

		if (lmove == true && v1y < 1.0f) {
			lypos += delta * vell;
		}
		if (lmoveb == true && v2y > -1.0f) {
			lypos += delta * (-vell);
		}

		return lxpos, lypos;
	}
};

struct rbar {
	float rv1x, rv2x, rv1y, rv2y;
	float rxpos = 0.85f;
	float rypos = 0.0f;
	float rxsize = 0.03f, rysize = 0.2f;
	float velr = 1.0f;
	float creat_bar(float delta, bool rmove, bool rmoveb) {
		rv1x = rxpos - rxsize / 2;
		rv2x = rxpos + rxsize / 2;
		rv1y = rypos + rysize / 2;
		rv2y = rypos - rysize / 2;

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex2f(rv1x, rv1y);
		glVertex2f(rv2x, rv1y);
		glVertex2f(rv2x, rv2y);
		glVertex2f(rv1x, rv2y);
		glEnd();

		//movimento

		if (rmove == true && rv1y < 1.0f) {
			rypos += delta * velr;
		}
		if (rmoveb == true && rv2y > -1.0f) {
			rypos += delta * (-velr);
		}

		return rxpos, rypos;
	}
};

    void drawText(float x, float y, const char* text) {
	char buffer[99999];
	int num_quads = stb_easy_font_print(x, y, (char*)text, NULL, buffer, sizeof(buffer));
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glScalef(0.01f, -0.01f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 16, buffer);
	glDrawArrays(GL_QUADS, 0, num_quads * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();

}

	void drawtextl(float x, float y, const char* text) {
		char buffer[99999];
		int num_quads = stb_easy_font_print(x, y, (char*)text, NULL, buffer, sizeof(buffer));
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		glScalef(0.01f, -0.01f, 1.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 16, buffer);
		glDrawArrays(GL_QUADS, 0, num_quads * 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}

	void drawhits(float x, float y, const char* text) {
		char buffer[99999];
		int num_quads = stb_easy_font_print(x, y, (char*)text, NULL, buffer, sizeof(buffer));
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		glScalef(0.005f, -0.005f, 1.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 16, buffer);
		glDrawArrays(GL_QUADS, 0, num_quads * 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}

GLFWwindow* create_window() {
	GLFWwindow* window;
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	window = glfwCreateWindow(mode->width, mode->height, "PONG", monitor, NULL);
	glfwMakeContextCurrent(window);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	return window;
}

int main() {
	int rcont = 0, lcont = 0, cont = 0;
	float start = glfwGetTime();
	bool xcol = false;
	ball b;
	lbar lb;
	rbar rb;
	float vel = 0.1f;
	glfwInit();
	float time = glfwGetTime();
	GLFWwindow* window = create_window();

	while (!glfwWindowShouldClose(window)) {
		bool lmove = glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_E);
		bool lmoveb = glfwGetKey(window, GLFW_KEY_S);
		bool rmove = glfwGetKey(window, GLFW_KEY_UP);
		bool rmoveb = glfwGetKey(window, GLFW_KEY_DOWN);
		float newtime = glfwGetTime();
		float delta = newtime - time;
		time = newtime;
		int ang2 = rand() % 180;
		float el = newtime - start;
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		b.create_ball(delta, el, xcol, cont);
		lb.creat_bar(delta, lmove, lmoveb);
		rb.creat_bar(delta, rmove, rmoveb);
		if (((b.xpos + b.r) >= 0.85f) && b.ypos <= rb.rv1y && b.ypos >= rb.rv2y && xcol == false && b.xpos <=0.91f ) {
			xcol = true;
			cont++;
		}
		if (((b.xpos + b.r) <= -0.85f) && b.ypos <= lb.v1y && b.ypos >= lb.v2y && xcol == true && b.xpos >= -0.91f) {
			xcol = false;
			cont++;
		}
		if (b.xpos > 1.0f) {
			b.xpos = 0;
			start = 0;
			start = glfwGetTime();
			lcont = lcont + 1;
			cont = 0;
			b.vel = 0.5f;
			b.xvel = 0.0f;
		}
		if (b.xpos < -1.0f) {
			b.xpos = 0;
			start = 0;
			start = glfwGetTime();
			rcont = rcont + 1;
			cont = 0;
			b.vel = 0.5f;
			b.xvel = 0.0f;
		}



		string dcont = to_string(rcont);
		drawText(0.3f, 0.9f, dcont.c_str());
		string econt = to_string(lcont);
		drawtextl(-0.35, 0.9f, econt.c_str());
		string hits = "batidas: " + to_string(cont);
		drawhits(-0.1, -0.9f, hits.c_str());




		glfwPollEvents();
		glfwSwapBuffers(window);
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwDestroyWindow(window);
		}
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}