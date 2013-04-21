#include ".\matrix44.h"

CMatrix44::CMatrix44(void)
{
	LoadIdentity();
}

CMatrix44::CMatrix44(float *_m)
{
	memcpy(m, _m, sizeof(float)*16);
}

CMatrix44::CMatrix44(CMatrix44 &mat)
{
	memcpy(m, mat.m, sizeof(float)*16);
}

CMatrix44::CMatrix44(float _m0, float _m1, float _m2, float _m3, 
		             float _m4, float _m5, float _m6, float _m7, 
		             float _m8, float _m9, float _m10, float _m11, 
		             float _m12, float _m13, float _m14, float _m15)
{
   m[0] = _m0;   m[1] = _m1;    m[2] = _m2;    m[3] = _m3;
   m[4] = _m4;   m[5] = _m5;    m[6] = _m6;    m[7] = _m7;
   m[8] = _m8;   m[9] = _m9;    m[10] = _m10;  m[11] = _m11;
   m[12] = _m12; m[13] = _m13;  m[14] = _m14;  m[15] = _m15;
}

CMatrix44::~CMatrix44(void)
{
}

int CMatrix44::Index(int row, int col)
{
	return (col * 4 + row);
}

// basic operation
void CMatrix44::LoadZero()
{
   memset(m, 0, sizeof(float)*16);
}

void CMatrix44::LoadIdentity(void)
{
	LoadZero();
	m[Index(0,0)] = 1;
	m[Index(1,1)] = 1;
	m[Index(2,2)] = 1;
	m[Index(3,3)] = 1;
}

CVector4 CMatrix44::GetRow(int pos)
{
   return CVector4(m[pos], m[pos+4], m[pos+8], m[pos+12]);
}

CVector4 CMatrix44::GetColumn(int pos)
{
	int i = Index(pos, 0);
	return CVector4(m[i], m[i+1], m[i+2], m[i+3]);	
}

// binary operator

CMatrix44 CMatrix44::operator+(CMatrix44 &mat)
{
	CMatrix44 r;
	for (int i = 0; i < 16; i++)
	{
		r.m[i] = m[i] + mat.m[i];
	}
	return r;
}

CMatrix44 CMatrix44::operator-(CMatrix44 &mat)
{
	CMatrix44 r;
	for (int i = 0; i < 16; i++)
	{
		r.m[i] = m[i] - mat.m[i];
	}
	return r;
}

CMatrix44 CMatrix44::operator*(CMatrix44 &mat)
{
	CMatrix44 r;
	r.LoadZero();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
			{
				r.m[Index(i,j)] += m[Index(i,k)] * mat.m[Index(k,j)];
			}
	return r;
}

CMatrix44 CMatrix44::operator*(float a)
{
	CMatrix44 r;
	for (int i = 0; i < 16; i++)
	{
		r.m[i] = m[i] * a;
	}
	return r;
}

CMatrix44 CMatrix44::operator/(float a)
{
	CMatrix44 r;
	for (int i = 0; i < 16; i++)
	{
		r.m[i] = m[i] / a;
	}
	return r;
}

// self-add operator
void CMatrix44::operator=(CMatrix44 &mat)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = mat.m[i];
	}
}

void CMatrix44::operator+=(CMatrix44 &mat)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] += mat.m[i];
	}
}

void CMatrix44::operator-=(CMatrix44 &mat)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] -= mat.m[i];
	}
}
void CMatrix44::operator*=(CMatrix44 &mat)
{
	(*this) = (*this) * mat;
}

void CMatrix44::operator*=(float a)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] *= a;
	}
}
void CMatrix44::operator/=(float a)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] /= a;
	}
}

CVector4 CMatrix44::operator*(CVector4 v)
{
	CVector4 r;
	r.x = GetRow(0) * v;
	r.y = GetRow(1) * v;
	r.z = GetRow(2) * v;
	r.w = GetRow(3) * v;
	return r;
}


CVector CMatrix44::GetRotatedVector(CVector &v)
{
	return CVector(m[0]*v.x + m[4]*v.y + m[8]*v.z,
		           m[1]*v.x + m[5]*v.y + m[9]*v.z,
		           m[2]*v.x + m[6]*v.y + m[10]*v.z);
}

CVector CMatrix44::GetInverseRotatedVector(CVector &v)
{
	//rotate by transpose:
	return CVector(m[0]*v.x + m[1]*v.y + m[2]*v.z,
		           m[4]*v.x + m[5]*v.y + m[6]*v.z,
		           m[8]*v.x + m[9]*v.y + m[10]*v.z);
}

