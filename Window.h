#ifndef _WINDOW_H_
#define _WINDOW_H_

class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processFunctionKeys(int key, int x, int y);


    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif

