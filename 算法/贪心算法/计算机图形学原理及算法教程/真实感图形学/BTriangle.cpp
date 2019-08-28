/////////////////////////////////////////////////////////////////////////////////
//	
// BTriangle.cpp: implementation of the CBTriangle class.
#include "stdafx.h"
#include "BTriangle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBTriangle::CBTriangle()
{}

CBTriangle::~CBTriangle(){}

void CBTriangle::DealEdge(int x1, int y1, int x2, int y2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB, int* pnCoord, FLOATCOLORRGBA* pColor, float* pfDepth, DWORD dwFeature)
{
	//������ĳ���Ӧ����y�����ľ���ֵ��1,
	ASSERT(pnCoord);
	ASSERT(pColor);
	ASSERT(pfDepth);

	//����һ��ˮƽֱ��,��򵥵ط��ص�һ������������ɫ
	//����һ��ˮƽֱ��,���ǲ�������������������ҹ�ϵ.
	if(y1 == y2)
	{
		pnCoord[0] = x1;
		pColor[0] = clr1;
		pfDepth[0] = z1;
		return;
	}

	//���濼��ֱ��б�ʲ�Ϊ0�����:

	//���˵���ˮƽƫ�����ʹ�ֱƫ����
	int nDx = x2 - x1;	
	int nDy = y2 - y1;

	//���˵���ˮƽ����ʹ�ֱ����
	int nIx = ABS(nDx);
	int nIy = ABS(nDy);

	//��㲽��(������ֵ)
	int nInc = MAX(nIx,nIy);
	
	//�����ж��Ƿ���nJudgeX,nJudgeY��������ǰ��
	int nJudgeX = -nIy, nJudgeY = -nIx;

	//ͨ����������õ��ĵ�ǰ��
	int x = x1, y = y1;

	//Bresenham�㷨
	int nTwoIx = 2 * nIx, nTwoIy = 2 * nIy;

	//ֱ�ߵ�ǰ�����ɫ
	float fPlotR = clr1.red, fPlotG = clr1.green, fPlotB = clr1.blue; 
	float fPlotA = clr1.alpha;

	//��ɫ����
	float fIncR = (clr2.red - fPlotR) / nInc;
	float fIncG = (clr2.green - fPlotG) / nInc;
	float fIncB = (clr2.blue - fPlotB) / nInc;
	float fIncA = (clr2.alpha - fPlotA) / nInc;

	//ˮƽ�߽�������յ�
	FLOATCOLORRGBA clrStart = {fPlotR,fPlotG,fPlotB,fPlotA};
	FLOATCOLORRGBA clrEnd = clrStart;

	//�����±꣬ˮƽ�߽�������յ�� x ����
	int nIndex = 0, nStartX = x1, nEndX = x1;
	
	//ˮƽ�߽�������յ�� z ����,��ǰ��� z ����
	//�Լ� z ��������
	float fStartZ = z1, fEndZ = z1, z = z1, fIncZ = (z2 - z1) / nInc; 

	
	//�������ֵ���Ƶ�һ����
	//�������е����
	float zInBuffer = pZB->GetDepth(x1,y1);
	
	//�����ǰ���z����С����Ȼ������е���ͬλ��z������
	if(z < zInBuffer)
	{
		//����ɫ�������л��Ƶ�һ����
		pCB->SetPixel(x1, y1, fPlotR, fPlotG, fPlotB, fPlotA); 

		//������Ȼ�������ֵ
		pZB->SetDepth(x1, y1, z);
	}

	//��ʼ��������
	for(int i = 0;i <= nInc; i++)
	{
		nJudgeX += nTwoIx;
		nJudgeY += nTwoIy;

		//ͨ������������ĵ�ǰ���Ƿ�����ֱ���ϵĵ�
		BOOL bRecord = FALSE;
		
		//��ǰ���Ƿ�Ϊֱ���ϵĵ�
		BOOL bPlot = FALSE;

		//�ȼ�� y ����
		if(nJudgeY >= 0)
		{
			bPlot = TRUE;
			bRecord = TRUE;
			nJudgeY -= nTwoIx;

			//�����������ֱ��ͳһ����
			if(nDy > 0)
			{
				nEndX = x;
				y++;
				//ˮƽ�߽���յ����ɫ
				clrEnd.red = fPlotR;
				clrEnd.green = fPlotG;
				clrEnd.blue = fPlotB;
				clrEnd.alpha = fPlotA;
				//ˮƽ�߽���յ�����(�ر߽��в�ֵ��������)
				fEndZ = z;
			}
			else if(nDy < 0)
			{
				nEndX = x;
				y--;
				//ˮƽ�߽���յ����ɫ
				clrEnd.red = fPlotR;
				clrEnd.green = fPlotG;
				clrEnd.blue = fPlotB;
				clrEnd.alpha = fPlotA;
				//ˮƽ�߽���յ�����(�ر߽��в�ֵ��������)
				fEndZ = z;
			}
		}//end if 

		//���� x ����
		if(nJudgeX >= 0)
		{
			bPlot = TRUE;
			nJudgeX -= nTwoIy;

			//�����������ֱ��ͳһ����
			if(nDx > 0)x++;
			else if(nDx < 0)x--;
		}

		if(bPlot)
		{
			fPlotR += fIncR;
			fPlotG += fIncG;
			fPlotB += fIncB;
			fPlotA += fIncA;
			
			z += fIncZ;
			if(i < (nInc - 1))
			{
				//�������ֵ���Ƶ�һ����
				zInBuffer = pZB->GetDepth(x,y);
				
				//�����ǰ���z����С����Ȼ������е���ͬλ��z������
				if(z < zInBuffer)
				{
					//����ɫ�������л��Ƶ�һ����
					pCB->SetPixel(x, y, fPlotR, fPlotG, fPlotB, fPlotA); 

					//������Ȼ�������ֵ
					pZB->SetDepth(x, y, z);
				
				}
			}

		}

		//�����ǰ����ֱ����,���¼��ǰ��
		if(bRecord)
		{
			//ȡ����ߵ�,���������
			if(dwFeature == G3D_TRIANGLE_ON_LINE_LEFT)
			{
				//ȡx������С��
				if(nStartX < nEndX)
				{
					pnCoord[nIndex] = nStartX;	
					pColor[nIndex] = clrStart;
					pfDepth[nIndex] = fStartZ;
				}
				else
				{
					pnCoord[nIndex] = nEndX;	
					pColor[nIndex] = clrEnd;
					pfDepth[nIndex] = fEndZ;
				}
			}//end if
				
			//ȡ���ұߵ�,�������Ҳ�
			else
			{
				//ȡx���������
				if(nStartX < nEndX)
				{
					pnCoord[nIndex] = nEndX;	
					pColor[nIndex] = clrEnd;
					pfDepth[nIndex] = fEndZ;
				}
				else
				{
					pnCoord[nIndex] = nStartX;	
					pColor[nIndex] = clrStart;
					pfDepth[nIndex] = fStartZ;
				}
			}//end else
			
			nIndex++;

			//��һ�����
			nStartX = x;
			
			//��һ������ z ����
			fStartZ = z;

			//��һ��������ɫ
			clrStart.red = fPlotR;
			clrStart.green = fPlotG;
			clrStart.blue = fPlotB;
			clrStart.alpha = fPlotA;
		}
	}

	//��б�ʵĺ�Сʱ,y������������,��ʱ��Ҫ�ر���
	if(nIndex < (ABS(y2 - y1) + 1))
	{
		//ȡ����ߵ�,���������
		if(dwFeature == G3D_TRIANGLE_ON_LINE_LEFT)
		{
			//ȡx������С��
			if(nStartX < x2)
			{
				pnCoord[nIndex] = nStartX;	
				pColor[nIndex] = clrStart;
				pfDepth[nIndex] = fStartZ;
			}
			else
			{
				pnCoord[nIndex] = x2;
				pColor[nIndex] = clr2;
				pfDepth[nIndex] = z2;
			}

		}//end if
		//ȡ���ұߵ�,�������Ҳ�
		else
		{
			//ȡx���������
			if(nStartX < x2)
			{
				pnCoord[nIndex] = x2;	
				pColor[nIndex] = clr2;
				pfDepth[nIndex] = z2;
			}
			else
			{
				pnCoord[nIndex] = nStartX;	
				pColor[nIndex] = clrStart;
				pfDepth[nIndex] = fStartZ;
			}
		}//end else
	}//end if(nIndex < (ABS(y2 - y1) + 1))
}

