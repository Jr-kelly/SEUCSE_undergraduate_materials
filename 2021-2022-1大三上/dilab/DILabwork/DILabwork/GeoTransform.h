#pragma once
#include<atlimage.h>
#include<algorithm>
#include"ImageData.h"

#ifndef CGEOTRANSFORM_H
#define CGEOTRANSFORM_H

using namespace std;

template<class T_DATA>
class CImageData;

// ��������ͼ�񼸺α任����
template<class T_DATA>
class CGeoTransform
{
public:
	static CImageData<T_DATA> rotate(CImageData<T_DATA>&, double);				// ��ת
	static CImageData<T_DATA> scaling(CImageData<T_DATA>&, double);				// ����
	static CImageData<T_DATA> translate(CImageData<T_DATA>&, double, double);	// ƽ��
private:
	static CImageData<T_DATA> generalGeoTrans(CImageData<T_DATA>&, double[3][4]);	// ���м��α任
	static pair<double,double>* affine(int, int, double[3][4]);						// ����任���õ�����
	static T_DATA* interpolate(pair<double,double>*, CImageData<T_DATA>&);			// ��ֵ���õ��Ҷ�ֵ

	static void printContent(CImageData<T_DATA>&);									// Ϊ��debug
};

#endif // CGEOTRANSFORM_H