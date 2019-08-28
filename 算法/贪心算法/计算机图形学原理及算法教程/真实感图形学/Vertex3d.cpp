
// Vertex3d.cpp: implementation of the CVertex3d class.
#include "stdafx.h"
#include "Vertex3d.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertex3d::CVertex3d()
{
	//��������:����ԭ��
	m_coord.x = m_coord.y = m_coord.z = 0.0f; m_coord.w = 1.0f;

	//���㷨��:ָ��Z��
	m_normal.x = m_normal.y = 0.0f; m_normal.z = 1.0f;

	//һ������, ������һ��������, �������û����������, �Ӷ���ʼ��Ϊ:
	m_asIndex.SetSize(0);
}

//���ƹ��캯��
CVertex3d::CVertex3d(const CVertex3d& vSrc)
{
	m_coord = vSrc.m_coord;
	m_clr = vSrc.m_clr;
	m_normal = vSrc.m_normal;
	m_bVisibility = vSrc.m_bVisibility;

	m_asIndex.SetSize(vSrc.m_asIndex.GetSize());
	m_asIndex.Copy(vSrc.m_asIndex);
	m_asIndex.FreeExtra();
}

CVertex3d::~CVertex3d()
{
	m_asIndex.RemoveAll();	
}


//���� "=" �����
CVertex3d CVertex3d::operator = (const CVertex3d& vSrc)
{
	m_coord = vSrc.m_coord;
	m_clr = vSrc.m_clr;
	m_normal = vSrc.m_normal;
	m_bVisibility = vSrc.m_bVisibility;

	m_asIndex.SetSize(vSrc.m_asIndex.GetSize());
	m_asIndex.Copy(vSrc.m_asIndex);
	m_asIndex.FreeExtra();

	return *this;
}

//����������(�������)
//pnInFacet-----�õ����ڵ�С���������, 
//nNumFacet-----���õ��С�����
void CVertex3d::DefineTopology(const int* pnInFacet,  int nNumFacet)
{
	ASSERT(nNumFacet >= 0);
	m_asIndex.SetSize(nNumFacet);
	for(int i = 0; i < nNumFacet; i++)
		m_asIndex[i] = pnInFacet[i];
	m_asIndex.FreeExtra();
}
