#include<atlimage.h>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include"pch.h"
#include"GeoTransform.h"

using namespace std;

const double eps=1e-7;

// ��ת
template<class T_DATA>
CImageData<T_DATA> CGeoTransform<T_DATA>::
rotate(CImageData<T_DATA>& src, double rad){
	// �õ��任����a���Ϳ����ˣ�
	double w=src.width,h=src.height;
	double c=cos(-rad),s=sin(-rad);
	// ��ΪҪ���������Ҷ�ֵ�����԰�a���󸳳��෴��ֵ��
	double a[3][4];
	a[1][1]=c, a[1][2]=-s, a[1][3]=(w/2-0.5)*(1-c)+(h/2-0.5)*s;
	a[2][1]=s, a[2][2]=c,  a[2][3]=(h/2-0.5)*(1-c)-(w/2-0.5)*s;
	// a[1][1]=c, a[1][2]=-s, a[1][3]=0;
	// a[2][1]=s, a[2][2]=c,  a[2][3]=0;

	return generalGeoTrans(src,a);
}

// ����
template<class T_DATA>
CImageData<T_DATA> CGeoTransform<T_DATA>::
scaling(CImageData<T_DATA>& src, double rate){
	double a[3][4];
	a[1][1]=a[2][2]=1/rate; // ͬ��Ҳ���෴��ֵ
	a[1][2]=a[2][1]=a[1][3]=a[2][3]=0;

	return generalGeoTrans(src,a);
}

// ƽ��
template<class T_DATA>
CImageData<T_DATA> CGeoTransform<T_DATA>::
translate(CImageData<T_DATA>& src, double xspace, double yspace){
	double a[3][4];
	a[1][1]=a[2][2]=1,a[1][2]=a[2][1]=0;
	a[1][3]=-xspace,a[2][3]=-yspace; // ͬ��Ҳ���෴��ֵ

	return generalGeoTrans(src,a);
}

// ���м��α任
template<class T_DATA>
CImageData<T_DATA> CGeoTransform<T_DATA>::
generalGeoTrans(CImageData<T_DATA>& src, double a[3][4]){

	// printContent(src);
	double w=src.width,h=src.height;
	pair<double,double>* pos=affine(w,h,a); // �����Ȱ�����õ���
	T_DATA* newval=interpolate(pos,src); // ͨ�������õ�ֵ��
	delete[] pos;

	CImageData<T_DATA> result;
	result.copy(newval,w,h); // ��ֵ��
	delete[] newval;
	// printContent(result);
	return result; // ok����
}

// ����任���õ�����
template<class T_DATA>
pair<double,double>* CGeoTransform<T_DATA>::
affine(int w, int h, double a[3][4]){
	pair<double,double>* pos=new pair<double,double>[w*h];
	for(int i=0;i<h;++i){
		for(int j=0;j<w;++j){
			pos[i*w+j].first= a[1][1]*j+a[1][2]*i+a[1][3];
			pos[i*w+j].second=a[2][1]*j+a[2][2]*i+a[2][3];
			// cout<<pos[i*w+j].first<<","<<pos[i*w+j].second<<" ";
		}
		// cout<<"endl"<<endl;
	}
	return pos;
}

// ��ֵ���õ��Ҷ�ֵ
template<class T_DATA>
T_DATA* CGeoTransform<T_DATA>::
interpolate(pair<double,double>* pos, CImageData<T_DATA>& src){
	int w=src.width, h=src.height;
	T_DATA* srcdata=src.pixelData;
	T_DATA* newval=new T_DATA[w*h];
	memset(newval,0,sizeof(newval));
	for(int i=0;i<h;++i)
		for(int j=0;j<w;++j){
			double x=pos[i*w+j].first,y=pos[i*w+j].second;
			if(!(0<=x+eps&&x-eps<=w-1&&0<=y+eps&&y-eps<=h-1)){
				// cout<<"x,y="<<x<<","<<y<<". sad, no value\n";
				newval[i*w+j]=0;
			}
			else{
				int xl=floor(x+eps),xr=ceil(x+eps),yl=floor(y+eps),yr=ceil(y+eps);
				newval[i*w+j]=round((xr-x)*((yr-y)*srcdata[yl*w+xl]
					+(y-yl)*srcdata[yr*w+xl])
					+(x-xl)*((yr-y)*srcdata[yl*w+xr]
						+(y-yl)*srcdata[yr*w+xr]));
				// cout<<"x,y,newval="<<x<<","<<y<<","<<newval[i*w+j]<<endl;
				// cout<<"xl,xr,yl,yr="<<xl<<","<<xr<<","<<yl<<","<<yr<<endl;
			}
		}
	return newval;
}

// Ϊ��debug
template<class T_DATA>
void CGeoTransform<T_DATA>::
printContent(CImageData<T_DATA>& src){
	cout<<"\nprint content please!\n";
	int w=src.width,h=src.height;
	for(int i=0;i<h;++i){
		for(int j=0;j<w;++j)
			cout<<src.pixelData[i*w+j]<<" ";
		cout<<"endl"<<endl;
	}
}

