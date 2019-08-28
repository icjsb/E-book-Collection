// Vertex3d.h: interface for the CVertex3d class.
#ifndef _CVERTEX3D_H
#define _CVERTEX3D_H

#ifndef _CSUBOBJ3D_H
#include "SubObject3d.h"
#endif

//has included afxcoll.h in the stdafx.h

class CVertex3d : public CSubObject3d
{
public:
	CVertex3d();
	CVertex3d(const CVertex3d& vSrc);
	virtual ~CVertex3d();

public:
	CVertex3d operator = (const CVertex3d& vSrc);

	//����������(�������)
	void DefineTopology(const int* pnInFacet, int nNumFacet);


public:
	
	//��Ա����,�����Ծ����ⲿ���в���

	//��������:�����������(HOMOCOORD)
	HOMOCOORD m_coord;

	//���㷨��(VECTOR3D)
	VECTOR3D m_normal;


	//��һ, ��ʵ��,����С�����һ�㲻��̫��,�ڵ����ڴ�ϴ�������,
	//      �򵥵ض���һ���㹻��ĳ�������,�Ӷ��ɼ��ٸ߼����ݽṹ��̬������ƶ�������ʱ�俪��(overhead)
	
	//����,�����Խ����ö�̬���ݽṹ,�����Լ����һ��ģ�嶯̬����,���ǽ�ֱ�Ӳ���Visual C++�������ṩ��.

	//����ö����С����������
	CArray<int,int> m_asIndex;
	
};

#endif 
