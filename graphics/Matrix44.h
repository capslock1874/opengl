#pragma once
#include "vector.h"
#include "vector4.h"
#include <memory.h>

class CMatrix44
{
public:
	float m[16];
	// openGL notation
	// m[0]  m[4]  m[8]   m[12]     v[0]
	// m[1]  m[5]  m[9]   m[13]  *  v[1]  
	// m[2]  m[6]  m[10]  m[14]     v[2]
	// m[3]  m[7]  m[11]  m[15]     v[3]
public:
	CMatrix44(void);
	CMatrix44(float *_m);
	CMatrix44(CMatrix44 &mat);
	CMatrix44(float _m0, float _m1, float _m2, float _m3, 
		      float _m4, float _m5, float _m6, float _m7, 
			  float _m8, float _m9, float _m10, float _m11, 
			  float _m12, float _m13, float _m14, float _m15);
	~CMatrix44(void);

	// basis operation
	int Index(int row, int col);
	void LoadIdentity(void);
	void LoadZero(void);
	CVector4 GetRow(int pos);
	CVector4 GetColumn(int pos);

	// binary operator
	CMatrix44 operator+(CMatrix44 &mat);
	CMatrix44 operator-(CMatrix44 &mat);
	CMatrix44 operator*(CMatrix44 &mat);
	CMatrix44 operator*(float a);
	CMatrix44 operator/(float b);

	//self-add operator
	void operator=(CMatrix44 &mat);
	void operator+=(CMatrix44 &mat);
	void operator-=(CMatrix44 &mat);
	void operator*=(CMatrix44 &mat);
	void operator*=(float rhs);
	void operator/=(float rhs);

	//multiply a vector by this matrix
	CVector4 operator*(CVector4 v);

	//geometry operation
	CVector GetRotatedVector(CVector &v);
	CVector GetInverseRotatedVector(CVector &v);
	CVector GetTranslatedVector(CVector &v);
	CVector GetInverseTranslatedVector(CVector &v);
	CMatrix44 GetInverse(void);
	CMatrix44 GetTranspose(void);
	CMatrix44 GetInverseTranspose(void);
	CMatrix44 GetAffineInverse(void);
	CMatrix44 GetAffineInverseTranspose(void);

	void Invert(void);
	void Transpose(void);
	void InvertTranspose(void);
	void AffineInvert(void);
	void AffineInvertTranspose(void);

	// set matrix
	void SetScale(CVector &scale);
	void SetUniformScale(float scale);
	void SetTranslation(CVector &translation);
	void SetRotationAxis(double angle, CVector &axis);
	void SetRotationX(double angle);
	void SetRotationY(double angle);
	void SetRotationZ(double angle);
	void SetRotationEuler(const double angle_x, const double angle_y, const double angle_z);
	void SetPerspective(	float left, float right, 
		                    float bottom, float top, 
							float n, float f );
	void SetPerspective(float fovy, float aspect, float n, float f);
	void SetOrtho(	float left, float right, 
		            float bottom, float top, 
					float n, float f);

private:
	void SetTranslationPart(CVector &translation);
	void SetRotationPartEuler(double angle_x, double angle_y, double angle_z);
	void SetRotationPartEuler(CVector & rotations);
};


