#pragma once

#ifndef FILE_H
#define FILE_H
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<fstream>
#include<Windows.h>
#include<vector>
#include<time.h>
#include<sstream>
using namespace std;

class File
{
public:
	File() 
	{
		readandwrite = true;
		f_createtime = "";
		f_changetime = "";
		f_size = 0;
		nextFile = NULL;
		f_content = "";
	}
	~File() {};
	bool readandwrite;//true�ɶ���д��falseֻ��
	string f_createtime;//����ʱ��
	string f_changetime;//�޸�ʱ��
	string f_name;//�ļ���
	int f_size;//�ļ���С
	File * nextFile;//ָ��ͬĿ¼�ļ���������һ���ļ�
	string f_content;//�ļ�����
};

#endif