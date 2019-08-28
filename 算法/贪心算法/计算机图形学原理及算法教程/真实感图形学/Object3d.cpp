	
// Object3d.cpp: implementation of the CObject3d class.

#include "stdafx.h"
#include "Object3d.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					    ȱʡ����ϵ
//		
//				X----ˮƽ�������� [-1.0, 1.0]
//				Y----��ֱ���¶��� [-1.0, 1.0]
//				Z----ˮƽ�������� [-1.0, 1.0]
//
//////////////////////////////////////////////////////////////////////////////////////////////
//���캯��
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CObject3d, CObject)
CObject3d::CObject3d() : m_bAutoColor(TRUE)
{
	m_vList.SetSize(0);
	m_eList.SetSize(0);
	m_sList.SetSize(0);
	m_mGeomTrans.Identity();
}

CObject3d::~CObject3d()
{
	if(m_vList.GetSize() > 0) m_vList.RemoveAll();
	if(m_eList.GetSize() > 0) m_eList.RemoveAll();
	if(m_sList.GetSize() > 0) m_sList.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//			  ��ȡ���ζ�����߱����Ĵ�С
//
//////////////////////////////////////////////////////////////////////////////////////////////

//��ȡ�����Ĵ�С
int CObject3d::GetVertexListSize() const
{
	return m_vList.GetSize();
}

//��ȡ�߱��С
int CObject3d::GetEdgeListSize() const
{
	return m_eList.GetSize();
}

//��ȡ����С
int CObject3d::GetFacetListSize() const
{
	return m_sList.GetSize();
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ���úͻ�ȡ�Զ���ɫ����
//
//////////////////////////////////////////////////////////////////////////////////////////////


//���úͻ�ȡ�Զ���ɫ����
//������ֻӰ��ƽ��������ɫģʽ�µĿ���ģ�ͻ��ƺ��߿�ģ�ͻ���
void CObject3d::SetAutoColorProperty(BOOL bAutoColor)
{
	m_bAutoColor = bAutoColor;
}
	
//��ȡ�Զ���ɫ����
BOOL CObject3d::GetAutoColorProperty() const
{
	return m_bAutoColor;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ���ö��㡢�ߡ�С����ɫ  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//���ö�����ɫ
//nIndex----�����
//rgba------��ɫ
void CObject3d::SetVertexColor(int nIndex,  const FLOATCOLORRGBA& rgba)
{
	m_vList[nIndex].m_clr = rgba;
}

//���ö�����ɫ
//nIndex----�����
//rgba------��ɫ
void CObject3d::SetVertexColor(int nIndex,  const FLOATCOLORRGB& rgb)
{
	m_vList[nIndex].m_clr.red = rgb.red;
	m_vList[nIndex].m_clr.green = rgb.green;
	m_vList[nIndex].m_clr.blue = rgb.blue;
	m_vList[nIndex].m_clr.alpha = 1.0f;	
}

//���ö�����ɫ
//nIndex----�����
//(fRed, fGreen, fBlue, fAlpha)----��ɫ
void CObject3d::SetVertexColor(int nIndex,  float fRed,  float fGreen,  float fBlue,  float fAlpha)
{
	m_vList[nIndex].m_clr.red = fRed;
	m_vList[nIndex].m_clr.green = fGreen;
	m_vList[nIndex].m_clr.blue = fBlue;
	m_vList[nIndex].m_clr.alpha = fAlpha;
}


//���ñ���ɫ
//nIndex----�ߺ�
//rgba------��ɫ
void CObject3d::SetEdgeColor(int nIndex,  const FLOATCOLORRGBA& rgba)
{
	m_eList[nIndex].m_clr = rgba;
}

//���ñ���ɫ
//nIndex----�ߺ�
//rgba------��ɫ
void CObject3d::SetEdgeColor(int nIndex,  const FLOATCOLORRGB& rgb)
{
	m_eList[nIndex].m_clr.red = rgb.red;
	m_eList[nIndex].m_clr.green = rgb.green;
	m_eList[nIndex].m_clr.blue = rgb.blue;
	m_eList[nIndex].m_clr.alpha = 1.0f;	
}

//���ñ���ɫ
//nIndex----�ߺ�
//(fRed, fGreen, fBlue, fAlpha)----��ɫ
void CObject3d::SetEdgeColor(int nIndex,  float fRed,  float fGreen,  float fBlue,  float fAlpha)
{
	m_eList[nIndex].m_clr.red = fRed;
	m_eList[nIndex].m_clr.green = fGreen;
	m_eList[nIndex].m_clr.blue = fBlue;
	m_eList[nIndex].m_clr.alpha = fAlpha;
}

//����С����ɫ
//nIndex----���
//rgba------��ɫ
void CObject3d::SetFacetColor(int nIndex,  const FLOATCOLORRGBA& rgba)
{
	m_sList[nIndex].m_clr = rgba;
}

//����С����ɫ
//nIndex----С���
//rgba------��ɫ
void CObject3d::SetFacetColor(int nIndex,  const FLOATCOLORRGB& rgb)
{
	m_sList[nIndex].m_clr.red = rgb.red;
	m_sList[nIndex].m_clr.green = rgb.green;
	m_sList[nIndex].m_clr.blue = rgb.blue;
	m_sList[nIndex].m_clr.alpha = 1.0f;	
}


//����С����ɫ
//nIndex----С���
//(fRed, fGreen, fBlue, fAlpha)----��ɫ
void CObject3d::SetFacetColor(int nIndex,  float fRed,  float fGreen,  float fBlue,  float fAlpha)
{
	m_sList[nIndex].m_clr.red = fRed;
	m_sList[nIndex].m_clr.green = fGreen;
	m_sList[nIndex].m_clr.blue = fBlue;
	m_sList[nIndex].m_clr.alpha = fAlpha;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ���ö��㡢С�淨��
//
//////////////////////////////////////////////////////////////////////////////////////////////

//���ö��㷨��
//nIndex------������
//normal------����
void CObject3d::SetVertexNormal(int nIndex,  const VECTOR3D& normal)
{
	m_vList[nIndex].m_normal = normal;
}

//���ö��㷨��
//nIndex------������
//normal------����
void CObject3d::SetVertexNormal(int nIndex,  float x,  float y,  float z)
{
	m_vList[nIndex].m_normal.x = x;
	m_vList[nIndex].m_normal.y = y;
	m_vList[nIndex].m_normal.z = z;
}

//����С�淨��
//nIndex------������
//normal------����
void CObject3d::SetFacetNormal(int nIndex,  const VECTOR3D& normal)
{
	m_sList[nIndex].m_normal = normal;
}

//����С�淨��
//nIndex------������
//normal------����
void CObject3d::SetFacetNormal(int nIndex,  float x,  float y,  float z)
{
	m_sList[nIndex].m_normal.x = x;
	m_sList[nIndex].m_normal.y = y;
	m_sList[nIndex].m_normal.z = z;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ���㶥�㡢С�淨��
//
//////////////////////////////////////////////////////////////////////////////////////////////

//����С�淨��
VECTOR3D CObject3d::CalcSingleFacetNoraml(const HOMOCOORD& v1,  const HOMOCOORD& v2,  const HOMOCOORD& v3)
{
	//���һ���������а�������Զ��, �����������һ������������, 
	float w1 = v1.w,  w2 = v2.w,  w3 = v3.w;
	if(ABS(w1) <= 0.00001f) w1 = 1.0f;
	if(ABS(w2) <= 0.00001f) w2 = 1.0f;
	if(ABS(w3) <= 0.00001f) w3 = 1.0f;

	float x1 = v1.x / w1,  y1 = v1.y / w1,  z1 = v1.z / w1;
	float x2 = v2.x / w2,  y2 = v2.y / w2,  z2 = v2.z / w2;
	float x3 = v3.x / w3,  y3 = v3.y / w3,  z3 = v3.z / w3;

	CVector3d vector1((x2 - x1),  (y2 - y1),  (z2 - z1)); 
	CVector3d vector2((x3 - x1),  (y3 - y1),  (z3 - z1)); 
	CVector3d noraml = vector1 * vector2;
	VECTOR3D n = {noraml.x,  noraml.y,  noraml.z};
	return n;
}

//������ķ���(�ɶ������)
void CObject3d::CalcFacetNormals()
{
	//��ȡС�����
	int nNumFacet = m_sList.GetSize();

	//��ѭ��
	for(int i = 0; i < nNumFacet; i++)
	{
		//һ��������Ӧ����������			
		ASSERT(m_sList[i].m_avIndex.GetSize() > 2);
		
		//��ȡ����������
		int n1 = m_sList[i].m_avIndex[0];
		int n2 = m_sList[i].m_avIndex[1];
		int n3 = m_sList[i].m_avIndex[2];
		m_sList[i].m_normal = this->CalcSingleFacetNoraml(m_vList[n1].m_coord,  m_vList[n2].m_coord,  m_vList[n3].m_coord);
	}
}

//���㶥���ƽ������(��ķ��߼���)
//�����ƽ������Ϊ��ö�����������ķ��ߵ�ƽ��ֵ
void CObject3d::EvenVertexNormals()
{
	//��ȡ�������
	int nNumVertex = m_vList.GetSize();
	
	//����ѭ��
	for(int i = 0; i < nNumVertex; i++)
	{
		//��ȡ��ǰ��������С������
		int nNumInFacet = m_vList[i].m_asIndex.GetSize();
		if(nNumInFacet > 0)
		{
			//С�淨��
			CVector3d nv(0.0f, 0.0f, 0.0f);
			for(int j = 0; j < nNumInFacet; j++)
			{
				//С���
				int n = m_vList[i].m_asIndex[j];
				
				//�������
				nv += m_sList[n].m_normal;
			}// end for j
			
			//����������
			nv.Unitize();
			
			//��ֵ(���г�Ա)
			m_vList[i].m_normal.x = nv.x;
			m_vList[i].m_normal.y = nv.y;
			m_vList[i].m_normal.z = nv.z;

		}//end if

	}//end  for i
}	


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  ���α任  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//�任(�ۻ��任)
void CObject3d::Transform(CMatrix3d m)
{
	//��ȡ�������
	int nNumVertex = m_vList.GetSize();
	for(int i = 0; i < nNumVertex; i++)
		m_vList[i].m_coord = m.Transform(m_vList[i].m_coord);

	//�� m �ۻ��� m_mGeomTrans ,  �Ӷ���¼���ϱ任�Ľ��
	m_mGeomTrans.Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//�任����, mΪ�Ѿ��ı任����, �����ڸ����˶�
void CObject3d::TransVertexNormals(CMatrix3d m)
{
	//��ȡ�������
	int nNumVertex = m_vList.GetSize();
	for(int i = 0; i < nNumVertex; i++)
		m_vList[i].m_normal = m.Transform(m_vList[i].m_normal);
}

//�任����, mΪ�Ѿ��ı任����, �����ڸ����˶�
void CObject3d::TransFacetNormals(CMatrix3d m)
{
	//��ȡС�����
	int nNumFacet = m_sList.GetSize();
	for(int i = 0; i < nNumFacet; i++)
		m_sList[i].m_normal = m.Transform(m_sList[i].m_normal);
}


//��ȡλ��
CMatrix3d  CObject3d::GetPosition() const 
{
	return m_mGeomTrans;
}




//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  �����༭������߱����Ĳ������ԣ�  
//
//////////////////////////////////////////////////////////////////////////////////////////////
