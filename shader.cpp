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

#include <cstdio>
#include <cstdlib>

#include "shader.h"

Shader::Shader(const char *vert, const char *frag, bool isFile)
{
	if(isFile)
	{
		char* vv = read(vert);
		char* vf = read(frag);

		setup(vv, vf);
		delete[] vv;
		delete[] vf;
	}
	else
		setup(vert, frag);
}

Shader::~Shader()
{
	glDeleteObjectARB(pid);
}

void
Shader::bind()
{
	glUseProgramObjectARB(pid);
}
void
Shader::unbind()
{
	glUseProgramObjectARB(0);
}

void
Shader::printLog(const char* tag)
{
	char glslLog[1024];
	GLsizei glslLogSize;
	glGetInfoLogARB(pid, 1024, &glslLogSize, glslLog);
	if(glslLogSize>0)
	{
		fprintf(stderr, "%s:shader error log: %s\n", tag, glslLog);
	}
	else
	{
		fprintf(stdout, "%s:shader all ok.\n", tag);
	}
}

char* Shader::read(const char *filename)
{
	char* shaderFile = 0;
	
	FILE* fp = fopen(filename, "rb");
	if(!fp){fprintf(stderr, "File doesn't exist (%s)\n", filename); std::exit(-1);}

	// obtain the file size
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);

	// alloc memory - will be deleted while setting the shader up
	shaderFile = new char[size+1];

	// copy the file to the shaderFile
	fread(shaderFile, sizeof(char), size, fp);
	shaderFile[size]='\0'; // eliminate the garbage at EOF
	fclose(fp);

	fprintf(stdout, "shaderfile = %p\n", shaderFile);
	return shaderFile;
}

void
Shader::setup(const char *vs, const char *fs)
{
	//fprintf(stdout, "vs, fs = %p, %p\n", vs, fs);
	
	//GLuint vid = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	//GLuint fid = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	GLhandleARB vid = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	GLhandleARB fid = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	
	glShaderSourceARB(vid, 1, &vs, 0);
	glShaderSourceARB(fid, 1, &fs, 0);
	
	glCompileShaderARB(vid);
	glCompileShaderARB(fid);
	char glslLog[1024];
	GLsizei glslLogSize;
	glGetInfoLogARB(vid, 1024, &glslLogSize, glslLog);
	if (glslLogSize)
		printf("vertex program log: %s\n", glslLog);
	glGetInfoLogARB(fid, 1024, &glslLogSize, glslLog);
	if (glslLogSize)
		printf("fragment program log: %s\n", glslLog);

	pid = glCreateProgramObjectARB();

	glAttachObjectARB(pid, vid);
	glAttachObjectARB(pid, fid);

	// delete shader objects as soon as they have been attached to a program
	glDeleteObjectARB(vid);
	glDeleteObjectARB(fid);
	
	glLinkProgramARB(pid);
}

