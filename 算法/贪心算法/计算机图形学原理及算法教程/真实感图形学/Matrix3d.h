// Matrix3d.h: interface for the CMatrix3d class.

//��ά�任����(���α任�͹۲�任)

#ifndef _CMATRIX3D_H
#define _CMATRIX3D_H
#include "Grphcs.h"

class CMatrix3d  
{
public:
	CMatrix3d();
	virtual ~CMatrix3d();

public:
	CMatrix3d operator = (const CMatrix3d& m);
	BOOL operator == (const CMatrix3d& m);

public:
	//��ȡ������
	void Set(const float* pfMatrix);
	void Get(float* pfMatrix) const;

	//��λ��
	void Identity();

	//ƽ��
	void Translate(float x,float y, float z);

	//���ű任
	//���Ųο���Ϊԭ��
	void Scale(float fs);
	void Scale(float fsx,float fsy,float fsz);
	//���Ųο���Ϊ(x,y,z)
	void Scale(float fsx,float fsy,float fsz,float x,float y,float z);

	//�� x ����ת
	void RotateX(float fTheta);
	void RotateX(float fTheta, float x, float y, float z);

	//�� y ����ת
	void RotateY(float fTheta);
	void RotateY(float fTheta, float x, float y, float z);

	//�� z ����ת
	void RotateZ(float fTheta);
	void RotateZ(float fTheta, float x, float y, float z);

	//�������ԭ�����(x,y,z)��ת(���ԭ��)
	void Rotate(float fTheta, float x, float y, float z);
	
	//��ָ��������ת
	void Rotate(float fTheta, VECTOR3D axis,VERTEX3D ptOn);

	//��� x �����
	void SkewX(float fsy, float fsz);
	void SkewX(float fsy, float fsz, float x, float y, float z);

	//��� y �����
	void SkewY(float fsx, float fsz);
	void SkewY(float fsx, float fsz, float x, float y, float z);

	//��� z �����
	void SkewZ(float fsx, float fsy);
	void SkewZ(float fsx, float fsy, float x, float y, float z);

	//������ƽ�����ԳƱ任(������任)
	void ReflexXOY();
	void ReflexYOZ();
	void ReflexZOX();

	//�������������ԭ�㷴��
	void ReflexX();
	void ReflexY();
	void ReflexZ();
	void ReflexO();

	//ִ�б任(����)
	HOMOCOORD	Transform(float x, float y, float z, float w = 1.0f);
	HOMOCOORD	Transform(HOMOCOORD vertex);
	
	//�任����,��ǰ�����������߷�λ����
	VECTOR3D Transform(VECTOR3D vector);


	//�������굽�۲�����ı任����
	void Watch(float x, float y, float z);

	//����˷�
	void Multiply(CMatrix3d m,DWORD dwMultiplier);
	
public:
	
	//����ϵ��(4��4��)
	//Ϊ�˷���ϰ��,���ǲ�����������������
	float a[4][4];
	//��������:
	//
	//		a00,  a01,  a02,  a03
	//		a10,  a11,  a12,  a13
	//		a20,  a21,  a22,  a23
	//		a30,  a31,  a32,  a33
	
	//�任��ʽ:
	//��PΪ�任ǰ�ĵ�,P1Ϊ�任��ĵ�,AΪ�任����,��
	//    
	//		P1 = P * A
	
};

#endif 
