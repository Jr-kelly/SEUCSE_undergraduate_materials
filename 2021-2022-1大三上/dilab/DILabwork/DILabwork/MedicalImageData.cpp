#include "pch.h"
#include "MedicalImageData.h"
#include <string> 
#include <fstream> 
#include <iostream> 

// ��ȡraw�ļ�
template<class T_DATA> bool CMedicalImageData<T_DATA>::
loadRaw(CString path){
	ifstream raw(path, ios::in|ios::binary);
	if (!raw.is_open()) return false;

	raw.read((char*)&width, sizeof(unsigned long));
	raw.read((char*)&height, sizeof(unsigned long));

	//CString temp_value = _T("");
	//temp_value.Format(_T("width,height=%u,%u"), width, height);//�̶���ʽ
	//AfxMessageBox(temp_value);

	if(pixelData!=NULL)delete pixelData;
	pixelData=new T_DATA[width*height];
	for(int i=0;i<width*height;++i){
		raw.read((char*)&pixelData[i], sizeof(unsigned short));
		pixelData[i]%=4096;
	}

	raw.close();
	return true;
}

// ���лҶȴ����ܵ� ��������ͬ��
template<class T_DATA> void CMedicalImageData<T_DATA>::
greyWindowSync(CImage* cimage, double wlevel, double wwidth){
	
	int tsize=570;
	cimage->Create(width,-1*long long(height),8*sizeof(byte));

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

	// �Ҷȴ�
	wlevel-=wwidth/2;
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++){
			byte value=0;
			if(pixelData[i*width+j]<=wlevel)value=0;
			else if(pixelData[i*width+j]>=wlevel+wwidth)value=255;
			else value=floor((pixelData[i*width+j]-wlevel)/wwidth*256);
			*(pDataSrc+pitchSrc*i+j) = value;
		}
}

// ��ʾ�ֲ�ͼ��
// int����Ϊͼ��ֲ������Ͻ���ߣ���СΪ570*570����double����Ϊ�Ҷȴ�����
template<class T_DATA> void CMedicalImageData<T_DATA>::
show(CDC* pDC, double wlevel, double wwidth){
	
	CImage cimage;
	greyWindowSync(&cimage, wlevel, wwidth); // cimageͬ����������

	cimage.Draw(pDC->GetSafeHdc(),0,0,width,height,
		0,0,width,height);
}