CVector CMatrix44::GetTranslatedVector(CVector &v)
{
	return CVector(v.x+m[12], v.y+m[13], v.z+m[14]);
}

CVector CMatrix44::GetInverseTranslatedVector(CVector &v)
{
	return CVector(v.x-m[12], v.y-m[13], v.z-m[14]);
}

void CMatrix44::Transpose(void)
{
	*this=GetTranspose();
}

CMatrix44 CMatrix44::GetTranspose(void)
{
	return CMatrix44(	m[ 0], m[ 4], m[ 8], m[12],
		m[ 1], m[ 5], m[ 9], m[13],
		m[ 2], m[ 6], m[10], m[14],
		m[ 3], m[ 7], m[11], m[15] );
}

void CMatrix44::Invert(void)
{
	*this=GetInverse();
}

CMatrix44 CMatrix44::GetInverse(void)
{
	CMatrix44 r = GetInverseTranspose();
	r.Transpose();
	return r;
}


void CMatrix44::InvertTranspose(void)
{
	*this=GetInverseTranspose();
}

CMatrix44 CMatrix44::GetInverseTranspose(void)
{
	CMatrix44 result;

	float tmp[12];												//temporary pair storage
	float det;													//determinant

	//calculate pairs for first 8 elements (cofactors)
	tmp[0] = m[10] * m[15];
	tmp[1] = m[11] * m[14];
	tmp[2] = m[9] * m[15];
	tmp[3] = m[11] * m[13];
	tmp[4] = m[9] * m[14];
	tmp[5] = m[10] * m[13];
	tmp[6] = m[8] * m[15];
	tmp[7] = m[11] * m[12];
	tmp[8] = m[8] * m[14];
	tmp[9] = m[10] * m[12];
	tmp[10] = m[8] * m[13];
	tmp[11] = m[9] * m[12];

	//calculate first 8 elements (cofactors)
	result.m[0] = ( tmp[0]*m[5] + tmp[3]*m[6] + tmp[4]*m[7]
	              -	tmp[1]*m[5] - tmp[2]*m[6] - tmp[5]*m[7] );

	result.m[1] = ( tmp[1]*m[4] + tmp[6]*m[6] + tmp[9]*m[7]
	              -	tmp[0]*m[4] - tmp[7]*m[6] - tmp[8]*m[7] );

	result.m[2] = (	tmp[2]*m[4] + tmp[7]*m[5] + tmp[10]*m[7]
	              -	tmp[3]*m[4] - tmp[6]*m[5] - tmp[11]*m[7] );

	result.m[3] = ( tmp[5]*m[4] + tmp[8]*m[5] + tmp[11]*m[6]
	              -	tmp[4]*m[4] - tmp[9]*m[5] - tmp[10]*m[6] );

	result.m[4] = (	tmp[1]*m[1] + tmp[2]*m[2] + tmp[5]*m[3]
	              -	tmp[0]*m[1] - tmp[3]*m[2] - tmp[4]*m[3] );

	result.m[5] = ( tmp[0]*m[0] + tmp[7]*m[2] + tmp[8]*m[3]
	              -	tmp[1]*m[0] - tmp[6]*m[2] - tmp[9]*m[3] );

	result.m[6] = ( tmp[3]*m[0] + tmp[6]*m[1] + tmp[11]*m[3]
	              -	tmp[2]*m[0] - tmp[7]*m[1] - tmp[10]*m[3] );

	result.m[7] = ( tmp[4]*m[0] + tmp[9]*m[1] + tmp[10]*m[2]
	              -	tmp[5]*m[0] - tmp[8]*m[1] - tmp[11]*m[2] );

	//calculate pairs for second 8 elements (cofactors)
	tmp[0] = m[2]*m[7];
	tmp[1] = m[3]*m[6];
	tmp[2] = m[1]*m[7];
	tmp[3] = m[3]*m[5];
	tmp[4] = m[1]*m[6];
	tmp[5] = m[2]*m[5];
	tmp[6] = m[0]*m[7];
	tmp[7] = m[3]*m[4];
	tmp[8] = m[0]*m[6];
	tmp[9] = m[2]*m[4];
	tmp[10] = m[0]*m[5];
	tmp[11] = m[1]*m[4];

	//calculate second 8 elements (cofactors)
	result.m[8] = ( tmp[0]*m[13] + tmp[3]*m[14] + tmp[4]*m[15]
	              -	tmp[1]*m[13] - tmp[2]*m[14] - tmp[5]*m[15] );

	result.m[9] = ( tmp[1]*m[12] + tmp[6]*m[14] + tmp[9]*m[15]
	              -	tmp[0]*m[12] - tmp[7]*m[14] - tmp[8]*m[15] );

	result.m[10] = ( tmp[2]*m[12] + tmp[7]*m[13] + tmp[10]*m[15]
	               - tmp[3]*m[12] - tmp[6]*m[13] - tmp[11]*m[15] );

	result.m[11] = ( tmp[5]*m[12] + tmp[8]*m[13] + tmp[11]*m[14]
	               - tmp[4]*m[12] - tmp[9]*m[13] - tmp[10]*m[14] );

	result.m[12] = ( tmp[2]*m[10] + tmp[5]*m[11] + tmp[1]*m[9]
	               - tmp[4]*m[11] - tmp[0]*m[9] - tmp[3]*m[10] );

	result.m[13] = ( tmp[8]*m[11] + tmp[0]*m[8] + tmp[7]*m[10]
	               - tmp[6]*m[10] - tmp[9]*m[11] - tmp[1]*m[8] );

	result.m[14] = ( tmp[6]*m[9] + tmp[11]*m[11] + tmp[3]*m[8]
	               - tmp[10]*m[11] - tmp[2]*m[8] - tmp[7]*m[9] );

	result.m[15] = ( tmp[10]*m[10] + tmp[4]*m[8] + tmp[9]*m[9]
	               - tmp[8]*m[9] - tmp[11]*m[10] - tmp[5]*m[8] );

	// calculate determinant
	det	=	 m[0]*result.m[0]
	        +m[1]*result.m[1]
			+m[2]*result.m[2]
            +m[3]*result.m[3];

	if(det==0.0f)
	{
		CMatrix44 id;
		return id;
	}

	result=result/det;
	return result;
}

