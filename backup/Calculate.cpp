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

void CCalculate::SetSegmentalPoint(int p_x, int p_y, int a_x, int a_y)
{
    segment_point_.first_x_ = p_x;
    segment_point_.first_y_ = p_y;
    segment_point_.second_x_ = a_x;
    segment_point_.second_y_ = a_y;
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