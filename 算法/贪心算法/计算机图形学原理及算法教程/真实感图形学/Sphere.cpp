/////////////////////////////////////////////////////////////////////////////////
//	
// Sphere.cpp: implementation of the CSphere class.
#include "stdafx.h"
#include "Sphere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSphere, CObject3d)

CSphere::CSphere()
{
	//����
}

CSphere::CSphere(float fRadius,  int nSlices,  int nStacks)
{
	m_fRadius = ABS(fRadius);
	m_nSlices = nSlices;
	m_nStacks = nStacks;

	//���ٲ���С��8, ���������
	if(m_nSlices < 8) m_nSlices = 8;
	if(m_nStacks < 8) m_nStacks = 8;

	//��ʼ����̬����Ĵ�С.
	m_vList.SetSize(m_nSlices * (m_nStacks - 1) + 2);
	m_eList.SetSize(m_nSlices * (2 * m_nStacks - 1));
	m_sList.SetSize(m_nSlices * m_nStacks);

	InitVertices();
	InitFacets();
	InitEdges();

}

//���ƹ��캯��
CSphere::CSphere(const CSphere& sphere)
{
	
	//���ƾ����༭���������
	//�༭��ָ�Լ������˵��޸�
	int nNumVertex = sphere.GetVertexListSize();
	int nNumEdge = sphere.GetEdgeListSize();
	int nNumFacet = sphere.GetFacetListSize();

	//���⸴�ƿն���
	ASSERT(nNumVertex > 2);
	ASSERT(nNumEdge > 2);
	ASSERT(nNumFacet > 0);

	m_vList.SetSize(nNumVertex);
	m_eList.SetSize(nNumEdge);
	m_sList.SetSize(nNumFacet);

	m_vList.Copy(sphere.m_vList);
	m_eList.Copy(sphere.m_eList);
	m_sList.Copy(sphere.m_sList);

	m_vList.FreeExtra();
	m_eList.FreeExtra();
	m_sList.FreeExtra();

	m_mGeomTrans = sphere.m_mGeomTrans;
	m_bAutoColor = sphere.m_bAutoColor;

	m_fRadius = sphere.m_fRadius;
	m_nSlices = sphere.m_nSlices;
	m_nStacks = sphere.m_nStacks;
}

CSphere::~CSphere()
{
	m_vList.RemoveAll();
	m_eList.RemoveAll();
	m_sList.RemoveAll();
}

//��¡
CSphere* CSphere::Clone()
{
	CSphere* pSphereCloned = new CSphere();
	
	//��¡���μ�����
	//����Ԫ�ظ���
	int nNumVertex = GetVertexListSize();
	int nNumEdge = GetEdgeListSize();
	int nNumFacet = GetFacetListSize();

	//�����¡�ն���
	ASSERT(nNumVertex > 2);
	ASSERT(nNumEdge > 2);
	ASSERT(nNumFacet > 0);

	pSphereCloned->m_vList.SetSize(nNumVertex);
	pSphereCloned->m_eList.SetSize(nNumEdge);
	pSphereCloned->m_sList.SetSize(nNumFacet);

	pSphereCloned->m_vList.Copy(m_vList);
	pSphereCloned->m_eList.Copy(m_eList);
	pSphereCloned->m_sList.Copy(m_sList);

	pSphereCloned->m_mGeomTrans = m_mGeomTrans;
	pSphereCloned->m_bAutoColor = m_bAutoColor;
	pSphereCloned->m_fRadius = m_fRadius;
	pSphereCloned->m_nSlices = m_nSlices;
	pSphereCloned->m_nStacks = m_nStacks;
	
	return pSphereCloned;
}