void CBTriangle::Scan(int x1, int x2, int nScanLine, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB)
{
	//������ظ��� 
	int nFillPixels = ABS(x2 - x1);
	//���Ϊͬһ�����������Ϊ0,�򷵻�;
	if(nFillPixels < 2) return;


	//��ɫ����(��ɫ��ֵ / ����)
	float fIncR = (clr2.red - clr1.red) / nFillPixels;
	float fIncG = (clr2.green - clr1.green) / nFillPixels;
	float fIncB = (clr2.blue - clr1.blue) / nFillPixels;
	float fIncA = (clr2.alpha - clr1.alpha) / nFillPixels;


	//��ǰ��ɫ
	float fRed = clr1.red + fIncR;
	float fGreen = clr1.green + fIncG;
	float fBlue = clr1.blue + fIncB;
	float fAlpha = clr1.alpha + fIncA;

	//��䷽��
	int nDirection = (x1 < x2) ? 1 : -1;

	//��ǰx����
	int x = x1 + nDirection;


	//��ǰ z ����, z��������,
	//ע�� ���ǲ�û�в���ƽ��ϵ�����������
	float z = z1, fIncZ = (z2 - z1) / nFillPixels;
	z += fIncZ;

	nFillPixels--;
	//��ʼ���
	for(int i = 0; i < nFillPixels ; i++)
	{
		float zInBuffer = pZB->GetDepth(x,nScanLine);
				
		//�����ǰ���z����С����Ȼ������е���ͬλ��z������
		if(z < zInBuffer)
		{
			//����ɫ�������л��Ƶ�һ����
			pCB->SetPixel(x, nScanLine, fRed, fGreen, fBlue, fAlpha); 

			//������Ȼ�������ֵ
			pZB->SetDepth(x, nScanLine, z);
		}

		//��������
		x += nDirection;
		z += fIncZ;
		fRed += fIncR;
		fGreen += fIncG;
		fBlue += fIncB;
		fAlpha += fIncA;
	}
} 

