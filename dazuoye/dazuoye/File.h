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
	bool readandwrite;//true可读可写，false只读
	string f_createtime;//创建时间
	string f_changetime;//修改时间
	string f_name;//文件名
	int f_size;//文件大小
	File * nextFile;//指向同目录文件链表中下一个文件
	string f_content;//文件内容
};

#endif