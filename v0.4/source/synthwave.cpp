#include "synthwave.h"
#include <math.h>

const int circle_resolution = 100;
const int sun_radius = 10;
const int sun_distance_far = 20;

void draw_circle(float posx, float posy, float circle_radius)
{
	glColor4f(1.0f,0.0f,1.0f,0.1f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(posx,posy,0.0f);
		for(int i = 0; i < circle_resolution; i++)
		{
			float angle = 2 * PI * (float)i / (float)circle_resolution;
			float x = circle_radius * sinf(angle);
			float y = circle_radius * cosf(angle);
			glVertex3f(posx+x,posy+y,0.0f);
		}
		glVertex3f(posx+0.0f,posy+float(circle_radius),0.0f);
	glEnd();
}

void draw_box(float room_length, float room_breadth, float room_height)
{
	glColor4f(0.0f,1.0f,1.0f,1.0f);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0.0f		  ,room_breadth,	   0.0f);
		glVertex3f(0.0f		  ,0.0f		   ,	   0.0f);
		glVertex3f(room_length,0.0f		   ,	   0.0f);
		glVertex3f(room_length,room_breadth,	   0.0f);
		glVertex3f(0.0f		  ,room_breadth,	   0.0f);
		glVertex3f(0.0f		  ,room_breadth,room_height);
		glVertex3f(room_length,room_breadth,room_height);
		glVertex3f(room_length,		   0.0f,room_height);
		glVertex3f(0.0f		  ,		   0.0f,room_height);
		glVertex3f(0.0f		  ,room_breadth,room_height);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.0f		  ,0.0f		   ,	   0.0f);
		glVertex3f(0.0f		  ,		   0.0f,room_height);

		glVertex3f(room_length,0.0f		   ,	   0.0f);
		glVertex3f(room_length,		   0.0f,room_height);

		glVertex3f(room_length,room_breadth,	   0.0f);
		glVertex3f(room_length,room_breadth,room_height);
	glEnd();
}

void draw_point(float w, float x, float y, float z, char wlan_code)
{
  glLineWidth(10.0f); // Normal to x-y plane
  glBegin(GL_LINES);
  glColor4f(0.0f, 0.0f, 0.0f, 0.3f);
  glVertex3f(x, y, z);
  glVertex3f(x, y, 0.0f);
  glEnd();

  switch (wlan_code) {
    case 'A': glColor4f(1.0f, 0.0f, 0.0f, 1.0f); break; // Bright Red
    case 'B': glColor4f(1.0f, 0.5f, 0.0f, 1.0f); break; // Bright Orange
    case 'C': glColor4f(1.0f, 1.0f, 0.0f, 1.0f); break; // Neon Yellow
    case 'D': glColor4f(0.0f, 1.0f, 0.0f, 1.0f); break; // Neon Green
    case 'E': glColor4f(0.0f, 1.0f, 1.0f, 1.0f); break; // Bright Cyan
    case 'F': glColor4f(0.0f, 0.0f, 1.0f, 1.0f); break; // Bright Blue
    case 'G': glColor4f(1.0f, 0.0f, 1.0f, 1.0f); break; // Magenta
    case 'H': glColor4f(1.0f, 0.5f, 0.5f, 1.0f); break; // Light Coral
    case 'I': glColor4f(0.5f, 0.5f, 0.0f, 1.0f); break; // Olive Green
    case 'J': glColor4f(0.8f, 0.8f, 0.0f, 1.0f); break; // Bright Yellow
    case 'K': glColor4f(0.8f, 0.0f, 0.0f, 1.0f); break; // Dark Red
    case 'L': glColor4f(0.0f, 0.8f, 0.0f, 1.0f); break; // Bright Green
    case 'M': glColor4f(0.5f, 0.0f, 0.5f, 1.0f); break; // Purple
    case 'N': glColor4f(1.0f, 0.8f, 0.0f, 1.0f); break; // Laser Lemon
    default: glColor4f(1.0f, 0.0f, 0.0f, 1.0f); break; // Default Bright room_breadth
  }

  if (w == 0.0f) //access point
  {
    pyramid(x, y, z, 0.25f, 0.25f);
    draw_circle(x, y, 1.0f);
  }

  else //station
  {
    glPointSize(15.0f);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
    //draw_circle(x, y, 1.0f);
  }
}

