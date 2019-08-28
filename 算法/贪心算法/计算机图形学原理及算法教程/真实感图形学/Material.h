// Material.h: interface for the CMaterial class.
#ifndef _CMATERIAL_H
#define _CMATERIAL_H
#include "Grphcs.h"

class CMaterial  
{
public:
	CMaterial();
	CMaterial(const CMaterial& material);
	virtual ~CMaterial();

public:

	//���ù�����
	void Materialf(DWORD dwFace, DWORD dwProperty, float fParam);
	void Materialfv(DWORD dwFace, DWORD dwProperty, const float* pfParams);
public:
	//���ʶԻ�����ķ�����(reflectivity)
	FLOATCOLORRGBA m_refAmb;
	//���ʶ��������ķ�����
	FLOATCOLORRGBA m_refDif;
	//���ʶԾ���߹�ķ�����
	FLOATCOLORRGBA m_refSpe;
	//���ʵ���������ɫ(Emission)
	FLOATCOLORRGBA m_clrEmi;
	
	//�������ȣ��߹�ָ����
	float m_fShininess;
	//�������,ǰ��,����,����ǰ������(˫��)
	DWORD m_dwFaceType;

};

#endif 
