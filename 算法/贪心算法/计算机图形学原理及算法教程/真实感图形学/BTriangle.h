// BTriangle.h: interface for the CBTriangle class.
//����Z��������������ɨ��ת��

#ifndef _CBTRIANGLE_H
#define _CBTRIANGLE_H

#include "ColorBuffer.h"
#include "ZBuffer.h"

class CBTriangle  
{
public:
	CBTriangle();
	virtual ~CBTriangle();

public:
	//����Gouraud������ɫ�������������
	void Draw(POINT pt1, POINT pt2, POINT pt3, float z1, float z2, float z3, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, FLOATCOLORRGBA clr3, CColorBuffer* pCB, CZBuffer* pZB);

private:

	//���Ʋ���ȡ����Ϣ:
	void DealEdge(int x1, int y1, int x2, int y2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB, int* pnCoord, FLOATCOLORRGBA* pColor, float* pfDepth,DWORD dwFeature = G3D_TRIANGLE_ON_LINE_RIGHT);
	//����ɨ����
	void Scan(int x1, int x2, int nScanLine, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB);
};

#endif 
