// Calculate.cpp: implementation of the CCalculate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "work.h"
#include "Calculate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalculate::CCalculate()
{

}

CCalculate::~CCalculate()
{

}

void CCalculate::SetSegmentalPoint(int first_x, int first_y, int second_x, int second_y)
{
    segment_point_.first_x_ = first_x;
    segment_point_.first_y_ = first_y;
    segment_point_.second_x_ = second_x;
    segment_point_.second_y_ = second_y;
};

int CCalculate::GetSegmentalProvess(int value) // 0~255
{
    int result;
    if(value<=segment_point_.first_x_)
        result = value * segment_point_.first_y_ / segment_point_.first_x_;
    else if(value<=segment_point_.second_x_)
        result = segment_point_.first_y_ + 
                (segment_point_.second_y_ - segment_point_.first_y_) /
                (segment_point_.second_x_ - segment_point_.first_x_) *
                (value - segment_point_.first_x_);
    else
        result = segment_point_.second_y_ + 
                (255 - segment_point_.second_y_) /
                (255 - segment_point_.second_x_) *
                (value - segment_point_.second_x_);

    return result;
}

void CCalculate::GetSegmentalProvess(int &b, int &g, int &r) // 0~255
{
	int value = (b + g + r)/3;
	if(!(b & g & r))
		return;
    int result;
    if(value<=segment_point_.first_x_)
        result = value * segment_point_.first_y_ / segment_point_.first_x_;
    else if(value<=segment_point_.second_x_)
        result = segment_point_.first_y_ + 
                (segment_point_.second_y_ - segment_point_.first_y_) /
                (segment_point_.second_x_ - segment_point_.first_x_) *
                (value - segment_point_.first_x_);
    else
        result = segment_point_.second_y_ + 
                (255 - segment_point_.second_y_) /
                (255 - segment_point_.second_x_) *
                (value - segment_point_.second_x_);

    b = b * result / value;
	g = g * result / value;
	r = r * result / value;

	b = b>255 ? 255:b;
	g = g>255 ? 255:g;
	r = r>255 ? 255:r;
}

// void CWorkDoc::OnSegmentalProvesssOparator(int first_x, int first_y, int second_x, int second_y)
// {
	// CCalculate calcul;
	// calcul.SetSegmentalPoint(first_x, first_y, second_x, second_y);

	// IplImage* inputRGBImg = m_img.GetImage();
	// uchar *data = (uchar *)inputRGBImg->imageData;

	// int  wp = inputRGBImg->widthStep;

	// for(int i = 0; i < inputRGBImg->height; i++)
	// {
	// 	for(int j = 0; j < inputRGBImg->width; j++)
	// 	{	
	// 		int b = data[(inputRGBImg->height-1-i) * wp + 3 * j];
	// 		int g = data[(inputRGBImg->height-1-i) * wp + 3 * j + 1];
	// 		int r = data[(inputRGBImg->height-1-i) * wp + 3 * j + 2];
	// 		data[(inputRGBImg->height-1-i) * wp + 3 * j] = calcul.GetSegmentalProvess(b);
	// 		data[(inputRGBImg->height-1-i) * wp + 3 * j + 1] = calcul.GetSegmentalProvess(g);
	// 		data[(inputRGBImg->height-1-i) * wp + 3 * j + 2] = calcul.GetSegmentalProvess(r);
	// 	}
	// }
// }