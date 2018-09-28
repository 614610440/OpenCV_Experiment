// workDoc.cpp : implementation of the CWorkDoc class
//

#include "stdafx.h"
#include "work.h"

#include <iostream>

#include "workDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkDoc

IMPLEMENT_DYNCREATE(CWorkDoc, CDocument)

BEGIN_MESSAGE_MAP(CWorkDoc, CDocument)
	//{{AFX_MSG_MAP(CWorkDoc)
	ON_COMMAND(ID_MENUITEM32771, OnLeftRight)
	ON_COMMAND(ID_MENUITEM32772, OnUpDown)
	ON_COMMAND(resize120, Onresize120)
	ON_COMMAND(resize110, Onresize110)
	ON_COMMAND(resize80, Onresize80)
	ON_COMMAND(resize90, Onresize90)
	ON_COMMAND(recover_img, OnRecover)
	ON_COMMAND(G_channel, Gchannel)
	ON_COMMAND(B_channel, Bchannel)
	ON_COMMAND(R_channel, Rchannel)
	ON_COMMAND(smooth_filtering, SmoothFiltering)
	ON_COMMAND(Histogram_equilibrium, Onequilibrium)
	ON_COMMAND(ID_MENUITEM32788, OnOpenBackground)
	ON_COMMAND(FUSION8, OnFusion8)
	ON_COMMAND(FUSION5, OnFUSION5)
	ON_COMMAND(FUSION2, OnFUSION2)
	ON_COMMAND(ID_MENUITEM32794, OnMedianFilter)
	ON_COMMAND(LAPLASEEOPRATOR, OnLaplasseOparator)
	ON_COMMAND(ID_MENUITEM32796, OnLaplasseOparatorNagetive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkDoc construction/destruction

CWorkDoc::CWorkDoc()
{
	// TODO: add one-time construction code here
	mag_factor = 1;
}

CWorkDoc::~CWorkDoc()
{
}

BOOL CWorkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWorkDoc serialization

void CWorkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		std::cout<<"test"<<std::endl;
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here

		std::cout<<"test1"<<std::endl;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWorkDoc diagnostics

#ifdef _DEBUG
void CWorkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWorkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);


}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkDoc commands

BOOL CWorkDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	m_img.Load(lpszPathName);

	origin_img.CopyOf(m_img);

	//function1();
	
	return TRUE;
}

bool CWorkDoc::function1()
{
	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;

	int  wp = inputRGBImg->widthStep;

	for(int i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{
			int r = data[i * wp + 3 * j];
			int g = data[i * wp + 3 * j + 1];
			int b = data[i * wp + 3 * j + 2];
		}
	}

	return true;
}

void CWorkDoc::OnLeftRight() 
{
	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;

	CvvImage cimg;
    cimg.CopyOf(m_img);

	IplImage* inputRGBImg2 = cimg.GetImage();
	uchar *data2 = (uchar *)inputRGBImg2->imageData;

	int  wp = inputRGBImg->widthStep;

	for(int i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{
			data[i * wp + 3 * (inputRGBImg->width-1-j)] = data2[i * wp + 3 * j];
			data[i * wp + 3 * (inputRGBImg->width-1-j) + 1] = data2[i * wp + 3 * j + 1];
			data[i * wp + 3 * (inputRGBImg->width-1-j) + 2] = data2[i * wp + 3 * j + 2];
		}
	}

	reDraw();
}

void CWorkDoc::OnUpDown()
{
	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;

	CvvImage cimg;

    cimg.CopyOf(m_img);

	IplImage* inputRGBImg2 = cimg.GetImage();
	uchar *data2 = (uchar *)inputRGBImg2->imageData;

	int  wp = inputRGBImg->widthStep;

	for(int i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{
			data[(inputRGBImg->height-1-i) * wp + 3 * j] = data2[i * wp + 3 * j];
			data[(inputRGBImg->height-1-i) * wp + 3 * j + 1] = data2[i * wp + 3 * j + 1];
			data[(inputRGBImg->height-1-i) * wp + 3 * j + 2] = data2[i * wp + 3 * j + 2];
		}
	}

	reDraw();
}

