// FloatData.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <math.h>
using namespace std;
int ConvertToInt(const float & val);
bool ConvertToInt(const double & val,int & i);
int _tmain(int argc, _TCHAR* argv[])
{
	short nCount = 100;
	while(--nCount)
	{
		double f = -1.0 * rand()/300.0;
		int i;
		ConvertToInt(f,i);
		cout<<"float:"<<f<<"   convert to int :"<<i<<endl;
	}

	//int i = 0;
	//float f1 = -7887704.125;

	///*12(10) = 1100(2) 
	////0.125(10) = 0.001(2)
	////so 12.125(10) = 1100.001(2) = 1.100001 * (2^3)
	//// 符号位      阶码(移位存储)(23~30)              尾码(0~22)
	////   0         127 + 3 = 130               1000010  00000000 00000000
	////   0         10000010                    1000010  00000000 00000000
	//// 01000001 01000010  00000000 00000000
	////    65       66        00       00
	//*/
	//char p[4] = {0};
	//memcpy(p,&f1,4);
	//for(int i = 0 ; i < 4 ; ++i)
	//	cout<<(int)p[i]<<" ";
	////输出应该就是 0 0 66 65
	//cout<<endl;
	//cout<<sizeof(int)<<endl;
	//cout<<sizeof(float)<<endl;
	//cout<<sizeof(short)<<endl;

	char chEnd;
	cin>>chEnd;
	
	/*
	//double和float的存储方式是一样的，只是double的范围比float大，因为double是64位的而float是32位的
	*/
	return 0;
}

int ConvertToInt(const float & val)
{
	int i = 0;
	memcpy(&i,&val,4);
	int nRes = (((i&0x7fffff) | 0x800000) >> (150 - ((i>>23)&0xff)));
	if(i&0x80000000)
		nRes = ~nRes + 1;
	return nRes;
}

bool ConvertToInt(const double & val,int & i)
{
	int num[2] = {0};
	memcpy(num,&val,8);
	int high = num[1];
	int nExp = ((high>>20)&0x7ff) - 1023;
	if(nExp <= 20)
	{
		i = ( high&0xfffff | 0x100000)>>(20 - nExp);
	}
	else if(nExp > 20 && nExp <= 30)
	{
		int low = num[0];
		i = ( ( high&0xfffff | 0x100000)<<(nExp - 20) )+ ( low >>(52 - nExp));
	}
	else
		return false;

	if(high&0x80000000)
		i = ~i + 1;
	return true;
}