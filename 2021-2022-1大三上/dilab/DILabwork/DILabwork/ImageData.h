#pragma once
#include<atlimage.h>
#include"GeoTransform.h"
#include"Enhancement.h"

#ifndef CIMAGEDATA_H
#define CIMAGEDATA_H

template<class T_DATA>
class CGeoTransform;

// �����洢ͼ�����ݵ���
// ֧�ָ���·����дͼ��֧����ʾͼ��
template<class T_DATA>
class CImageData
{
	template<class T_DATA>
	friend class CGeoTransform;			// ���α任������Ԫ��
	template<class T_DATA>
	friend class CEnhancement;			// ͼ����ǿ������Ԫ��
	template<class T_DATA>
	friend class CSegment;				// ͼ��ָ�������Ԫ��
protected:
	unsigned long width;				// ͼ��Ŀ���λ������
	unsigned long height;				// ͼ��ĸߣ���λ������
	T_DATA* pixelData;					// ��������

	void syncPixel(CImage*);			// ������ͬ����CImage��

public:
	CImageData(){pixelData=NULL;}		// Ĭ�Ϲ��캯��
	CImageData(int, int);				// ����һ����ɫ����
	virtual ~CImageData(){}				// ��������

	bool copy(T_DATA*,int,int);			// ����ͼ����Ϣ

	int getWidth() const {return width;}
	int getHeight() const {return height;}

	bool load(LPCTSTR path);			// �����ļ�·������ͼ��
	bool save(LPCTSTR path);			// ��ͼ�񱣴浽��Ӧ·�����ļ�
	bool show(CDC* pDC,int,int);		// ��ʾͼ��

};

#endif // CIMAGEDATA_H
/*
�ҵ���Ҫд��ʲô��
�����ǣ�CImageData�࣬����ʵ�ֹ��ܾͺá�
Ȼ���ǣ�GeoTransform�࣬����дһ��affine�任��������width��height�;������������ǡ�ÿһ������ӳ�䵽�ĺ������꡿��
��affine����Ҫ���в�ֵ����ô��ֵ�أ�ÿһ������ӳ�䵽�ĺ������꣬�������ȡֵ���͵õ��ˡ�

*/