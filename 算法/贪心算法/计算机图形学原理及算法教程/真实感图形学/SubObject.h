/////////////////////////////////////////////////////////////////////////////////
//
// SubObject3d.h: interface for the CSubObject3d class.
//
////////////////////////////////////////////////////////////////////////////////
// ��Ȩ����(2002)
// Copyright(2002)
// ��д��: ������
// Author: Xiang Shiming


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
