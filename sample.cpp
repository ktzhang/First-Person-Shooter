/*
*    OpenGL Cube Mapping Sample
*   Copyright (C) 2010  Gian Martini
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
* Sample demonstrating the use of cube mapping using OpenGL, Glut and Glee libraries
* \author Gian Martini
* \version 1.0.0
* \date 08/05/2010
*/
#ifdef _WIN32
#include <GL/glew.h>
#endif
#include <GL/glui.h>
#include "Callbacks.h"
#include "TargaLoader.h"


/**
* Main GLUT window identification
*/
int mainWindowId = 0;
/**
* Aspect Ratio, set by Callbacks.h
*/
float aspectRatio;
/**
* GLUI right window
*/
GLUI * gluiBottomWindow = 0;
/**
* Fov (for zoom)
*/
float fov = 45.0f;
/**
* Wireframe mode
*/
int enableGrid = 1;
/**
* Show texture planes
*/
int showTexturePlanes = 0;
/**
* Matrix holding scene's rotation (identity)
*/
float sceneRotation[16] = {1.0f, 0.0f, 0.0f ,0.0f,
                           0.0f, 1.0f, 0.0f ,0.0f,
                           0.0f, 0.0f, 1.0f ,0.0f,
                           0.0f, 0.0f, 0.0f ,1.0f};
/**
* Matrix holding lights's rotation (identity)
*/
float lightRotation[16] = {1.0f, 0.0f, 0.0f ,0.0f,
                           0.0f, 1.0f, 0.0f ,0.0f,
                           0.0f, 0.0f, 1.0f ,0.0f,
                           0.0f, 0.0f, 0.0f ,1.0f};
/**
* Matrix holding camera's rotation (identity)
*/
float cameraRotation[16] = {1.0f, 0.0f, 0.0f ,0.0f,
                           0.0f, 1.0f, 0.0f ,0.0f,
                           0.0f, 0.0f, 1.0f ,0.0f,
                           0.0f, 0.0f, 0.0f ,1.0f};
