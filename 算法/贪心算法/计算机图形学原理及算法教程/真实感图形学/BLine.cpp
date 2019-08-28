/////////////////////////////////////////////////////////////////////////////////
//	
// BLine.cpp: implementation of the CBLine class.
#include "stdafx.h"
#include "BLine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBLine::CBLine()
{
}

CBLine::~CBLine()
{
}

//����һ��ֱ��,ֱ�ߵĿ��Ϊ1,ֱ�ߵ���ɫ��ֱ�������˵����ɫ��ͬ����
//ע��,������ɫ����ЧֵΪ[0,1]�����ڵĸ���С��
//��Windows���Ӧ,���㷨Ҳ���������һ����(x2,y2)
//z1,z2Ϊ��ǰ������ֵ
//pCB,pZB�ֱ�Ϊ��ɫ�������Ȼ���
//ע��,��(x1,y1)--(x2,y2)��(x2,y2)--(x1,y1)����Щ��ͬ.
//����:�ú������Ƶ�ֱ��(����λ��)��Windows��LineTo()�������ƵĽ������ȫһ�µ�
void CBLine::Draw(int x1,int y1,  int x2, int y2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB)
{
	//���˵���ˮƽƫ�����ʹ�ֱƫ����
	int nDx = x2 - x1;	
	int nDy = y2 - y1;

	//���˵���ˮƽ����ʹ�ֱ����
	int nIx = ABS(nDx);
	int nIy = ABS(nDy);

	//��㲽��(������ֵ)
	int nInc = MAX(nIx,nIy);

	//ֱ�ߵ�ǰ�����ɫ
	float fPlotR = clr1.red, fPlotG = clr1.green, fPlotB = clr1.blue, fPlotA = clr1.alpha; 

	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	//��Ҫ������,��ʼ
	
	//�������е����
	float zInBuffer = pZB->GetDepth(x1,y1);
	//��ǰ���
	float z = z1;
	
	//�����ǰ���z����С����Ȼ������е���ͬλ��z������
	if(z < zInBuffer)
	{
		//����ɫ�������л��Ƶ�һ����
		pCB->SetPixel(x1, y1, fPlotR, fPlotG, fPlotB, fPlotA); 

		//������Ȼ�������ֵ
		pZB->SetDepth(x1, y1, z);
	
	}
	
	if(nInc < 2) return;

	//��ֱ�ߵ��������
	float fIncZ = (z2 - z1) / nInc;

	//����	
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////


	//�����ж��Ƿ���nJudgeX,nJudgeY��������ǰ��
	int nJudgeX = -nIy, nJudgeY = -nIx;

	//ͨ����������õ��ĵ�ǰ��
	int x = x1, y = y1;
	
	//��ʼ������������
	//����Bresenham�㷨.������,���ǽ��㷨���иĽ�,
	//ʹ���������б�ʵ�ֱ�߶��ܻ���,���һ��Ʒ���ʼ��Ϊ�������Ƶ��յ�

	//��Windows���Ӧ,���㷨Ҳ���������һ����(x2,y2)
	nInc--;

	//ע��,������2�ڼ�����в�����λʵ��
	//Bresenham�㷨
	int nTwoIx = 2 * nIx, nTwoIy = 2 * nIy;

	//��ɫ����
	float fIncR = (clr2.red - fPlotR) / nInc;
	float fIncG = (clr2.green - fPlotG) / nInc;
	float fIncB = (clr2.blue - fPlotB) / nInc;
	float fIncA = (clr2.alpha - fPlotA) / nInc;


	//��ʼ��������
	for(int i = 0;i < nInc; i++)
	{
		nJudgeX += nTwoIx;
		nJudgeY += nTwoIy;

		//ͨ������������ĵ�ǰ���Ƿ�����ֱ���ϵĵ�
		BOOL bPlot = FALSE;

		//��� nJudgeX ����
		if(nJudgeX >= 0)
		{
			bPlot = TRUE;
			nJudgeX -= nTwoIy;

			//�����������ֱ��ͳһ����
			if(nDx > 0)x++;
			else if(nDx < 0)x--;
		}

		//��� nJudgeY ����
		if(nJudgeY >= 0)
		{
			bPlot = TRUE;
			nJudgeY -= nTwoIx;

			//�����������ֱ��ͳһ����
			if(nDy > 0)y++;
			else if(nDy < 0)y--;
		}
		//�����ǰ����ֱ����
		if(bPlot)
		{
			fPlotR += fIncR;
			fPlotG += fIncG;
			fPlotB += fIncB;
			fPlotA += fIncA;
			
			////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////
			//��Ҫ������,��ʼ

			z += fIncZ; 
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
}


void CBLine::Draw(POINT pt1, POINT pt2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB)
{
	Draw(pt1.x, pt1.y, pt2.x, pt2.y, z1, z2, clr1, clr2, pCB, pZB);
}