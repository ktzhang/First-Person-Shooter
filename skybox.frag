#version 400

in vec3 texcoords;
//uniform sampler2D cube_texture;
out vec4 frag_colour;

void main () {
  //frag_colour = texture (cube_texture, texcoords);
  //frag_colour = vec4(1.0, 0.0, 1.0, 1.0);
	gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);

}