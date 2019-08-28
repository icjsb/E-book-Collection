// Sphere.h: interface for the CVirtualSphere class.

#ifndef _CVSPHERE_H
#define _CVSPHERE_H

class CSphere  
{
public:
	CSphere(int nRadius);
	virtual ~CSphere();

public:

	void SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue);
	void SetPrecision(int nDifPrecision, int nSpePrecision);
	void Draw(CDC* pDC, int x, int y);

private:

	//�뾶
	int m_nRadius;

	//������ɫ
	BYTE m_byRed, m_byGreen, m_byBlue;
	
	//��ϸ�̶�

	//��ɢɫ����ıƽ�����
	int m_nDifPrecision;

	//�߹�����ıƽ�����
	int m_nSpePrecision;

};

#endif 