/**
* Enables or disables lighting
*/
int lightEnable = 1;
/**
* Cube map Texture ID's
*/
dword texPosY,texNegY,texPosZ,texNegZ,texPosX,texNegX;
/**
* Plane texture ID's
*/
dword planeTexPosX,planeTexPosY,planeTexPosZ,planeTexNegX,planeTexNegY,planeTexNegZ;
/**
* Main
* \param argc Number of arguments
* \param argv Array of argument strings
*/
int main(int argc, char* argv[])
{
    // Initialize OpenGL utility toolkit
    glutInit(&argc, argv);
    // Initialize display mode, RGBA, Double buffer and Depth buffer
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    // Position window (in desktop coordinates)
    glutInitWindowPosition( 100, 100 );
    // Set window's size
    glutInitWindowSize( 800, 600 );
    // Defines our callbacks

    // Creates our main rendering window
    mainWindowId = glutCreateWindow( "OpenGL Cube Mapping Sample" );
    // Initialize glew
    #ifdef _WIN32
    if(!(glewInit() == GLEW_OK))
    {
        printf("Error initializing GLEW");
    }
    #endif
    // Some tests to see if our particular example is hardware supported
    if(!GLEW_ARB_texture_cube_map)
    {
        printf("GL_ARB_texture_cube_map is required by this sample \n");
    }
    // Rendering callback, defined in Callbacks.h
    glutDisplayFunc(displayCallback);
    // Resize callback, sets OpenGL viewport, recalculates aspect ratio
    GLUI_Master.set_glutReshapeFunc(resizeCallback);
    // Keyboard callback, handles keys, if any
    GLUI_Master.set_glutKeyboardFunc(keyboardCallback);

    // Creates GLUI controls

    // Create GLUI window to hold our controls
    gluiBottomWindow = GLUI_Master.create_glui_subwindow(mainWindowId,GLUI_SUBWINDOW_BOTTOM);

    // Creates some options rollout
    GLUI_Rollout *options = new GLUI_Rollout(gluiBottomWindow, "Options", true );
    // Creates a checkbox for wireframe mode
    new GLUI_Checkbox( options, "Draw grid", &enableGrid );
    // Creates a checkbox for showing the texture planes
    new GLUI_Checkbox( options, "Show planes", &showTexturePlanes );
    // Creates a checkbox for enabling and disabling lighting
    new GLUI_Checkbox( options, "Enable lights", &lightEnable );


    // Create a new collumn in the bottom window to add another controller
    new GLUI_Column(gluiBottomWindow,false);
    // Scene rotation controller
    GLUI_Rotation * sceneRotationBall = new GLUI_Rotation(gluiBottomWindow, "Scene Rotation", sceneRotation );

    // Create a new collumn in the bottom window to add another controller
    new GLUI_Column(gluiBottomWindow,false);
    // Light rotation controller
    GLUI_Rotation * lightRotationBall = new GLUI_Rotation(gluiBottomWindow, "Light Rotation", lightRotation );
    // Create a new collumn in the bottom window to add another controller
    new GLUI_Column(gluiBottomWindow,false);
    // Light rotation controller
    GLUI_Rotation * cameraRotationBall = new GLUI_Rotation(gluiBottomWindow, "Camera Rotation", cameraRotation );
    // Create a new collumn in the bottom window to add another controller
    new GLUI_Column(gluiBottomWindow,false);
    // Create a Zoom controller (+/- fov)
    GLUI_Translation *fovController = new GLUI_Translation( gluiBottomWindow, "Zoom", GLUI_TRANSLATION_Z,&fov);
    // Set speed in which fov changes
    fovController->set_speed( 1.0f );
    // Set the windows that actually draws stuff
    gluiBottomWindow->set_main_gfx_window( mainWindowId );
    // Create a few light parameters
    float light0Diffuse[4] = {1.0f,1.0f,1.0f,1.0f};
    // Set light parameters
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light0Diffuse);
    // Setups some basic states
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_CUBE_MAP);
    // Enable texture generation for S,T,R coords
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);
    // Sets the coordinates to be generated and how
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_NORMAL_MAP);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_NORMAL_MAP);
    glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_NORMAL_MAP);

    // This glut implementation has an strange issue
    // the Teapot (glutSolidTeapot) is draw using
    // clock-wise face ordering. Other primitives are
    // draw with Counter clock-wise face ordering...
    // Case this is an isolated issue (which I don't
    // believe) please, revert to GL_CCW
    glFrontFace(GL_CW);

    // Create and load the 6 textures of the cube map
    CTargaLoader * imgPositiveX = new CTargaLoader("OutdoorsPositiveX.tga");
    CTargaLoader * imgNegativeX = new CTargaLoader("OutdoorsNegativeX.tga");
    CTargaLoader * imgPositiveY = new CTargaLoader("OutdoorsPositiveY.tga");
    CTargaLoader * imgNegativeY = new CTargaLoader("OutdoorsNEgativeY.tga");
    CTargaLoader * imgPositiveZ = new CTargaLoader("OutdoorsPositiveZ.tga");
    CTargaLoader * imgNegativeZ = new CTargaLoader("OutdoorsNegativeZ.tga");

    // Create the cube map textures, positive X
    glGenTextures(1,&texPosX);
    glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X,texPosX);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGB,imgPositiveX->header->imgWidth,imgPositiveX->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgPositiveX->imageData);
    // Create the cube map textures, negative X
    glGenTextures(1,&texNegX);
    glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,texNegX);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGB,imgNegativeX->header->imgWidth,imgNegativeX->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgNegativeX->imageData);
    // Create the cube map textures, positive Y
    glGenTextures(1,&texPosY);
    glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,texPosY);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGB,imgPositiveY->header->imgWidth,imgPositiveY->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgPositiveY->imageData);
    // Create the cube map textures, negative Y
    glGenTextures(1,&texNegY);
    glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,texNegY);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGB,imgNegativeY->header->imgWidth,imgNegativeY->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgNegativeY->imageData);
    // Create the cube map textures, positive Z
    glGenTextures(1,&texPosZ);
    glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,texPosZ);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGB,imgPositiveZ->header->imgWidth,imgPositiveZ->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgPositiveZ->imageData);
    // Create the cube map textures, negative Z
    glGenTextures(1,&texNegZ);
    glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,texNegZ);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGB,imgNegativeZ->header->imgWidth,imgNegativeZ->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgNegativeZ->imageData);

    // Sets the texture's behavior for wrapping (optional)
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_REPEAT);
    // Sets the texture's max/min filters
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    // Now we re-create the textures to texturize the planes

    // Create plane texture, postive X
    glGenTextures(1,&planeTexPosX);
    glBindTexture(GL_TEXTURE_2D,planeTexPosX);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imgPositiveX->header->imgWidth,imgPositiveX->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgPositiveX->imageData);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // Create plane texture, negative X
    glGenTextures(1,&planeTexNegX);
    glBindTexture(GL_TEXTURE_2D,planeTexNegX);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imgNegativeX->header->imgWidth,imgNegativeX->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgNegativeX->imageData);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // Create plane texture, postive X
    glGenTextures(1,&planeTexPosY);
    glBindTexture(GL_TEXTURE_2D,planeTexPosY);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imgPositiveY->header->imgWidth,imgPositiveY->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgPositiveY->imageData);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // Create plane texture, negative X
    glGenTextures(1,&planeTexNegY);
    glBindTexture(GL_TEXTURE_2D,planeTexNegY);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imgNegativeY->header->imgWidth,imgNegativeY->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgNegativeY->imageData);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // Create plane texture, postive X
    glGenTextures(1,&planeTexPosZ);
    glBindTexture(GL_TEXTURE_2D,planeTexPosZ);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imgPositiveZ->header->imgWidth,imgPositiveZ->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgPositiveZ->imageData);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // Create plane texture, negative X
    glGenTextures(1,&planeTexNegZ);
    glBindTexture(GL_TEXTURE_2D,planeTexNegZ);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imgNegativeZ->header->imgWidth,imgNegativeZ->header->imgHeight,1,GL_BGR,GL_UNSIGNED_BYTE,imgNegativeZ->imageData);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    // START!
    glutMainLoop();
    return 0;
}