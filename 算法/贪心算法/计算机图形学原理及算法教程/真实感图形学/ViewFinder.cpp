// ViewFinder.cpp: implementation of the CViewFinder class.
#include "stdafx.h"
#include "ViewFinder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewFinder::CViewFinder(VIEWFINDER viewFinder) : m_viewFinder(viewFinder)
{}

CViewFinder::~CViewFinder()
{}

//���۲�����ϵ�µĵ�任����Ļ����ϵ
//��ʵ��, ����任�ʺ����ӵ���Z�����ϵ�����
//vertex----�۲�����ϵ�µĵ�
POINT CViewFinder::Perspective(VERTEX3D vertex)
{
	float xe = vertex.x,  ye = vertex.y,  ze = vertex.z;

	//����ze = 0.0f�����, ����ֻ���򻯴���:
	if(ABS(ze) < 0.00001f) ze = 1.0f;

	//��Ļ�ϵĵ�
	POINT pt;
	pt.x = (int)((xe * m_viewFinder.fDistView) / ze * m_viewFinder.xScale
				+ m_viewFinder.ptCenter.x);
	
	//����ƽ��ֱ������ϵ��Ϊ����ֱ������ϵ
	pt.y = (int)((-ye * m_viewFinder.fDistView) / ze * m_viewFinder.yScale
				+ m_viewFinder.ptCenter.y);

	return pt;
}

//���۲�����ϵ�µĵ�任����Ļ����ϵ
//vertex----�۲�����ϵ�µĵ�
POINT CViewFinder::Perspective(HOMOCOORD vertex)
{
	VERTEX3D v;
	float w = vertex.w;
	//����һ������Զ��
	if(ABS(w) <= 0.00001f)
	{
		v.x = vertex.x;
		v.y = vertex.y;
		v.z = 1000000.0f;
	}
	else
	{
		v.x = vertex.x / w;
		v.y = vertex.y / w;
		v.z = vertex.z / w;
	}
	return (Perspective(v));
}