void CWorkDoc::reDraw()
{
	pos = GetFirstViewPosition();
	pView = GetNextView(pos);
	pView->Invalidate();
}

void CWorkDoc::Onresize120() 
{
	// TODO: Add your command handler code here
	mag_factor *= 1.2;
	ResizeImage();
	//ImageSmoothing();
	reDraw();
}

void CWorkDoc::Onresize110() 
{
	// TODO: Add your command handler code here
	mag_factor *= 1.1;
	ResizeImage();
	//ImageSmoothing();
	reDraw();
}

void CWorkDoc::Onresize80() 
{
	// TODO: Add your command handler code here
	mag_factor *= 0.8;
	ResizeImage();
	reDraw();
}

void CWorkDoc::Onresize90() 
{
	// TODO: Add your command handler code here
	mag_factor *= 0.9;
	//ResizeImage(0.9);
	ResizeImage();
	reDraw();
}

void CWorkDoc::ResizeImage(double proportion)
{
	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;
	IplImage* Img2;
	CvSize size;	
	size.width = inputRGBImg->width*proportion;
	size.height = inputRGBImg->height*proportion;	
	Img2 = cvCreateImage(size, inputRGBImg->depth, inputRGBImg->nChannels);	
	uchar *data2 = (uchar *)Img2->imageData;
	int  wp = inputRGBImg->widthStep;
	int  wp2 = Img2->widthStep;
	//cvResize(inputRGBImg, Img2, CV_INTER_CUBIC);

	for(int i = 0; i < Img2->height; i++)
	{
		for(int j = 0; j < Img2->width; j++)
		{
			data2[i * wp2 + 3 * j] = data[int(i/proportion) * wp + 3 * int(j/proportion)];
			data2[i * wp2 + 3 * j + 1] = data[int(i/proportion) * wp + 3 * int(j/proportion) + 1];
			data2[i * wp2 + 3 * j + 2] = data[int(i/proportion) * wp + 3 * int(j/proportion) + 2];
		}
	}
	*data = *data2;
	*inputRGBImg = *Img2;
}

void CWorkDoc::ResizeImage()
{
	IplImage* inputRGBImg = origin_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;
	IplImage* Img2;
	CvSize size;	
	size.width = inputRGBImg->width*mag_factor;
	size.height = inputRGBImg->height*mag_factor;	
	Img2 = cvCreateImage(size, inputRGBImg->depth, inputRGBImg->nChannels);	
	uchar *data2 = (uchar *)Img2->imageData;
	int  wp = inputRGBImg->widthStep;
	int  wp2 = Img2->widthStep;
	//cvResize(inputRGBImg, Img2, CV_INTER_CUBIC);

	for(int i = 0; i < Img2->height; i++)
	{
		for(int j = 0; j < Img2->width; j++)
		{
			data2[i * wp2 + 3 * j] = data[int(i/mag_factor) * wp + 3 * int(j/mag_factor)];
			data2[i * wp2 + 3 * j + 1] = data[int(i/mag_factor) * wp + 3 * int(j/mag_factor) + 1];
			data2[i * wp2 + 3 * j + 2] = data[int(i/mag_factor) * wp + 3 * int(j/mag_factor) + 2];
		}
	}
	IplImage* m_inputRGBImg = m_img.GetImage();
	uchar *m_data = (uchar *)m_inputRGBImg->imageData;
	*m_data = *data2;
	*m_inputRGBImg = *Img2;
}

void CWorkDoc::SmoothFiltering() 
{
	// TODO: Add your command handler code here
	ImageSmoothing(9);
	reDraw();
}

