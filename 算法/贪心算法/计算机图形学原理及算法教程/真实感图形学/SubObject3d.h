// SubObject3d.h: interface for the CSubObject3d class.

#ifndef _CSUBOBJ3D_H
#define _CSUBOBJ3D_H
#include "Grphcs.h"

class CSubObject3d 
{
public:
	CSubObject3d();
	virtual ~CSubObject3d();

public:

	//��������ɫ:������ɫ,RGBA��ɫģ��
	FLOATCOLORRGBA m_clr;

	//����ɼ���
	BOOL m_bVisibility;
	
	//���ڴ�����Ĳ���
	//���鲻�漰�ⲿ������
	//and so on
};

#endif 
