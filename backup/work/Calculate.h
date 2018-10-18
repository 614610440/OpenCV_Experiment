// Calculate.h: interface for the CCalculate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCULATE_H__16AFB289_7C32_4DE5_9BA4_093E8A38B03B__INCLUDED_)
#define AFX_CALCULATE_H__16AFB289_7C32_4DE5_9BA4_093E8A38B03B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalculate  
{
public:
	CCalculate();
	virtual ~CCalculate();

	void SetSegmentalPoint(int p_x, int p_y, int a_x, int a_y);
	int GetSegmentalProvess(int value);
	void GetSegmentalProvess(int &b, int &g, int &r);

private:
	struct SegmentPoint
	{
		int first_x_;
		int first_y_;
		int second_x_;
		int second_y_;
	};
	SegmentPoint segment_point_;
};

#endif // !defined(AFX_CALCULATE_H__16AFB289_7C32_4DE5_9BA4_093E8A38B03B__INCLUDED_)
