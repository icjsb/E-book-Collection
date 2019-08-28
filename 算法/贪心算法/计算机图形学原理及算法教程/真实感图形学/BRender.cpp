/////////////////////////////////////////////////////////////////////////////////
//	
// CBRender.cpp: implementation of the CBRender class.
#include "stdafx.h"
#include "BRender.h"

#include "ViewFinder.h"
#include "BLine.h"
#include "BTriangle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBRender::CBRender()
{

}

CBRender::~CBRender()
{

}

//��ɫ����, ������Ƚ�������
//pObj---------��ά�������   (��������)
//viewer------�ӵ�(��������������ϵ)
//viewFinder--ȡ����
//pCB---------��ɫ����
//pZB---------��Ȼ���
//dwRop-------��ɫģʽ
void CBRender::Render(CObject3d* pObj,  VERTEX3D viewer,  VIEWFINDER viewFinder,  CColorBuffer* pCB,  CZBuffer* pZB,  DWORD dwRop)
{
	ASSERT(pCB);
	ASSERT(pZB);
	//��һ��, ��ȡ����Ԫ�صĸ���
	
	//���嶥��ĸ���
	int nNumVertex = pObj->GetVertexListSize();
	

	//�洢����������任Ϊ�۲������Ľ��
	HOMOCOORD* pvInView = new HOMOCOORD[nNumVertex];

	if(pvInView == NULL)
	{
		::AfxMessageBox("�ڴ����ʧ��!");
		exit(1);
	}
	
	//////////////////////////////////////////
	//�ڶ���:��ɴ��������굽�۲�����ı任

	//�۲����(��ʼ��Ϊ��λ����)
	CMatrix3d mWatch;

	//��ȡ�۲����
	mWatch.Watch(viewer.x,  viewer.y,  viewer.z);

	int i;
	//����������ϵ�ĵ�任Ϊ�۲�����ϵ�ĵ�
	for(i = 0; i < nNumVertex; i++)
	{
		//��ȡһ��������������
		//������任������ȡ�۲�����
		pvInView[i] = mWatch.Transform(pObj->m_vList[i].m_coord);
	}//end for i (1st)

	//
	//////////////////////////////////////////
	//������:��ɴӹ۲����굽��Ļ����ı任

	//�м�ʡ�������¼�������:
	//��һ, ͸�Ӽ���;���, �豸������
	
	//����任֮���
	POINT* pPtOnScrn = new POINT[nNumVertex];

	if(pPtOnScrn == NULL)
	{
		::AfxMessageBox("�ڴ����ʧ��!");
		exit(1);
	}

	//�����ӿڱ任����.
	CViewFinder  vf(viewFinder);
	//ִ��������͸�ӱ任���ӿڱ任
	for(i = 0; i < nNumVertex; i++)
		pPtOnScrn[i] = vf.Perspective(pvInView[i]);

	//���Ĳ�, �ù۲�����ϵ�е� z ������������Ļ����ϵ�µ� z ����
	//����һ�����ο�Խ

	//������������ȡʵ�����, 
	//ע��, CViewFinder���Perspective()�����������º������ѭ����ͬ�ĳ�������;
	//�ڼ�������Щ�ظ�, ���۲������ڸ��Ӹ��ӵ�ϵͳ�л���������Ӧ��.
	//���, ���ǲ���ͨ��CViewFinder���Perspective()�������ѹ۲�����任Ϊ�ȼ۵���ά����
	//

	for(i = 0; i < nNumVertex; i++)
	{
		float z = pvInView[i].z;
		float w = pvInView[i].w;

		if(ABS(w) < 0.00001f)
			z = 100000.0f;
		else
			z /= w;
		pvInView[i].z = z;
	}

	//���岽, ����

	//����ѡ����
	switch(dwRop)
	{
		case G3D_RENDER_VERTICES:
			Vertexize(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;

		case G3D_RENDER_WIRE:
			FlatWirize(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;

		case G3D_RENDER_WIRE_LIGHTED:
			GouraudWirize(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;

		case G3D_RENDER_FLAT:
			Flat(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;

		case G3D_RENDER_GOURAUD_SMOOTH:
			Gouraud(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;
	}
}

//���Ƶ�ģ��

void CBRender::Vertexize(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//�������
	int nNumPt = pObj->GetVertexListSize();
	
	//���Ƶ�ģ��
	for(int i = 0; i < nNumPt; i++)
	{
		//��ɫ(R, G, B, A)
		float fRed = pObj->m_vList[i].m_clr.red;
		float fGreen = pObj->m_vList[i].m_clr.green;
		float fBlue = pObj->m_vList[i].m_clr.blue;
		float fAlpha = pObj->m_vList[i].m_clr.alpha;

		//����
		int x = pPtOnScrn[i].x;
		int y = pPtOnScrn[i].y;

		//���

		float z = pvInView[i].z;
		
		//�������е����
		float zInBuffer = pZB->GetDepth(x,  y);
		
		//�����ǰ���z����С����Ȼ������е���ͬλ��z������
		if(z < zInBuffer)
		{
			//����ɫ�������л��Ƶ�һ����
			pCB->SetPixel(x,  y,  fRed,  fGreen,  fBlue,  fAlpha); 

			//������Ȼ�������ֵ
			pZB->SetDepth(x,  y,  z);
		
		}
		
	} 

}

//�����߿�ģ��
//pObj---------��ά�������
//pPtOnScrn---����͸�ӵ���Ļ�ϵĵ�
//pvInView----�۲�����ϵ�е�����
//pCB---------��ɫ����
//pZB---------��Ȼ���
void CBRender::FlatWirize(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//�������
	int nNumEdge = pObj->GetEdgeListSize();
	
	//���ƹ���:ֱ�߻�Ԫ
	CBLine bl;
	//���Ƶ�ɫģ��
	for(int i = 0; i < nNumEdge; i++)
	{
		//��ȡ�ߵĶ�������
		int n1 = pObj->m_eList[i].m_nStart;
		int n2 = pObj->m_eList[i].m_nEnd;

		//�˵����
		float z1 = pvInView[n1].z;
		float z2 = pvInView[n2].z;
		
		//�ɶ�������ߵ���ɫ, �������ⲿ�����ߵ���ɫ
		BOOL bAutoColor = pObj->GetAutoColorProperty();

		if(bAutoColor)
		{

			//��ȡ��һ���������ɫ���������ߵ���ɫ
			FLOATCOLORRGBA rgba = pObj->m_vList[n1].m_clr;
			//����
			bl.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  z1,  z2,   rgba,  rgba,  pCB,  pZB);
		}
		else
		{
			FLOATCOLORRGBA rgba = pObj->m_eList[i].m_clr;
			bl.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  z1,  z2,   rgba,  rgba,  pCB,  pZB);
		}
	}
}


//�����߿�ģ��
//pObj---------��ά�������
//pPtOnScrn---����͸�ӵ���Ļ�ϵĵ�
//pvInView----�۲�����ϵ�е�����
//pCB---------��ɫ����
//pZB---------��Ȼ���
void CBRender::GouraudWirize(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//�������
	int nNumEdge = pObj->GetEdgeListSize();
	
	//���ƹ���:ֱ�߻�Ԫ
	CBLine bl;
	//���Ƶ�ɫģ��
	for(int i = 0; i < nNumEdge; i++)
	{
		//��ȡ�ߵĶ�������
		int n1 = pObj->m_eList[i].m_nStart;
		int n2 = pObj->m_eList[i].m_nEnd;

		//�˵����
		float z1 = pvInView[n1].z;
		float z2 = pvInView[n2].z;
		
		//��ȡ������ĸ�����ɫ
		FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
		FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
		
		//����
		bl.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  z1,  z2,  rgba1,  rgba2,  pCB,  pZB);

	}
}

//����ʵ��ģ��, Flatģ��
//pObj---------��ά�������
//pPtOnScrn---����͸�ӵ���Ļ�ϵĵ�
//pvInView----�۲�����ϵ�е�����
//pCB---------��ɫ����
//pZB---------��Ȼ���
void CBRender::Flat(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//����С�����
	int nNumFacet = pObj->GetFacetListSize();
	
	//����ƹ���: �����λ�Ԫ
	CBTriangle bt;

	//�ɶ������С�����ɫ, �������ⲿ����С�����ɫ
	BOOL bAutoColor = pObj->GetAutoColorProperty();

	//����, ��ѭ��
	for(int i = 0; i < nNumFacet; i++)
	{
		//��ȡС��Ķ�����
		int nNumVertex = pObj->m_sList[i].m_avIndex.GetSize();
		if(nNumVertex == 3)
		{
			//��ȡ����������
			int n1 = pObj->m_sList[i].m_avIndex[0];
			int n2 = pObj->m_sList[i].m_avIndex[1];
			int n3 = pObj->m_sList[i].m_avIndex[2];

			//�������
			float z1 = pvInView[n1].z;
			float z2 = pvInView[n2].z;
			float z3 = pvInView[n3].z;

			//С����ɫ
			FLOATCOLORRGBA rgba;
				
			//��ȡ������ɫ
			if(bAutoColor)
			{
				//һ���, ���õ�һ���������ɫ����ʾС�����ɫ
				//���ģ�͵Ķ��㰲��Ҫ��Ƚϸ�
				//���, ���ǲ�������������ɫ��ƽ��ֵ����ʾС�����ɫ
				//�ڹ���������, ��������Ҳ�ǿ��Խ��ܵ�
				FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
				FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
				FLOATCOLORRGBA rgba3 = pObj->m_vList[n3].m_clr;

				//������ɫ��һ��Ӧ�����ⲿ����
				rgba.red = (rgba1.red + rgba2.red + rgba3.red) / 3.0f;
				rgba.green = (rgba1.green + rgba2.green + rgba3.green) / 3.0f;
				rgba.blue = (rgba1.blue + rgba2.blue +  rgba3.blue) / 3.0f;
				
				//͸����, ����Ҳ�򵥵ش����ͬһֵ
				rgba.alpha = (rgba1.alpha + rgba2.alpha +  rgba3.alpha) / 3.0f;

			}
			//��ȡС����ɫ
			else
				rgba = pObj->m_sList[i].m_clr;

			//����
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  pPtOnScrn[n3], z1,  z2,  z3,  rgba,  rgba,  rgba,  pCB,  pZB);

		}

		else if(nNumVertex == 4)
		{
			//��ȡ����������
			int n1 = pObj->m_sList[i].m_avIndex[0];
			int n2 = pObj->m_sList[i].m_avIndex[1];
			int n3 = pObj->m_sList[i].m_avIndex[2];
			int n4 = pObj->m_sList[i].m_avIndex[3];

			//�������
			float z1 = pvInView[n1].z;
			float z2 = pvInView[n2].z;
			float z3 = pvInView[n3].z;
			float z4 = pvInView[n4].z;

			//С����ɫ
			FLOATCOLORRGBA rgba;
	
			//��ȡ������ɫ
			if(bAutoColor)
			{
				//һ���, ���õ�һ���������ɫ����ʾС�����ɫ
				//���ģ�͵Ķ��㰲��Ҫ��Ƚϸ�
				//���, ���ǲ�������������ɫ��ƽ��ֵ����ʾС�����ɫ
				//�ڹ���������, ��������Ҳ�ǿ��Խ��ܵ�
				FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
				FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
				FLOATCOLORRGBA rgba3 = pObj->m_vList[n3].m_clr;
				FLOATCOLORRGBA rgba4 = pObj->m_vList[n4].m_clr;
			
				rgba.red = (rgba1.red + rgba2.red + rgba3.red + rgba4.red) / 4.0f;
				rgba.green = (rgba1.green + rgba2.green + rgba3.green + rgba4.green) / 4.0f;
				rgba.blue = (rgba1.blue + rgba2.blue +  rgba3.blue + rgba4.blue) / 4.0f;
				
				//͸����, ����Ҳ�򵥵ش����ͬһֵ
				rgba.alpha = (rgba1.alpha + rgba2.alpha + rgba3.alpha + rgba4.alpha) / 4.0f;

			}
			//��ȡС����ɫ
			else
				rgba = pObj->m_sList[i].m_clr;


			//ϸ���ı���, ����ɻ���
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  pPtOnScrn[n3],  z1,  z2,  z3,  rgba,  rgba,  rgba,  pCB,  pZB);
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n3],  pPtOnScrn[n4],  z1,  z3,  z4,  rgba,  rgba,  rgba,  pCB,  pZB);

		}
		
		}

}