//Invert if only composed of rotations & translations
void CMatrix44::AffineInvert(void)
{
	(*this)=GetAffineInverse();
}

CMatrix44 CMatrix44::GetAffineInverse(void)
{
	//return the transpose of the rotation part
	//and the negative of the inverse rotated translation part
	return CMatrix44(	m[0], m[4], m[8], 0.0f,
		                m[1], m[5], m[9], 0.0f,
                        m[2], m[6], m[10], 0.0f,
                        -(m[0]*m[12]+m[1]*m[13]+m[2]*m[14]),
                        -(m[4]*m[12]+m[5]*m[13]+m[6]*m[14]),
		                -(m[8]*m[12]+m[9]*m[13]+m[10]*m[14]),
		                1.0f);
}

void CMatrix44::AffineInvertTranspose(void)
{
	(*this)=GetAffineInverseTranspose();
}

CMatrix44 CMatrix44::GetAffineInverseTranspose(void)
{
	//return the transpose of the rotation part
	//and the negative of the inverse rotated translation part
	//transposed
	return CMatrix44(	m[0], m[1],	m[2], -(m[0]*m[12]+m[1]*m[13]+m[2]*m[14]),
		                m[4], m[5], m[6], -(m[4]*m[12]+m[5]*m[13]+m[6]*m[14]),
		                m[8], m[9], m[10], -(m[8]*m[12]+m[9]*m[13]+m[10]*m[14]),
		                0.0f, 0.0f, 0.0f, 1.0f);
}

void CMatrix44::SetScale(CVector &scale)
{
	LoadIdentity();
	m[0]=scale.x;
	m[5]=scale.y;
	m[10]=scale.z;
}

void CMatrix44::SetUniformScale(float scale)
{
	LoadIdentity();
	m[0]=m[5]=m[10]=scale;
}


void CMatrix44::SetTranslation(CVector &translation)
{
	LoadIdentity();
	SetTranslationPart(translation);
}


void CMatrix44::SetRotationAxis(double angle, CVector &axis)
{
	CVector u=axis.Normalized();

	float sinAngle=(float)sin(PI*angle/180);
	float cosAngle=(float)cos(PI*angle/180);
	float oneMinusCosAngle=1.0f-cosAngle;

	LoadIdentity();

	m[0]=(u.x)*(u.x) + cosAngle*(1-(u.x)*(u.x));
	m[4]=(u.x)*(u.y)*(oneMinusCosAngle) - sinAngle*u.z;
	m[8]=(u.x)*(u.z)*(oneMinusCosAngle) + sinAngle*u.y;

	m[1]=(u.x)*(u.y)*(oneMinusCosAngle) + sinAngle*u.z;
	m[5]=(u.y)*(u.y) + cosAngle*(1-(u.y)*(u.y));
	m[9]=(u.y)*(u.z)*(oneMinusCosAngle) - sinAngle*u.x;

	m[2]=(u.x)*(u.z)*(oneMinusCosAngle) - sinAngle*u.y;
	m[6]=(u.y)*(u.z)*(oneMinusCosAngle) + sinAngle*u.x;
	m[10]=(u.z)*(u.z) + cosAngle*(1-(u.z)*(u.z));
}

