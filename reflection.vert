#version 400

in vec3 vp; // positions from mesh
in vec3 vn; // normals from mesh
uniform mat4 projMat, modelVMat; // proj, view, model matrices
out vec3 pos_eye;
out vec3 n_eye;

void main () {
  pos_eye = vec3 (modelVMat * vec4 (vp, 1.0));
  n_eye = vec3 (modelVMat * vec4 (vn, 0.0));

  n_eye = vn;
  gl_Position = projMat * modelVMat * vec4 (vp, 1.0);
}