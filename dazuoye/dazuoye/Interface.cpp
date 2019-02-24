#define _CRT_SECURE_NO_WARNINGS
#include"Interface.h"
#include"FileSystem.h"
#include"Dir.h"
using namespace std;

Interface::Interface(){}

Interface::~Interface(){}

void Interface::i_main() {
	Interface itface;
	string str;
	while (1)
	{
		system("cls");//��������
		cout << "��ӭʹ��cfeng�û��ļ�ϵͳ\n����login���е�½\n����exit�˳�ϵͳ\n";
		cin >> str;
		if (str == "login")
		{
			itface.i_login();
		}
		else if (str == "exit")
		{
			exit(0);
		}
	}
}

void Interface::i_login() {
	Interface itface;
	string username, password;
	string readusername, readpassword;
	int flag = 0;
	cout << "�˺�:";
	cin >> username;
	cout << "����:";
	cin >> password;
	while (!flag)
	{
		ifstream inFile;
		inFile.open("user_info.txt");//��ȡ�˺��ļ����жϵ�¼
		while (inFile >> readusername >> readpassword)
		{
			if (readusername == username && readpassword == password)
			{
				flag++;
				break;
			}
		}
		if (!flag)//flag==0
		{
			cout << "�˺�����������������룬������backtomain����������" << endl;
			cout << "�˺�: ";
			cin >> username;
			if (username == "backtomain")
			{
				itface.i_main();
			}
			cout << "����: ";
			cin >> password;
			if (password == "backtomain")
			{
				itface.i_main();
			}
		}
		ofstream out;//������
		out.open("username_login.txt");
		if (flag)
		{
			out << username << endl;
		}
		out.close();
		inFile.close();
	}
	itface.i_function();//���빦�ܽ���
}

void Interface::i_function() {
	FileSystem fs;
	Interface itface;
	string str;
	time_t Time = time(0);      //����Ŀ¼ʱ��
	char t[255];
	strftime(t, 255, "%Y��%m��%d  %H��%M��%S", localtime(&Time));//����ϵͳʱ��
	cout << "��½�ɹ������ڵ�ʱ���� -- " << t << endl;
	while (true)
	{
		fs.showplace();
		cin >> str;
		if (str == "help")
			itface.i_help();
		else if (str == "help?")
			cout << "��ʾ�����ĵ�: help" << endl;
		else if (str == "exit")
			exit(0);
		else if (str == "exit?")
			cout << "�˳�ϵͳ: exit" << endl;
		else if (str == "createdir")
			fs.createdir();
		else if (str == "createdir?")
			cout << "����һ��Ŀ¼: createdir Ŀ¼�� (��:createdir name)" << endl;
		else if (str == "movedir")
			fs.movedir();
		else if (str == "movedir?")
			cout << "ɾ��һ��Ŀ¼: movedir Ŀ¼�� (��:movedir name)" << endl;
		else if (str == "namedir")
			fs.namedir();
		else if (str == "namedir?")
			cout << "�������ļ�: namedir   ���ļ��� ���ļ��� (��:namedir name_old name_new)" << endl;
		else if (str == "copydir")
			fs.copydir();
		else if (str == "copydir?")
			cout << "����Ŀ¼: copydir Ŀ¼�� (��:copydir name)" << endl;
		else if (str == "pastedir")
			fs.pasteDir();
		else if (str == "pastedir?")
			cout << "ճ��Ŀ¼: pastedir " << endl;
		else if (str == "cd")
			fs.cd();
		else if (str == "cd..")
			fs.back();
		else if (str == "cd?")
		{
			cout << "�����¼�Ŀ¼: cd Ŀ¼�� (��:cd name)" << endl;
			cout << "�����ϼ�Ŀ¼: cd.. " << endl;
		}
		else if (str == "ls")
			fs.ls();
		else if (str == "ls?")
			cout << "��ʾ��ǰ·���µ��ļ��к��ļ�: ls " << endl;
		else if (str == "pwd")
			fs.pwd();
		else if (str == "pwd?")
			cout << "��ʾ��ǰ·��: pwd " << endl;
		else if (str == "createfile")
			fs.createfile();
		else if (str == "createfile?")
			cout << "����һ���ļ�: createfile Ŀ¼�� (��:createfile name)" << endl;
		else if (str == "movefile")
			fs.movefile();
		else if (str == "movefile?")
			cout << "ɾ��һ���ļ�: movefile  �ļ��� (��:movefile  name)" << endl;
		else if (str == "namefile")
			fs.namefile();
		else if (str == "namefile?")
			cout << "�������ļ�: namefile   ���ļ��� ���ļ��� (��:namefile name_old name_new)" << endl;
		else if (str == "copyfile")
			fs.copyfile();
		else if (str == "copyfile?")
			cout << "�����ļ�: copyfile �ļ��� (��:copyfile name)" << endl;
		else if (str == "pastefile")
			fs.pastefile();
		else if (str == "pastefile?")
			cout << "ճ���ļ�: pastefile " << endl;
		else if (str == "cat")
			fs.cat();
		else if (str == "cat?")
			cout << "�鿴�ļ�����: cat �ļ��� (��:cat name)" << endl;
		else if (str == "vi")
			fs.vi();
		else if (str == "vi?")
			cout << "�༭�ļ�: vi �ļ��� (��:vi name)" << endl;
		else if (str == "rw")
			fs.readandwrite();
		else if (str == "rw?")
			cout << "�޸��ļ���д����: rw �ļ���  (��:rw a)" << endl;
		else if (str == "loginout")
			itface.i_main();
		else if (str == "loginout?")
			cout << "�˳���¼: loginout" << endl;
		else if(str=="clear")
			system("cls");
		else if (str == "clear?")
			cout << "����: clear" << endl;
		else if (str == "showall")
			fs.showAll();
		else if (str == "showall?")
			cout << "��ʾϵͳ�ļ��ṹ:showall" << endl;
		else
			cout << "�������ָ����������������" << endl;
	}
}

void Interface::i_help() {
	cout << "�������Ҫ���°�����" << endl;
	cout << "	Ŀ¼����:\n"
		<< "		createdir	�½�Ŀ¼\n"
		<< "		movedir		ɾ��Ŀ¼\n"
		<< "		namedir		������Ŀ¼\n"
		<< "		copydir		����Ŀ¼\n"
		<< "		pastedir	ճ��Ŀ¼\n"
		<< "		ls		��ʾ��ǰ·���µ��ļ��к��ļ�\n"
		<< "		cd		��Ŀ¼\n"
		<< "		cd..		������һ��Ŀ¼\n"
		<< "		pwd		��ʾ��ǰ·��\n"
		<< "		showall		��ʾϵͳ�ļ��ṹ\n"
		<< "	�ļ�����:\n"
		<< "		creatfile	�½��ļ�\n"
		<< "		movefile	ɾ���ļ�\n"
		<< "		namefile	�������ļ�\n"
		<< "		copyfile	�����ļ�\n"
		<< "		pastefile	ճ���ļ�\n"
		<< "		cat		���ļ�\n"
		<< "		vi		�༭�ļ�\n"
		<< "		rw		�޸��ļ�����\n"
		<< "	ϵͳ����:\n"
		<< "		clear		����\n"
		<< "		loginout	ע��\n"
		<< "		exit		ֱ���˳�\n"
		<< "		help		�鿴����\n";
	cout << "�����������?�ɲ鿴����ʹ�÷���������createdir?\n\n";
	Interface itface;
	itface.i_function();
}