#include<atlimage.h>
#include<iostream>
#include<cstring>
#include"pch.h"
#include"ImageData.h"
using namespace std;

// CImageData���ʵ��

// ����һ����ɫ����
template<class T_DATA> CImageData<T_DATA>::
CImageData(int w, int h):
	width(w),height(h),pixelData(new T_DATA[w*h]){
	memset(pixelData,0,sizeof(pixelData));
}

// ����ͼ����Ϣ
template<class T_DATA> bool CImageData<T_DATA>::
copy(T_DATA* data,int w,int h){
	if(pixelData)delete[] pixelData;
	pixelData=new T_DATA[w*h];
	memcpy(pixelData,data,sizeof(T_DATA)*w*h);
	width=w,height=h;
	return true;
}

// ������ͬ����CImage��
template<class T_DATA> void CImageData<T_DATA>::
syncPixel(CImage* cimage){
	cimage->Create(width,-1*long long(height),8*sizeof(T_DATA));

	// ��ɫ��
	RGBQUAD* pLUT = new RGBQUAD[256];
	for (int i = 0; i < 256; ++i) {
		(pLUT + i)->rgbRed = (pLUT + i)->rgbGreen = (pLUT + i)->rgbBlue = i;	
		(pLUT + i)->rgbReserved = 0;
	}
	cimage->SetColorTable(0, 256, pLUT);
	delete[] pLUT;

	// ���ظ�ֵ
	byte* pDataSrc = (byte*)cimage->GetBits(); // ��ȡָ��ͼ�����ݵ�ָ��
	int pitchSrc = cimage->GetPitch(); // ��ȡÿ��ͼ��ռ�õ��ֽ��� +��top-down��-��bottom-up DIB 
	int bitCountSrc = cimage->GetBPP()/8;  // ��ȡÿ������ռ�õ��ֽ���

	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++){
			*(pDataSrc+pitchSrc*i+j) = pixelData[i*width+j];
			// *(pDataSrc+pitchSrc*i+j*bitCountSrc) = pixelData[i*width+j];
		}

	/*for(int i=0;i<height;++i)
		for(int j=0;j<width;++j)
			cimage->SetPixel(j,height-1-i,
				RGB(pixelData[i*width+j],
					pixelData[i*width+j],
					pixelData[i*width+j]));*/


}

// �����ļ�·������ͼ��
template<class T_DATA> bool CImageData<T_DATA>::
load(LPCTSTR path){
	if(!PathFileExists(path)) return false; // �ļ������ڣ�����ʧ��
	//AfxMessageBox(_T("����ͼ���Ǵ��ڵ�"));

	// ����ͼƬ����¼�ߴ�
	CImage cimage;
	cimage.Load(path);
	width=cimage.GetWidth();
	height=cimage.GetHeight();

	// �������ݵ��ڴ����
	if(pixelData)delete[] pixelData; // �ջ��ڴ�
	pixelData=new T_DATA[width*height]; // �����ڴ�

	byte* pDataSrc = (byte*)cimage.GetBits(); // ��ȡָ��ͼ�����ݵ�ָ��
	int pitchSrc = cimage.GetPitch(); // ��ȡÿ��ͼ��ռ�õ��ֽ��� +��top-down��-��bottom-up DIB 
	int bitCountSrc = cimage.GetBPP()/8;  // ��ȡÿ������ռ�õ��ֽ���

	/*byte tmpR,tmpG,tmpB,avg;
	for(int i=0;i<width;i++)
		for(int j=0;j<height;j++){
			tmpR = *(pDataSrc+pitchSrc*j+i*bitCountSrc);
			tmpG = *(pDataSrc+pitchSrc*j+i*bitCountSrc+1);
			tmpB = *(pDataSrc+pitchSrc*j+i*bitCountSrc+2);
			avg = (byte)(tmpR+tmpG+tmpB)/3;
			*(pixelData+pitchDst*j+i*bitCountDst) = avg;
		}*/

	// ȡ���صĺ�ɫ���ݣ��õ��Ҷ�ֵ
	byte tmpR,tmpG,tmpB,avg;
	for(int i=0;i<height;++i)
		for(int j=0;j<width;++j){
			tmpR = *(pDataSrc+pitchSrc*i+j*bitCountSrc);
			pixelData[i*width+j]=tmpR;
			// pixelData[i*width+j]=255;
			// GetRValue(cimage.GetPixel(j,height-1-i))
		}

	return true; // �����ɹ�
}

// ��ͼ�񱣴浽��Ӧ·�����ļ�
template<class T_DATA> bool CImageData<T_DATA>::
save(LPCTSTR path){
	CImage cimage;
	syncPixel(&cimage); // cimageͬ����������
	cimage.Save(path); // �洢���ļ�
	// ���û�������ļ����ж����ͣ���Ĭ�ϴ洢��bmp����
	return true; // �����ɹ�
}

// ��ʾͼ��
template<class T_DATA> bool CImageData<T_DATA>::
show(CDC* pDC,int x,int y){
	CImage cimage;
	syncPixel(&cimage); // cimageͬ����������
	// cimage.Load(_T("test.bmp"));
	cimage.Draw(pDC->GetSafeHdc(),x,y,min(width,570),min(height,570),
		0,0,width,height);

	return true;
}



/*
�ο����ϣ�

CImage �������ص�
https://bbs.csdn.net/topics/330056240

Cimage��Ľ��ܼ�ʹ��
https://blog.csdn.net/u013472838/article/details/80519525

MFC��ʾͼƬ
https://blog.csdn.net/lynn1258/article/details/54376311

CImage �����������ص�RGBֵ
https://blog.csdn.net/u011450490/article/details/53638942

ʹ�� CImage �ཫ��ɫͼ��ת����8λ��ɫͼ��
https://blog.csdn.net/hero_myself/article/details/45152453

*/