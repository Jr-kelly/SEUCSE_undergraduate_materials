#pragma once
#include<atlimage.h>
#include<algorithm>
#include"ImageData.h"

#ifndef CENHANCEMENT_H
#define CENHANCEMENT_H

using namespace std;

template<class T_DATA>
class CImageData;

// ��������ͼ����ǿ����
template<class T_DATA>
class CEnhancement
{
public:
	static CImageData<T_DATA> laplacian(CImageData<T_DATA>&, double);		// ������˹��
	static CImageData<T_DATA> medianFilter(CImageData<T_DATA>&);			// ��ֵ�˲���
private:
	static CImageData<T_DATA> conv(CImageData<T_DATA>&, int, double*);		// �������
};

#endif // CENHANCEMENT_H


