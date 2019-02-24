#pragma once
#ifndef DIR_H
#define DIR_H

#include"File.h"
using namespace std;

class Dir
{
public:
	Dir() {
		d_createtime = "";
		d_changetime = "";
		d_size = 0;
		nextDir = NULL;
		preDir = NULL;
		fileptr = NULL;
		dirptr = NULL;
	}
	Dir(string time, string name, int size, Dir *nextdir, Dir*predir, File *fileptr1, Dir *dirptr1) 
	{
		d_createtime = time;
		d_changetime = name;
		d_size = size;
		nextDir = nextdir;
		preDir = predir;
		fileptr = fileptr1;
		dirptr = dirptr1;
	}
	~Dir() {}
	string d_createtime;//创建时间
	string d_changetime;//最近修改时间
	string d_name;//目录名
	int d_size;//目录大小
	Dir * nextDir;//后继目录
	Dir * preDir;//前继目录
	File * fileptr;//该目录下文件链表指针
	Dir * dirptr; //该目录下目录链表指针
};
#endif