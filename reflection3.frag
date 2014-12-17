#version 400

varying vec3 normal1;

uniform sampler2D top;
uniform sampler2D leftCube;
uniform sampler2D rightCube;
uniform sampler2D front;
uniform sampler2D back;
uniform mat4 modelVMat; 

out vec4 color;

void main () {
 	vec3 normal = vec3(inverse(modelVMat) * vec4(normal1, 1.0));
 	if(abs(normal[0]) > abs(normal[1]) && abs(normal[0]) > abs(normal[2])) {
 		if(normal[0] < 0) {
 			float a = (normal[1] / abs(normal[0]) + 1) / 2;
 			float b = (normal[2] / abs(normal[0]) + 1) / 2;
			color = texture(rightCube, vec2(a, b));
		} else {
			float a = (normal[1] / abs(normal[0]) + 1) / 2;
 			float b = (normal[2] / abs(normal[0]) + 1) / 2;
			color = texture(leftCube, vec2(a, b));
		}
 	}

 	else if(abs(normal[1]) > abs(normal[0]) && abs(normal[1]) > abs(normal[2])) {
 		if(normal[1] < 0) {
 			//Bottom
 			float a = (normal[0] / abs(normal[1]) + 1) / 2;
 			float b = (normal[2] / abs(normal[1]) + 1) / 2;
			color = texture(top, vec2(a, b));
		} else {
			//Top
			float a = (normal[0] / abs(normal[1]) + 1) / 2;
 			float b = (normal[2] / abs(normal[1]) + 1) / 2;
			color = texture(top, vec2(a, b));
		}
 	}

 	else if(abs(normal[2]) > abs(normal[0]) && abs(normal[2]) > abs(normal[1])) {
 		if(normal[2] < 0) {
 			float a = (normal[0] / abs(normal[2]) + 1) / 2;
 			float b = (normal[1] / abs(normal[2]) + 1) / 2;
			color = texture(back, vec2(a, b));
		} else {
			float a = (normal[0] / abs(normal[2]) + 1) / 2;
 			float b = (normal[1] / abs(normal[2]) + 1) / 2;
			color = texture(front, vec2(a, b));
		}
 	}

 	else {
 		color = vec4(.5,.5,.5,1);
 	}
}