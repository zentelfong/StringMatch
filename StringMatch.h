#pragma once

//�������������룬һ����ƥ����ַ���str1������С��20��һ��ƥ���ַ���str2������С��100
//str1��������С�*��������������ַ���һ����������������κ�һ�����ֻ�����ĸ����*����������������������ֺ���ĸ
//������str2���ҵ����ַ���str1ƥ�������λ�ã������һ����ĸ��λ�õ�ֵindex

template<class T>
int strLenT(const T* str){
    int count = 0;
    while(*str++){
        ++count;
    }
    return count;
}

//�㷨��ʾ
//���룺ab*cd
//		qaxabc12xrcdwew   
//��������
//   q  a  x  a  b  c  1  2  x  r  c  d  w  e  w
//a  0  2  0  4  0  0  0  0  0  0  0  0  0  0  0  
//b  0  0  0  0  5  0  0  0  0  0  0  0  0  0  0
//?  0  0  0  0  0  6  0  0  0  0  0  0  0  0  0
//1  0  0  0  0  0  0  7  0  0  0  0  0  0  0  0
//2  0  0  0  0  0  0  0  8  0  0  0  0  0  0  0
//*  0  0  0  0  0  0  0  0  9  9  9  9  9  9  9
//c  0  0  0  0  0  6  0  0  0  0  10 0  0  0  0
//d  0  0  0  0  0  6  0  0  0  0  0  11 0  0  0

//�� 11-len��"ab?12*cd"��+1=4
//str1 ƥ��ģ��
//str2 ��ƥ����ַ���
template<class T>
int strMatchT(const T* str1,const T* str2)
{
	int flag=0;
	int i ,j;
	int len1=strLenT<T>(str1);
	int len2=strLenT<T>(str2);
	int * calc_arr = new int[len1*len2];

	memset(calc_arr,0,sizeof(int) *len1*len2);

	for(j=0;j<len2;j++)
	{
		if(str1[0]==str2[j])
		{
			calc_arr[j]=j+1;
		}
	}

	//��һ����Ҫ��ʼ�����ڵ�һ����ĸƥ���ʱ�򣬱�ǳ����֣����ֵ�ֵΪ��ǰ��һ����ĸ�ڴ��е�λ��
	for(i=1;i<len1;i++) 
	{
		for(j=i;j<len2;j++)
		{
			if(str1[i]=='?')
			{
				if(calc_arr[(i-1)*len2 + j-1]!=0)
				{
					calc_arr[i*len2+j]=calc_arr[(i-1)*len2 + j-1]+1;
				}
			}
			else if(str1[i]=='*')
			{
				calc_arr[i*len2+j]=calc_arr[(i-1)*len2+j-1]==0?calc_arr[i*len2+j-1]:calc_arr[(i-1)*len2 + j-1]+1;
			}
			else if(str1[i]==str2[j])
			{
				if(calc_arr[(i-1)*len2+j-1]!=0)
				{
					calc_arr[i*len2 + j]=calc_arr[(i-1)*len2 + j-1]+1;
				}
			}
		}
	}
	for(j=0;j<len2;j++)
	{
		if(calc_arr[(len1-1)*len2 + j]!=0)
		{
			printf("%d\n",calc_arr[(len1-1)*len2 + j]-len1+1);
			flag=1;
		}
	}
	if(flag==0)
	{
		printf("No match!\n");
	}

	delete calc_arr;
	return flag;
}
