#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#define M_PI 3.14159265358979323846

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)
    
  public:
    Matrix4();     
    Matrix4& operator=(const Matrix4&);
    double* getPointer(); 
    void identity(); 
    void transpose();
    void makeRotateY(double); 
};

#endif