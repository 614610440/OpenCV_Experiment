// workView.cpp : implementation of the CWorkView class
//

#include "stdafx.h"
#include "work.h"
#include <iostream>

#include "workDoc.h"
#include "workView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkView

IMPLEMENT_DYNCREATE(CWorkView, CView)

BEGIN_MESSAGE_MAP(CWorkView, CView)
	//{{AFX_MSG_MAP(CWorkView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkView construction/destruction

CWorkView::CWorkView()
{
	// TODO: add construction code here

}

CWorkView::~CWorkView()
{
}

BOOL CWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWorkView drawing

void CWorkView::OnDraw(CDC* pDC)
{
	CWorkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rect;
	GetClientRect(&rect);
	if(pDoc->m_img.GetImage() != NULL)
	{
		rect.right = rect.left + pDoc->m_img.Width();
		rect.bottom = rect.top + pDoc->m_img.Height();
		pDoc->m_img.DrawToHDC(pDC->GetSafeHdc(), &rect);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWorkView printing

BOOL CWorkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWorkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWorkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWorkView diagnostics

#ifdef _DEBUG
void CWorkView::AssertValid() const
{
	CView::AssertValid();
}

void CWorkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWorkDoc* CWorkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkDoc)));
	return (CWorkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkView message handlers