//ɨ��ת��������

void CBTriangle::Draw(POINT pt1, POINT pt2, POINT pt3, float z1, float z2, float z3, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, FLOATCOLORRGBA clr3, CColorBuffer* pCB, CZBuffer* pZB)
{
	ASSERT(pCB);
	ASSERT(pZB);
	
	
	if((pt1.y == pt2.y) && (pt2.y == pt3.y))
	{
		//pt1λ���м�(����ʸ����������ж�)
		if((pt2.x - pt1.x) * (pt3.x - pt1.x) <= 0)
		{
			Scan(pt1.x, pt2.x, pt1.y, z1, z2, clr1, clr2, pCB, pZB);
			Scan(pt1.x, pt3.x, pt1.y, z1, z3, clr1, clr3, pCB, pZB);
		}
		//pt2λ���м�
		else if((pt1.x - pt2.x) * (pt3.x - pt2.x) <= 0)
		{
			Scan(pt2.x, pt1.x, pt1.y, z2, z1, clr2, clr1, pCB, pZB);
			Scan(pt2.x, pt3.x, pt1.y, z2, z3, clr2, clr3, pCB, pZB);
		}
		//pt3λ���м�
		else 
		{
			Scan(pt3.x, pt1.x, pt1.y, z3, z1, clr3, clr1, pCB, pZB);
			Scan(pt3.x, pt2.x, pt1.y, z3, z2, clr3, clr2, pCB, pZB);
		}

		//���������˵�
		float zInBuffer = pZB->GetDepth(pt1.x, pt1.y);
				
		//�����ǰ���z����С����Ȼ������е���ͬλ��z������
		if(z1 < zInBuffer)
		{
			//����ɫ�������л��Ƶ�һ����
			pCB->SetPixel(pt1.x, pt1.y, clr1.red, clr1.green, clr1.blue, clr1.alpha);
			//������Ȼ�������ֵ
			pZB->SetDepth(pt1.x, pt1.y, z1);
		}

		//
		zInBuffer = pZB->GetDepth(pt2.x, pt2.y);
				
		//�����ǰ���z����С����Ȼ������е���ͬλ��z������
		if(z2 < zInBuffer)
		{
			//����ɫ�������л��Ƶ�һ����
			pCB->SetPixel(pt2.x, pt2.y, clr2.red, clr2.green, clr2.blue, clr2.alpha);
			//������Ȼ�������ֵ
			pZB->SetDepth(pt2.x, pt2.y, z2);
		}

		zInBuffer = pZB->GetDepth(pt3.x, pt3.y);
				
		//�����ǰ���z����С����Ȼ������е���ͬλ��z������
		if(z3 < zInBuffer)
		{
			//����ɫ�������л��Ƶ�һ����
			pCB->SetPixel(pt3.x, pt3.y, clr3.red, clr3.green, clr3.blue, clr3.alpha);
			//������Ȼ�������ֵ
			pZB->SetDepth(pt3.x, pt3.y, z3);
		}

		return;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	POINT point1 = pt1, point2 = pt2, point3 = pt3;
	FLOATCOLORRGBA color1 = clr1, color2 = clr2, color3 = clr3;
	float fz1 = z1, fz2 = z2, fz3 = z3;

	//point1��¼y������С��
	if(point1.y > point2.y)
	{
		point1 = pt2;
		point2 = pt1;

		color1 = clr2;
		color2 = clr1;

		fz1 = z2;
		fz2 = z1;
	}
	if(point1.y > point3.y) 
	{
		POINT ptTemp = point1;
		FLOATCOLORRGBA clrTemp = color1;
		float zTemp = fz1;
		point1 = point3;
		color1 = color3;
		fz1 = fz3;

		point3 = ptTemp;
		color3 = clrTemp;
		fz3 = zTemp;
	}
	//point2��¼y���������
	if(point2.y < point3.y)
	{
		POINT ptTemp = point2;
		FLOATCOLORRGBA clrTemp = color2;
		float zTemp = fz2;
		point2 = point3;
		color2 = color3;
		fz2 = fz3;

		point3 = ptTemp;
		color3 = clrTemp;
		fz3 = zTemp;
	}


	//��ȡ�߽��� x ����,����߽���ɫ
	//12 --- 1 to 2, 13 ---- 1 to 3,  32 ---- 3 to 2
	//y����֮��ľ���
	int nDy12 = (point2.y - point1.y) + 1;
	int nDy13 = (point3.y - point1.y) + 1;
	int nDy32 = (point2.y - point3.y) + 1;
	//��ȡɨ���ߵ� x ����
	int* pnEdge12 = new int[nDy12];
	int* pnEdge13 = new int[nDy13];
	int* pnEdge32 = new int[nDy32];
		
	//��ȡ�߽���ɫ
	//ע��,����֧��͸������,�����ɫ����������
	FLOATCOLORRGBA* pClrEdge12 = new FLOATCOLORRGBA[nDy12];
	FLOATCOLORRGBA* pClrEdge13 = new FLOATCOLORRGBA[nDy13];
	FLOATCOLORRGBA* pClrEdge32 = new FLOATCOLORRGBA[nDy32];

	//��¼�߽����
	float* pfzEdge12 = new float[nDy12];
	float* pfzEdge13 = new float[nDy13];
	float* pfzEdge32 = new float[nDy32];


	//��ȡ�߽缰����ɫ

	//����ʸ�����(ֻ��Ҫ����Z����),���ж������ε�λ�ù�ϵ
	int nDelta = ((point3.x - point1.x) * (point2.y - point3.y)
				 - (point2.x - point3.x) * (point3.y - point1.y));

	if(nDelta > 0)
	{
		DealEdge(point1.x, point1.y, point2.x, point2.y, fz1, fz2, color1, color2, pCB, pZB, pnEdge12, pClrEdge12, pfzEdge12); 
		DealEdge(point1.x, point1.y, point3.x, point3.y, fz1, fz3, color1, color3, pCB, pZB, pnEdge13, pClrEdge13, pfzEdge13, G3D_TRIANGLE_ON_LINE_LEFT); 
		DealEdge(point3.x, point3.y, point2.x, point2.y, fz3, fz2, color3, color2, pCB, pZB, pnEdge32, pClrEdge32, pfzEdge32, G3D_TRIANGLE_ON_LINE_LEFT); 
	}
	else
	{
		DealEdge(point1.x, point1.y, point2.x, point2.y, fz1, fz2, color1, color2, pCB, pZB, pnEdge12, pClrEdge12, pfzEdge12, G3D_TRIANGLE_ON_LINE_LEFT); 
		DealEdge(point1.x, point1.y, point3.x, point3.y, fz1, fz3, color1, color3, pCB, pZB, pnEdge13, pClrEdge13, pfzEdge13);
		DealEdge(point3.x, point3.y, point2.x, point2.y, fz3, fz2, color3, color2, pCB, pZB, pnEdge32, pClrEdge32, pfzEdge32);
	}

	//�������һ����
	//CPLine��Ԫ��Windows����ֱ�ߵķ�ʽ��һ�µ�,�����������һ����

	float zInBuffer = pZB->GetDepth(point2.x, point2.y);
			
	//�����ǰ���z����С����Ȼ������е���ͬλ��z������
	if(fz2 < zInBuffer)
	{
		//����ɫ�������л��Ƶ�һ����
		pCB->SetPixel(point2.x, point2.y, color2.red, color2.green, color2.blue, color2.alpha);
		//������Ȼ�������ֵ
		pZB->SetDepth(point2.x, point2.y, fz2);
	}
	//����������
	if(point3.y == point2.y)
	{
		zInBuffer = pZB->GetDepth(point3.x, point3.y);
				
		//�����ǰ���z����С����Ȼ������е���ͬλ��z������
		if(fz3 < zInBuffer)
		{
			//����ɫ�������л��Ƶ�һ����
			pCB->SetPixel(point3.x, point3.y, color3.red, color3.green, color3.blue, color3.alpha);
			//������Ȼ�������ֵ
			pZB->SetDepth(point3.x, point3.y, fz3);
		}	
	}

	
	int y, nPlumbScan = 0;
	if(point1.y < point3.y)
	{
		for(y = point1.y; y < point3.y; y++)
		{
			//һ��ɨ���ߵ�x����
			int	x12 = pnEdge12[nPlumbScan];
			int	x13 = pnEdge13[nPlumbScan];
			
			//һ��ɨ���ߵ���ȱ仯
			float z12 = pfzEdge12[nPlumbScan];
			float z13 = pfzEdge13[nPlumbScan];

			//��ɫ
			FLOATCOLORRGBA clrEdge12 = pClrEdge12[nPlumbScan];
			FLOATCOLORRGBA clrEdge13 = pClrEdge13[nPlumbScan];
			
			//���
			Scan(x12, x13, y, z12, z13, clrEdge12,clrEdge13, pCB, pZB);

			nPlumbScan++;
		}//end for y
	
	}
	
	int nPlumbScan32 = 0;
	for(y = point3.y; y <= point2.y; y++)
	{
		//һ��ɨ���ߵ�x����
		int	x12 = pnEdge12[nPlumbScan];
		int	x32 = pnEdge32[nPlumbScan32];

		//һ��ɨ���ߵ���ȱ仯
		float z12 = pfzEdge12[nPlumbScan];
		float z32 = pfzEdge32[nPlumbScan32];

		//��ɫ
		FLOATCOLORRGBA clrEdge12 = pClrEdge12[nPlumbScan];
		FLOATCOLORRGBA clrEdge32 = pClrEdge32[nPlumbScan32];

		//���
		Scan(x12, x32, y, z12, z32, clrEdge12,clrEdge32, pCB, pZB);

		nPlumbScan++;
		nPlumbScan32++;

	}//end for y

	delete[] pnEdge12;
	delete[] pnEdge13;
	delete[] pnEdge32;
	delete[] pClrEdge12;
	delete[] pClrEdge13;
	delete[] pClrEdge32;
	delete[] pfzEdge12;
	delete[] pfzEdge13;
	delete[] pfzEdge32;
}

