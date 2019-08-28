/////////////////////////////////////////////////////////////////////////////////
//	
// Matrix3d.cpp: implementation of the CMatrix3d class.
//

#include "stdafx.h"
#include "Matrix3d.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix3d::CMatrix3d()
{
	Identity();
}

CMatrix3d::~CMatrix3d()
{}

//��λ����
void CMatrix3d::Identity()
{
	a[0][0] = 1.0f;	a[0][1] = 0.0f; a[0][2] = 0.0f;  a[0][3] = 0.0f;
	a[1][0] = 0.0f;	a[1][1] = 1.0f; a[1][2] = 0.0f;  a[1][3] = 0.0f;
	a[2][0] = 0.0f;	a[2][1] = 0.0f; a[2][2] = 1.0f;  a[2][3] = 0.0f;
	a[3][0] = 0.0f;	a[3][1] = 0.0f; a[3][2] = 0.0f;  a[3][3] = 1.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ���������  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//����"="�����(�û�)
CMatrix3d CMatrix3d::operator = (const CMatrix3d& m)
{
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
		a[i][j] = m.a[i][j];
	return *this;
}

//����"=="�����
BOOL CMatrix3d::operator == (const CMatrix3d& m)
{
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
		if(ABS(a[i][j] - m.a[i][j]) > 0.0001f)
			return FALSE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  �������ȡ 
//
//////////////////////////////////////////////////////////////////////////////////////////////

//���ñ任����(�û�)
void CMatrix3d::Set(const float* pfMatrix)
{
	for(int i = 0;i < 4;i++)
	for(int j = 0;j < 4;j++)
		a[i][j] = pfMatrix[ (4 * i + j) ];
}

//��ȡ�任����
void CMatrix3d::Get(float* pfMatrix) const
{
	ASSERT(pfMatrix);
	for(int i = 0;i < 4;i++)
	for(int j = 0;j < 4;j++)
		pfMatrix[ (4 * i + j) ]	 = a[i][j];
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//				  �����ͼ��ѧ�������Ա任
//
//////////////////////////////////////////////////////////////////////////////////////////////

//�������任����

//ƽ�Ʊ任, ƽ����(x, y, z)
void CMatrix3d::Translate(float x, float y,  float z)
{
	a[3][0] += x;
	a[3][1] += y;
	a[3][2] += z;
}

//���ű任
//fsx, fsy, fsz----Ϊ��������
//��Ӧ��ʱ, Ҫ�ر�ע��, ��ֻ�ı����Խ����ϵ�Ԫ��
//���, �����ڵ�һ�α任
void CMatrix3d::Scale(float fs)
{
	a[0][0] *= fs;
	a[1][1] *= fs;
	a[2][2] *= fs;
}

//���ű任
//fsx, fsy, fsz----Ϊ��������
//��Ӧ��ʱ, Ҫ�ر�ע��, ��ֻ�ı����Խ����ϵ�Ԫ��
//���, �����ڵ�һ�α任
void CMatrix3d::Scale(float fsx, float fsy, float fsz)
{
	a[0][0] *= fsx;
	a[1][1] *= fsy;
	a[2][2] *= fsz;
}

//���ű任
//fsx, fsy, fsz----Ϊ��������
//x, y, zΪ���ű任�Ĳο���, ȱʡ����Ϊ��������ϵ������ԭ��
void CMatrix3d::Scale(float fsx, float fsy, float fsz, float x, float y, float z)
{
	CMatrix3d m;
	m.a[0][0] = fsx;
	m.a[1][1] = fsy;
	m.a[2][2] = fsz;
	m.a[3][0] = (1- fsx) * x;
	m.a[3][1] = (1- fsy) * y;
	m.a[3][2] = (1- fsz) * z;
	
	//�����ҳ�
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//�� x ����ת
//fThetaΪ�Ƕȵ�λ, �ο���Ϊ����ԭ��
void CMatrix3d::RotateX(float fTheta)
{
	//���Ƕ�ת��Ϊ����
	float fRad = (float)((fTheta * PIE) / 180.0);
	CMatrix3d m;
	m.a[1][1] = (float)cos(fRad);
	m.a[1][2] = (float)sin(fRad);
	m.a[2][1] = -m.a[1][2];
	m.a[2][2] = m.a[1][1];
	//�����ҳ�
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//�� x ����ת
//fThetaΪ�Ƕȵ�λ, �ο���Ϊ����(x, y, z)
void CMatrix3d::RotateX(float fTheta,  float x,  float y,  float z)
{
	//����˷���������
	this->Translate(-x,  -y,  -z);
	this->RotateX(fTheta);
	this->Translate(x,  y,  z);
}

//�� y ����ת
//fThetaΪ�Ƕȵ�λ, �ο���Ϊ����ԭ��
void CMatrix3d::RotateY(float fTheta)
{
	//���Ƕ�ת��Ϊ����
	float fRad = (float)((fTheta * PIE) / 180.0);
	CMatrix3d m;
	m.a[0][0] = (float)cos(fRad);
	m.a[2][0] = (float)sin(fRad);
	m.a[0][2] = -m.a[2][0];
	m.a[2][2] = m.a[0][0];
	//�����ҳ�
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//�� y ����ת
//fThetaΪ�Ƕȵ�λ, �ο���Ϊ����(x, y, z)
void CMatrix3d::RotateY(float fTheta,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->RotateY(fTheta);
	this->Translate(x,  y,  z);
}

//�� z ����ת
//fThetaΪ�Ƕȵ�λ, �ο���Ϊ����ԭ��
void CMatrix3d::RotateZ(float fTheta)
{
	//���Ƕ�ת��Ϊ����
	float fRad = (float)((fTheta * PIE) / 180.0);
	CMatrix3d m;
	m.a[0][0] = (float)cos(fRad);
	m.a[0][1] = (float)sin(fRad);
	m.a[1][0] = -m.a[0][1];
	m.a[1][1] = m.a[0][0];
	//�����ҳ�
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//�� z ����ת
//fThetaΪ�Ƕȵ�λ, �ο���Ϊ����(x, y, z)
void CMatrix3d::RotateZ(float fTheta,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->RotateZ(fTheta);
	this->Translate(x,  y,  z);
}

//��������(x, y, z)��ת�Ƕ�fTheta, �������ԭ��
void CMatrix3d::Rotate(float fTheta,  float x,  float y,  float z)
{
	//���ᵥλ��
	float fMag = (float)sqrt(x * x + y * y + z * z);
	if(fMag < 0.0001f)
	{
		//��������ԭ��, ����, �ôα任��������ļ���λ�ò���Ӱ��
		return;
	}
	
	//��ת��ķ�����,��λ����
	float fx = (x / fMag),  fy = (y / fMag),  fz = (z / fMag);

	//���Ƕ�ת��Ϊ����
	float fRad = (float)((fTheta * PIE) / 180.0);


	//�Ƕȵ����Һ�����
	float c = (float)cos(fRad);
	float s = (float)sin(fRad);

	//�任����m
	CMatrix3d m;

	//��α任�ĺϳ�,�ο���Ӧ�ļ����ͼ��ѧ�鼮
	m.a[0][0] = fx * fx * (1.0f - c) + c;
	m.a[0][1] = fx * fy * (1.0f - c) - fz * s;
	m.a[0][2] = fx * fz * (1.0f - c) + fy * s;

	m.a[1][0] = fy * fx * (1.0f - c) + fz * s;
	m.a[1][1] = fy * fy * (1.0f - c) + c;
	m.a[1][2] = fy * fz * (1.0f - c) - fx * s;

	m.a[2][0] = fz * fx * (1.0f - c) - fy * s;
	m.a[2][1] = fz * fy * (1.0f - c) + fx * s;
	m.a[2][2] = fz * fz * (1.0f - c) + c;

	
	//��ԭ�б任���кϳ�
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//��ת, ���ɷ���axis�͵�ptOn����
void CMatrix3d::Rotate(float fTheta,  VECTOR3D axis, VERTEX3D ptOn)
{
	this->Translate(-ptOn.x,  -ptOn.y,  -ptOn.z);
	this->Rotate(fTheta,  axis.x,  axis.y,  axis.z);
	this->Translate(ptOn.x,  ptOn.y,  ptOn.z);
}

//��� x �����, ��Ե�Ϊ����ԭ��
//ʹ�ù�ʽ: x1 = x0 , y1 = y0 + a * x0,  z1 = z0 + b * x0
void CMatrix3d::SkewX(float fsy,  float fsz)
{
	CMatrix3d m;
	m.a[0][1] = fsy; m.a[0][2] = fsz;
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//��� x �����, ��Ե�Ϊ(x, y, z)
void CMatrix3d::SkewX(float fsy,  float fsz,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->SkewX(fsy, fsz);
	this->Translate(x,  y,  z);
}

//��� y �����, ��Ե�Ϊ����ԭ��
//ʹ�ù�ʽ: x1 = x0 + a * y0,  y1 = y0,  z1 = z0 + b * y0
void CMatrix3d::SkewY(float fsx,  float fsz)
{
	CMatrix3d m;
	m.a[1][0] = fsx; m.a[1][2] = fsz;
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//��� y �����, ��Ե�Ϊ(x, y, z)
void CMatrix3d::SkewY(float fsx,  float fsz,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->SkewY(fsx, fsz);
	this->Translate(x,  y,  z);
}

//��� z �����, ��Ե�Ϊ����ԭ��
//ʹ�ù�ʽ: x1 = x0 + a * z0,  y1 = y0 + b * z0,  z1 = z0
void CMatrix3d::SkewZ(float fsx,  float fsy)
{
	CMatrix3d m;
	m.a[2][0] = fsx; m.a[2][1] = fsy;
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//��� z �����, ��Ե�Ϊ(x, y, z)
void CMatrix3d::SkewZ(float fsx,  float fsy,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->SkewZ(fsx, fsy);
	this->Translate(x,  y,  z);
}

//��xoyƽ�����ԳƱ任(������任)
void CMatrix3d::ReflexXOY()
{
	a[0][2] = -a[0][2];
	a[1][2] = -a[1][2];
	a[2][2] = -a[2][2];
	a[3][2] = -a[3][2];
}

//��yozƽ�����ԳƱ任(������任)
void CMatrix3d::ReflexYOZ()
{
	a[0][0] = -a[0][0];
	a[1][0] = -a[1][0];
	a[2][0] = -a[2][0];
	a[3][0] = -a[3][0];
}

//��zoxƽ�����ԳƱ任(������任)
void CMatrix3d::ReflexZOX()
{
	a[0][1] = -a[0][1];
	a[1][1] = -a[1][1];
	a[2][1] = -a[2][1];
	a[3][1] = -a[3][1];
}

//�� x �ᷴ��
void CMatrix3d::ReflexX()
{
	//�ڶ���
	a[0][1] = -a[0][1];		a[1][1] = -a[1][1];
	a[2][1] = -a[2][1];		a[3][1] = -a[3][1];

	//������
	a[0][2] = -a[0][2];		a[1][2] = -a[1][2];
	a[2][2] = -a[2][2];		a[3][2] = -a[3][2];
}

//�� y �ᷴ��
void CMatrix3d::ReflexY()
{
	//��һ��
	a[0][0] = -a[0][0];		a[1][0] = -a[1][0];
	a[2][0] = -a[2][0];		a[3][0] = -a[3][0];

	//������
	a[0][2] = -a[0][2];		a[1][2] = -a[1][2];
	a[2][2] = -a[2][2];		a[3][2] = -a[3][2];
}

//�� z �ᷴ��
void CMatrix3d::ReflexZ()
{
	//��һ��
	a[0][0] = -a[0][0];		a[1][0] = -a[1][0];
	a[2][0] = -a[2][0];		a[3][0] = -a[3][0];

	//�ڶ���
	a[0][1] = -a[0][1];		a[1][1] = -a[1][1];
	a[2][1] = -a[2][1];		a[3][1] = -a[3][1];
}

//��ԭ�㷴��
void CMatrix3d::ReflexO()
{
	//��һ��
	a[0][0] = -a[0][0];		a[1][0] = -a[1][0];
	a[2][0] = -a[2][0];		a[3][0] = -a[3][0];

	//�ڶ���
	a[0][1] = -a[0][1];		a[1][1] = -a[1][1];
	a[2][1] = -a[2][1];		a[3][1] = -a[3][1];

	//������
	a[0][2] = -a[0][2];		a[1][2] = -a[1][2];
	a[2][2] = -a[2][2];		a[3][2] = -a[3][2];
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ִ�б任
//
//////////////////////////////////////////////////////////////////////////////////////////////

//ִ�б任, ����Ϊ��ά����:�������
//����ָ��, ����һ�� w = 1.0f ����ʵ����б任ʱ, �����п���ת��Ϊ w != 1.0f �ĵ�.
//��Ӧ�õ�ʱ��, ��һ�����Ҫ���.
//���˵���, ���Ǵ󲿷�ʱ�����ڼ��α任�д���Transform()����, 
//����, ��Щ�������������ʾΪ (z, y, z, 1.0f).
HOMOCOORD CMatrix3d::Transform(float x,  float y,  float z,  float w)
{

	//���ζ���
	HOMOCOORD hc;
	hc.x = x * a[0][0] + y * a[1][0] + z * a[2][0] + w * a[3][0];
	hc.y = x * a[0][1] + y * a[1][1] + z * a[2][1] + w * a[3][1];
	hc.z = x * a[0][2] + y * a[1][2] + z * a[2][2] + w * a[3][2];
	hc.w = x * a[0][3] + y * a[1][3] + z * a[2][3] + w * a[3][3];
	return hc;
}

//ִ�б任, ����Ϊ��ά���� HOMOCOORD
HOMOCOORD CMatrix3d::Transform(HOMOCOORD vertex)
{
	//���ζ���
	HOMOCOORD hc;
	hc.x = vertex.x * a[0][0] + vertex.y * a[1][0] + vertex.z * a[2][0] + vertex.w * a[3][0];
	hc.y = vertex.x * a[0][1] + vertex.y * a[1][1] + vertex.z * a[2][1] + vertex.w * a[3][1];
	hc.z = vertex.x * a[0][2] + vertex.y * a[1][2] + vertex.z * a[2][2] + vertex.w * a[3][2];
	hc.w = vertex.x * a[0][3] + vertex.y * a[1][3] + vertex.z * a[2][3] + vertex.w * a[3][3];
	return hc;
}

//�任����, ��ǰ�����������߷�λ����
VECTOR3D CMatrix3d::Transform(VECTOR3D vector)
{
	//����
	VECTOR3D v;
	v.x = vector.x * a[0][0] + vector.y * a[1][0] + vector.z * a[2][0];
	v.y = vector.x * a[0][1] + vector.y * a[1][1] + vector.z * a[2][1];
	v.z = vector.x * a[0][2] + vector.y * a[1][2] + vector.z * a[2][2];
	return v;
}



//////////////////////////////////////////////////////////////////////////////////////////////
//
//					�������굽�۲�����ı任����
//
//////////////////////////////////////////////////////////////////////////////////////////////

//(x, y, z)Ϊ��������ϵ�¶�����ӵ�
//�۲�����Ϊ����ԭ��,������Ϊ(0,1,0)
void CMatrix3d::Watch(float x,  float y,  float z)
{
	//����ϵ�ı任���̷������岽:
	//��һ, ���û�����ϵƽ�����ӵ�;
	//�ڶ�, ��ƽ�ƺ��������ϵ�� X' ����ת90��;
	//����, �ٽ�������ϵ�� Y' ����ת�Ƕ� theta . sin(theta) = -x / sqrt( x * x + y * y); 
	//����, �ٽ�������ϵ�� X' ����ת�Ƕ� alpha . sin(alpha) = c / mag(a, b, c)
	//����, ����������ϵ��Ϊ��������ϵ, Z �ᷴ��


	//���������ؼ���
	float fv = (float)sqrt(x * x + y * y);
	float fu = (float)sqrt(x * x + y * y + z * z);
	
	//�ӵ��Զ�����ƶ�������λ(����ȱʡ����ϵͳ֮��);
	if(fu < 0.00001)fu = 2.0f;


	//�۲�任�ڼ��α任���֮�����
	//�۲�任����, ����ֱ��д���۲�任�Ľ��, �����ɼ�������
	CMatrix3d mv;

	//����ӵ�λ�� z ����
	if(fv <= 0.00001f)
	{

		//��ʱ, ͶӰƽ��ƽ���� xoy ƽ��, ͶӰ����Ϊ�� z ������ָ����(��������ϵ)
		mv.a[2][2] = -1;
		mv.a[3][2] = fu;

		//����:
		//��������������Ĵν�Ҫ���������ǲ�������
		//�����������(fv > 0.00001f)

		/*
		mv.a[0][0] = -1.0f;   mv.a[0][1] = 0.0;       mv.a[0][2] = -x / fu;
		mv.a[1][0] = 0.0f;    mv.a[1][1] = -1.0f;     mv.a[1][2] = -y / fu;
		mv.a[2][1] = fv / fu; mv.a[2][2] = -z / fu;
		mv.a[3][2] = fu;
		*/
	}
	else
	{
		//����һ������
		mv.a[0][0] = -y / fv; mv.a[0][1] = -(x * z) / (fu * fv); mv.a[0][2] = -x / fu;
		mv.a[1][0] = x / fv;  mv.a[1][1] = -(y * z) / (fu * fv); mv.a[1][2] = -y / fu;
		mv.a[2][1] = fv / fu; mv.a[2][2] = -z / fu;
		mv.a[3][2] = fu;

		//����:
		//����һ������µ�͸�ӱ任, �ñ任���ܻ�����λ�÷����ı�, 
		//����, һ�����ŵ�����, ���ܻᱻ�ŵ�.
	}

	//����:

	//�ڱ�̷�����,���ǲ����˾����ۻ��˷�����.
	//���Ƿ������������������,
	//��ʵ��,Ҳ���Բ���һ���任����,������Լ���ɡ�

	this->Multiply(mv, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ����˷�
//
//////////////////////////////////////////////////////////////////////////////////////////////

//����˷�
void CMatrix3d::Multiply(CMatrix3d m, DWORD dwMultiplier)
{
	//A * B
	CMatrix3d A, B;
	
	if(dwMultiplier == G3D_MATRIX_MULTIPLIER_PRECONCAT)
	{
		A = m;
		B = *this;
	}
	else if(dwMultiplier == G3D_MATRIX_MULTIPLIER_POSTCONCAT)
	{
		A = *this;
		B = m;
	}


	//չ������, ����ѭ��, �Լ��ټӷ��������
	a[0][0] = A.a[0][0] * B.a[0][0] + A.a[0][1] * B.a[1][0] + A.a[0][2] * B.a[2][0] + A.a[0][3] * B.a[3][0];
	a[0][1] = A.a[0][0] * B.a[0][1] + A.a[0][1] * B.a[1][1] + A.a[0][2] * B.a[2][1] + A.a[0][3] * B.a[3][1];
	a[0][2] = A.a[0][0] * B.a[0][2] + A.a[0][1] * B.a[1][2] + A.a[0][2] * B.a[2][2] + A.a[0][3] * B.a[3][2];
	a[0][3] = A.a[0][0] * B.a[0][3] + A.a[0][1] * B.a[1][3] + A.a[0][2] * B.a[2][3] + A.a[0][3] * B.a[3][3];

	a[1][0] = A.a[1][0] * B.a[0][0] + A.a[1][1] * B.a[1][0] + A.a[1][2] * B.a[2][0] + A.a[1][3] * B.a[3][0];
	a[1][1] = A.a[1][0] * B.a[0][1] + A.a[1][1] * B.a[1][1] + A.a[1][2] * B.a[2][1] + A.a[1][3] * B.a[3][1];
	a[1][2] = A.a[1][0] * B.a[0][2] + A.a[1][1] * B.a[1][2] + A.a[1][2] * B.a[2][2] + A.a[1][3] * B.a[3][2];
	a[1][3] = A.a[1][0] * B.a[0][3] + A.a[1][1] * B.a[1][3] + A.a[1][2] * B.a[2][3] + A.a[1][3] * B.a[3][3];

	a[2][0] = A.a[2][0] * B.a[0][0] + A.a[2][1] * B.a[1][0] + A.a[2][2] * B.a[2][0] + A.a[2][3] * B.a[3][0];
	a[2][1] = A.a[2][0] * B.a[0][1] + A.a[2][1] * B.a[1][1] + A.a[2][2] * B.a[2][1] + A.a[2][3] * B.a[3][1];
	a[2][2] = A.a[2][0] * B.a[0][2] + A.a[2][1] * B.a[1][2] + A.a[2][2] * B.a[2][2] + A.a[2][3] * B.a[3][2];
	a[2][3] = A.a[2][0] * B.a[0][3] + A.a[2][1] * B.a[1][3] + A.a[2][2] * B.a[2][3] + A.a[2][3] * B.a[3][3];

	a[3][0] = A.a[3][0] * B.a[0][0] + A.a[3][1] * B.a[1][0] + A.a[3][2] * B.a[2][0] + A.a[3][3] * B.a[3][0];
	a[3][1] = A.a[3][0] * B.a[0][1] + A.a[3][1] * B.a[1][1] + A.a[3][2] * B.a[2][1] + A.a[3][3] * B.a[3][1];
	a[3][2] = A.a[3][0] * B.a[0][2] + A.a[3][1] * B.a[1][2] + A.a[3][2] * B.a[2][2] + A.a[3][3] * B.a[3][2];
	a[3][3] = A.a[3][0] * B.a[0][3] + A.a[3][1] * B.a[1][3] + A.a[3][2] * B.a[2][3] + A.a[3][3] * B.a[3][3];

	/*
	//��ѭ����д
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
	{
		a[i][j] = 0.0f;
		for(int k = 0; k < 4; k++)
			a[i][j] += (A.a[i][k] * B.a[k][j]);
	}
	*/
}