void CWorkDoc::ImageSmoothing(int size)
{
	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;
	int wp = inputRGBImg->widthStep;
	int size0 = size/2;	//	range
	CvvImage cimg;

    cimg.CopyOf(m_img);

	IplImage* inputRGBImg2 = cimg.GetImage();
	uchar *data2 = (uchar *)inputRGBImg2->imageData;

	for(int i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{
			int R = 0, G = 0, B = 0;

			for(int h = i-size0, h0; h<=i+size0; h++)
			{
				for(int w = j-size0, w0; w<=j+size0; w++ )
				{
					if(h<0) h0 = 0;
					else if(h>inputRGBImg->height-1) h0=inputRGBImg->height-1;
					else h0 = h;

					if(w<0) w0 = 0;
					else if(w>inputRGBImg->width-1) w0 = inputRGBImg->width-1;
					else w0 = w;

					R += data2[h0 * wp + 3 * w0];
					G += data2[h0 * wp + 3 * w0 + 1];
					B += data2[h0 * wp + 3 * w0 + 2];
				}
			}

			data[i * wp + 3 * j] = R/(size*size);
			data[i * wp + 3 * j + 1] = G/(size*size);
			data[i * wp + 3 * j + 2] = B/(size*size);
		}
	}
}

void CWorkDoc::OnRecover() 
{
	m_img.CopyOf(origin_img);
	mag_factor = 1;
	reDraw();
}

void CWorkDoc::Rchannel() 
{
	// TODO: Add your command handler code here
	DepartChannel('R');
	reDraw();
	
}

void CWorkDoc::Gchannel() 
{
	// TODO: Add your command handler code here
	DepartChannel('G');
	reDraw();
}

void CWorkDoc::Bchannel() 
{
	// TODO: Add your command handler code here
	DepartChannel('B');
	reDraw();
}

void CWorkDoc::DepartChannel(char color)
{
	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;

	int  wp = inputRGBImg->widthStep;

	for(int i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{	
			if(color != 'B')
				data[(inputRGBImg->height-1-i) * wp + 3 * j] = 0;

			if(color != 'G')
				data[(inputRGBImg->height-1-i) * wp + 3 * j + 1] = 0;

			if(color != 'R')
				data[(inputRGBImg->height-1-i) * wp + 3 * j + 2] = 0;
		}
	}
}

void CWorkDoc::HistogramEquilibrium() 
{
	// TODO: Add your command handler code here
	int R[256] = {0}, G[256] = {0}, B[256] = {0},
		SR[256], SG[256], SB[256];

	double RP[256], GP[256], BP[256], 
		   sR[256], sG[256], sB[256];


	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;

	int  wp = inputRGBImg->widthStep;

	for(int i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{	
			int b = data[(inputRGBImg->height-1-i) * wp + 3 * j];
			int g = data[(inputRGBImg->height-1-i) * wp + 3 * j + 1];
			int r = data[(inputRGBImg->height-1-i) * wp + 3 * j + 2];
			R[r]++;
			G[g]++;
			B[b]++;
		}
	}
	
	int size = inputRGBImg->height*inputRGBImg->width;

	for(i=0; i<=255; i++)
	{
		RP[i] = 1.0 *R[i]/size;
		GP[i] = 1.0 *G[i]/size;
		BP[i] = 1.0 *B[i]/size;
	}

	sR[0] = RP[0];
	sB[0] = BP[0];
	sG[0] = GP[0];

	for(i=1; i<=255; i++)
	{
		sR[i] = sR[i-1] + RP[i];
		sG[i] = sG[i-1] + GP[i];
		sB[i] = sB[i-1] + BP[i];
	}

	for(i=0; i<=255; i++)
	{
		SR[i] = 255*sR[i] + 0.5;
		SG[i] = 255*sG[i] + 0.5;
		SB[i] = 255*sB[i] + 0.5;
	}

	for(i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{	
			int b = data[(inputRGBImg->height-1-i) * wp + 3 * j];
			int g = data[(inputRGBImg->height-1-i) * wp + 3 * j + 1];
			int r = data[(inputRGBImg->height-1-i) * wp + 3 * j + 2];
			data[(inputRGBImg->height-1-i) * wp + 3 * j] = SB[b];
			data[(inputRGBImg->height-1-i) * wp + 3 * j + 1] = SG[g];
			data[(inputRGBImg->height-1-i) * wp + 3 * j + 2] = SR[r];
		}
	}
}

