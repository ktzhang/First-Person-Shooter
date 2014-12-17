#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

/* Try uncommenting this include line to compile on Max OSX
#include <GLUT/glut.h>
*/

#include <math.h>   // include math functions, such as sin, cos, M_PI
#include <iostream> // allow c++ style console printouts

using namespace std; // allow console printouts without std::

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);
/*! GLUT idle callback function */
void idle();

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

	if ( (fp=fopen(filename, "rb")) == NULL)
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
		retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width  = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
	  retval_fgets=fgets(buf[0], BUFSIZE, fp);
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

// initialize OpenGL state
void initGL()
{
  glEnable(GL_TEXTURE_2D);   // enable texture mapping
  glShadeModel(GL_SMOOTH);   // enable smooth shading
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // black background
  glClearDepth(1.0f);        // depth buffer setup
  glEnable(GL_DEPTH_TEST);   // enables depth testing
  glDepthFunc(GL_LEQUAL);    // configure depth testing
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // really nice perspective calculations
}

// load image file into texture object
void loadTexture()
{
  GLuint texture[1];     // storage for one texture
  int twidth, theight;   // texture width/height [pixels]
  unsigned char* tdata;  // texture pixel data
  
  // Load image file
  tdata = loadPPM("image.ppm", twidth, theight);
  if (tdata==NULL) return;
  
  // Create ID for texture
  glGenTextures(1, &texture[0]);   

  // Set this texture to be the one we are working with
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  
  // Generate the texture
  glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
  
  // Set bi-linear filtering for both minification and magnification
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  /* set the window size to 512 x 512 */
  glutInitWindowSize(512, 512);

  /* set the display mode to Red, Green, Blue and Alpha
    allocate a depth buffer
    enable double buffering
  */
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  /* create the window */
  glutCreateWindow("Texturing Example");
  
  /* set the glut display callback function
    this is the function GLUT will call every time
    the window needs to be drawn
  */
  glutDisplayFunc(display);

  /* set the glut reshape callback function
    this is the function GLUT will call whenever
    the window is resized, including when it is
    first created
  */
  glutReshapeFunc(reshape);
  
  glutIdleFunc(idle);

  loadTexture();
  
  initGL();

  /* enter the main event loop so that GLUT can process
    all of the window event messages
  */
  glutMainLoop();

  return 0;
}

/*! glut display callback function.  Every time the window needs to be drawn,
  glut will call this function.  This includes when the window size
  changes, or when another window covering part of this window is
  moved so this window is uncovered.
*/
void display()
{
  cerr << "display callback" << endl;

  /* clear the color buffer (resets everything to black) */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  /* draw quad, takes 4 vertices */
  glBegin(GL_QUADS);   

    // set the current drawing color to white to use original texture colors
    glColor3f(1, 1, 1);

    // specify texture coordinates for each vertex
    // note that textures are stored "upside down"
    glTexCoord2f(0, 1); glVertex3f(-2, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(2, -1, 0);
    glTexCoord2f(1, 0); glVertex3f(2, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-2, 1, 0);

  /* tell OpenGL we're done drawing quads */
  glEnd();

  /* swap the back and front buffers so we can see what we just drew */
  glutSwapBuffers();
}

/*! glut reshape callback function.  GLUT calls this function whenever
  the window is resized, including the first time it is created.
  You can use variables to keep track the current window size.
*/
void reshape(int width, int height)
{
  cerr << "reshape callback" << endl;

  /* tell OpenGL we want to display in a recangle that is the 
    same size as the window
  */
  glViewport(0,0,width,height);

  /* switch to the projection matrix */
  glMatrixMode(GL_PROJECTION);

  /* clear the projection matrix */
  glLoadIdentity();

  /* set the camera view, orthographic projection with 4x4 unit square canvas*/
  glOrtho(-2,2,-2,2,2,-2);

  /* switch back to the model view matrix */
  glMatrixMode(GL_MODELVIEW);
}

/* Gets called whenever computer doesn't have anything else to do */
void idle() 
{
  cerr << "idle callback" << endl;
  display();     // call display callback, useful for animation
} 