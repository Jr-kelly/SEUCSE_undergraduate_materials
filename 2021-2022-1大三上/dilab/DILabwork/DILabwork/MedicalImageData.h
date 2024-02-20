#pragma once
#include "ImageData.h"

#ifndef CMEDICALIMAGEDATA_H
#define CMEDICALIMAGEDATA_H

template<class T_DATA>
class CMedicalImageData : public CImageData<T_DATA>
{
public:
	bool loadRaw(CString);						// ��ȡҽѧͼ������
	void greyWindowSync(CImage*,double,double);	// �����Ҷȴ�
	void show(CDC*,double,double);				// ��ʾͼ��
};

#endif
