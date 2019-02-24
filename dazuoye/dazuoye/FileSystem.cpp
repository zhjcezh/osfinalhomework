#define _CRT_SECURE_NO_WARNINGS
#include"FileSystem.h"
#include"Interface.h"
#include"Dir.h"
#include<iostream>
using namespace std;

FileSystem::FileSystem() 
{
	root = new Dir();//新建用户后，默认一个目录为用户根目录，文件夹名为root
	root->d_name = "root";
	nowDir = root;//当前目录为根目录
	tempfile = NULL;//复制文件为空
	tempdir = NULL;//复制文件夹为空
}
FileSystem::~FileSystem()
{
	delete root;
	delete nowDir;
	delete tempfile;
	delete tempdir;
}
/*显示当前位置*/
void FileSystem::showplace()//显示当前位置
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
/*创建目录*/
Dir* FileSystem::createdir()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H：%M：%S", localtime(&Time));
	Dir *temp = new Dir();
	cin >> temp->d_name;
	if (nowDir->dirptr == NULL)//如果该目录下没有文件夹
	{
		nowDir->dirptr = temp;
		temp->preDir = nowDir;
		temp->d_createtime = t;
		temp->d_changetime = t;
	}
	else//目录下有文件夹，所以要找到目录链表末端
	{
		Dir *tp;
		tp = nowDir->dirptr;
		while (tp->nextDir != NULL)
		{
			if (tp->d_name == temp->d_name)
			{
				cout << "同目录下文件夹不能重名！" << endl;
				return nowDir;
			}
			tp = tp->nextDir;
		}
		if (tp->d_name == temp->d_name)
		{
			cout << "同目录下文件夹不能重名！" << endl;
			return nowDir;
		}
		tp->nextDir = temp;
		temp->preDir = nowDir;
		temp->d_createtime = t;
		temp->d_changetime = t;
	}
	cout << "目录创建成功" << endl;
	return nowDir;
}
/*删除目录中的文件*/
void FileSystem::movefileindir(Dir *dir)
{
	dir->fileptr = NULL;
	return;
}
/*删除目录中的子目录*/
void FileSystem::submovedir(Dir* dir)
{
	if (dir == NULL)
		return;
	if (dir->fileptr != NULL)
		movefileindir(dir);
	if (dir->dirptr != NULL)//不为空
	{
		submovedir(dir->dirptr);//把该目录删除掉
	}
	if (dir->nextDir != NULL)//下一目录不为空
	{
		submovedir(dir->nextDir);//把该目录的下一目录也删除掉，递归
	}
	delete dir;
}
/*删除目录*/
void FileSystem::movedir()
{
	string name;
	cin >> name;
	Dir *tp = new Dir();
	tp = nowDir->dirptr;//当前目录的子目录链表指针
	if (nowDir->dirptr == NULL) 
	{
		cout << "当前目录中没有文件夹" << endl;
		return;
	}
	else if (tp->nextDir == NULL)//如果只有一个目录
	{
		if (tp->d_name == name)
		{
			movefileindir(tp);//删除子文件
			if (tp->dirptr == NULL)//如果没有子目录
			{
				nowDir->dirptr = NULL;
			}
			else//若果有子目录
			{
				submovedir(tp->dirptr);//删除子目录
				tp->dirptr = NULL;
				nowDir->dirptr = NULL;
			}
			cout << "目录删除成功" << endl;
			return;
		}
	}
	else//如果有多个目录
	{
		if (tp->d_name == name)
		{
			movefileindir(tp);//删除子文件
			nowDir->dirptr = tp->nextDir;//下一个目录接上
			cout << "目录删除成功" << endl;
			return;
		}
		else
		{
			while (tp->nextDir != NULL)
			{
				if (tp->nextDir->d_name == name)
				{
					movefileindir(tp->nextDir);//删除子文件
					if (tp->nextDir->dirptr != NULL)//如果有子目录
					{
						submovedir(tp->nextDir->dirptr);
					}
					tp->nextDir=tp->nextDir->nextDir;//下一个目录接上
					cout << "目录删除成功" << endl;
					return;
				}
				tp = tp->nextDir;
			}
		}
	}
	cout << "不存在要删除的目录" << endl;
}
/*重命名目录*/
void FileSystem::namedir()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H：%M：%S", localtime(&Time));
	string old, xin;
	cin >> old >> xin;
	if (nowDir->dirptr == NULL)
		cout << "当前路径下不存在目录!" << endl;
	else
	{
		Dir *temp = new Dir();
		temp = nowDir->dirptr;
		Dir *tp = new Dir();
		tp = nowDir->dirptr;
		while (temp != NULL)
		{
			if (temp->d_name == old)//当前路径下存在要重命名的目录
			{
				while (tp != NULL)
				{
					if (tp->d_name == xin)//重命名后的目录名字与原来存在的目录相同
					{
						cout << "新目录名与原有目录名重名!" << endl;
						return;
					}
					tp = tp->nextDir;
				}
				temp->d_name = xin;
				temp->d_changetime = t;
				cout << "重命名成功！" << endl;
				return;
			}
			temp = temp->nextDir;
		}
		cout << "不存在重命名目录" << endl;
	}
	return;
}
/*复制目录*/
void FileSystem::copydir()
{
	string name;
	cin >> name;
	if (nowDir->dirptr == NULL)//目录不存在
		cout << "该目录不存在目录!" << endl;
	else//有 查到放到tempdir
	{
		Dir *tp = new Dir();
		tp = nowDir->dirptr;
		while (tp != NULL)
		{
			if (tp->d_name == name)
			{
				tempdir = tp;
				cout << "复制成功" << endl;
				return;
			}
			tp = tp->nextDir;
		}
		cout <<"该目录不存在!" << endl;
	}
	return;
}
/*复制子目录*/
void FileSystem::subpastedir(Dir *dir1, Dir *dir2)
{
	if (dir1->dirptr != NULL)//1不空，把1放到2里面
	{
		dir2->dirptr = new Dir();
		dir2->dirptr->d_createtime = dir1->dirptr->d_createtime;
		dir2->dirptr->d_name = dir1->dirptr->d_name;
		dir2->dirptr->d_size = dir1->dirptr->d_size;
		dir2->dirptr->preDir = dir2;
		//文件复制
		subpastefile(dir1->dirptr->fileptr, dir2->dirptr);
		//递归
		subpastedir(dir1->dirptr, dir2->dirptr);
	}

	if (dir1->nextDir != NULL)//1有同级后续 继续复制
	{
		dir2->nextDir = new Dir();
		dir2->nextDir->d_createtime = dir1->nextDir->d_createtime;
		dir2->nextDir->d_name = dir1->nextDir->d_name;
		dir2->nextDir->d_size = dir1->nextDir->d_size;
		dir2->nextDir->preDir = dir2->preDir;
		//文件复制
		subpastefile(dir1->nextDir->fileptr, dir2->nextDir);
		subpastedir(dir1->nextDir, dir2->nextDir);
	}
	return;
}
/*粘贴复制目录下的文件*/
void FileSystem::subpastefile(File *file, Dir*dir)
{
	File *file1 = new File();
	file1 = file;
	Dir *dir1 = new Dir();
	dir1 = dir;
	if (dir1->fileptr != NULL)//有
	{
		File *ptr = new File();
		ptr = dir1->fileptr;
		while (ptr->nextFile != NULL) //同级后续文件复制
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
/*粘贴目录*/
void FileSystem::pasteDir()
{
	int flag = 0;
	if (tempdir == NULL)
	{
		cout << "您还未复制目录!" << endl;
		return;
	}
	Dir *temp = new Dir();
	temp = nowDir;
	while (temp != NULL)//绝对不能复制到本分支，保证本分支各个节点都不是tempdir
	{
		if (temp->d_name == tempdir->d_name)
		{
			cout << "不能将父目录复制到子目录下!" << endl;
			return;
		}
		temp = temp->preDir;
	}
	if (nowDir->dirptr == NULL)//当前目录下没有子目录
	{
		//复制文件夹
		nowDir->dirptr = new Dir();
		nowDir->dirptr->d_createtime = tempdir->d_createtime;
		nowDir->dirptr->d_name = tempdir->d_name;
		nowDir->dirptr->d_size = tempdir->d_size;
		nowDir->dirptr->preDir = nowDir;
		subpastefile(tempdir->fileptr, nowDir->dirptr);
		//复制文件夹中目录
		if (tempdir->dirptr != NULL)
		{

			nowDir->dirptr->dirptr = new Dir();
			nowDir->dirptr->dirptr->d_createtime = tempdir->dirptr->d_createtime;
			nowDir->dirptr->dirptr->d_name = tempdir->dirptr->d_name;
			nowDir->dirptr->dirptr->d_size = tempdir->dirptr->d_size;
			nowDir->dirptr->dirptr->preDir = nowDir->dirptr;
			//子文件复制
			subpastefile(tempdir->dirptr->fileptr, nowDir->dirptr->dirptr);
			//子目录
			subpastedir(tempdir->dirptr, nowDir->dirptr->dirptr);//把前面给后面的目标地址
		}
		cout << "文件粘贴成功！" << endl;
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
			//复制文件
			subpastefile(tempdir->fileptr, temp->nextDir);
			if (tempdir->dirptr != NULL)
			{
				temp->nextDir->dirptr = new Dir();
				temp->nextDir->dirptr->d_createtime = tempdir->dirptr->d_createtime;
				temp->nextDir->dirptr->d_name = tempdir->dirptr->d_name;
				temp->nextDir->dirptr->d_size = tempdir->dirptr->d_size;
				temp->nextDir->dirptr->preDir = temp->nextDir;
				//复制文件

				subpastefile(tempdir->dirptr->fileptr, temp->nextDir->dirptr);
				subpastedir(tempdir->dirptr, temp->nextDir->dirptr);
				cout << "粘贴目录成功!" << endl;
			}
		}
		else
			cout << "当前目录已存在!" << endl;

	}
}
/*进入目录*/
Dir* FileSystem::cd()
{
	string name;
	cin >> name;
	if (nowDir->dirptr == NULL)//当前目录下没有目录，就不用搜索了
	{
		cout << "请先创建一个目录!" << endl;
	}
	else
	{
		Dir *tp = new Dir();
		tp = nowDir->dirptr;
		while (tp != NULL)
		{
			if (tp->d_name == name)//找到要进入的目录
			{
				nowDir = tp;
				return nowDir;
			}
			tp = tp->nextDir;
		}
		cout << "该目录不存在" << endl;
	}
	return nowDir;
}
/*返回上级目录*/
Dir* FileSystem::back()
{
	if (nowDir == root)
	{
		cout << "当前为根目录，无法返回" << endl;
	}
	else
	{
		nowDir = nowDir->preDir;
	}
	return nowDir;
}
/*显示当前目录下所有目录和文件*/
void FileSystem::ls()
{
	if (nowDir->dirptr == NULL&&nowDir->fileptr == NULL)
	{
		cout << "当前目录下没有任何文件和文件夹" << endl;
	}
	cout << "----------------当 前 目 录 信 息----------------" << endl;
	Dir *temp = new Dir();
	temp = nowDir->dirptr;
	if (temp != NULL)
		cout << "子目录名称-------" << "创建时间------------------" << "修改时间------" << endl;
	while (temp != NULL)
	{
		cout << temp->d_name << string(10 - (temp->d_name.length()), ' ') << temp->d_createtime<< string(4, ' ') << temp->d_changetime << endl;
		temp = temp->nextDir;
	}
	
	File *tp = new File();
	tp = nowDir->fileptr;
	if (tp != NULL)
		cout << "子文件名称-------" << "创建时间------------------" << "修改时间------------------" <<"文件属性"<< endl;
	while (tp != NULL) 
	{
		cout << tp->f_name << string(10 - (tp->f_name.length()), ' ') << tp->f_createtime << string(4, ' ') << tp->f_changetime << string(11, ' ');
		if (tp->readandwrite == true)
			cout << "可读可写" << endl;
		else
			cout << "可读" << endl;
		tp = tp->nextFile;
	}
}
/*显示当前路径*/
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
/*递归显示所有目录*/
void FileSystem::showdir(Dir *dir, int num)//目录展示子函数，递归目录
{
	if (dir->d_name != "")
		cout << string(4 * num, '-') << "目录" << dir->d_name << endl;
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
/*显示文件*/
void FileSystem::showfile(File *file, int num)//目录展示子函数，递归文件
{
	if (file->f_name!= "")
		cout << string(4 * num, '-') << "文件" << file->f_name << endl;
	if (file->nextFile != NULL)
		showfile(file->nextFile, num);
	return;
}
/*显示文件系统结构*/
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
/*创建文件*/
void FileSystem::createfile()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H：%M：%S", localtime(&Time));
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
				cout << "该目录下已有同名文件，创建失败" << endl;
				return;
			}
			tp = tp->nextFile;
		}
		if (tp->f_name == temp->f_name)
		{
			cout << "该目录下已有同名文件，创建失败" << endl;
			return;
		}
		tp->nextFile = temp;
		temp->f_changetime = t;
		temp->f_createtime = t;
	}
	cout << "文件创建成功" << endl;
	return;
}
/*删除文件*/
void FileSystem::movefile()
{
	string name;
	cin >> name;
	File *tp = new File();
	tp = nowDir->fileptr;
	if (tp == NULL)
	{
		cout << "该目录下没有文件" << endl;
		return;
	}
	else if (tp->nextFile == NULL)
	{
		if (tp->f_name == name)
		{
			nowDir->fileptr = NULL;
			cout << "文件删除成功" << endl;
			return;
		}
	}
	else
	{
		if (tp->f_name == name)
		{
			nowDir->fileptr = tp->nextFile;
			cout << "文件删除成功" << endl;
			return;
		}
		else
		{
			while (tp->nextFile != NULL)
			{
				if (tp->nextFile->f_name == name)
				{
					tp->nextFile = tp->nextFile->nextFile;
					cout << "文件删除成功" << endl;
					return;
				}
				tp = tp->nextFile;
			}
		}
	}
	cout << "没有找到指定删除文件" << endl;
	return;
}
/*重命名文件*/
void FileSystem::namefile()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H：%M：%S", localtime(&Time));
	string old, xin;
	cin >> old >> xin;
	if (nowDir->fileptr == NULL)
		cout << "当前路径下不存在文件!" << endl;
	else
	{
		File *ptr = new File();
		File *ptr1 = new File();
		ptr = nowDir->fileptr;
		ptr1 = nowDir->fileptr;
		while (ptr != NULL)
		{
			if (ptr->f_name == old)//当前路径下存在要重命名的文件
			{
				while (ptr1 != NULL)
				{
					if (ptr1->f_name == xin)//重命名后的文件名字与原来存在的文件相同
					{
						cout << "新文件名与原有某文件名重名!" << endl;
						return;
					}
					ptr1 = ptr1->nextFile;
				}
				ptr->f_name = xin;
				ptr->f_changetime = t;
				cout << "重命名成功！" << endl;
				return;
			}
			ptr = ptr->nextFile;
		}
		cout << "不存在指定文件" << endl;
	}
	return;
}
/*复制文件*/
void FileSystem::copyfile()
{
	string name;
	cin >> name;
	if (nowDir->fileptr == NULL)//文件不存在
		cout << "该文件不存在!" << endl;
	else//有 查到放到tempfile
	{
		File *tp = new File();
		tp = nowDir->fileptr;
		while (tp != NULL)
		{
			if (tp->f_name == name)
			{
				tempfile = tp;
				cout << "复制成功！" << endl;
				return;
			}
			tp = tp->nextFile;
		}
		cout << "该文件不存在!" << endl;
	}
	return;
}
/*粘贴文件*/
void FileSystem::pastefile()
{
	if (tempfile == NULL)
	{
		cout << "您还未复制文件" << endl;
	}
	else if (nowDir->fileptr == NULL)
	{
		nowDir->fileptr = new File();
		nowDir->fileptr->f_name = tempfile->f_name;
		nowDir->fileptr->f_changetime = tempfile->f_changetime;
		nowDir->fileptr->f_content = tempfile->f_content;
		nowDir->fileptr->f_createtime = tempfile->f_createtime;
		nowDir->fileptr->f_size = tempfile->f_size;
		cout << "粘贴文件成功" << endl;
	}
	else
	{
		File *temp = new File();
		temp = nowDir->fileptr;
		bool flag = false;
		while (temp->nextFile != NULL)//直到为空
		{
			if (temp->f_name == tempfile->f_name)
			{
				flag = true;
				break;
			}
			temp = temp->nextFile;
		}
		if (nowDir->fileptr->f_name == tempfile->f_name||(temp->nextFile == NULL && temp->f_name == tempfile->f_name))//判断链表第一个文件和最后一个文件是否与要粘贴的同名
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
			cout << "文件粘贴成功！" << endl;
		}
		else
			cout << "当前目录有同名文件" << endl;
	}
}
/*读取文件*/
void FileSystem::cat()
{
	string name;
	cin >> name;
	if (nowDir->fileptr == NULL)
		cout << "当前目录下没有文件" << endl;
	else
	{
		File *tp = new File();
		tp = nowDir->fileptr;
		while (tp != NULL)
		{
			if (tp->f_name == name)
			{
				cout << "文件" << tp->f_name << ":" << tp->f_content << endl;
				return;
			}
			tp = tp->nextFile;
		}
		cout << "文件名输入有误，找不到指定文件" << endl;
	}
	return;
}
/*修改文件属性*/
void FileSystem::readandwrite()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H：%M：%S", localtime(&Time));
	string name;
	cin >> name;
	if (nowDir->fileptr == NULL)
		cout << "当前目录没有文件" << endl;
	else
	{
		File *tp = new File();
		tp = nowDir->fileptr;
		while (tp != NULL)
		{
			if (tp->f_name == name)
			{
				cout << "文件：" << tp->f_name << "属性为";
				if (tp->readandwrite == true)
					cout << "可读可写" << endl;
				else
					cout << "可读" << endl;
				cout << "输入0将更改为只读，输入1将更改为可读可写:";
				int type; cin >> type;
				if (type == 1)
					tp->readandwrite = true;
				else
					tp->readandwrite = false;
				cout << "修改成功，当前文件属性为:";
				if (tp->readandwrite == true)
					cout << "可读可写" << endl;
				else
					cout << "可读" << endl;
				tp->f_changetime = t;
				return;
			}
			tp = tp->nextFile;
		}
		cout << "不存在要指定文件" << endl;
	}
	return;
}
/*编辑文件内容*/
void FileSystem::vi()
{
	time_t Time = time(0);
	char t[255];
	strftime(t, 255, "%Y/%m/%d  %H：%M：%S", localtime(&Time));
	string name;
	cin >> name;
	if (nowDir->fileptr == NULL)
		cout << "当前目录没有文件" << endl;
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
					cout << "请输入文件内容,单独一行输入'#'结束输入" << endl;
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
					cout << "文件写入成功！" << endl;
					return;
				}
				else
				{
					cout << "该文件为只读文件，不能写入!" << endl;
				}
				return;
			}
			tp = tp->nextFile;
		}
		cout << "不存在指定文件" << endl;
	}
	return;
}