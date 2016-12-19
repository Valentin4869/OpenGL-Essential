// OpenGL2.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#define GLEW_STATIC
#include "helpers.h"
#include <SOIL\SOIL.h>
#define OBJECT_COUNT 80
#define PARTICLE_COUNT 1

glm::vec3 positions[OBJECT_COUNT];
glm::vec3 positions_particles[PARTICLE_COUNT];

float rotations[OBJECT_COUNT];

int _tmain(int argc, _TCHAR* argv[])
{
	//glewExperimental = GL_TRUE;
	//glewInit();
	
	/*InitWindow();
	
	 MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
           
        }
    }*/

	
//GLfloat vertices[] = {
//    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 
//     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 
//     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 
//     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 
//    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 
//    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 
//
//    -0.5f, -0.5f,  0.5f, 0.7f, 0.7f, 0.7f, 
//     0.5f, -0.5f,  0.5f, 0.7f, 0.7f, 0.7f, 
//     0.5f,  0.5f,  0.5f, 0.7f, 0.7f, 0.7f,
//     0.5f,  0.5f,  0.5f, 0.7f, 0.7f, 0.7f,
//    -0.5f,  0.5f,  0.5f, 0.7f, 0.7f, 0.7f, 
//    -0.5f, -0.5f,  0.5f, 0.7f, 0.7f, 0.7f,
//
//    -0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, 
//    -0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 
//    -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f,
//    -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f,
//    -0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f,
//    -0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f,
//
//     0.5f,  0.5f,  0.5f, 0.4f, 0.4f, 0.4f,
//     0.5f,  0.5f, -0.5f, 0.4f, 0.4f, 0.4f,
//     0.5f, -0.5f, -0.5f, 0.4f, 0.4f, 0.4f,
//     0.5f, -0.5f, -0.5f, 0.4f, 0.4f, 0.4f,
//     0.5f, -0.5f,  0.5f, 0.4f, 0.4f, 0.4f, 
//     0.5f,  0.5f,  0.5f, 0.4f, 0.4f, 0.4f,
//
//    -0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f, 
//     0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f, 
//     0.5f, -0.5f,  0.5f, 0.3f, 0.3f, 0.3f,
//     0.5f, -0.5f,  0.5f, 0.3f, 0.3f, 0.3f, 
//    -0.5f, -0.5f,  0.5f, 0.3f, 0.3f, 0.3f, 
//    -0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f, 
//
//    -0.5f,  0.5f, -0.5f, 0.2f, 0.2f, 0.2f, 
//     0.5f,  0.5f, -0.5f, 0.2f, 0.2f, 0.2f, 
//     0.5f,  0.5f,  0.5f, 0.2f, 0.2f, 0.2f, 
//     0.5f,  0.5f,  0.5f, 0.2f, 0.2f, 0.2f, 
//    -0.5f,  0.5f,  0.5f, 0.2f, 0.2f, 0.2f, 
//    -0.5f,  0.5f, -0.5f, 0.2f, 0.2f, 0.2f, 
//};

	

	int w,h;
	unsigned char* image =SOIL_load_image("data//wall.jpg", &w,&h, 0, SOIL_LOAD_RGB);
	cout<<"Width: "<<w<<", height: "<<h<<endl;
	int spacing=30, factor=OBJECT_COUNT*1;

for(int i=0; i<OBJECT_COUNT; i++)
{
	positions[i]=glm::vec3(float(rand()%(OBJECT_COUNT*spacing) -spacing*OBJECT_COUNT/2.0)/(factor), 
		float(rand()%(OBJECT_COUNT*spacing) -spacing*OBJECT_COUNT/2.0)/(factor),
		float(rand()%(OBJECT_COUNT*spacing) -spacing*OBJECT_COUNT/2.0)/(factor));

	rotations[i]=float(rand()%360);

}

float p_x=-40;

for(int i=0; i<PARTICLE_COUNT; i++)
{
	positions_particles[i]=glm::vec3(
		p_x+float(rand()%(PARTICLE_COUNT*spacing) -spacing*PARTICLE_COUNT/2.0)/(factor), 
		float(rand()%(PARTICLE_COUNT*spacing) -spacing*PARTICLE_COUNT/2.0)/(factor),
		float(rand()%(PARTICLE_COUNT*spacing) -spacing*PARTICLE_COUNT/2.0)/(factor));

}


//init

glm::mat4 model, //MODEL matrix is a transform matrix to move the model around.
		  view, 
		  proj,
		  L, T, rot, identity;

GLuint vao1, vao2, texture;
GLuint vbo, vbo2, vboPlane;
GLuint ebo;
GLuint fbo;

InitWindowGLFW(width, height); //basic init all

proj= glm::perspective(glm::radians(45.0f), width / height, 0.1f, 1000.0f);

ShaderProgram(); //compile and link shader program

currentShader=shaderObjects;
glUseProgram(currentShader);

//get globals. Uniforms are global across whole program.
GLuint uniColor= glGetUniformLocation(shaderObjects,"Color");
GLuint uniInv= glGetUniformLocation(shaderObjects,"inv");
GLuint uniProj = glGetUniformLocation(shaderObjects, "proj");
GLuint uniAxis= glGetUniformLocation(shaderObjects, "color_from_vert");
GLuint uniLightPos= glGetUniformLocation(shaderObjects, "lightpos");
GLuint uniCameraPos= glGetUniformLocation(shaderObjects, "camerapos");
GLuint uniModel = glGetUniformLocation(shaderObjects, "model");
GLuint uniView = glGetUniformLocation(shaderObjects, "view");
GLuint uniLighting = glGetUniformLocation(shaderObjects, "lighting");
GLuint uniTex = glGetUniformLocation(shaderObjects, "tex");
GLuint uniParticles = glGetUniformLocation(shaderObjects, "particles");
GLuint uniObjPos = glGetUniformLocation(shaderObjects, "obj_pos");
glUniform1i(uniAxis,false);
glUniform1i(uniLighting,true);
glUniform1i(uniTex,false);
glUniform1i(uniParticles,false);

glGenVertexArrays(1, &vao1);
glGenVertexArrays(1, &vao2);
glGenBuffers(1, &vbo);
glGenBuffers(1, &vbo2);
glGenBuffers(1, &ebo);
glGenTextures(1, &texture);
glGenFramebuffers(1, &fbo);


glBindVertexArray(vao1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_n), vertices_n, GL_STATIC_DRAW);
	ShaderAttrib("position", XYZ_XYZ_XY, POSITION);
	ShaderAttrib("normal", XYZ_XYZ_XY, NORMAL);
	ShaderAttrib("texCoord", XYZ_XYZ_XY, TEXTURE2D);



