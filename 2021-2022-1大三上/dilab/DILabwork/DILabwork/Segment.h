#pragma once
#include<atlimage.h>
#include<algorithm>
#include"ImageData.h"

#ifndef CSEGMENT_H
#define CSEGMENT_H

using namespace std;

template<class T_DATA>
class CImageData;

// ��������ͼ�񼸺α任����
template<class T_DATA>
class CSegment{
public:
	CSegment(double);
	CImageData<T_DATA> twoClassSegment(CImageData<T_DATA>&);	// ������ͼ��ָ�
private:
	double conv[5][5];											// ������ȡ����ֵ�ľ����
	double eps;													// ��������������������ֵ
	double* getFeature(CImageData<T_DATA>&);					// �õ�����ֵ
	CImageData<T_DATA> regionalGrowth(int, int, double*);		// ����������
};
#endif // CSEGMENT_H