//����ʵ��ģ��, Gouraudģ��
//pObj---------��ά�������
//pPtOnScrn---����͸�ӵ���Ļ�ϵĵ�
//pvInView----�۲�����ϵ�е�����
//pCB---------��ɫ����
//pZB---------��Ȼ���
void CBRender::Gouraud(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//����С�����
	int nNumFacet = pObj->GetFacetListSize();
	
	//����ƹ���: �����λ�Ԫ
	CBTriangle bt;

	//����, ��ѭ��
	for(int i = 0; i < nNumFacet; i++)
	{
		//��ȡС��Ķ�����
		int nNumVertex = pObj->m_sList[i].m_avIndex.GetSize();
		if(nNumVertex == 3)
		{
			//��ȡ����������
			int n1 = pObj->m_sList[i].m_avIndex[0];
			int n2 = pObj->m_sList[i].m_avIndex[1];
			int n3 = pObj->m_sList[i].m_avIndex[2];

			//��ȡ������ɫ
			FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
			FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
			FLOATCOLORRGBA rgba3 = pObj->m_vList[n3].m_clr;

			//�������
			float z1 = pvInView[n1].z;
			float z2 = pvInView[n2].z;
			float z3 = pvInView[n3].z;

			//����
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  pPtOnScrn[n3], z1,  z2,  z3,  rgba1,  rgba2,  rgba3,  pCB,  pZB);

		}//end if (nNumVertex == 3)
		else if(nNumVertex == 4)
		{
			//��ȡ����������
			int n1 = pObj->m_sList[i].m_avIndex[0];
			int n2 = pObj->m_sList[i].m_avIndex[1];
			int n3 = pObj->m_sList[i].m_avIndex[2];
			int n4 = pObj->m_sList[i].m_avIndex[3];

			//��ȡ������ɫ
			//��ȡ������ɫ
			FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
			FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
			FLOATCOLORRGBA rgba3 = pObj->m_vList[n3].m_clr;
			FLOATCOLORRGBA rgba4 = pObj->m_vList[n4].m_clr;

			//�������
			float z1 = pvInView[n1].z;
			float z2 = pvInView[n2].z;
			float z3 = pvInView[n3].z;
			float z4 = pvInView[n4].z;

			//ϸ���ı���, ����ɻ���
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  pPtOnScrn[n3],  z1,  z2,  z3,  rgba1,  rgba2,  rgba3,  pCB,  pZB);
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n3],  pPtOnScrn[n4],  z1,  z3,  z4,  rgba1,  rgba3,  rgba4,  pCB,  pZB);

		}
	
	}
}

