/*
 Copyright (C) 2006 So Yamaoka

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 */

#ifndef _SHADER_H_
#define _SHADER_H_
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include "glee.h"
#endif

/*! Handles GLSL shaders.  It can load the code from the file or read straight
 * from the char array. */
class Shader
{
public:
	//unsigned int pid; // prog id
	GLhandleARB pid; // prog id

public:
	Shader(const char *vert, const char *frag, bool isFile=true);
	~Shader();

	/** bind/unbind this shader. */
	void bind();
	void unbind();

	/** get the program */
	//unsigned int getPid()
	GLhandleARB getPid()
	{
		return pid;
	}

	/** dump log */
	void printLog(const char* tag = "");

	static void enable();
	static void disable();

private:
	/** read a shader file
	 programmer is responsible for deleting returned buffer */
	char* read(const char *filename);

	/** create shaders from given vert and frag programs. */
	void setup(const char *vs, const char *fs);	
};


#endif
