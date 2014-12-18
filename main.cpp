#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <Windows.h>
#include "GLee.h"
#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Camera.h"
#include "Light.h"
#include "shader.h"

#include "Reader.h"
#include "Water.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

/** Load a ppm file from disk.
@input filename The location of the PPM file.  If the file is not found, an error message
will be printed and this function will return 0
@input width This will be modified to contain the width of the loaded image, or 0 if file not found
@input height This will be modified to contain the height of the loaded image, or 0 if file not found
@return Returns the RGB pixel data as interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
**/
unsigned char* loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}


char* textFileRead(const char *filename)
{
	char* shaderFile = 0;
	//cout << filename << "\n";
	FILE* fp = fopen(filename, "rb");
	if (!fp){ fprintf(stderr, "File doesn't exist (%s)\n", filename); std::exit(-1); }

	// obtain the file size
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);

	//5 alloc memory - will be deleted while setting the shader up
	shaderFile = new char[size + 1];

	// copy the file to the shaderFile
	fread(shaderFile, sizeof(char), size, fp);
	shaderFile[size] = '\0'; // eliminate the garbage at EOF
	fclose(fp);
	//cout << shaderFile[0] << '\n';
	fprintf(stdout, "shaderfile = %p\n", shaderFile);
	return shaderFile;
}

GLuint p;
void setShaders() {
	GLuint v, f;
	char *vs, *gs, *fs;

	// Create shader handlers
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	// Read source code from files
	vs = textFileRead("skybox.vert");
	fs = textFileRead("skybox.frag");

	const char * vv = vs;
	const char * ff = fs;

	// Set shader source
	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);

	free(vs); free(fs);

	// Compile all shaders
	glCompileShader(v);
	glCompileShader(f);


	// Create the program
	p = glCreateProgram();

	// Attach shaders to program
	glAttachShader(p, v);
	glAttachShader(p, f);

	// Link and set program to use
	glLinkProgram(p);
	glUseProgram(p);
}

void printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}

void printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}

// initialize OpenGL state
void initGL()
{
	//glEnable(GL_TEXTURE_CUBE_MAP);   // enable texture mapping
	glEnable(GL_TEXTURE_2D);   // enable texture mapping

	glShadeModel(GL_SMOOTH);   // enable smooth shading
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // black background
	glClearDepth(1.0f);        // depth buffer setup
	glEnable(GL_DEPTH_TEST);   // enables depth testing
	glDepthFunc(GL_LEQUAL);    // configure depth testing
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // really nice perspective calculations
}

GLuint texture[6];     // storage for one texture
GLuint* textures = new GLuint[6];     // storage for one texture
GLuint* tex_cube = new GLuint;
GLuint* top;
GLuint* rightCube;
GLuint* leftCube;
GLuint* back;
GLuint* front;
GLuint* bottom;




