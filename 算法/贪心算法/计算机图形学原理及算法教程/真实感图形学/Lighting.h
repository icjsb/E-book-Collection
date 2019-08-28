// Lighting.h: interface for the CLighting class.
#ifndef _CLIGHTING_H
#define _CLIGHTING_H

#include "LightObj.h"
#include "Material.h"
#include "Object3d.h"

class CLighting  
{
public:
	CLighting();
	virtual ~CLighting();

public:
	//���ù���ģ��
	void LightModelb(DWORD dwProperty, BOOL bParam);

	//����ȫ�ֻ�����
	void LightModelfv(DWORD dwProperty, const float* pfParams);
public:

	//���Դ����ϵͳ
	void Lighting(CObject3d* pObj, const CMaterial& material, VERTEX3D viewer,const CLightObj* lights, int nNumLight);

public:

	//ȫ�ֻ�����
	FLOATCOLORRGBA m_clrGlobalAmb;

	//��ֲ��ӵ�
	BOOL m_bLocalViewer;

	//�Ƿ�˫�����
	BOOL m_bTwoSides;
};

#endif 
