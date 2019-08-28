// ZBuffer.h: interface for the CZBuffer class.

//32λ��Ȼ���

#ifndef _CZBUFFER_H
#define _CZBUFFER_H 

class CZBuffer  
{
public:
	CZBuffer(int nWidth, int nHeight);
	virtual ~CZBuffer();


public:

	//��ȡ��Ȼ��������
	int GetWidth() const;
	//��ȡ��Ȼ������߶�
	int GetHeight() const;
	//��ȡ��Ȼ�����ָ��
	float* GetDepthPtr() const;

	//��ʼ�����
	void InitAllDepth(float fDepth);

	//�������ֵ
	void SetDepth(int x, int y, float fDepth);

	//��ȡ���ֵ
	float GetDepth(int x, int y) const;


private:
	
	//���
	int	m_nWidth;
	//�߶�
	int m_nHeight;

	//���ֵ
	float* m_pfDepth;
};
#endif 
