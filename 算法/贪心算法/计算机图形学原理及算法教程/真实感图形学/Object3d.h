/////////////////////////////////////////////////////////////////////////////////
//	
// Object3d.h: interface for the CObject3d class.

//��ά����,�����任����������ϵ

#ifndef _COBJECT3D_H
#define _COBJECT3D_H
#include "Vertex3d.h"
#include "Edge.h"
#include "Facet.h"
#include "Matrix3d.h"
#include "Vector3d.h"

class CObject3d : public CObject 
{
DECLARE_DYNAMIC(CObject3d)
public:
	CObject3d();
	virtual ~CObject3d();
	

public:

	//�����Զ���ɫ����
	void SetAutoColorProperty(BOOL bAutoColor);

	//��ȡ�Զ���ɫ����
	BOOL GetAutoColorProperty() const;

	//��ȡ�����Ĵ�С
	int GetVertexListSize() const;
	//��ȡ�߱��С
	int GetEdgeListSize() const;
	//��ȡ����С
	int GetFacetListSize() const;

	//���ö�����ɫ
	void SetVertexColor(int nIndex, const FLOATCOLORRGBA& rgba);
	void SetVertexColor(int nIndex, const FLOATCOLORRGB& rgb);
	void SetVertexColor(int nIndex, float fRed, float fGreen, float fBlue, float fAlpha = 1.0f);

	//���ñ���ɫ
	void SetEdgeColor(int nIndex, const FLOATCOLORRGBA& rgba);
	void SetEdgeColor(int nIndex, const FLOATCOLORRGB& rgb);
	void SetEdgeColor(int nIndex, float fRed, float fGreen, float fBlue, float fAlpha = 1.0f);
	
	//����С����ɫ
	void SetFacetColor(int nIndex, const FLOATCOLORRGBA& rgba);
	void SetFacetColor(int nIndex, const FLOATCOLORRGB& rgb);
	void SetFacetColor(int nIndex, float fRed, float fGreen, float fBlue, float fAlpha = 1.0f);


	//���α任(��������ϵ,����)
	void Transform(CMatrix3d m);

	//�任����,�����ڸ����˶�
	void TransVertexNormals(CMatrix3d m);
	void TransFacetNormals(CMatrix3d m);


	//��ȡ���λ��
	CMatrix3d GetPosition() const;

	//���ö��㷨��
	void SetVertexNormal(int nIndex, const VECTOR3D& normal);
	void SetVertexNormal(int nIndex, float x, float y, float z);

	//����С�淨��
	void SetFacetNormal(int nIndex, const VECTOR3D& normal);
	void SetFacetNormal(int nIndex, float x, float y, float z);

	//����С�淨��
	VECTOR3D CalcSingleFacetNoraml(const HOMOCOORD& v1, const HOMOCOORD& v2, const HOMOCOORD& v3);
	//������ķ���(�ɶ������)
	void CalcFacetNormals();


	//���㶥���ƽ������(����ķ��߼���)
	void EvenVertexNormals();
	


public:

	//��ҪӦ�ø�������ݵ�����: CPRender��,����������Щ��Ϊ������Ѻ���,Ȼ�����ӱ�����ʩ���ṩ�������ݵĻ���.
	//Ϊ�˷������,���Ǽ򵥵���������Ϊ���г�Ա����

	//�����
	CArray<CVertex3d,CVertex3d> m_vList;

	//�߱�
	CArray<CEdge,CEdge> m_eList;

	//���
	CArray<CFacet,CFacet> m_sList;

protected:

	//�任����
	CMatrix3d m_mGeomTrans;

	BOOL m_bAutoColor;
};

#endif 

