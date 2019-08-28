// ColorBuffer.h: interface for the CColorBuffer class.

//�������������ɫ������

#ifndef _CCOLORBUFFER_H
#define _CCOLORBUFFER_H
#include "Grphcs.h"
#include "Img.h"

class CColorBuffer  
{
public:
	CColorBuffer(int nWidth, int nHeight);
	virtual ~CColorBuffer();

public:

	//��ȡ��ɫ���������
	int GetWidth() const;
	//��ȡ��ɫ�������߶�
	int GetHeight() const;
	//��ȡ��ɫ������ָ��
	BYTE* GetColorPtr() const;

	//��ָ������ɫ����Ϊ����ɫ
	void SetBkColor(BYTE r, BYTE g, BYTE b, BYTE a);
	
	//��һ������ɫ�������ȴ�С��ͼ������Ϊ����
	void SetBkImage(const BYTE* pbyImage, int nWidth, int nHeight);

	//����һ�������ɫ
	void SetPixel(int x, int y, float r, float g, float b , float a = 1.0f);

	void SetPixel(int x, int y, BYTE r, BYTE g, BYTE b , BYTE a = 255);
	
	//��ȡ��ɫ
	PIXELCOLORRGBA GetPixel(int x, int y) const;

	//����ɫ�����������ݴ���һ���ڴ�λͼ����(���)
	HBITMAP CColorBuffer::CreateDdb(HDC hDC);

	//����ɫ�����������ݽ�����ǰ̨(�������ɫ������)
	void CColorBuffer::SwapBuffer(CDC* pDC);


private:
	//��ɫ��������С
	int m_nWidth;
	int m_nHeight;
	
	//��ɫ������
	BYTE* m_pbyColor;

};

#endif 
