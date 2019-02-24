#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include"Dir.h"

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	//目录
	Dir* createdir();//新建目录
	void movedir();//删除目录
	void namedir();//重命名目录
	void copydir();//复制目录    
	void pasteDir();//粘贴目录
	void subpastedir(Dir *dir1, Dir *dir2);//粘贴函数复制函数
	void subpastefile(File *file, Dir*dir);//粘贴复制目录下的文件
	Dir* back();//返回上一级目录
	Dir* cd();//打开目录
	void submovedir(Dir *dir);//目录删除子函数，删除要删除目录下的目录
	void movefileindir(Dir *dir);//目录删除子函数，删除要删除目录下的文件
	void ls();//显示当前目录的内容
	void showAll();//展示所有目录
	void showdir(Dir *dir, int num);//目录展示子函数，递归目录
	void showfile(File *file, int num);//目录展示子函数，递归文件
	void pwd();//显示当前路径
	void showplace();//显示当前用户和位置
	//文件
	void createfile();//新建文件
	void movefile();//删除文件
	void namefile();//重命名文件
	void copyfile();//复制文件
	void pastefile();//粘贴文件
	void cat();//打开文件
	void vi();//编辑文件
	void readandwrite();//修改文件属性为可读
private:
	Dir *root;//根目录
	Dir *nowDir;//当前目录
	File *tempfile;//存放复制的文件，以便粘贴使用
	Dir *tempdir;//存放复制的目录，以便粘贴使用
};

#endif