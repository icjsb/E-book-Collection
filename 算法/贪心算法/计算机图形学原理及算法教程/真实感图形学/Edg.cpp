/////////////////////////////////////////////////////////////////////////////////
//	
// Edge.cpp: implementation of the CEdge class.
//
////////////////////////////////////////////////////////////////////////////////
// ��Ȩ����(2002)
// Copyright(2002)
// ��д��: ������
// Author: Xiang Shiming


#include "stdafx.h"
#include "Edge.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CEdge::CEdge() : m_nStart(0),  m_nEnd(0)
{
	m_asIndex.SetSize(0);
}

//���ƹ��캯��
CEdge::CEdge(const CEdge& eSrc)
{
	m_nStart = eSrc.m_nStart;
	m_nEnd = eSrc.m_nEnd;

	m_clr = eSrc.m_clr;
	m_bVisibility = eSrc.m_bVisibility;

	m_asIndex.SetSize(eSrc.m_asIndex.GetSize());
	m_asIndex.Copy(eSrc.m_asIndex);
	m_asIndex.FreeExtra();
}

CEdge::~CEdge()
{
	m_asIndex.RemoveAll();	
}

//��������� "=" 
CEdge CEdge::operator = (const CEdge& eSrc)
{
	m_nStart = eSrc.m_nStart;
	m_nEnd = eSrc.m_nEnd;

	m_clr = eSrc.m_clr;
	m_bVisibility = eSrc.m_bVisibility;

	m_asIndex.SetSize(eSrc.m_asIndex.GetSize());
	m_asIndex.Copy(eSrc.m_asIndex);
	m_asIndex.FreeExtra();

	return *this;
}

//�����
//nStart----������
//nEnd------�յ����
void CEdge::DefineEdge(int nStart,  int nEnd)
{
	m_nStart = nStart;
	m_nEnd = nEnd;
} 

//����ߵ�����(���ߵ���)
//pnInFacet-----�ñ����ڵ�С���������, 
//nNumFacet-----���ñߵ�С�����
void CEdge::DefineTopology(const int* pnInFacet,  int nNumFacet)
{
	ASSERT(nNumFacet >= 0);
	m_asIndex.SetSize(nNumFacet);
	for(int i = 0; i < nNumFacet; i++)
		m_asIndex[i] = pnInFacet[i];
	m_asIndex.FreeExtra();
}