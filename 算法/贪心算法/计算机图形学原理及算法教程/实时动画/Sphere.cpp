// Sphere.cpp: implementation of the CVirtualSphere class.

#include "stdafx.h"
#include "Sphere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSphere::CSphere(int nRadius)
{
	m_nRadius = nRadius;
	if(m_nRadius < 1) m_nRadius = 1;
	m_byRed = 192;
	m_byGreen = 192;
	m_byBlue = 192;

	m_nDifPrecision = 8;
	m_nSpePrecision = 4;

}

CSphere::~CSphere()
{

}

//�����������������ɫ
void CSphere::SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue)
{
	m_byRed = byRed;
	m_byGreen = byGreen;
	m_byBlue = byBlue;
}

//������ɢ����͸߹�����ıƽ�����
//nDifPrecision-----������������ƴ���
//nSpePrecision-----�߹�������ƴ���
//���߿��Ծ�������������͸߹�������ռ�еı���
void CSphere::SetPrecision(int nDifPrecision, int nSpePrecision)
{
	m_nDifPrecision = nDifPrecision;
	m_nSpePrecision = nSpePrecision;
	if(m_nDifPrecision < 1) m_nDifPrecision = 1;
	if(m_nSpePrecision < 1) m_nDifPrecision = 1;
}

//����
//(x,y)------���Ͻ�λ��
void CSphere::Draw(CDC* pDC, int x ,int y)
{
	pDC->SelectStockObject(NULL_PEN);
	//�������ƽ�����
	int nDifTimes = min(m_nDifPrecision, m_nRadius);
	
	//��ĸ
	int nDenominator = (7 * nDifTimes);

	//��������������
	for(int i = 0; i < nDifTimes; i++)
	{
		//��ɫ
		BYTE byRed = (BYTE)((i * m_byRed * 4) / nDenominator + 3 * (int)m_byRed / 7);
		BYTE byGreen = (BYTE)((i * m_byGreen * 4) / nDenominator + 3 * (int)m_byGreen / 7);
		BYTE byBlue = (BYTE)((i * m_byBlue * 4) / nDenominator + 3 * (int)m_byBlue / 7);

		//��ˢ
		CBrush brush;
		brush.CreateSolidBrush(RGB(byRed, byGreen, byBlue));
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		
		//���Ͻ�����
		int xLT = x + i;
		int yLT = y + (i * 2) / 5;
		
		//��С
		int nSize = m_nRadius - (5 * i) / 4 + 1;

		//���½�����
		int xRB = xLT + nSize;
		int yRB = yLT + nSize;


		//����
		pDC->Ellipse(xLT, yLT, xRB, yRB);
		
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}

	//���Ƹ߹�����
	
	//�߹�ƽ�����
	int nSpeTimes = min(m_nSpePrecision, (m_nRadius - nDifTimes));
	if(nSpeTimes < 1) return;
	
	//��ʱ����,��ĸ
	nDenominator = (2 * nSpeTimes);

	
	//���Ƹ߹�����
	for(i = 0; i < nSpeTimes; i++)
	{
		int nIndex = i + nDifTimes;
		//��ɫ
		BYTE byRed = (BYTE)(m_byRed + ((255 - m_byRed) * i) / nDenominator);
		BYTE byGreen = (BYTE)(m_byGreen + ((255 - m_byGreen) * i) / nDenominator);
		BYTE byBlue = (BYTE)(m_byBlue + ((255 - m_byBlue) * i) / nDenominator);

		//��ˢ
		CBrush brush;
		brush.CreateSolidBrush(RGB(byRed, byGreen, byBlue));
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		
		//���Ͻ�����
		int xLT = x + nIndex;
		int yLT = y + (nIndex * 2) / 5;
		
		//��С
		int nSize = m_nRadius - (5 * nIndex) / 4 + 1;

		int xRB = xLT + nSize;
		int yRB = yLT + nSize;


		//����
		pDC->Ellipse(xLT, yLT, xRB, yRB);
		
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}

}
