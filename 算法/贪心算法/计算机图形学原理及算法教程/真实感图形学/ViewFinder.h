// ViewFinder.h: interface for the CViewFinder class.

#ifndef _CVIEWFINDER_H
#define _CVIEWFINDER_H
#include "Grphcs.h"

class CViewFinder  
{
public:
	CViewFinder(VIEWFINDER viewFinder);
	virtual ~CViewFinder();

public:

	//���۲�����ϵ�µĵ�任����Ļ����ϵ,vertex----�۲�����ϵ�µĵ�
	POINT Perspective(VERTEX3D vertex);

	//���۲�����ϵ�µĵ�任����Ļ����ϵ,vertex----�۲�����ϵ�µĵ�
	POINT Perspective(HOMOCOORD vertex);

private:
	//ȡ������
	VIEWFINDER m_viewFinder;
};

#endif 
