// ZBuffer.cpp: implementation of the CZBuffer class.
#include "stdafx.h"
#include "ZBuffer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZBuffer::CZBuffer(int nWidth,  int nHeight)
{

	m_nWidth = (nWidth < 0) ? 0 : nWidth;
	m_nHeight = (nHeight < 0) ? 0 : nHeight;

	//����ȫ���ڴ�(z-buffer��ȱ��)
	m_pfDepth = new float[m_nWidth * m_nHeight];
	
	if(m_pfDepth == NULL)
	{
		AfxMessageBox("�ڴ����ʧ��!");
		exit(1);
	}
}

CZBuffer::~CZBuffer()
{
	if(m_pfDepth)
	{
		delete[] m_pfDepth;
		m_pfDepth = NULL;
	}
}

//��ȡ��Ȼ������߶�
int CZBuffer::GetWidth() const
{
	return m_nWidth;
}


//��ȡ��Ȼ������߶�
int CZBuffer::GetHeight() const
{
	return m_nHeight;
}

//��ȡ��Ȼ�����ָ��
float* CZBuffer::GetDepthPtr() const
{
	return m_pfDepth;
}

//��ʼ�����
void CZBuffer::InitAllDepth(float fDepth)
{
	int nSize = m_nWidth * m_nHeight;
	for(int i = 0; i < 	nSize; i++)
		m_pfDepth[i] = fDepth;
}

//�������ֵ
void CZBuffer::SetDepth(int x,  int y,  float fDepth)
{
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))return;
	int nIndex = y * m_nWidth + x;
	m_pfDepth[nIndex] = fDepth;

}

//��ȡ���ֵ
float CZBuffer::GetDepth(int x,  int y) const
{
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))
		return - 1.0f;
	int nIndex = y * m_nWidth + x;
	return m_pfDepth[nIndex];
}