bool load_cube_map_side(GLuint texture, GLenum side_target, string file_name) {

	unsigned char* tdata;  // texture pixel data
	int twidth, theight;   // texture width/height [pixels]

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	// copy image data into 'target' side of cube map
	tdata = loadPPM("Skybox_Water222_back.ppm", twidth, theight);
	if (tdata == NULL) return false;

	glTexImage2D(side_target, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
	// Set bi-linear filtering for both minification and magnification
	//glTexImage2D(side_target,0,GL_RGBA,	x,y,0,GL_RGBA,	GL_UNSIGNED_BYTE,image_data	);
	return true;
}

void create_cube_map(
	const char* front,
	const char* back,
	const char* top,
	const char* bottom,
	const char* left,
	const char* right,
	GLuint* tex_cube
	) {

	GLuint axis[6] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};


	unsigned char* tdata;  // texture pixel data
	int twidth, theight;   // texture width/height [pixels]


	// generate a cube-map texture to hold all the sides
	//glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *tex_cube);
	//for (int i = 0; i < 6; i++) {
	tdata = loadPPM("Skybox_Water222_right.ppm", twidth, theight);
	if (tdata == NULL) return;
	// Create ID for texture
	// Set this texture to be the one we are working with

	// Generate the texture
	glTexImage2D(axis[0], 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	tdata = loadPPM("Skybox_Water222_left.ppm", twidth, theight);
	if (tdata == NULL) return;
	// Create ID for texture
	// Set this texture to be the one we are working with

	// Generate the texture
	glTexImage2D(axis[1], 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	tdata = loadPPM("Skybox_Water222_top.ppm", twidth, theight);
	if (tdata == NULL) return;
	// Create ID for texture
	// Set this texture to be the one we are working with

	// Generate the texture
	glTexImage2D(axis[2], 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	tdata = loadPPM("Skybox_Water222_top.ppm", twidth, theight);
	if (tdata == NULL) return;
	// Create ID for texture
	// Set this texture to be the one we are working with

	// Generate the texture
	glTexImage2D(axis[3], 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	tdata = loadPPM("Skybox_Water222_front.ppm", twidth, theight);
	if (tdata == NULL) return;
	// Create ID for texture
	// Set this texture to be the one we are working with

	// Generate the texture
	glTexImage2D(axis[4], 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	tdata = loadPPM("Skybox_Water222_back.ppm", twidth, theight);
	if (tdata == NULL) return;
	// Create ID for texture
	// Set this texture to be the one we are working with

	// Generate the texture
	glTexImage2D(axis[5], 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);



	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//}



	//// load each image and copy into a side of the cube-map texture
	//load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	//load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	//load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	//load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	//load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	//load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
	//// format cube map texture
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

// load image file into texture object
GLuint* loadTexture(char* file_name)
{
	GLuint * tex = new GLuint;
	int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata;  // texture pixel data
	unsigned char* tdata2;  // texture pixel data

	glGenTextures(1, tex);
	// Load image file
	tdata = loadPPM(file_name, twidth, theight);
	if (tdata == NULL) return 0;
	// Create ID for texture
	// Set this texture to be the one we are working with
	glBindTexture(GL_TEXTURE_2D, *tex);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	// Set bi-linear filtering for both minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}



int main(int argc, char *argv[])
{
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess[] = { 128.0 };
	float position[] = { 0.0, 0.0, 0.0, 0.0 };	// lightsource position
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };

	glutInit(&argc, argv);      	      	      // initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
	glutInitWindowSize(Window::width, Window::height);      // set initial window size
	glutCreateWindow("OpenGL Cube");    	      // open window and set window title

	glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);

	// Generate material properties:
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Generate light source:
	/*glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);*/

	//glEnable(GL_LIGHTING);
	glDisable(GL_LIGHTING);


	/* set the window size to 512 x 512 */
	//glutInitWindowSize(512, 512);

	/* set the display mode to Red, Green, Blue and Alpha
	allocate a depth buffer
	enable double buffering
	*/
	//glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	/* create the window */
	//glutCreateWindow("Texturing Example");

	/* set the glut display callback function
	this is the function GLUT will call every time
	the window needs to be drawn
	*/
	glutDisplayFunc(Window::displayCallback);

	/* set the glut reshape callback function
	this is the function GLUT will call whenever
	the window is resized, including when it is
	first created
	*/
	glutReshapeFunc(Window::reshapeCallback);
	glutIdleFunc(Window::idleCallback);
	glutKeyboardFunc(Window::processNormalKeys);
	glutSpecialFunc(Window::processFunctionKeys);
	glutMotionFunc(Window::processMotionFunction);
	glutMouseFunc(Window::processMouseFunction);
	glutPassiveMotionFunc(Window::passiveMouseFunction);
	//Shader shade = Shader("reflection3.vert", "reflection3.frag");
	//printProgramInfoLog(shade.pid);
	//p = shade.pid;
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);


	glActiveTexture(GL_TEXTURE1);
	top = loadTexture("Skybox_Water222_top.ppm");
	glActiveTexture(GL_TEXTURE2);
	leftCube = loadTexture("Skybox_Water222_left.ppm");
	glActiveTexture(GL_TEXTURE3);
	rightCube = loadTexture("Skybox_Water222_right.ppm");
	glActiveTexture(GL_TEXTURE4);
	back = loadTexture("Skybox_Water222_back.ppm");
	glActiveTexture(GL_TEXTURE5);
	front = loadTexture("Skybox_Water222_front.ppm");
	bottom = loadTexture("floor__.ppm");

	Window::init();
	Window::genList();
	//create_cube_map("Skybox_Water222_front.ppm", "Skybox_Water222_back.ppm", "Skybox_Water222_top.ppm", "Skybox_Water222_top.ppm", "Skybox_Water222_left.ppm", "Skybox_Water222_right.ppm", tex_cube);
	initGL();
	glutMainLoop();

	return 0;
}