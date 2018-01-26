#pragma once

//问题描述：输入，一个待匹配的字符串str1，串长小于20，一个匹配字符串str2，串长小于100
//str1里面包含有“*”，“？”替代字符，一个“？”可以替代任何一个数字或者字母，“*”可以替代几个连续的数字和字母
//现在在str2中找到和字符串str1匹配的所有位置，输出第一个字母的位置的值index

template<class T>
int strLenT(const T* str){
    int count = 0;
    while(*str++){
        ++count;
    }
    return count;
}

//算法演示
//输入：ab*cd
//		qaxabc12xrcdwew   
//举例如下
//   q  a  x  a  b  c  1  2  x  r  c  d  w  e  w
//a  0  2  0  4  0  0  0  0  0  0  0  0  0  0  0  
//b  0  0  0  0  5  0  0  0  0  0  0  0  0  0  0
//?  0  0  0  0  0  6  0  0  0  0  0  0  0  0  0
//1  0  0  0  0  0  0  7  0  0  0  0  0  0  0  0
//2  0  0  0  0  0  0  0  8  0  0  0  0  0  0  0
//*  0  0  0  0  0  0  0  0  9  9  9  9  9  9  9
//c  0  0  0  0  0  6  0  0  0  0  10 0  0  0  0
//d  0  0  0  0  0  6  0  0  0  0  0  11 0  0  0

//答案 11-len（"ab?12*cd"）+1=4
//str1 匹配模板
//str2 待匹配的字符串
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

	//第一行先要初始化，在第一个字母匹配的时候，标记出数字，数字的值为当前第一个字母在串中的位置
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
