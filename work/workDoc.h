// workDoc.h : interface of the CWorkDoc class

//

/////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_WORKDOC_H__6792600C_B5BC_42A1_8D6D_443938597B4A__INCLUDED_)

#define AFX_WORKDOC_H__6792600C_B5BC_42A1_8D6D_443938597B4A__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000

#include "cv.h"
#include "highgui.h"
#include "Calculate.h"

class CWorkDoc : public CDocument
{
protected: // create from serialization only
	CWorkDoc();
	DECLARE_DYNCREATE(CWorkDoc)

// Attributes
public:
	CvvImage m_img;
	CvvImage origin_img;
	CvvImage back_img;
	bool function1();

// Operations

public:

// Overrides

	// ClassWizard generated virtual function overrides

	//{{AFX_VIRTUAL(CWorkDoc)

	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

	//}}AFX_VIRTUAL



// Implementation

public:
	virtual ~CWorkDoc();
	void ResizeImage(double proportion);
	void ResizeImage();
	void DepartChannel(char color);
	void HistogramEquilibrium();
	void ImageSmoothing(int size);
	bool Fusion(double param);
	void RectangleMedianFilter(int size);
	void LaplasseOperator(int factor, int mould[]);
	void LaplasseOperatorBoard(int factor, int mould[]);
	void SegmentalProvessOperator(int first_x, int first_y, int secondx, int secondy);
	void DepartHSII();
	void DepartHSIS();
	void DepartHSIH();
	void AddGaussianNoise(double mu, double sigma, int k); 
	void AddSaltpeperNoise(double SNR);

//	calculate data function

	int Median(int *P, int size);
	int Min(int r, int g, int b);
	double GenerateGaussianNoise(double mu, double sigma);
	//void LaplasseTemplateA();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions

protected:

	//{{AFX_MSG(CWorkDoc)
	afx_msg void OnLeftRight();
	afx_msg void OnUpDown();
	afx_msg void Onresize120();
	afx_msg void Onresize110();
	afx_msg void Onresize80();
	afx_msg void Onresize90();
	afx_msg void OnRecover();
	afx_msg void Gchannel();
	afx_msg void Bchannel();
	afx_msg void Rchannel();
	afx_msg void SmoothFiltering();
	afx_msg void Onequilibrium();
	afx_msg bool OnOpenBackground();
	afx_msg void OnFusion8();
	afx_msg void OnFUSION5();
	afx_msg void OnFUSION2();
	afx_msg void OnMedianFilter();
	afx_msg void OnLaplasseOparator();
	afx_msg void OnLaplasseOparatorNagetive();
	afx_msg void OnSegmentalProvess1();
	afx_msg void OnHSII();
	afx_msg void OnHSIS();
	afx_msg void OnHSIH();
	afx_msg void OnSobel1();
	afx_msg void OnSobel2();
	afx_msg void OnLaplaceBoard1();
	afx_msg void OnLaplaceBoard2();
	afx_msg void OnSobelBoard1();
	afx_msg void OnSobelBoard2();
	afx_msg void OnGaussianNoise();
	afx_msg void OnSaltPepperNoise();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void reDraw();

	POSITION pos;
	CView* pView;
	double mag_factor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKDOC_H__6792600C_B5BC_42A1_8D6D_443938597B4A__INCLUDED_)
