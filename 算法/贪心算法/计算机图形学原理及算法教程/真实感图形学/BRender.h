// BRender.h: interface for the BRender class.
#ifndef _CBRENDER_H
#define _CBRENDER_H

#include "Object3d.h"
#include "ColorBuffer.h"
#include "ZBuffer.h"

class CBRender  
{
public:
	CBRender();
	virtual ~CBRender();

public:

	//��ɫ
	void Render(CObject3d* pObj, VERTEX3D viewer, VIEWFINDER viewFinder, CColorBuffer* pCB, CZBuffer* pZB, DWORD dwRop);
private:

	//����ģ��
	void Vertexize(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);
	
	//�߿�ģ��
	void FlatWirize(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);
	void GouraudWirize(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);

	//ʵ��ģ��
	void Flat(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);
	void Gouraud(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);

};

#endif
