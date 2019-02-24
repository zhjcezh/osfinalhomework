#define _CRT_SECURE_NO_WARNINGS
#include"FileSystem.h"
#include"Interface.h"
#include"Dir.h"
#include<iostream>
using namespace std;

FileSystem::FileSystem() 
{
	root = new Dir();//�½��û���Ĭ��һ��Ŀ¼Ϊ�û���Ŀ¼���ļ�����Ϊroot
	root->d_name = "root";
	nowDir = root;//��ǰĿ¼Ϊ��Ŀ¼
	tempfile = NULL;//�����ļ�Ϊ��
	tempdir = NULL;//�����ļ���Ϊ��
}
FileSystem::~FileSystem()
{
	delete root;
	delete nowDir;
	delete tempfile;
	delete tempdir;
}
/*��ʾ��ǰλ��*/
void FileSystem::showplace()//��ʾ��ǰλ��
{
	ifstream in;
	in.open("username_login.txt");
	string username;
	in >> username;
	Dir *temp = nowDir;
	if (temp == root)
	{
		cout << "user:" << username << ">" << temp->d_name << "\\";
	}
	else
	{
		vector<Dir*> vc;
		while (temp != NULL)
		{
			vc.push_back(temp);
			temp = temp->preDir;
		}
		cout << "user:" << username << ">";
		for (int i = 0; i != vc.size(); i++)
		{
			cout << vc[vc.size() - 1 - i]->d_name << "\\";
		}
		vc.clear();
	}
	in.close();
}
/*����Ŀ¼*/
Dir* FileSystem::createdir()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H��%M��%S", localtime(&Time));
	Dir *temp = new Dir();
	cin >> temp->d_name;
	if (nowDir->dirptr == NULL)//�����Ŀ¼��û���ļ���
	{
		nowDir->dirptr = temp;
		temp->preDir = nowDir;
		temp->d_createtime = t;
		temp->d_changetime = t;
	}
	else//Ŀ¼�����ļ��У�����Ҫ�ҵ�Ŀ¼����ĩ��
	{
		Dir *tp;
		tp = nowDir->dirptr;
		while (tp->nextDir != NULL)
		{
			if (tp->d_name == temp->d_name)
			{
				cout << "ͬĿ¼���ļ��в���������" << endl;
				return nowDir;
			}
			tp = tp->nextDir;
		}
		if (tp->d_name == temp->d_name)
		{
			cout << "ͬĿ¼���ļ��в���������" << endl;
			return nowDir;
		}
		tp->nextDir = temp;
		temp->preDir = nowDir;
		temp->d_createtime = t;
		temp->d_changetime = t;
	}
	cout << "Ŀ¼�����ɹ�" << endl;
	return nowDir;
}
/*ɾ��Ŀ¼�е��ļ�*/
void FileSystem::movefileindir(Dir *dir)
{
	dir->fileptr = NULL;
	return;
}
/*ɾ��Ŀ¼�е���Ŀ¼*/
void FileSystem::submovedir(Dir* dir)
{
	if (dir == NULL)
		return;
	if (dir->fileptr != NULL)
		movefileindir(dir);
	if (dir->dirptr != NULL)//��Ϊ��
	{
		submovedir(dir->dirptr);//�Ѹ�Ŀ¼ɾ����
	}
	if (dir->nextDir != NULL)//��һĿ¼��Ϊ��
	{
		submovedir(dir->nextDir);//�Ѹ�Ŀ¼����һĿ¼Ҳɾ�������ݹ�
	}
	delete dir;
}
/*ɾ��Ŀ¼*/
void FileSystem::movedir()
{
	string name;
	cin >> name;
	Dir *tp = new Dir();
	tp = nowDir->dirptr;//��ǰĿ¼����Ŀ¼����ָ��
	if (nowDir->dirptr == NULL) 
	{
		cout << "��ǰĿ¼��û���ļ���" << endl;
		return;
	}
	else if (tp->nextDir == NULL)//���ֻ��һ��Ŀ¼
	{
		if (tp->d_name == name)
		{
			movefileindir(tp);//ɾ�����ļ�
			if (tp->dirptr == NULL)//���û����Ŀ¼
			{
				nowDir->dirptr = NULL;
			}
			else//��������Ŀ¼
			{
				submovedir(tp->dirptr);//ɾ����Ŀ¼
				tp->dirptr = NULL;
				nowDir->dirptr = NULL;
			}
			cout << "Ŀ¼ɾ���ɹ�" << endl;
			return;
		}
	}
	else//����ж��Ŀ¼
	{
		if (tp->d_name == name)
		{
			movefileindir(tp);//ɾ�����ļ�
			nowDir->dirptr = tp->nextDir;//��һ��Ŀ¼����
			cout << "Ŀ¼ɾ���ɹ�" << endl;
			return;
		}
		else
		{
			while (tp->nextDir != NULL)
			{
				if (tp->nextDir->d_name == name)
				{
					movefileindir(tp->nextDir);//ɾ�����ļ�
					if (tp->nextDir->dirptr != NULL)//�������Ŀ¼
					{
						submovedir(tp->nextDir->dirptr);
					}
					tp->nextDir=tp->nextDir->nextDir;//��һ��Ŀ¼����
					cout << "Ŀ¼ɾ���ɹ�" << endl;
					return;
				}
				tp = tp->nextDir;
			}
		}
	}
	cout << "������Ҫɾ����Ŀ¼" << endl;
}
/*������Ŀ¼*/
void FileSystem::namedir()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H��%M��%S", localtime(&Time));
	string old, xin;
	cin >> old >> xin;
	if (nowDir->dirptr == NULL)
		cout << "��ǰ·���²�����Ŀ¼!" << endl;
	else
	{
		Dir *temp = new Dir();
		temp = nowDir->dirptr;
		Dir *tp = new Dir();
		tp = nowDir->dirptr;
		while (temp != NULL)
		{
			if (temp->d_name == old)//��ǰ·���´���Ҫ��������Ŀ¼
			{
				while (tp != NULL)
				{
					if (tp->d_name == xin)//���������Ŀ¼������ԭ�����ڵ�Ŀ¼��ͬ
					{
						cout << "��Ŀ¼����ԭ��Ŀ¼������!" << endl;
						return;
					}
					tp = tp->nextDir;
				}
				temp->d_name = xin;
				temp->d_changetime = t;
				cout << "�������ɹ���" << endl;
				return;
			}
			temp = temp->nextDir;
		}
		cout << "������������Ŀ¼" << endl;
	}
	return;
}
/*����Ŀ¼*/
void FileSystem::copydir()
{
	string name;
	cin >> name;
	if (nowDir->dirptr == NULL)//Ŀ¼������
		cout << "��Ŀ¼������Ŀ¼!" << endl;
	else//�� �鵽�ŵ�tempdir
	{
		Dir *tp = new Dir();
		tp = nowDir->dirptr;
		while (tp != NULL)
		{
			if (tp->d_name == name)
			{
				tempdir = tp;
				cout << "���Ƴɹ�" << endl;
				return;
			}
			tp = tp->nextDir;
		}
		cout <<"��Ŀ¼������!" << endl;
	}
	return;
}
/*������Ŀ¼*/
void FileSystem::subpastedir(Dir *dir1, Dir *dir2)
{
	if (dir1->dirptr != NULL)//1���գ���1�ŵ�2����
	{
		dir2->dirptr = new Dir();
		dir2->dirptr->d_createtime = dir1->dirptr->d_createtime;
		dir2->dirptr->d_name = dir1->dirptr->d_name;
		dir2->dirptr->d_size = dir1->dirptr->d_size;
		dir2->dirptr->preDir = dir2;
		//�ļ�����
		subpastefile(dir1->dirptr->fileptr, dir2->dirptr);
		//�ݹ�
		subpastedir(dir1->dirptr, dir2->dirptr);
	}

	if (dir1->nextDir != NULL)//1��ͬ������ ��������
	{
		dir2->nextDir = new Dir();
		dir2->nextDir->d_createtime = dir1->nextDir->d_createtime;
		dir2->nextDir->d_name = dir1->nextDir->d_name;
		dir2->nextDir->d_size = dir1->nextDir->d_size;
		dir2->nextDir->preDir = dir2->preDir;
		//�ļ�����
		subpastefile(dir1->nextDir->fileptr, dir2->nextDir);
		subpastedir(dir1->nextDir, dir2->nextDir);
	}
	return;
}
/*ճ������Ŀ¼�µ��ļ�*/
void FileSystem::subpastefile(File *file, Dir*dir)
{
	File *file1 = new File();
	file1 = file;
	Dir *dir1 = new Dir();
	dir1 = dir;
	if (dir1->fileptr != NULL)//��
	{
		File *ptr = new File();
		ptr = dir1->fileptr;
		while (ptr->nextFile != NULL) //ͬ�������ļ�����
		{
			ptr = ptr->nextFile;
		}
		ptr->nextFile = new File();
		ptr->nextFile->f_createtime = file1->f_createtime;
		ptr->nextFile->f_content = file1->f_content;
		ptr->nextFile->f_name = file1->f_name;
		ptr->nextFile->f_size= file->f_size;

	}
	else
	{
		if (file == NULL) {
			dir->fileptr = file1;
		}
		else {
			File *ptr = new File();
			ptr = file1;
			File *tempfile = new File();
			tempfile->f_createtime = file1->f_createtime;
			tempfile->f_content = file1->f_content;
			tempfile->f_name = file1->f_name;
			tempfile->f_size = file1->f_size;
			ptr = tempfile;
			while (file1->nextFile != NULL)
			{
				File *tempfile2 = new File();
				tempfile->f_createtime = file1->f_createtime;
				tempfile->f_content = file1->f_content;
				tempfile->f_name = file1->f_name;
				tempfile->f_size = file1->f_size;
				ptr->nextFile = tempfile2;
				ptr = ptr->nextFile;

			}
			dir->fileptr = tempfile;
		}
	}
	return;

}
/*ճ��Ŀ¼*/
void FileSystem::pasteDir()
{
	int flag = 0;
	if (tempdir == NULL)
	{
		cout << "����δ����Ŀ¼!" << endl;
		return;
	}
	Dir *temp = new Dir();
	temp = nowDir;
	while (temp != NULL)//���Բ��ܸ��Ƶ�����֧����֤����֧�����ڵ㶼����tempdir
	{
		if (temp->d_name == tempdir->d_name)
		{
			cout << "���ܽ���Ŀ¼���Ƶ���Ŀ¼��!" << endl;
			return;
		}
		temp = temp->preDir;
	}
	if (nowDir->dirptr == NULL)//��ǰĿ¼��û����Ŀ¼
	{
		//�����ļ���
		nowDir->dirptr = new Dir();
		nowDir->dirptr->d_createtime = tempdir->d_createtime;
		nowDir->dirptr->d_name = tempdir->d_name;
		nowDir->dirptr->d_size = tempdir->d_size;
		nowDir->dirptr->preDir = nowDir;
		subpastefile(tempdir->fileptr, nowDir->dirptr);
		//�����ļ�����Ŀ¼
		if (tempdir->dirptr != NULL)
		{

			nowDir->dirptr->dirptr = new Dir();
			nowDir->dirptr->dirptr->d_createtime = tempdir->dirptr->d_createtime;
			nowDir->dirptr->dirptr->d_name = tempdir->dirptr->d_name;
			nowDir->dirptr->dirptr->d_size = tempdir->dirptr->d_size;
			nowDir->dirptr->dirptr->preDir = nowDir->dirptr;
			//���ļ�����
			subpastefile(tempdir->dirptr->fileptr, nowDir->dirptr->dirptr);
			//��Ŀ¼
			subpastedir(tempdir->dirptr, nowDir->dirptr->dirptr);//��ǰ��������Ŀ���ַ
		}
		cout << "�ļ�ճ���ɹ���" << endl;
	}
	else
	{
		Dir *temp = new Dir();
		temp = nowDir->dirptr;
		while (temp->nextDir != NULL)
		{
			if (temp->nextDir->d_name == tempdir->d_name)
			{
				flag++;
				break;
			}
			temp = temp->nextDir;
		}
		if (nowDir->dirptr->d_name == tempdir->d_name || (temp->nextDir == NULL && temp->d_name == tempdir->d_name))
		{
			flag++;
		}
		if (!flag)
		{
			temp->nextDir = new Dir();
			temp->nextDir->d_createtime = tempdir->d_createtime;
			temp->nextDir->d_name = tempdir->d_name;
			temp->nextDir->d_size = tempdir->d_size;
			temp->nextDir->preDir = nowDir;
			//�����ļ�
			subpastefile(tempdir->fileptr, temp->nextDir);
			if (tempdir->dirptr != NULL)
			{
				temp->nextDir->dirptr = new Dir();
				temp->nextDir->dirptr->d_createtime = tempdir->dirptr->d_createtime;
				temp->nextDir->dirptr->d_name = tempdir->dirptr->d_name;
				temp->nextDir->dirptr->d_size = tempdir->dirptr->d_size;
				temp->nextDir->dirptr->preDir = temp->nextDir;
				//�����ļ�

				subpastefile(tempdir->dirptr->fileptr, temp->nextDir->dirptr);
				subpastedir(tempdir->dirptr, temp->nextDir->dirptr);
				cout << "ճ��Ŀ¼�ɹ�!" << endl;
			}
		}
		else
			cout << "��ǰĿ¼�Ѵ���!" << endl;

	}
}
/*����Ŀ¼*/
Dir* FileSystem::cd()
{
	string name;
	cin >> name;
	if (nowDir->dirptr == NULL)//��ǰĿ¼��û��Ŀ¼���Ͳ���������
	{
		cout << "���ȴ���һ��Ŀ¼!" << endl;
	}
	else
	{
		Dir *tp = new Dir();
		tp = nowDir->dirptr;
		while (tp != NULL)
		{
			if (tp->d_name == name)//�ҵ�Ҫ�����Ŀ¼
			{
				nowDir = tp;
				return nowDir;
			}
			tp = tp->nextDir;
		}
		cout << "��Ŀ¼������" << endl;
	}
	return nowDir;
}
/*�����ϼ�Ŀ¼*/
Dir* FileSystem::back()
{
	if (nowDir == root)
	{
		cout << "��ǰΪ��Ŀ¼���޷�����" << endl;
	}
	else
	{
		nowDir = nowDir->preDir;
	}
	return nowDir;
}
/*��ʾ��ǰĿ¼������Ŀ¼���ļ�*/
void FileSystem::ls()
{
	if (nowDir->dirptr == NULL&&nowDir->fileptr == NULL)
	{
		cout << "��ǰĿ¼��û���κ��ļ����ļ���" << endl;
	}
	cout << "----------------�� ǰ Ŀ ¼ �� Ϣ----------------" << endl;
	Dir *temp = new Dir();
	temp = nowDir->dirptr;
	if (temp != NULL)
		cout << "��Ŀ¼����-------" << "����ʱ��------------------" << "�޸�ʱ��------" << endl;
	while (temp != NULL)
	{
		cout << temp->d_name << string(10 - (temp->d_name.length()), ' ') << temp->d_createtime<< string(4, ' ') << temp->d_changetime << endl;
		temp = temp->nextDir;
	}
	
	File *tp = new File();
	tp = nowDir->fileptr;
	if (tp != NULL)
		cout << "���ļ�����-------" << "����ʱ��------------------" << "�޸�ʱ��------------------" <<"�ļ�����"<< endl;
	while (tp != NULL) 
	{
		cout << tp->f_name << string(10 - (tp->f_name.length()), ' ') << tp->f_createtime << string(4, ' ') << tp->f_changetime << string(11, ' ');
		if (tp->readandwrite == true)
			cout << "�ɶ���д" << endl;
		else
			cout << "�ɶ�" << endl;
		tp = tp->nextFile;
	}
}
/*��ʾ��ǰ·��*/
void FileSystem::pwd()
{
	vector<Dir*> vc;
	Dir *temp = new Dir();
	temp = nowDir;
	while (temp != NULL)
	{
		vc.push_back(temp);
		temp = temp->preDir;
	}
	for (int i = 0; i != vc.size(); i++)
	{
		cout << vc[vc.size() - 1 - i]->d_name << "\\";
	}
	vc.clear();
	cout << endl;
	return;
}
/*�ݹ���ʾ����Ŀ¼*/
void FileSystem::showdir(Dir *dir, int num)//Ŀ¼չʾ�Ӻ������ݹ�Ŀ¼
{
	if (dir->d_name != "")
		cout << string(4 * num, '-') << "Ŀ¼" << dir->d_name << endl;
	if (dir->dirptr != NULL) {
		showdir(dir->dirptr, num + 1);
	}
	if (dir->fileptr != NULL)
		showfile(dir->fileptr, num + 1);
	if (dir->nextDir != NULL)
	{
		showdir(dir->nextDir, num);
	}
	return;
}
/*��ʾ�ļ�*/
void FileSystem::showfile(File *file, int num)//Ŀ¼չʾ�Ӻ������ݹ��ļ�
{
	if (file->f_name!= "")
		cout << string(4 * num, '-') << "�ļ�" << file->f_name << endl;
	if (file->nextFile != NULL)
		showfile(file->nextFile, num);
	return;
}
/*��ʾ�ļ�ϵͳ�ṹ*/
void FileSystem::showAll()
{
	Dir *d = new Dir();
	File *f = new File();
	d = root;
	cout << "root" << endl;
	if (d->dirptr != NULL)
		showdir(d->dirptr, 1);
	if (d->fileptr != NULL) {
		showfile(d->fileptr, 1);
	}
	return;
}
/*�����ļ�*/
void FileSystem::createfile()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H��%M��%S", localtime(&Time));
	File *temp = new File();
	cin >> temp->f_name;
	if (nowDir->fileptr == NULL)
	{
		nowDir->fileptr = temp;
		temp->f_changetime = t;
		temp->f_createtime = t;
	}
	else
	{
		File *tp = new File();
		tp = nowDir->fileptr;
		while (tp->nextFile != NULL)
		{
			if (tp->f_name == temp->f_name)
			{
				cout << "��Ŀ¼������ͬ���ļ�������ʧ��" << endl;
				return;
			}
			tp = tp->nextFile;
		}
		if (tp->f_name == temp->f_name)
		{
			cout << "��Ŀ¼������ͬ���ļ�������ʧ��" << endl;
			return;
		}
		tp->nextFile = temp;
		temp->f_changetime = t;
		temp->f_createtime = t;
	}
	cout << "�ļ������ɹ�" << endl;
	return;
}
/*ɾ���ļ�*/
void FileSystem::movefile()
{
	string name;
	cin >> name;
	File *tp = new File();
	tp = nowDir->fileptr;
	if (tp == NULL)
	{
		cout << "��Ŀ¼��û���ļ�" << endl;
		return;
	}
	else if (tp->nextFile == NULL)
	{
		if (tp->f_name == name)
		{
			nowDir->fileptr = NULL;
			cout << "�ļ�ɾ���ɹ�" << endl;
			return;
		}
	}
	else
	{
		if (tp->f_name == name)
		{
			nowDir->fileptr = tp->nextFile;
			cout << "�ļ�ɾ���ɹ�" << endl;
			return;
		}
		else
		{
			while (tp->nextFile != NULL)
			{
				if (tp->nextFile->f_name == name)
				{
					tp->nextFile = tp->nextFile->nextFile;
					cout << "�ļ�ɾ���ɹ�" << endl;
					return;
				}
				tp = tp->nextFile;
			}
		}
	}
	cout << "û���ҵ�ָ��ɾ���ļ�" << endl;
	return;
}
/*�������ļ�*/
void FileSystem::namefile()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H��%M��%S", localtime(&Time));
	string old, xin;
	cin >> old >> xin;
	if (nowDir->fileptr == NULL)
		cout << "��ǰ·���²������ļ�!" << endl;
	else
	{
		File *ptr = new File();
		File *ptr1 = new File();
		ptr = nowDir->fileptr;
		ptr1 = nowDir->fileptr;
		while (ptr != NULL)
		{
			if (ptr->f_name == old)//��ǰ·���´���Ҫ���������ļ�
			{
				while (ptr1 != NULL)
				{
					if (ptr1->f_name == xin)//����������ļ�������ԭ�����ڵ��ļ���ͬ
					{
						cout << "���ļ�����ԭ��ĳ�ļ�������!" << endl;
						return;
					}
					ptr1 = ptr1->nextFile;
				}
				ptr->f_name = xin;
				ptr->f_changetime = t;
				cout << "�������ɹ���" << endl;
				return;
			}
			ptr = ptr->nextFile;
		}
		cout << "������ָ���ļ�" << endl;
	}
	return;
}
/*�����ļ�*/
void FileSystem::copyfile()
{
	string name;
	cin >> name;
	if (nowDir->fileptr == NULL)//�ļ�������
		cout << "���ļ�������!" << endl;
	else//�� �鵽�ŵ�tempfile
	{
		File *tp = new File();
		tp = nowDir->fileptr;
		while (tp != NULL)
		{
			if (tp->f_name == name)
			{
				tempfile = tp;
				cout << "���Ƴɹ���" << endl;
				return;
			}
			tp = tp->nextFile;
		}
		cout << "���ļ�������!" << endl;
	}
	return;
}
/*ճ���ļ�*/
void FileSystem::pastefile()
{
	if (tempfile == NULL)
	{
		cout << "����δ�����ļ�" << endl;
	}
	else if (nowDir->fileptr == NULL)
	{
		nowDir->fileptr = new File();
		nowDir->fileptr->f_name = tempfile->f_name;
		nowDir->fileptr->f_changetime = tempfile->f_changetime;
		nowDir->fileptr->f_content = tempfile->f_content;
		nowDir->fileptr->f_createtime = tempfile->f_createtime;
		nowDir->fileptr->f_size = tempfile->f_size;
		cout << "ճ���ļ��ɹ�" << endl;
	}
	else
	{
		File *temp = new File();
		temp = nowDir->fileptr;
		bool flag = false;
		while (temp->nextFile != NULL)//ֱ��Ϊ��
		{
			if (temp->f_name == tempfile->f_name)
			{
				flag = true;
				break;
			}
			temp = temp->nextFile;
		}
		if (nowDir->fileptr->f_name == tempfile->f_name||(temp->nextFile == NULL && temp->f_name == tempfile->f_name))//�ж������һ���ļ������һ���ļ��Ƿ���Ҫճ����ͬ��
		{
			flag = true;
		}
		if (flag == false)
		{
			temp->nextFile = new File();
			temp->nextFile->f_changetime = tempfile->f_changetime;
			temp->nextFile->f_createtime = tempfile->f_createtime;
			temp->nextFile->f_content = tempfile->f_content;
			temp->nextFile->f_name = tempfile->f_name;
			temp->nextFile->f_size = tempfile->f_size;
			cout << "�ļ�ճ���ɹ���" << endl;
		}
		else
			cout << "��ǰĿ¼��ͬ���ļ�" << endl;
	}
}
/*��ȡ�ļ�*/
void FileSystem::cat()
{
	string name;
	cin >> name;
	if (nowDir->fileptr == NULL)
		cout << "��ǰĿ¼��û���ļ�" << endl;
	else
	{
		File *tp = new File();
		tp = nowDir->fileptr;
		while (tp != NULL)
		{
			if (tp->f_name == name)
			{
				cout << "�ļ�" << tp->f_name << ":" << tp->f_content << endl;
				return;
			}
			tp = tp->nextFile;
		}
		cout << "�ļ������������Ҳ���ָ���ļ�" << endl;
	}
	return;
}
/*�޸��ļ�����*/
void FileSystem::readandwrite()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H��%M��%S", localtime(&Time));
	string name;
	cin >> name;
	if (nowDir->fileptr == NULL)
		cout << "��ǰĿ¼û���ļ�" << endl;
	else
	{
		File *tp = new File();
		tp = nowDir->fileptr;
		while (tp != NULL)
		{
			if (tp->f_name == name)
			{
				cout << "�ļ���" << tp->f_name << "����Ϊ";
				if (tp->readandwrite == true)
					cout << "�ɶ���д" << endl;
				else
					cout << "�ɶ�" << endl;
				cout << "����0������Ϊֻ��������1������Ϊ�ɶ���д:";
				int type; cin >> type;
				if (type == 1)
					tp->readandwrite = true;
				else
					tp->readandwrite = false;
				cout << "�޸ĳɹ�����ǰ�ļ�����Ϊ:";
				if (tp->readandwrite == true)
					cout << "�ɶ���д" << endl;
				else
					cout << "�ɶ�" << endl;
				tp->f_changetime = t;
				return;
			}
			tp = tp->nextFile;
		}
		cout << "������Ҫָ���ļ�" << endl;
	}
	return;
}
/*�༭�ļ�����*/
void FileSystem::vi()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H��%M��%S", localtime(&Time));
	string name;
	cin >> name;
	if (nowDir->fileptr == NULL)
		cout << "��ǰĿ¼û���ļ�" << endl;
	else
	{
		File *tp = new File();
		tp = nowDir->fileptr;
		while (tp != NULL)
		{
			if (tp->f_name == name)
			{
				if (tp->readandwrite == true)
				{
					cout << "�������ļ�����,����һ������'#'��������" << endl;
					string s = "", str;
					while (getline(cin, str))
					{
						if (str == "#")
							break;
						s += str;
						s += "\n";
					}
					tp->f_content = s;
					tp->f_size = s.length() - 1;
					tp->f_changetime = t;
					cout << "�ļ�д��ɹ���" << endl;
					return;
				}
				else
				{
					cout << "���ļ�Ϊֻ���ļ�������д��!" << endl;
				}
				return;
			}
			tp = tp->nextFile;
		}
		cout << "������ָ���ļ�" << endl;
	}
	return;
}