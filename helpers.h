#pragma once

#include <process.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "shaders.h"
#include "data.h"
#include "Object3d.h"

using namespace std;

#define POSITION 0
#define COLOR 1
#define NORMAL 1
#define TEXTURE2D 2

HINSTANCE               g_hInst = NULL;
HWND                    g_hWnd = NULL;
GLFWwindow*				window;

float /*y-axis*/ theta=30, /*x-axis*/ phi=0, 
	  pan_x=0, pan_y=0,
	  depth=-550.0;
float pan_factor=20, depth_factor=10;
float width=800.0, height=600.0;
float xi=0, yi=0;
bool mouse_lb=false, mouse_rb=false, mouse_mb=false;
bool colorMode=false;
bool sw=true;
bool planemode=false;
bool lightmode=false;
GLuint		currentShader;	
GLuint		shaderObjects, shaderLight, shaderParticles;
vector <GLuint> VAO_array(0);
glm::vec3 objColor(0.0f,0.6f,0.7f);

HRESULT InitWindow(  );
GLFWwindow* InitWindowGLFW(); 
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );

glm::vec3 lightPos(0.0f), planePos(0.0f,0.0f,-4.0f);

void ShaderProgram(); //compile and link shader program
void GetShaderError(GLuint);
void GetShaderError(char* name, GLuint label);
GLint ShaderAttrib(char* label , VertexFormat, short part);
//input callbacks
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


void InitWindowGLFW(int width, int height){

	 glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window= glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr); // Windowed
	
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	glewExperimental = GL_TRUE;
	glewInit();

	cout<<(char *)glGetString(GL_VERSION)<<endl;
	cout<<"\nWidth: "<<width<<", height: "<<height<<endl;
	glEnable(GL_DEPTH_TEST);
	
}

void ShaderProgram(){

GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexSource, NULL);
glCompileShader(vertexShader);
GetShaderError(vertexShader);

GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
glCompileShader(fragmentShader);
GetShaderError(fragmentShader);

GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader2, 1, &particleFragment, NULL);
glCompileShader(fragmentShader2);
GetShaderError("particleFragment", fragmentShader2);

shaderObjects = glCreateProgram();
shaderParticles = glCreateProgram();

glAttachShader(shaderObjects, vertexShader);
glAttachShader(shaderObjects, fragmentShader);

glAttachShader(shaderParticles, vertexShader);
glAttachShader(shaderParticles, fragmentShader2);

glBindFragDataLocation(shaderObjects, 0, "outColor");
glBindFragDataLocation(shaderParticles, 0, "outColor");

glLinkProgram(shaderObjects);
glLinkProgram(shaderParticles);
}

void GetShaderError(GLuint label)
{
GLint status;
glGetShaderiv(label, GL_COMPILE_STATUS, &status);
status==GL_TRUE? cout<<"Successfully compiled shader.\n": cout<<"Failed to compile shader.\n";

}

void GetShaderError(char* name, GLuint label)
{
GLint status;
glGetShaderiv(label, GL_COMPILE_STATUS, &status);
status==GL_TRUE? cout<<"Successfully compiled "<< name<<" shader.\n": cout<<"Failed to compile "<< name <<" shader.\n";

}

GLint ShaderAttrib(char* label, VertexFormat hints, short part){

	GLint attrib= glGetAttribLocation(currentShader, label); //get reference to position in vertexShader
	short components=0, stride=0, offset=0;
	
	glEnableVertexAttribArray(attrib);
	

	switch (hints){
		
	case XYZ_RGB:
	case XYZ_XYZ:
		components=3;
		stride=6;
		offset=part*3; //if POSITION, offset=0: offset=3
		break;

	case XYZ_XYZ_XY:
		if(part==2)
		{components=2;
		stride=8;
		offset=6;}
		else
		{components=3;
		stride=8;
		offset=part*3;}
		break;

	case XYZ:
		components=3;
		stride=3;
		offset=0; //if POSITION, offset=0: offset=3
		break;
	default:
		break;
	}

glVertexAttribPointer(attrib,
					components, //x,y,z | r,g,b
					GL_FLOAT,
					GL_FALSE,
					stride*sizeof(float), //-->[x,y,z,r,g,b]
					(void*)(offset*sizeof(float))); //-->[x,y,z],r,g,b


	return attrib;
}



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	mouse_lb=true;
else
	mouse_lb=false;

if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	mouse_rb=true;
else
	mouse_rb=false;

if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	mouse_mb=true;
else
	mouse_mb=false;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static float acx=0, acy=0;
	if(mouse_lb)
	{theta+=xpos-xi; phi+=ypos-yi;
	printf("theta: %f, phi: %f\n",theta, phi);
	}
	
	if(mouse_mb)
	{
	pan_x+=xpos-xi; pan_y-=ypos-yi;
	}

	if(mouse_rb)
	depth+=ypos-yi;
	
	if(colorMode)
	{acx+=xpos-xi; acy-=ypos-yi;
		objColor.x=(int(objColor.x)+ int(acx)/100)%11/10.0f;
		objColor.y=(int(objColor.y)+ int(acy)/100)%11/10.0f;
		if(objColor.x<0)objColor.x=0;
		if(objColor.y<0)objColor.y=0;
		printf("Color set to %f, %f, %f.\n",objColor.x, objColor.y, objColor.z);
	}
	

	xi=xpos; yi=ypos; //to the next call, these will be the coordinates from "last position".
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static float speed=0.6;
if (key == GLFW_KEY_RIGHT  && action == GLFW_PRESS)
{lightPos.x+=speed;}


if (key == GLFW_KEY_LEFT  && action == GLFW_PRESS)
	lightPos.x-=speed;

if (key == GLFW_KEY_UP  && action == GLFW_PRESS)
	lightPos.y+=speed;

if (key == GLFW_KEY_DOWN  && action == GLFW_PRESS)
	lightPos.y-=speed;

if (key == GLFW_KEY_N  && action == GLFW_PRESS)
	lightPos.z-=speed;

if (key == GLFW_KEY_M  && action == GLFW_PRESS)
	lightPos.z+=speed;

if (key == GLFW_KEY_P  && action == GLFW_PRESS)
{planemode=true; lightmode=false;}

if (key == GLFW_KEY_P  && action == GLFW_PRESS)
	{lightmode=true; planemode=false;}
}
	