void draw_grid()
{
	glColor4f(1.0f,0.0f,1.0f,1.0f);
	glLineWidth(2.0f);
	for(float i=-50;i<=50;i=i+1) //simple for loop to draw many squares
	{
		glBegin(GL_LINES);
			glVertex3f(i,+50.0f,0.0f);
			glVertex3f(i,-50.0f,0.0f);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(+50.0f,i,0.0f);
			glVertex3f(-50.0f,i,0.0f);
		glEnd();
	}
}

void pyramid(float x, float y, float z, float py_w, float py_h)
{
	//glColor4f(1.0,0.0,1.0,0.3);
	glBegin(GL_TRIANGLES);
		glVertex3f(  x+0.0f,  y+0.0f, z+0.0f); //triangle 1
		glVertex3f(x+py_w/2,y+py_w/2, z+py_h);
		glVertex3f(  x+py_w,  y+0.0f, z+0.0f);
		glVertex3f(  x+py_w,  y+0.0f, z+0.0f); //triangle 2
		glVertex3f(x+py_w/2,y+py_w/2, z+py_h);
		glVertex3f(  x+py_w,  y+py_w, z+0.0f);
		glVertex3f(  x+py_w,  y+py_w, z+0.0f); //triangle 3
		glVertex3f(x+py_w/2,y+py_w/2, z+py_h);
		glVertex3f(  x+0.0f,  y+py_w, z+0.0f);
		glVertex3f(  x+0.0f,  y+py_w, z+0.0f); //triangle 4
		glVertex3f(x+py_w/2,y+py_w/2, z+py_h);
		glVertex3f(  x+0.0f,  y+0.0f, z+0.0f);
	glEnd();

	glLineWidth(5.0f); //this part of the code is for making the thick borders
	glColor4f(0.0f,0.0f,0.0f,1.0f); //the code just before this serves the purpose of making the pyramids/mountains have a sort of translucent look
	glBegin(GL_LINES);
		glVertex3f(x+0.0f,y+0.0f,z+0.0f);
		glVertex3f(x+py_w,y+0.0f,z+0.0f);
		glVertex3f(x+py_w,y+0.0f,z+0.0f);
		glVertex3f(x+py_w,y+py_w,z+0.0f);
		glVertex3f(x+py_w,y+py_w,z+0.0f);
		glVertex3f(x+0.0f,y+py_w,z+0.0f);
		glVertex3f(x+0.0f,y+py_w,z+0.0f);
		glVertex3f(x+0.0f,y+0.0f,z+0.0f);
	glEnd(); //so satisfying

	
	glBegin(GL_LINES); //for drawing the square base of the pyramid
		glVertex3f(  x+0.0f,  y+0.0f, z+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, z+py_h);
		glVertex3f(  x+py_w,  y+0.0f, z+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, z+py_h);
		glVertex3f(  x+py_w,  y+py_w, z+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, z+py_h);
		glVertex3f(  x+0.0f,  y+py_w, z+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, z+py_h);
	glEnd(); //even more satisfying
}

void draw_axes()
{
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	glLineWidth(10.0f);
	glBegin(GL_LINES);
		glVertex2f(-50.0f,0.0f);
		glVertex2f(+50.0f,0.0f);

		glVertex2f(0.0f,-50.0f);
		glVertex2f(0.0f,+50.0f);

		glVertex3f(0.0f,0.0f,-50.0f);
		glVertex3f(0.0f,0.0f,+50.0f);
	glEnd();
}