void CWorkDoc::Onequilibrium() 
{
	// TODO: Add your command handler code here
	HistogramEquilibrium();
	reDraw();
}

bool CWorkDoc::OnOpenBackground() 
{
	CFileDialog dlg(TRUE,"",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"(*.bmp; *.jpg; *.png)|*.bmp; *.jpg; *.png||");
	CString fileName;
	 if(dlg.DoModal() == IDOK)
	 {
		fileName = dlg.GetPathName();
	 }

	 if (!CDocument::OnOpenDocument(fileName))
		return FALSE;

	back_img.Load(fileName);
	return TRUE;
}

void CWorkDoc::OnFusion8() 
{
	if(Fusion(0.8))
		reDraw();
}

void CWorkDoc::OnFUSION5() 
{
	if(Fusion(0.5))
		reDraw();
}


void CWorkDoc::OnFUSION2() 
{
	if(Fusion(0.2))
		reDraw();
}

bool CWorkDoc::Fusion(double param)
{
	if(back_img.GetImage() == NULL)
	{
		AfxMessageBox("��ѡ�񱳾�ͼƬ");
		return false;
	}

	IplImage* m_RGBImg = m_img.GetImage();
	uchar *data = (uchar *)m_RGBImg->imageData;
	IplImage* Img2  = back_img.GetImage();
	uchar *data2 = (uchar *)Img2->imageData;

	int  wp = m_RGBImg->widthStep;
	int  wp2 = Img2->widthStep;
	double height_proportion = 1.0 * Img2->height / m_RGBImg->height;
	double width_proportion = 1.0 * Img2->width / m_RGBImg->width;

	for(int i = 0; i < m_RGBImg->height; i++)
	{
		for(int j = 0; j < m_RGBImg->width; j++)
		{
			data[i * wp + 3 * j] = param * data[i * wp + 3 * j] + (1-param) * data2[int(i*height_proportion) * wp2 + 3 * int(j*width_proportion)];
			data[i * wp + 3 * j + 1] = param * data[i * wp + 3 * j + 1] + (1-param) * data2[int(i*height_proportion) * wp2 + 3 * int(j*width_proportion) + 1];
			data[i * wp + 3 * j + 2] = param * data[i * wp + 3 * j + 2] + (1-param) * data2[int(i*height_proportion) * wp2 + 3 * int(j*width_proportion) + 2];
		}
	}
	return true;
}


void CWorkDoc::OnMedianFilter() 
{
	// TODO: Add your command handler code here
	RectangleMedianFilter(3);
	reDraw();
}

void CWorkDoc::RectangleMedianFilter(int size)
{
	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;
	int wp = inputRGBImg->widthStep;
	int size0 = size/2;	//	range
	CvvImage cimg;

    cimg.CopyOf(m_img);

	IplImage* inputRGBImg2 = cimg.GetImage();
	uchar *data2 = (uchar *)inputRGBImg2->imageData;

	for(int i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{
			int *R = (int*)malloc(sizeof(int) * size * size),
				*G = (int*)malloc(sizeof(int) * size * size),
				*B = (int*)malloc(sizeof(int) * size * size);

			int sit = 0;

			for(int h = i-size0, h0; h<=i+size0; h++)
			{
				for(int w = j-size0, w0; w<=j+size0; w++ )
				{
					if(h<0) h0 = 0;
					else if(h>inputRGBImg->height-1) h0=inputRGBImg->height-1;
					else h0 = h;

					if(w<0) w0 = 0;
					else if(w>inputRGBImg->width-1) w0 = inputRGBImg->width-1;
					else w0 = w;

					R[sit] = data2[h0 * wp + 3 * w0];
					G[sit] = data2[h0 * wp + 3 * w0 + 1];
					B[sit] = data2[h0 * wp + 3 * w0 + 2];
					sit++;
				}
			}

			data[i * wp + 3 * j] = Median(R, size*size);
			data[i * wp + 3 * j + 1] = Median(G, size*size);
			data[i * wp + 3 * j + 2] = Median(B, size*size);

			free(R);
			free(G);
			free(B);
		}
	}
}

