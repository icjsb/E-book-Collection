// Edge.h: interface for the CEdge class.
#ifndef _CEDGE_H
#define _CEDGE_H

#ifndef _CSUBOBJ3D_H
#include "SubObject3d.h"
#endif

//has included afxcoll.h in the stdafx.h

class CEdge  : public CSubObject3d
{
public:
	CEdge();
	CEdge(const CEdge& eSrc);
	virtual ~CEdge();

public:
	
	//���� " = " �����
	CEdge operator = (const CEdge& eSrc);

	//�����
	void DefineEdge(int nStart, int nEnd);
	
	//��������(���ߵ���)
	void DefineTopology(const int* pnInFacet, int nNumFacet); 

public:

	//�ߵ���������ź��յ�������
	int m_nStart, m_nEnd;
	
	//����ñߵ�С����������
	CArray<int,int> m_asIndex;

};

#endif 