void CMatrix44::SetRotationX(double angle)
{
	LoadIdentity();
	m[5]=(float)cos(PI*angle/180);
	m[6]=(float)sin(PI*angle/180);
	m[9]=-m[6];
	m[10]=m[5];
}

void CMatrix44::SetRotationY(double angle)
{
	LoadIdentity();
	m[0]=(float)cos(PI*angle/180);
	m[2]=-(float)sin(PI*angle/180);
	m[8]=-m[2];
	m[10]=m[0];
}

void CMatrix44::SetRotationZ(double angle)
{
	LoadIdentity();
	m[0]=(float)cos(PI*angle/180);
	m[1]=(float)sin(PI*angle/180);
	m[4]=-m[1];
	m[5]=m[0];
}

void CMatrix44::SetRotationEuler(const double angle_x, const double angle_y, const double angle_z)
{
	LoadIdentity();
	SetRotationPartEuler(angle_x, angle_y, angle_z);
}

void CMatrix44::SetPerspective(	float left, float right, float bottom,
							   float top, float n, float f)
{
	float nudge=0.999f;		//prevent artifacts with infinite far plane

	LoadZero();

	//check for division by 0
	if(left==right || top==bottom || n==f)
		return;

	m[0]=(2*n)/(right-left);

	m[5]=(2*n)/(top-bottom);

	m[8]=(right+left)/(right-left);
	m[9]=(top+bottom)/(top-bottom);

	if(f!=-1)
	{
		m[10]=-(f+n)/(f-n);
	}
	else		//if f==-1, use an infinite far plane
	{
		m[10]=-nudge;
	}

	m[11]=-1;

	if(f!=-1)
	{
		m[14]=-(2*f*n)/(f-n);
	}
	else		//if f==-1, use an infinite far plane
	{
		m[14]=-2*n*nudge;
	}
}

void CMatrix44::SetPerspective(float fovy, float aspect, float n, float f)
{
	float left, right, top, bottom;

	//convert fov from degrees to radians
	fovy*=(float)PI/180;

	top=n*tanf(fovy/2.0f);
	bottom=-top;

	left=aspect*bottom;
	right=aspect*top;

	SetPerspective(left, right, bottom, top, n, f);
}

void CMatrix44::SetOrtho(	float left, float right, float bottom,
						 float top, float n, float f)
{
	LoadIdentity();

	m[0]=2.0f/(right-left);

	m[5]=2.0f/(top-bottom);

	m[10]=-2.0f/(f-n);

	m[12]=-(right+left)/(right-left);
	m[13]=-(top+bottom)/(top-bottom);
	m[14]=-(f+n)/(f-n);
}

void CMatrix44::SetTranslationPart(CVector &translation)
{
	m[12]=translation.x;
	m[13]=translation.y;
	m[14]=translation.z;
}

void CMatrix44::SetRotationPartEuler(double angle_x, double angle_y, double angle_z)
{
	double cr = cos( PI*angle_x/180 );
	double sr = sin( PI*angle_x/180 );
	double cp = cos( PI*angle_y/180 );
	double sp = sin( PI*angle_y/180 );
	double cy = cos( PI*angle_z/180 );
	double sy = sin( PI*angle_z/180 );

	m[0] = ( float )( cp*cy );
	m[1] = ( float )( cp*sy );
	m[2] = ( float )( -sp );

	double srsp = sr*sp;
	double crsp = cr*sp;

	m[4] = ( float )( srsp*cy-cr*sy );
	m[5] = ( float )( srsp*sy+cr*cy );
	m[6] = ( float )( sr*cp );

	m[8] = ( float )( crsp*cy+sr*sy );
	m[9] = ( float )( crsp*sy-sr*cy );
	m[10] = ( float )( cr*cp );
}

void CMatrix44::SetRotationPartEuler(CVector &rotations)
{
	SetRotationPartEuler((double)rotations.x, (double)rotations.y, (double)rotations.z);
}