void CWorkDoc::OnLaplasseOparator() 
{
	LaplasseOperator(1);
	reDraw();
}


void CWorkDoc::OnLaplasseOparatorNagetive() 
{
	LaplasseOperator(-1);
	reDraw();
}

void  CWorkDoc::LaplasseOperator(int factor)
{
	if(factor<0) factor = -1;
	else factor = 1;
	IplImage* inputRGBImg = m_img.GetImage();
	uchar *data = (uchar *)inputRGBImg->imageData;

	CvvImage cimg;

    cimg.CopyOf(m_img);

	IplImage* inputRGBImg2 = cimg.GetImage();
	uchar *data2 = (uchar *)inputRGBImg2->imageData;

	int  wp = inputRGBImg->widthStep;

	for(int i = 0; i < inputRGBImg->height; i++)
	{
		for(int j = 0; j < inputRGBImg->width; j++)
		{
			int R = 0, G = 0, B = 0, r, g, b;
			int x_sit, y_sit;

			for(int k = 0; k<4; k++)
			{
				switch(k)
				{
				case 0:						//  *
					if(i-1<0) y_sit = 0;	// 000
					else y_sit = i-1;		//  0
					x_sit = j;
					break;

				case 1:
					if(j+1>inputRGBImg->width-1) x_sit = inputRGBImg->width-1;		//   0
					else x_sit = j+1;												//  00*
					y_sit = i;														//   0
					break;

				case 2:																//  0
					if(i+1>inputRGBImg->height-1) y_sit = inputRGBImg->height-1;	// 000
					else y_sit = i+1;												//  *
					x_sit = j;
					break;

				case 3:
					if(j-1<0) x_sit = 0;											//   0
					else x_sit = j-1;												//  *00
					y_sit = i;														//   0
					break;

				}
				B += data2[y_sit * wp + 3 * x_sit];
				G += data2[y_sit * wp + 3 * x_sit + 1];
				R += data2[y_sit * wp + 3 * x_sit + 2];
			}

			b = data[i * wp + 3 * j] + factor*(B - 4*data[i * wp + 3 * j]);
			g = data[i * wp + 3 * j + 1] + factor*(G - 4*data[i * wp + 3 * j + 1]);
			r = data[i * wp + 3 * j + 2] + factor*(R - 4*data[i * wp + 3 * j + 2]);

			if(b<0) b=0;
			else if(b>255) b=255;

			if(g<0) g=0;
			else if(g>255) g=255;

			if(r<0) r=0;
			else if(r>255) r=255;

			data[i * wp + 3 * j] = b;
			data[i * wp + 3 * j + 1] = g;
			data[i * wp + 3 * j + 2] = r;
		}
	}

}

//	calculate data function

int CWorkDoc::Median(int *p, int size)
{
	int p0 = p[0];
	for(int i = 1; i<size; i++)
	{
		bool mark = false;
		for(int j = 1; j<size-i; j++)
		{
			if(p[j] < p[j-1])
			{
				int pt = p[j];
				p[j] = p[j-1];
				p[j-1] = pt;
				mark = true;
			}
		}
		if(!mark)
			break;
	}

	return p[size/2];
}