//��ʼ������ļ���(����ͷ���)
void CSphere::InitVertices()
{
	//����ʽ, 
	//��һ, γ���Ա������ϼ�����, ����������������ֱ�γ����γ
	//�ڶ�, ���ȴ�y������ʼ, ����ʱ�뷽������, �����ֶ���������.

	//γ�ȵ�����, ���ȱ�ʾ
	float fStepLttd = (float) (PIE / m_nStacks);

	//���ȵ�����, ���ȱ�ʾ
	float fStepLngtd = (float) (2.0 * PIE / m_nSlices);

	//γ��
	float fLatitude = fStepLttd;

	//��һ��, ��������

	//����������:��һ, ����; ���, ����; ����, �������ڵ�С�����
	
	m_vList[0].m_coord.x = 0.0f;
	m_vList[0].m_coord.y = 0.0f;
	m_vList[0].m_coord.z = m_fRadius;
	
	//������ȱʡֵ��ͬ

	//i��γ��ѭ��,  j������ѭ��

	//�������ڵ�С��(��̬����)
	for(int j = 0; j < m_nSlices; j++)
		m_vList[0].m_asIndex.Add(j);


	//�ڶ���, ����γ���ϵĵ�
	for(int i = 0; i < (m_nStacks - 1); i++)
	{
		//�ڲ���������ѭ��

		//��ǰ�����ڵľ���λ��(����), �� x ��н�
		//��ʼ��Ϊ -1.5* PIE;
		float fLongitude = -4.712389f;

		//���� z ����
		float zn = (float)cos(fLatitude);

		//���� z ����
		float z = m_fRadius * zn;

		//������ѭ��
		for(j = 0; j < m_nSlices; j++)
		{
			//���� x, y ����
			float xn = (float)(sin(fLatitude) * cos(fLongitude));
			float yn = (float)(sin(fLatitude) * sin(fLongitude));
			
			//�������: x,  y
			float x = m_fRadius * xn,   y = m_fRadius * yn;
			
			//��һ, ��д�������

			//�������
			int nIndex = i * m_nSlices + j + 1;

			m_vList[nIndex].m_coord.x = x;
			m_vList[nIndex].m_coord.y = y;
			m_vList[nIndex].m_coord.z = z;

			//���, ��д���߷���
			m_vList[nIndex].m_normal.x = xn;
			m_vList[nIndex].m_normal.y = yn;
			m_vList[nIndex].m_normal.z = zn;

			//����, �������ڵ�С��
			if(j == 0)
			{
				int anInFacets[4] = {
					i * m_nSlices,            (i + 1) * m_nSlices, 
					(i + 1) * m_nSlices - 1,  (i + 2) * m_nSlices - 1};

				m_vList[nIndex].DefineTopology(anInFacets,  4);
			}
			else
			{
				int anInFacets[4] = {
					i * m_nSlices + j - 1,  (i + 1) * m_nSlices + j - 1, 
					i * m_nSlices + j,      (i + 1) * m_nSlices + j};

				m_vList[nIndex].DefineTopology(anInFacets,  4);
			}//end j > 0

			//��һ����
			fLongitude += fStepLngtd;

		}//end for j

		//��һγ��
		fLatitude += fStepLttd;
	}//end for i

	//������, �����ϼ���
	
	int nIndex = m_nSlices * (m_nStacks - 1) + 1;
	
	//��һ, ����
	m_vList[nIndex].m_coord.x = 0.0f;
	m_vList[nIndex].m_coord.y = 0.0f;
	m_vList[nIndex].m_coord.z = -m_fRadius;

	//���, ����
	m_vList[nIndex].m_normal.x = 0.0f;
	m_vList[nIndex].m_normal.y = 0.0f;
	m_vList[nIndex].m_normal.z = -1.0f;

	//����, ����С��

	//С�����
	int nFacetBase = m_nSlices * (m_nStacks - 1);
	
	//С�����:
	for(j = 0; j < m_nSlices; j++)
		m_vList[nIndex].m_asIndex.Add(nFacetBase + j);
}

//��ʼ��С�漸��(����)
void CSphere::InitFacets()
{
	//i��γ��ѭ��,  j������ѭ��
	
	//���ȴ���λ�ڱ���Ȧ�ڵ���:
	for(int j = 0; j < (m_nSlices - 1); j++)
	{
		m_sList[j].m_avIndex.Add(0);
		m_sList[j].m_avIndex.Add(j + 1);
		m_sList[j].m_avIndex.Add(j + 2);
	}

	m_sList[j].m_avIndex.Add(0);
	m_sList[j].m_avIndex.Add(m_nSlices);
	m_sList[j].m_avIndex.Add(1);


	//�ڶ�, ��������������С��
	for(int i = 0; i < (m_nStacks - 2); i++)
	{
		//С��λ����γ��֮��, 
		//��γ��(ͶӰ)�� y �ύ�����
		int nIndexUp = i * m_nSlices + 1;
		
		//��γ��(ͶӰ)�� y �ύ�����
		int nIndexDown = nIndexUp + m_nSlices;

		//������ѭ��
		for(j = 0; j < (m_nSlices - 1); j++)
		{
			int anVertices[4] =  {
				nIndexUp + j,        nIndexDown + j, 
				nIndexDown + j + 1,  nIndexUp + j + 1};
			m_sList[nIndexDown + j - 1].DefineTopology(anVertices,  4);
		}//end for j

		//j = m_nSlices - 1
		m_sList[nIndexDown + j - 1].m_avIndex.Add(nIndexUp + j);
		m_sList[nIndexDown + j - 1].m_avIndex.Add(nIndexDown + j);
		m_sList[nIndexDown + j - 1].m_avIndex.Add(nIndexDown);
		m_sList[nIndexDown + j - 1].m_avIndex.Add(nIndexUp);
	}//end for i;

	//������ϼ�Ȧ�ڵ�С��

	//С����Ż���
	int nIndexFacet = (m_nStacks - 1) * m_nSlices;

	//������Ż���
	int nIndexVertex = m_nSlices * (m_nStacks - 2) + 1;

	for(j = 0; j < m_nSlices - 1; j++)
	{
		m_sList[nIndexFacet + j].m_avIndex.Add(nIndexVertex	+ j);
		m_sList[nIndexFacet + j].m_avIndex.Add(nIndexFacet	+ 1);
		m_sList[nIndexFacet + j].m_avIndex.Add(nIndexVertex	+ j + 1);
	}


	//�����һ��С��
	m_sList[nIndexFacet + j].m_avIndex.Add(nIndexVertex	+ j);
	m_sList[nIndexFacet + j].m_avIndex.Add(nIndexFacet	+ 1);
	m_sList[nIndexFacet + j].m_avIndex.Add(nIndexVertex);

}

