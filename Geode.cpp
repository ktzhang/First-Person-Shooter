#include "Geode.h"
#include <GL/glut.h>


void Geode::draw(Matrix4 matrix) {
	setModelView(matrix);
	render();
	unsetModelView();
}

void Geode::drawBoundingSpheres(Matrix4 worldMatrix) { 
	setModelView(worldMatrix);
	glColor3f(1, 1, 1);
	glutWireSphere(sphereRadius, 10, 10);
	unsetModelView();
}

void Geode::setModelView(Matrix4 matrix) {
	glPushMatrix();
	glMultMatrixd(matrix.getPointer());
}

void Geode::unsetModelView() {
	glPopMatrix();
}

//Apply a Matrix4 transform on a point
Vector3 transformVector(Vector3 vector, Matrix4 transformMatrix) {
	Vector4* origin4 = &Vector4(vector.m[0], vector.m[1], vector.m[2], 1);
	*origin4 = transformMatrix * *origin4;
	origin4->dehomogenize();
	return Vector3(origin4->m[0], origin4->m[1], origin4->m[2]);
}

void Geode::update(Matrix4 transformMatrix) {
	Vector4 temp = transformMatrix * Vector4(sphereOrigin.m[0], sphereOrigin.m[1], sphereOrigin.m[2], 1);
	sphereOrigin = Vector3(temp.m[0], temp.m[1], temp.m[2]);


	// Method which is to create a vector from 0 to the radius
	// and then any transformation would change the vector
	// and then take the vector's final length as the new radius.
	Vector4 sizeVector = Vector4(0, sphereRadius, 0, 0);
	//cout << " " << sizeVector.length() << " ";
	Vector4 tempSize = transformMatrix * sizeVector;
	newSphereRadius = tempSize.length();;
	//cout << newSphereRadius << " ";


	//Converting the spheres
	//Vector3 xVector = Vector3(sphereRadius + sphereOrigin.m[0], sphereOrigin.m[1], sphereOrigin.m[2]);
	//Vector3 yVector = Vector3(sphereOrigin.m[0], sphereRadius + sphereOrigin.m[1], sphereOrigin.m[2]);
	//Vector3 zVector = Vector3(sphereOrigin.m[0], sphereOrigin.m[1], sphereRadius + sphereOrigin.m[2]);

	//Vector3 newX = transformVector(xVector, transformMatrix);
	//Vector3 newY = transformVector(yVector, transformMatrix);
	//Vector3 newZ = transformVector(zVector, transformMatrix);
	//sphereOrigin = transformVector(sphereOrigin, transformMatrix);

	//double distanceX = 0, distanceY = 0, distanceZ = 0;
	//for (int j = 0; j < 3; j++) {
	//	
	//	distanceX += (newX.m[j] - sphereOrigin.m[j])*(newX.m[j] - sphereOrigin.m[j]);
	//	distanceY += (newY.m[j] - sphereOrigin.m[j])*(newY.m[j] - sphereOrigin.m[j]);
	//	distanceZ += (newZ.m[j] - sphereOrigin.m[j])*(newZ.m[j] - sphereOrigin.m[j]);
	//}
	//double maxDist = distanceX;
	//if (distanceY > maxDist) maxDist = distanceY;
	//if (distanceZ > maxDist) maxDist = distanceZ;

	//sphereRadius = sqrt(maxDist);

	//shouldRender(transformMatrix);
}

void Geode::shouldRender(Matrix4 transformMatrix) {
	int sum = 0;
	double radius = sphereRadius + 10;
	for (int i = 0; i < 12; i += 2) {
		Vector3 point = planes[i];
		Vector3 direction = planes[i + 1];
		Vector3 newVector = (sphereOrigin - point);
		double distance = newVector.dot(newVector, direction);
		if (distance < radius) {
			sum++;
		}
	}
	if (sum == 6) {
		shouldRenderObj = 1;
	}
	else {
		shouldRenderObj = 0;
	}
}
