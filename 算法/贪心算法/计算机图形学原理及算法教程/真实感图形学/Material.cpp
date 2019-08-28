/////////////////////////////////////////////////////////////////////////////////
//	
// Material.cpp: implementation of the CMaterial class.
#include "stdafx.h"
#include "Material.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMaterial::CMaterial()
{
	//ȱʡ����
	m_refAmb.red  = 0.2f;		m_refAmb.green = 0.2f;
	m_refAmb.blue = 0.2f;		m_refAmb.alpha = 1.0f;

	m_refDif.red  = 0.8f;		m_refDif.green = 0.8f;
	m_refDif.blue = 0.8f;		m_refDif.alpha = 1.0f;

	m_refSpe.red  = 0.0f;		m_refSpe.green = 0.0f;
	m_refSpe.blue = 0.0f;		m_refSpe.alpha = 1.0f;

	m_clrEmi.red =  0.0f;		m_clrEmi.green = 0.0f;
	m_clrEmi.blue = 0.0f;		m_clrEmi.alpha = 1.0f;

	m_fShininess = 128.0f;
	m_dwFaceType = G3D_FRONT;
}

CMaterial::CMaterial(const CMaterial& material)
{
	m_refAmb = material.m_refAmb;
	m_refDif = material.m_refDif;
	m_refSpe = material.m_refSpe;
	m_clrEmi = material.m_clrEmi;
	m_fShininess = material.m_fShininess;
	m_dwFaceType = material.m_dwFaceType;
}

CMaterial::~CMaterial()
{

}

//���ù�����
//dwFace-------������, ȡö��ֵ
//dwProperty---����, ȡ G3D_SHININESS Ϊ��Ч
//fParam-------�������ֵ
void CMaterial::Materialf(DWORD dwFace,  DWORD dwProperty,  float fParam)
{
	if(dwProperty == G3D_SHININESS)
	{
		m_dwFaceType = dwFace;
		m_fShininess = (fParam < 0.0f) ? 0.0f : ((fParam > 128.0f) ? 128.0f : fParam);
	}
}

//������������
//dwFace-------������, ȡö��ֵ
//dwProperty---����, 
//pfParams-----�������ֵ
void CMaterial::Materialfv(DWORD dwFace,  DWORD dwProperty,  const float* pfParams)
{
	ASSERT(pfParams);
	m_dwFaceType = dwFace;
	switch(dwProperty)
	{
		//�����ⷴ��ϵ��
		case G3D_AMBIENT:
			m_refAmb.red   = pfParams[0];
			m_refAmb.green = pfParams[1];
			m_refAmb.blue  = pfParams[2];
			m_refAmb.alpha = pfParams[3];
			break;
		//������ⷴ��ϵ��
		case G3D_DIFFUSE:
			m_refDif.red   = pfParams[0];
			m_refDif.green = pfParams[1];
			m_refDif.blue  = pfParams[2];
			m_refDif.alpha = pfParams[3];
			break;
		//����߹ⷴ��ϵ��
		case G3D_SPECULAR:
			m_refSpe.red   = pfParams[0];
			m_refSpe.green = pfParams[1];
			m_refSpe.blue  = pfParams[2];
			m_refSpe.alpha = pfParams[3];
			break;

		//������������ϵ����ͬ
		case G3D_AMBIENT_AND_DIFFUSE:
			m_refAmb.red   = pfParams[0];
			m_refAmb.green = pfParams[1];
			m_refAmb.blue  = pfParams[2];
			m_refAmb.alpha = pfParams[3];

			m_refDif.red   = pfParams[0];
			m_refDif.green = pfParams[1];
			m_refDif.blue  = pfParams[2];
			m_refDif.alpha = pfParams[3];
			break;
		//��������ɫ
		case G3D_EMISSION:	
			m_clrEmi.red   = pfParams[0];
			m_clrEmi.green = pfParams[1];
			m_clrEmi.blue  = pfParams[2];
			m_clrEmi.alpha = pfParams[3];
			break;
	}
}
