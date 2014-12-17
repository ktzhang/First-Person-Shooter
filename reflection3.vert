#version 400

in vec3 vp; // positions from mesh
in vec3 vn; // normals from mesh
uniform mat4 projMat, modelVMat; // proj, view, model matrices
varying vec3 normal1;

void main () {
  vec3 worldPos = vec3 (modelVMat * vec4 (vp, 1.0));
  gl_Position = projMat * vec4 (worldPos, 1.0);
  normal1 = normalize(reflect(normalize(-worldPos), vn));
}