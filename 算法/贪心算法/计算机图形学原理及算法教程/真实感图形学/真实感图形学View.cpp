// ��ʵ��ͼ��ѧView.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "��ʵ��ͼ��ѧ.h"

#include "��ʵ��ͼ��ѧDoc.h"
#include "��ʵ��ͼ��ѧView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "ZBuffer.h"
#include "BRender.h"
#include "TypedStack.h"
#include "Lighting.h"
/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
//�ӵ�
	VERTEX3D viewer = {0.0f,  0.0f,  8.0f};

	//�ӿڱ任�н��зŴ���, ��Ļλ�þ����ӵ�100����λ;
	//͸������(��Ļ����)Ϊ(250, 250)
	VIEWFINDER viewFinder = {100.0f,  8.0f,  8.0f,  {200,  200}};

	m_viewer = viewer;
	m_viewFinder = viewFinder;
}


	


CMyView::~CMyView()
{
delete m_pSphere0;
	delete m_pSphere1;
	delete m_pSphere2;
//	delete m_pSphere3;
//	delete m_pSphere4;
//	delete m_pSphere5;
	delete[] m_pLights;
	delete m_pCB;
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	m_pCB->SwapBuffer(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView printing

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

int CMyView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//
	//the first stage

	//��һ�׶�, �������������ù�Դ�Ͳ������ԣ���ɹ��ռ���
	
	//��һ��, ����һ�������
	m_pSphere0 = new CSphere(0.5f, 32, 32);

	//��¡�����
	m_pSphere1 = m_pSphere0->Clone();
	m_pSphere2 = m_pSphere0->Clone();
//	m_pSphere3 = m_pSphere0->Clone();
//	m_pSphere4 = m_pSphere0->Clone();
//	m_pSphere5 = m_pSphere0->Clone();

	//��֯����, ���м��α任

	//����һ�������ջ
	CTypedStack<CMatrix3d> matrixStack;
	//�任����
	CMatrix3d mGeometry;

	//��λ����
	mGeometry.RotateX(45.0f);
	matrixStack.Push(mGeometry);

	//��һ����
	mGeometry.Translate(-1.1f,  1.0f,  0.0f);
	m_pSphere0->Transform(mGeometry);
	
	mGeometry.Translate(1.1f,  0.0f,  0.0f);
	m_pSphere1->Transform(mGeometry);

	mGeometry.Translate(1.1f,  0.0f,  0.0f);
	m_pSphere2->Transform(mGeometry);

/*	//��һ����
	mGeometry.Translate(0.0f,  -1.4f,  0.0f);
	m_pSphere5->Transform(mGeometry);

	mGeometry.Translate(-1.1f,  0.0f,  0.0f);
	m_pSphere4->Transform(mGeometry);

	mGeometry.Translate(-1.1f,  0.0f,  0.0f);
	m_pSphere3->Transform(mGeometry);*/

	//����:
	CMatrix3d mn = matrixStack.Pop();

	
	//����Ķ��㷨��:
	m_pSphere0->TransVertexNormals(mn);
	m_pSphere1->TransVertexNormals(mn);
	m_pSphere2->TransVertexNormals(mn);
//	m_pSphere3->TransVertexNormals(mn);
//	m_pSphere4->TransVertexNormals(mn);
//	m_pSphere5->TransVertexNormals(mn);
	

	//�ڶ���:���ò��ʺ͹�Դ

	//����������Դ
	m_pLights = new CLightObj[2];

	//���õ�һյ��(�����)
	float amb_omni[4] = {0.2f,  0.2f,  0.2f,  1.0f};
	float dif_omni[4] = {1.0f,  1.0f,  1.0f,  1.0f};
	float spe_omni[4] = {1.0f,  1.0f,  1.0f,  1.0f};
	float pos_omni[4] = {0.0f,  0.0f,  8.0f,  1.0f};

	m_pLights[0].Lightfv(G3D_AMBIENT,   amb_omni);
	m_pLights[0].Lightfv(G3D_DIFFUSE,   dif_omni);
	m_pLights[0].Lightfv(G3D_SPECULAR,  spe_omni);
	m_pLights[0].Lightfv(G3D_POSITION,  pos_omni);
	//m_pLights[0].Lightf(G3D_CONSTANT_ATTENUATION,  2.5f);
	//m_pLights[0].Lightb(G3D_LIGHT_ON_OFF,  FALSE);

	//���õ�һյ��(�۹��)
	float amb_spot[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	float dif_spot[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	float spe_spot[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float pos_spot[4] = {0.0f, 8.0f, 8.0f, 1.0f};
	float dir_spot[4] = {0.0f, -1.0f, -1.0f, 1.0f};

	m_pLights[1].Lightfv(G3D_AMBIENT,  amb_spot);
	m_pLights[1].Lightfv(G3D_DIFFUSE,  dif_spot);
	m_pLights[1].Lightfv(G3D_SPECULAR,  spe_spot);
	m_pLights[1].Lightfv(G3D_POSITION,  pos_spot);
	m_pLights[1].Lightfv(G3D_SPOT_DIRECTION,  dir_spot);

	m_pLights[1].Lightf(G3D_SPOT_CUTOFF,  5.3f);
	m_pLights[1].Lightf(G3D_SPOT_EXPONENT, 50.0f);
	//m_pLights[1].Lightf(G3D_CONSTANT_ATTENUATION,  2.5f);
	//m_pLights[1].Lightb(G3D_LIGHT_ON_OFF,  FALSE);



	//������, �������
	//��ɫ����
	float ambMaterial[4] = {0.2f,  0.2f,  0.2f,  1.0f};
	float difMaterial[4] = {0.8f,  0.8f,  0.0f,  1.0f};
	float speMaterial[4] = {1.0f,  1.0f,  1.0f,  1.0f};

	float shininess = 50.0f;	


	//��
	//float ambMaterial[4] = {0.247f,  0.200f,  0.075f,  1.0f};
	//float difMaterial[4] = {0.752f,  0.606f,  0.226f,  1.0f};
	//float speMaterial[4] = {0.628f,  0.556f,  0.336f,  1.0f};
	//float shininess = 51.2f;	
	

	//���ò���
	m_material.Materialfv(G3D_FRONT,  G3D_AMBIENT,  ambMaterial);
	m_material.Materialfv(G3D_FRONT,  G3D_DIFFUSE,  difMaterial);
	m_material.Materialfv(G3D_FRONT,  G3D_SPECULAR,  speMaterial);
	m_material.Materialf(G3D_FRONT,   G3D_SHININESS,  shininess);

	
	//���Ĳ�, ���й��ռ���
	CLighting lighting;
	
	//����ֲ�����ģ��
	lighting.LightModelb(G3D_LIGHT_MODEL_LOCAL_VIEWER,  TRUE);

	//���ռ���
	lighting.Lighting(m_pSphere0,  m_material,  m_viewer,  m_pLights,  2);
	lighting.Lighting(m_pSphere1,  m_material,  m_viewer,  m_pLights,  2);
	lighting.Lighting(m_pSphere2,  m_material,  m_viewer,  m_pLights,  2);
	
//	lighting.Lighting(m_pSphere3,  m_material,  m_viewer,  m_pLights,  2);
//	lighting.Lighting(m_pSphere4,  m_material,  m_viewer,  m_pLights,  2);
//	lighting.Lighting(m_pSphere5,  m_material,  m_viewer,  m_pLights,  2);

	//��һ�׶��Ѿ����


	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//

	//       The second stage      

	//�ڶ��׶�, ��ʼ���Ƶ��ڴ�


	//��һ��, ��ʼ����ɫ������, ������Ȼ�����
	m_pCB = new CColorBuffer(410, 350);
	
	//��Ȼ�����, ����ɫ��������С����һ��
	CZBuffer* pZB = new CZBuffer(410,  350);
	pZB->InitAllDepth(500.0f);

	//�ڶ���,  ��ɫ
	CBRender renderer;

	//�߿�ģ��
	renderer.Render(m_pSphere0,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_WIRE);

	//����ģ��
	renderer.Render(m_pSphere1,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_FLAT);

	//�⻬����ģ��
	renderer.Render(m_pSphere2,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_GOURAUD_SMOOTH);

/*	//�߿�ģ��
	renderer.Render(m_pSphere3,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_WIRE);

	//����ģ��
	renderer.Render(m_pSphere4,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_FLAT);

	//�⻬����ģ��
	renderer.Render(m_pSphere5,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_GOURAUD_SMOOTH);*/
	
	delete pZB;
	return 0;
}
