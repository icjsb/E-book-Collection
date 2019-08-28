/////////////////////////////////////////////////////////////////////////////////
//	
// ColorBuffer.cpp: implementation of the CColorBuffer class.
#include "stdafx.h"
#include "ColorBuffer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorBuffer::CColorBuffer(int nWidth,  int nHeight)
{

	m_nWidth = (nWidth < 0) ? 0 : nWidth;
	m_nHeight = (nHeight < 0) ? 0 : nHeight;

	//����ȫ���ڴ�(z-buffer��ȱ��)
	//������ɫ��ɺ�ɫ
	m_pbyColor = new BYTE[m_nWidth * m_nHeight * 4];
	
	if(m_pbyColor == NULL)
	{
		AfxMessageBox("�ڴ����ʧ��!");
		exit(1);
	}
	memset(m_pbyColor,  0,  m_nWidth * m_nHeight * 4);
 
}

CColorBuffer::~CColorBuffer()
{
	if(m_pbyColor)
	{
		delete[] m_pbyColor;
		m_pbyColor = NULL;
	}
}


//��ѯ����

//��ȡ��ɫ���������
int CColorBuffer::GetWidth() const
{
	return m_nWidth;
}

//��ȡ��ɫ�������߶�
int CColorBuffer::GetHeight() const
{
	return m_nHeight;
}

//��ȡ��ɫ������ָ��
BYTE* CColorBuffer::GetColorPtr() const
{
	return m_pbyColor;
}

//���ñ�����ɫ

//��ָ������ɫ����Ϊ����ɫ
//��һ��ɫ(r, g, b, a)
void CColorBuffer::SetBkColor(BYTE r,  BYTE g,  BYTE b,  BYTE a)
{
	//��, ��, ��, alpha
	BYTE* pbyColor = m_pbyColor;
	for(int i = 0; i < m_nWidth; i++)
	{
		*pbyColor++ = b;
		*pbyColor++ = g;
		*pbyColor++ = r;
		*pbyColor++ = a;
	}

	//�ڴ�֮�俽��, ����ʣ�µ� (m_nHeight - 1)��.
	DWORD dwScanLength = 4 * (DWORD)m_nWidth;
	for(i = 1; i < m_nHeight; i++)
	{
		//ָ��һ�п�ʼ��λ��
		pbyColor = m_pbyColor + (i * dwScanLength);
		//�ӵ�һ�п������� i ��:
		memcpy(pbyColor,  m_pbyColor,  dwScanLength);
	}
}

//����Ϊһ��ָ���ı���ͼ��
//ʹ��ʱ�ľ���:ͼ���������ɫ�������ߴ���ȫ��ͬ!
void CColorBuffer::SetBkImage(const BYTE* pbyImage,  int nWidth,  int nHeight)
{
	ASSERT(pbyImage);
	if((nWidth != m_nWidth) || (nHeight != m_nHeight))
	{
		::AfxMessageBox("ͼ��ߴ�����ɫ��������С��ƥ��");
		return;
	}

	::CopyMemory(m_pbyColor,  pbyImage,  m_nWidth * m_nHeight * 4);
}


//����һ�������ɫ
//����z-buffer�㷨������ɫ����������Ҫ����
void CColorBuffer::SetPixel(int x,  int y,  float r,  float g,  float b , float a)
{
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))return;

	DWORD dwIndex = y * m_nWidth * 4 + 4 * x;

	BYTE byRed = (BYTE)(r * 255.0f);
	BYTE byGreen = (BYTE)(g * 255.0f);
	BYTE byBlue = (BYTE)(b * 255.0f);
	BYTE byAlpha = (BYTE)(a * 255.0f);
	BYTE* pbyColor = (m_pbyColor + dwIndex);
	*pbyColor++ = byBlue;
	*pbyColor++ = byGreen;
	*pbyColor++ = byRed;
	*pbyColor++ = byAlpha;
}


void CColorBuffer::SetPixel(int x,  int y,  BYTE r,  BYTE g,  BYTE b ,  BYTE a)
{
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))return;

	DWORD dwIndex = y * m_nWidth * 4 + 4 * x;

	BYTE* pbyColor = m_pbyColor + dwIndex;

	//�����̡��졢Alpha
	*pbyColor++ = b;
	*pbyColor++ = g;
	*pbyColor++ = r;
	*pbyColor++ = a;
} 

//��ȡ��ɫ
PIXELCOLORRGBA CColorBuffer::GetPixel(int x,  int y) const
{
	PIXELCOLORRGBA rgba = {0,  0,  0,  0};
	
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))
		return rgba;

	DWORD dwIndex = y * m_nWidth * 4 + 4 * x;

	BYTE* pbyColor = m_pbyColor + dwIndex;

	
	//�����̡��졢Alpha
	rgba.blue = *pbyColor++;
	rgba.green = *pbyColor++;
	rgba.red = *pbyColor++;
	rgba.alpha = *pbyColor++;
	return rgba;
}

//����ɫ�������е�����ֱ�Ӵ���һ��DDB����, ��HBITMAP����
HBITMAP CColorBuffer::CreateDdb(HDC hDC)
{
	// ����һ��BITMAPV4HEADER�ṹ

	//�����ڴ�:
	BYTE* pbyBits = new BYTE[sizeof(BITMAPV4HEADER)];
	if(pbyBits == NULL) return NULL;
	//ָ���������ݵ�ָ��, 
	BITMAPV4HEADER* pbmih = (BITMAPV4HEADER*)pbyBits;
	
	pbmih->bV4Size = sizeof(BITMAPV4HEADER);	//108
	pbmih->bV4Width = (LONG)m_nWidth;
	pbmih->bV4Height = (LONG)(-m_nHeight);
	pbmih->bV4Planes = 1;
	pbmih->bV4BitCount = 32;

    pbmih->bV4V4Compression = BI_RGB;    
	pbmih->bV4SizeImage = 0;
	pbmih->bV4XPelsPerMeter = 0;    
	pbmih->bV4YPelsPerMeter = 0;
	pbmih->bV4ClrUsed = 0;    
	pbmih->bV4ClrImportant = 0;
 
	//�ڶ���, ����һ��DDB
	HBITMAP hBitmap = ::CreateDIBitmap(hDC, (BITMAPINFOHEADER*)pbmih, CBM_INIT, m_pbyColor, (BITMAPINFO*)pbmih, DIB_RGB_COLORS);

	delete[] pbyBits;
	return hBitmap;
}

//����ɫ�����������ݽ�����ǰ̨(�������ɫ������)
void CColorBuffer::SwapBuffer(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	HBITMAP hBitmap = CreateDdb(pDC->m_hDC);
	HBITMAP hOldBitmap = (HBITMAP)memDC.SelectObject(hBitmap);
	pDC->BitBlt(0, 0, m_nWidth, m_nHeight, &memDC, 0, 0, SRCCOPY);
	::DeleteObject(hBitmap);
	memDC.SelectObject(hOldBitmap);
}