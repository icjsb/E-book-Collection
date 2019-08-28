// LightObj.h: interface for the CLightObj class.
#ifndef _CLIGHTOBJ_H
#define _CLIGHTOBJ_H
#include "Grphcs.h"

class CLightObj  
{
public:
	CLightObj();
	CLightObj(const CLightObj& light);
	virtual ~CLightObj();

public:
	//���Ƿ�Ϊ����״̬
	void Lightb(DWORD dwProperty, BOOL bOnOff);
	//���ñ�������
	void Lightf(DWORD dwProperty, float fParam);
	//������������
	void Lightfv(DWORD dwProperty, const float* pfParams);

public:

	//��Ļ�����ɫ
	FLOATCOLORRGBA m_clrAmb;
	//�����������ɫ
	FLOATCOLORRGBA m_clrDif;
	//��ľ���߹���ɫ
	FLOATCOLORRGBA m_clrSpe;

	//��Դλ��
	HOMOCOORD m_hcPosition;
	
	//�۹����䷽��: 
	VECTOR3D  m_spotDirection;
	
	//�۹�ָ��
	float m_fSpotExp;

	//�۹ⷢɢ���
	float m_fSpotCutoff;
	
	//����˥��ϵ��
	float m_fAttCoef0;
	//����˥��ϵ��
	float m_fAttCoef1;
	//����˥��ϵ��
	float m_fAttCoef2;

	//���Ƿ���
	BOOL m_bOnOff;

};

#endif 
