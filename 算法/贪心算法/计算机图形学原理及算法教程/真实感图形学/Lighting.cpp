/////////////////////////////////////////////////////////////////////////////////
//	
// Lighting.cpp: implementation of the CLighting class.
#include "stdafx.h"
#include "Lighting.h"

//#include "FloatColor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLighting::CLighting()
{
	m_clrGlobalAmb.red  = 0.2f;		m_clrGlobalAmb.green = 0.2f;
	m_clrGlobalAmb.blue = 0.2f;		m_clrGlobalAmb.alpha = 1.0f;
	
	//ȱʡֵ: ����Զ�ӵ�ģ��
	m_bLocalViewer = FALSE;

	//ȱʡֵ:ֻ����ǰ��
	m_bTwoSides = FALSE;
}

CLighting::~CLighting()
{
}

//���ù���ģ��
void CLighting::LightModelb(DWORD dwProperty,  BOOL bParam)
{
	if(dwProperty == G3D_LIGHT_MODEL_LOCAL_VIEWER)
		m_bLocalViewer = bParam;
	else if(dwProperty == G3D_LIGHT_MODEL_TWO_SIDE)
		m_bTwoSides = bParam;
}

//����ȫ�ֻ�����
void CLighting::LightModelfv(DWORD dwProperty,  const float* pfParams)
{
	if(dwProperty == G3D_LIGHT_MODEL_AMBIENT)
	{
		m_clrGlobalAmb.red   = pfParams[0];
		m_clrGlobalAmb.green = pfParams[1];
		m_clrGlobalAmb.blue  = pfParams[2];
		m_clrGlobalAmb.alpha = pfParams[3];
	}
}

