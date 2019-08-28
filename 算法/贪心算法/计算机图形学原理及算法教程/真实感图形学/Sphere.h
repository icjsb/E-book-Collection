	
// Sphere.h: interface for the CSphere class.

#ifndef _CSPHERE_H
#define _CSPHERE_H

#ifndef _COBJECT3D_H
#include "Object3d.h"
#endif

class CSphere  : public CObject3d
{
DECLARE_DYNAMIC(CSphere)

public:

	//����
	CSphere();

	CSphere(float fRadius, int nSlices, int nStacks);
	CSphere(const CSphere& sphere);
	virtual ~CSphere();

public:
	CSphere* Clone();

private:
	//��ʼ������ļ���,��������ͷ���
	void InitVertices();
	
	//��ʼ��С�漸��
	void InitFacets();

	//��ʼ����
	void InitEdges();

private:

	//��İ뾶
	float m_fRadius;

	//��ľ����������,��ƾ�����, (���������������)
	int m_nSlices;

	//���γ�ȴ�״��������,���γ����, (γ������������ 1)
	int m_nStacks;

};

#endif 
