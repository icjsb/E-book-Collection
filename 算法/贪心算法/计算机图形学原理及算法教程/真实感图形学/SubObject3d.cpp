	
// SubObject3d.cpp: implementation of the CSubObject3d class.

#include "stdafx.h"
#include "SubObject3d.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubObject3d::CSubObject3d() :m_bVisibility(TRUE)
{
	//�������ʼ��ɫ:��ɫ
	m_clr.red = m_clr.green = m_clr.blue = 0.0f; m_clr.alpha = 1.0f;
}

CSubObject3d::~CSubObject3d()
{
}