//���ռ���
//pObj---------�����յ�����    (��������)
//material-----�����׼����
//viewer-------�ӵ�, ���ڹ��ռ���, ����������������ϵ
//lights-------���Դ
//nNumLight----��Դ����
void CLighting::Lighting(CObject3d* pObj,  const CMaterial& material,  VERTEX3D viewer,  const CLightObj* lights,  int nNumLight)
{
	//ע:   �ù��ռ�������������ϵ�����

	ASSERT(pObj);
	ASSERT(lights);

	//��ʽ��ʾ�ӵ�, ������������������ϵ
	float xViewer = viewer.x,   yViewer = viewer.y,   zViewer = viewer.z;

	//����һ������Զ�ӵ�۲�����, 
	//
	CVector3d vLocalView(xViewer,  yViewer,  zViewer);

	//�������߹�ʱ��������Զ�ӵ�, �����ھ͵�λ��, �⽫���ٴ����ļ���
	
	if(!m_bLocalViewer)
		vLocalView.Unitize();

	
	//���嶥�����
	int nNumVertex = pObj->GetVertexListSize();

	//��ʼ����
	// i �����嶥���������ѭ��,  j �򰴹�Դ��������ѭ��
	for(int i = 0; i < nNumVertex; i++)
	{
		
		//��ȡ����ĵ� i ������:
		float xVertex = pObj->m_vList[i].m_coord.x;
		float yVertex = pObj->m_vList[i].m_coord.y;
		float zVertex = pObj->m_vList[i].m_coord.z;
		float wVertex = pObj->m_vList[i].m_coord.w;

		//���������ת��Ϊ��ʵ����
		//����Զ��, ���Ƶ��� 0.0001 ������(�����������10000���ĵ�����������Զ�����ɫ)
		//���ؿ��� wVertex ������ 0 ʱ�ķ���
		if(ABS(wVertex) < 0.0001f)wVertex = 0.0001f;
		
		xVertex /= wVertex;
		yVertex /= wVertex;
		zVertex /= wVertex;

		//����������ɫ
		//��һ��, ���������ɫ, ����ֱ�ӹ�����
		float fLastR = material.m_clrEmi.red;
		float fLastG = material.m_clrEmi.green;
		float fLastB = material.m_clrEmi.blue;
		
		//ȫ�ֻ�����Ĺ���
		//ȫ�ֻ����� * ���ʶԻ�����ķ���ϵ�� ----- 
		//������Ӧ��˺�, �ۻ���������ɫ֮��.
		fLastR += (m_clrGlobalAmb.red * material.m_refAmb.red);
		fLastG += (m_clrGlobalAmb.green * material.m_refAmb.green);
		fLastB += (m_clrGlobalAmb.blue * material.m_refAmb.blue);

		//�����ڹ�Դ�Ĺ���
		float fr,  fg,  fb;

		for(int j = 0; j < nNumLight; j++)
		{
			//�����Դ�ǿ�����
			if(lights[j].m_bOnOff)
			{
				//��һ, ����˥��ϵ��

				//˥��ϵ��.����1.0��˥��
				float fAttenuCoef = 1.0f;
				
				//��ȡ�� j ����Դλ��
				float xLight = lights[j].m_hcPosition.x;
				float yLight = lights[j].m_hcPosition.y;
				float zLight = lights[j].m_hcPosition.z;
				float wLight = lights[j].m_hcPosition.w;


				//ֻ�е��Դ���ǲ���Ϊ���ǿ�˥����, ��ʱ, w = 1.0f.
				//�����Դ��ƽ�й�Դ, �������Դ, ��˥��, ʱʱ, w = 0.0f

				//��λ��Դ
				if(ABS(wLight) > 0.0001f)
				{
					//��ʵλ��, ������������������
					xLight /= wLight;
					yLight /= wLight;
					zLight /= wLight;
					
					//����˥��ϵ��
					fAttenuCoef = lights[j].m_fAttCoef0;
					
					//һ��˥��ϵ�������˥��ϵ��
					float fc1 = lights[j].m_fAttCoef1;
					float fc2 = lights[j].m_fAttCoef2;
					if((fc1 > 0.0001f) || (fc2 > 0.0001f))
					{
						//�󶥵�����Դ�ľ���
						float fDist = (float)sqrt((xLight - xVertex) * (xLight - xVertex) +
										   (yLight - yVertex) * (yLight - yVertex) +
										   (zLight - zVertex) * (zLight - zVertex) );
					
						//����һ�κͶ�������
						fAttenuCoef += (fc1 * fDist + fc2 * fDist * fDist);
					}
					
					if(fAttenuCoef < 0.0001f) fAttenuCoef = 0.0001f;
					fAttenuCoef = 1.0f / fAttenuCoef;

					//˥��ϵ�����ô���1.0
					fAttenuCoef = MIN(1.0f,  fAttenuCoef);
				
				}
				
				//����۹�����

				//�۹�����, һ����Դ�ľ۹�����Ϊ 1.0f, (��ɢ���Ϊ180��)
				float fSpotFactor = 1.0f;
				
				//��ɢ���
				float fCutoff = lights[j].m_fSpotCutoff;

				//�۹����������:��һ, ��Ϊ��λ��Դ; �ڶ�, ��ķ�ɢ���С�ڻ����90��
				if((ABS(wLight) > 0.0001f) && (fCutoff < 90.0001f))
				{
					//��Դ����ʵλ���Ѿ�Ϊ(xLight,  yLight,  zLight), 
					//�����Դ�������۹�Ч��
					
					//����: �۹�λ��ָ�����䶥��
					CVector3d vLightToVertex((xVertex - xLight),  (yVertex - yLight),  (zVertex - zLight));
					
					//��λ��
					vLightToVertex.Unitize();

					//�۹����䷽��(�Ѿ���һ����λ����) �� ���� vLightToVertex �нǵ�����
					float fInsideCone = vLightToVertex.Dot(lights[j].m_spotDirection);

					//�������λ�ڹ�׶֮��, �򲻻��о۹�������䵽������
					if(fInsideCone < (float)cos((fCutoff * PIE) / 180.0))
						fSpotFactor = 0.0f;
					else
					{
						//���þ۹�ָ�����м���
						fSpotFactor = (float)pow(fInsideCone,  lights[j].m_fSpotExp);
					}
				
				}//enf if ---- for calculating spot factor
				

				// �������Թ�Դ�Ĺ���(�����Ѿ����㹻��������)
				
				//���뻷�����䲿��:
				fr = material.m_refAmb.red * lights[j].m_clrAmb.red;
				fg = material.m_refAmb.green * lights[j].m_clrAmb.green;
				fb = material.m_refAmb.blue * lights[j].m_clrAmb.blue;

				//���, ���������䲿��
				
				//����ָ���Դ������
				CVector3d vVertexToLight((xLight - xVertex),  (yLight - yVertex),  (zLight - zVertex)); 
				
				//�����ԴΪƽ�й�Դ(��λ��Դ)
				if((ABS(wLight) <= 0.0001f))
				{
					//��Դ��λ�þ������䷽��, �����������Դ���������ǹ�Դλ���������෴����
					vVertexToLight.x = -xLight;
					vVertexToLight.y = -yLight;
					vVertexToLight.z = -zLight;
				}
				
				//��λ��
				vVertexToLight.Unitize();

				//���㷨�������� vVertexToLight �����ļнǵ�����
				//���㷨��Ӧ�ǵ�λ����, ���ڽ�ģʱ�Ѿ�����뱣֤��
				float fCos = vVertexToLight.Dot(pObj->m_vList[i].m_normal);
				
				fCos = (fCos < 0.0f) ? 0.0f : fCos;

				//���������䲿�ֵĹ���
				fr += (material.m_refDif.red * lights[j].m_clrDif.red * fCos);
				fg += (material.m_refDif.green * lights[j].m_clrDif.green * fCos);
				fb += (material.m_refDif.blue * lights[j].m_clrDif.blue * fCos);

				// ����߹ⲿ��

				//������㷨���붥������Դ�������нǴ���90��, ��û�и߹����
				//����Ͳ���
				if(fCos > 0.0f)
				{
					//���㶥��ָ���ӵ�ĵ�λ����:
					CVector3d vVertexToViewer;
					
					//����Զ�ӵ�ģ��
					if(!m_bLocalViewer)
					{
						vVertexToViewer = vLocalView;
					}
					//�ֲ��ӵ�ģ��
					else
					{
						vVertexToViewer.x = (xViewer - xVertex);
						vVertexToViewer.y = (yViewer - yVertex);
						vVertexToViewer.z = (zViewer - zVertex);
						//��λ��:
						vVertexToViewer.Unitize();
					}
					
					//���϶���ָ���Դ�ĵ�λ����:
					vVertexToViewer += vVertexToLight;
					
					//�ٴε�λ��:
					vVertexToViewer.Unitize();

					//������ӻ���:�붥�㷨�������
					float fShine = vVertexToViewer.Dot(pObj->m_vList[i].m_normal);
					fShine = (fShine < 0.0f) ? 0.0f : fShine;
					float fShineFactor = (float)pow(fShine,  material.m_fShininess);
					
					//����߹ⲿ�ֵĹ���
					fr += (material.m_refSpe.red * lights[j].m_clrSpe.red * fShineFactor);
					fg += (material.m_refSpe.green * lights[j].m_clrSpe.green * fShineFactor);
					fb += (material.m_refSpe.blue * lights[j].m_clrSpe.blue * fShineFactor);
				}// end if(fCos > 0.0f)
				
				//������˥���;۹����ӣ��� j ���������ĵڸ����������:
				fr *= (fAttenuCoef * fSpotFactor);
				fg *= (fAttenuCoef * fSpotFactor);
				fb *= (fAttenuCoef * fSpotFactor);

				//�ۼ��������ɫ:
				fLastR += fr;
				fLastG += fg;
				fLastB += fb;
			}// end if(lights[0].m_bOnOff)
		}//end j (number of lights)
		
		//����ɫ��һ������:
		fLastR = (fLastR < 0.0f) ? 0.0f : ((fLastR > 1.0f) ? 1.0f : fLastR);
		fLastG = (fLastG < 0.0f) ? 0.0f : ((fLastG > 1.0f) ? 1.0f : fLastG);
		fLastB = (fLastB < 0.0f) ? 0.0f : ((fLastB > 1.0f) ? 1.0f : fLastB);

		//��ɫ��ֵ:
		pObj->m_vList[i].m_clr.red = fLastR;
		pObj->m_vList[i].m_clr.green = fLastG;
		pObj->m_vList[i].m_clr.blue = fLastB;

		//����alpha, ����򵥵��ò�������������������
		pObj->m_vList[i].m_clr.alpha = material.m_refDif.alpha;

	}

}