glBindVertexArray(vao2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_axis), vert_axis, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements2), elements2, GL_STATIC_DRAW);
	ShaderAttrib("position", XYZ_RGB, POSITION);
	ShaderAttrib("color", XYZ_RGB, COLOR);



	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		while(!glfwWindowShouldClose(window))
		{ 
				glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
		  
			glfwPollEvents();

			//transform view
				view=identity;	
				view=glm::translate(view,glm::vec3(pan_x/20.0f, pan_y/20.0f, depth/depth_factor));
				view=glm::rotate(view, glm::radians(-float(phi)),  glm::vec3(-1.0f, 0.0f, 0.0f));
				view=glm::rotate(view, glm::radians(float(theta)), glm::vec3(0.0f, 1.0f, 0.0f));
				//get camera direction
				glm::vec4 camera(0.0f);
				camera.w=1.0f;
				camera=view*camera;

			
	glStencilMask(0x00); 

				//objects
				glUseProgram(shaderObjects);
				glBindTexture(GL_TEXTURE_2D, texture);  
					glBindVertexArray(vao1);
						glm::vec3 nc;
						glUniform1i(uniLighting,true);
						glUniform1i(uniAxis,false);
						glUniform3f(uniLightPos,lightPos.x, lightPos.y, lightPos.z);
						glUniform3f(uniCameraPos,-camera.x,-camera.y, -camera.z);
		
			
							for(int i=0; i<OBJECT_COUNT; i++)
							{
								rotations[i]+=0.05;
								model=identity;
	
								model=glm::rotate(model, glm::radians(rotations[i]),  glm::vec3(1.0f,0.0f,0.0f));
								model=glm::translate(model,positions[i]);
								model=glm::rotate(model, glm::radians(rotations[i]),  positions[i]);
								nc=glm::normalize(positions[i]);
								
								nc.x=sqrt(nc.x*nc.x);
								nc.y=sqrt(nc.y*nc.y);
								nc.z=sqrt(nc.z*nc.z);

								glUniform3f(uniColor,nc.x,nc.y,nc.z);
								glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
								glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
								glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
			
								glDrawArrays(GL_TRIANGLES, 0, 36);
							
							}	

					
				//wall
				glUseProgram(shaderObjects);
				float sc=40;
				model=identity;
				model=glm::translate(model,glm::vec3(0.0f,0.0f,-5.0f));
				model=glm::scale(model,glm::vec3(sc,sc,sc/20));

				glUniform1i(uniTex,true);
				glUniform3f(uniColor,objColor.x,objColor.y, objColor.z);
				glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
				glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
				glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
				glDrawArrays(GL_TRIANGLES, 0, 36);

				//particles
							
							glUniform1i(uniTex,false);
							
							sc=0.4;

							glStencilFunc(GL_ALWAYS, 1, 0xFF); 
							glStencilMask(0xFF);

							for(int i=0; i<PARTICLE_COUNT; i++)
							{
								model=identity;
								model=glm::translate(model,positions_particles[i]);
								model=glm::scale(model,glm::vec3(sc,sc,sc));
								glUniform3f(uniColor,1.0f, 0.6f, 0.3f);
								glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
								glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
								glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
								glDrawArrays(GL_TRIANGLES, 0, 36);
							}	
							glUniform1i(uniLighting,false);
glUniform1i(uniParticles,true);
							glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
							glStencilMask(0x00); 
							//glDisable(GL_DEPTH_TEST);
							sc=0.8;
for(int i=0; i<PARTICLE_COUNT; i++)
							{
								model=identity;
								model=glm::translate(model,positions_particles[i]);
								model=glm::scale(model,glm::vec3(sc,sc,sc));
								glUniform3f(uniColor,1.0f, 0.6f, 0.3f);
								glUniform3f(uniObjPos,positions_particles[i].x, positions_particles[i].y, positions_particles[i].z);
								glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
								glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
								glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
								glDrawArrays(GL_TRIANGLES, 0, 36);
							}	
							glUniform1i(uniParticles,false);

							glStencilMask(0xFF);
							glEnable(GL_DEPTH_TEST); 
				//light
					
					static float inc=0.0;
					
					lightPos.z=(10*sin(glfwGetTime()*0.8)-10.0f);
					lightPos.y=(30*cos(glfwGetTime()*0.8));
					
					model=identity;
					model=glm::translate(model,lightPos);
					
					
					glUniform3f(uniColor,1.0f,1.0f,1.0f);
					glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
					glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
					glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
					glDrawArrays(GL_TRIANGLES, 0, 36);

				
					
				//axes
					glBindVertexArray(vao2);
					//use light's matrix
					glUniform1i(uniAxis,true);
					glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT,0);
 
			glfwSwapBuffers(window);	
				}


    glfwTerminate();
	return 0;
}







HRESULT InitWindow()
{
	HINSTANCE hInstance= GetModuleHandle(0);
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon =LoadIcon(hInstance, IDC_ARROW);
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadCursor( hInstance,IDC_ARROW );

    if( !RegisterClassEx( &wcex ) )
        printf("%d", GetLastError());

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( L"TutorialWindowClass", L"OpenGL", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );
    if( !g_hWnd )
        return E_FAIL;

    ShowWindow( g_hWnd, SW_SHOW );

    return S_OK;
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}