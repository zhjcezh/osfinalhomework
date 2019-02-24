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

	//Ŀ¼
	Dir* createdir();//�½�Ŀ¼
	void movedir();//ɾ��Ŀ¼
	void namedir();//������Ŀ¼
	void copydir();//����Ŀ¼    
	void pasteDir();//ճ��Ŀ¼
	void subpastedir(Dir *dir1, Dir *dir2);//ճ���������ƺ���
	void subpastefile(File *file, Dir*dir);//ճ������Ŀ¼�µ��ļ�
	Dir* back();//������һ��Ŀ¼
	Dir* cd();//��Ŀ¼
	void submovedir(Dir *dir);//Ŀ¼ɾ���Ӻ�����ɾ��Ҫɾ��Ŀ¼�µ�Ŀ¼
	void movefileindir(Dir *dir);//Ŀ¼ɾ���Ӻ�����ɾ��Ҫɾ��Ŀ¼�µ��ļ�
	void ls();//��ʾ��ǰĿ¼������
	void showAll();//չʾ����Ŀ¼
	void showdir(Dir *dir, int num);//Ŀ¼չʾ�Ӻ������ݹ�Ŀ¼
	void showfile(File *file, int num);//Ŀ¼չʾ�Ӻ������ݹ��ļ�
	void pwd();//��ʾ��ǰ·��
	void showplace();//��ʾ��ǰ�û���λ��
	//�ļ�
	void createfile();//�½��ļ�
	void movefile();//ɾ���ļ�
	void namefile();//�������ļ�
	void copyfile();//�����ļ�
	void pastefile();//ճ���ļ�
	void cat();//���ļ�
	void vi();//�༭�ļ�
	void readandwrite();//�޸��ļ�����Ϊ�ɶ�
private:
	Dir *root;//��Ŀ¼
	Dir *nowDir;//��ǰĿ¼
	File *tempfile;//��Ÿ��Ƶ��ļ����Ա�ճ��ʹ��
	Dir *tempdir;//��Ÿ��Ƶ�Ŀ¼���Ա�ճ��ʹ��
};

#endif