//��ʼ����
void CSphere::InitEdges()
{
	//i��γ��ѭ��,  j������ѭ��	

	//��һ��, ���ȴ������ϵı�, Ȼ����γ���ϵı�

	
	//��һ, �����һ�����߱�

	m_eList[0].DefineEdge(0, 1);
	m_eList[0].m_asIndex.Add(0);
	m_eList[0].m_asIndex.Add(m_nSlices - 1);
	
	for(int i = 1; i < (m_nStacks - 1); i++)
	{
		m_eList[i].DefineEdge((i - 1) * m_nSlices + 1, 
							  i * m_nSlices + 1);
		m_eList[i].m_asIndex.Add(i * m_nSlices);
		m_eList[i].m_asIndex.Add((i + 1) * m_nSlices - 1);
	}


	i--;	//i = m_nStack - 2;

	m_eList[m_nStacks - 1].DefineEdge(i * m_nSlices + 1,  
									 m_nSlices * (m_nStacks - 1) + 1 );
	m_eList[m_nStacks - 1].m_asIndex.Add(m_nSlices * (m_nStacks - 1));
	m_eList[m_nStacks - 1].m_asIndex.Add(m_nSlices * m_nStacks - 1);


	//���, �������������ϵı�
	for(int j = 1; j < m_nSlices; j++)
	{

		int nIndex = j * m_nStacks;
		m_eList[nIndex].DefineEdge(0,  (j + 1));
		m_eList[nIndex].m_asIndex.Add(j - 1);
		m_eList[nIndex].m_asIndex.Add(j);

		//�������ڵľ��߱�
		for(i = 1; i < (m_nStacks - 1); i++)
		{
			m_eList[nIndex + i].DefineEdge((i - 1) * m_nSlices + j + 1, 
										   i * m_nSlices + j + 1);
			m_eList[nIndex + i].m_asIndex.Add(i * m_nSlices + j - 1);
			m_eList[nIndex + i].m_asIndex.Add(i * m_nSlices + j);
		}

		//λ���ϼ��ڵı�
		m_eList[nIndex + i].DefineEdge((m_nStacks - 2) * m_nSlices + j + 1, 
								       m_nSlices * (m_nStacks - 1) + 1);
		m_eList[nIndex + i].m_asIndex.Add(m_nSlices * (m_nStacks - 1) + j - 1);
		m_eList[nIndex + i].m_asIndex.Add(m_nSlices * (m_nStacks - 1) + j);
	}//end for j

	//γ�߱߻���
	int neBase = m_nStacks * m_nSlices;
	for(i = 0; i < (m_nStacks - 1); i++)
	{
		//�������� (��ʼֵ - 1)
		int nvBase = i * m_nSlices;

		//ͬһ��γ���ϵı�
		int nIndex = neBase + nvBase;
		for(j = 0; j < (m_nSlices - 1); j++)
		{
			m_eList[nIndex + j].DefineEdge(nvBase + j + 1,  nvBase + j + 2);
			m_eList[nIndex + j].m_asIndex.Add(nvBase + j);
			m_eList[nIndex + j].m_asIndex.Add(nvBase + m_nSlices + j);
		}

		//j = m_nSlices - 1;
		m_eList[nIndex + j].DefineEdge(nvBase + j + 1,  nvBase + 1);
		m_eList[nIndex + j].m_asIndex.Add(nvBase + m_nSlices - 1);
		m_eList[nIndex + j].m_asIndex.Add(nvBase + 2 * m_nSlices - 1);

	}//end for i(2nd)
}
