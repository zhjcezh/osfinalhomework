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
	string d_createtime;//����ʱ��
	string d_changetime;//����޸�ʱ��
	string d_name;//Ŀ¼��
	int d_size;//Ŀ¼��С
	Dir * nextDir;//���Ŀ¼
	Dir * preDir;//ǰ��Ŀ¼
	File * fileptr;//��Ŀ¼���ļ�����ָ��
	Dir * dirptr; //��Ŀ¼��Ŀ¼����ָ��
};
#endif