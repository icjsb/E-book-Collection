// Facet.h: interface for the CFacet class.
#ifndef _CFACET_H
#define _CFACET_H

#ifndef _CSUBOBJ3D_H
#include "SubObject3d.h"
#endif

//has included afxcoll.h in the stdafx.h

class CFacet : public CSubObject3d
{
public:
	CFacet();
	CFacet(const CFacet& fctSrc);
	virtual ~CFacet();

public:
	CFacet operator = (const CFacet& fctSrc);

	//����С�������(�����)
	void DefineTopology(const int* pnVertex, int nNumVertex);

public:
	
	//С�淨��:
	VECTOR3D m_normal;

	//��ͼ�δ�����,С��һ��Ϊ�����λ��ı���

	//С�涥�����
	CArray<int,int> m_avIndex;

};

#endif
