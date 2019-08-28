/////////////////////////////////////////////////////////////////////////////////
//	
// LightObj.cpp: implementation of the CLightObj class.
#include "stdafx.h"
#include "LightObj.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLightObj::CLightObj()
{
	//ȱʡ��ԴΪһȫ���ɫ���Դ
	m_clrAmb.red  = 0.0f;		m_clrAmb.green = 0.0f;
	m_clrAmb.blue = 0.0f;		m_clrAmb.alpha = 1.0f;

	m_clrDif.red  = 1.0f;		m_clrDif.green = 1.0f;
	m_clrDif.blue = 1.0f;		m_clrDif.alpha = 1.0f;

	m_clrSpe.red  = 1.0f;		m_clrSpe.green = 1.0f;
	m_clrSpe.blue = 1.0f;		m_clrSpe.alpha = 1.0f;
	
	m_hcPosition.x = 0.0f;		m_hcPosition.y = 0.0f;
	m_hcPosition.z = 8.0f;		m_hcPosition.w = 1.0f;

	m_spotDirection.x = 0.0f;	m_spotDirection.y = 0.0f;
	m_spotDirection.z = -1.0f;


	m_fSpotExp = 0.0f;
	m_fSpotCutoff = 180.0f;
	m_fAttCoef0 = 1.0f;
	m_fAttCoef1 = 0.0f;
	m_fAttCoef2 = 0.0f;
	m_bOnOff = TRUE;
}

CLightObj::CLightObj(const CLightObj& light)
{
	m_clrAmb = light.m_clrAmb;
	m_clrDif = light.m_clrDif;
	m_clrSpe = light.m_clrSpe;
	m_hcPosition = light.m_hcPosition;
	m_spotDirection = light.m_spotDirection;

	m_fSpotExp = light.m_fSpotExp;
	m_fSpotCutoff = light.m_fSpotCutoff;
	m_fAttCoef0 = light.m_fAttCoef0;
	m_fAttCoef1 = light.m_fAttCoef1;
	m_fAttCoef2 = light.m_fAttCoef2;
	m_bOnOff = light.m_bOnOff;
}

CLightObj::~CLightObj()
{}

//���ù�Դ�Ƿ���Կ���
//��ʽ��ͳһ, ��һ������ΪG3D_LIGHT_ON_OFF��Ч
void CLightObj::Lightb(DWORD dwProperty,  BOOL bOnOff)
{
	if(dwProperty == G3D_LIGHT_ON_OFF) m_bOnOff = bOnOff;
}

//dwProperty----����
//fParam------����ֵ, ����
void CLightObj::Lightf(DWORD dwProperty,  float fParam)
{
	switch(dwProperty)
	{
		//�۹�ָ��
		case G3D_SPOT_EXPONENT:
			//��ɢָ����[0, 128]֮��
			m_fSpotExp = (fParam < 0.0f) ? 0.0f : ((fParam > 128.0f) ? 128.0f : fParam);
			break;
		//��ɢ���
		case G3D_SPOT_CUTOFF:
			//��ɢ���ȡ [0, 90] �� 180
			if(ABS(fParam - 180.0f) < 0.001f) m_fSpotCutoff = 180.0f;
			else
				m_fSpotCutoff = (fParam < 0.0f) ? 0.0f : ((fParam > 90.0f) ? 90.0f : fParam);
			break;
		//����˥������
		case G3D_CONSTANT_ATTENUATION:
			m_fAttCoef0 = ABS(fParam);
			break;
		//����˥������
		case G3D_LINEAR_ATTENUATION:
			m_fAttCoef1 = ABS(fParam);
			break;

		//����˥������
		case G3D_QUADRATIC_ATTENUATION:
			m_fAttCoef2 = ABS(fParam);
			break;
	}
}

//��������, ����ֵ(һά����)
//dwProperty----����
//pfParams------����ֵ, �� RGBA ˳��� XYZW ˳����֯����

void CLightObj::Lightfv(DWORD dwProperty,  const float* pfParams)
{
	ASSERT(pfParams);
	switch(dwProperty)
	{
		//������
		case G3D_AMBIENT:
			m_clrAmb.red   = pfParams[0];
			m_clrAmb.green = pfParams[1];
			m_clrAmb.blue  = pfParams[2];
			m_clrAmb.alpha = pfParams[3];
			break;
		//�������
		case G3D_DIFFUSE:
			m_clrDif.red   = pfParams[0];
			m_clrDif.green = pfParams[1];
			m_clrDif.blue  = pfParams[2];
			m_clrDif.alpha = pfParams[3];
			break;
		//����߹�
		case G3D_SPECULAR:
			m_clrSpe.red   = pfParams[0];
			m_clrSpe.green = pfParams[1];
			m_clrSpe.blue  = pfParams[2];
			m_clrSpe.alpha = pfParams[3];

			break;
		//���λ��
		case G3D_POSITION:
			m_hcPosition.x = pfParams[0];
			m_hcPosition.y = pfParams[1];
			m_hcPosition.z = pfParams[2];
			m_hcPosition.w = pfParams[3];
			break;

		//�۹����䷽��(���������)
		case G3D_SPOT_DIRECTION:
			
			//ֱ�ӵ�λ��
			float fMag = (float)sqrt(pfParams[0] * pfParams[0] + 
							pfParams[1] * pfParams[1] +
							pfParams[2] * pfParams[2]);
			
			//�����˻�����, �����䷽������ z ��
			if(fMag < 0.0001f)
			{
				m_spotDirection.x = 0.0f;
				m_spotDirection.y = 0.0f;
				m_spotDirection.z = -1.0f;
			}
			else
			{
				m_spotDirection.x = pfParams[0] / fMag;
				m_spotDirection.y = pfParams[1] / fMag;
				m_spotDirection.z = pfParams[2] / fMag;
			}
			break;
	}
}

