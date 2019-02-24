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
		system("cls");//清屏函数
		cout << "欢迎使用cfeng用户文件系统\n输入login进行登陆\n输入exit退出系统\n";
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
	cout << "账号:";
	cin >> username;
	cout << "密码:";
	cin >> password;
	while (!flag)
	{
		ifstream inFile;
		inFile.open("user_info.txt");//读取账号文件，判断登录
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
			cout << "账号密码错误，请重新输入，或输入backtomain返回主界面" << endl;
			cout << "账号: ";
			cin >> username;
			if (username == "backtomain")
			{
				itface.i_main();
			}
			cout << "密码: ";
			cin >> password;
			if (password == "backtomain")
			{
				itface.i_main();
			}
		}
		ofstream out;//保存用
		out.open("username_login.txt");
		if (flag)
		{
			out << username << endl;
		}
		out.close();
		inFile.close();
	}
	itface.i_function();//进入功能界面
}

void Interface::i_function() {
	FileSystem fs;
	Interface itface;
	string str;
	time_t Time = time(0);      //创建目录时间
	char t[255];
	strftime(t, 255, "%Y·%m·%d  %H：%M：%S", localtime(&Time));//存入系统时间
	cout << "登陆成功，现在的时间是 -- " << t << endl;
	while (true)
	{
		fs.showplace();
		cin >> str;
		if (str == "help")
			itface.i_help();
		else if (str == "help?")
			cout << "显示帮助文档: help" << endl;
		else if (str == "exit")
			exit(0);
		else if (str == "exit?")
			cout << "退出系统: exit" << endl;
		else if (str == "createdir")
			fs.createdir();
		else if (str == "createdir?")
			cout << "创建一个目录: createdir 目录名 (例:createdir name)" << endl;
		else if (str == "movedir")
			fs.movedir();
		else if (str == "movedir?")
			cout << "删除一个目录: movedir 目录名 (例:movedir name)" << endl;
		else if (str == "namedir")
			fs.namedir();
		else if (str == "namedir?")
			cout << "重命名文件: namedir   旧文件名 新文件名 (例:namedir name_old name_new)" << endl;
		else if (str == "copydir")
			fs.copydir();
		else if (str == "copydir?")
			cout << "复制目录: copydir 目录名 (例:copydir name)" << endl;
		else if (str == "pastedir")
			fs.pasteDir();
		else if (str == "pastedir?")
			cout << "粘贴目录: pastedir " << endl;
		else if (str == "cd")
			fs.cd();
		else if (str == "cd..")
			fs.back();
		else if (str == "cd?")
		{
			cout << "进入下级目录: cd 目录名 (例:cd name)" << endl;
			cout << "返回上级目录: cd.. " << endl;
		}
		else if (str == "ls")
			fs.ls();
		else if (str == "ls?")
			cout << "显示当前路径下的文件夹和文件: ls " << endl;
		else if (str == "pwd")
			fs.pwd();
		else if (str == "pwd?")
			cout << "显示当前路径: pwd " << endl;
		else if (str == "createfile")
			fs.createfile();
		else if (str == "createfile?")
			cout << "创建一个文件: createfile 目录名 (例:createfile name)" << endl;
		else if (str == "movefile")
			fs.movefile();
		else if (str == "movefile?")
			cout << "删除一个文件: movefile  文件名 (例:movefile  name)" << endl;
		else if (str == "namefile")
			fs.namefile();
		else if (str == "namefile?")
			cout << "重命名文件: namefile   旧文件名 新文件名 (例:namefile name_old name_new)" << endl;
		else if (str == "copyfile")
			fs.copyfile();
		else if (str == "copyfile?")
			cout << "复制文件: copyfile 文件名 (例:copyfile name)" << endl;
		else if (str == "pastefile")
			fs.pastefile();
		else if (str == "pastefile?")
			cout << "粘贴文件: pastefile " << endl;
		else if (str == "cat")
			fs.cat();
		else if (str == "cat?")
			cout << "查看文件内容: cat 文件名 (例:cat name)" << endl;
		else if (str == "vi")
			fs.vi();
		else if (str == "vi?")
			cout << "编辑文件: vi 文件名 (例:vi name)" << endl;
		else if (str == "rw")
			fs.readandwrite();
		else if (str == "rw?")
			cout << "修改文件读写属性: rw 文件名  (例:rw a)" << endl;
		else if (str == "loginout")
			itface.i_main();
		else if (str == "loginout?")
			cout << "退出登录: loginout" << endl;
		else if(str=="clear")
			system("cls");
		else if (str == "clear?")
			cout << "清屏: clear" << endl;
		else if (str == "showall")
			fs.showAll();
		else if (str == "showall?")
			cout << "显示系统文件结构:showall" << endl;
		else
			cout << "您输入的指令有误，请重新输入" << endl;
	}
}

void Interface::i_help() {
	cout << "你可能需要以下帮助：" << endl;
	cout << "	目录命令:\n"
		<< "		createdir	新建目录\n"
		<< "		movedir		删除目录\n"
		<< "		namedir		重命名目录\n"
		<< "		copydir		复制目录\n"
		<< "		pastedir	粘贴目录\n"
		<< "		ls		显示当前路径下的文件夹和文件\n"
		<< "		cd		打开目录\n"
		<< "		cd..		返回上一级目录\n"
		<< "		pwd		显示当前路径\n"
		<< "		showall		显示系统文件结构\n"
		<< "	文件命令:\n"
		<< "		creatfile	新建文件\n"
		<< "		movefile	删除文件\n"
		<< "		namefile	重命名文件\n"
		<< "		copyfile	复制文件\n"
		<< "		pastefile	粘贴文件\n"
		<< "		cat		打开文件\n"
		<< "		vi		编辑文件\n"
		<< "		rw		修改文件属性\n"
		<< "	系统命令:\n"
		<< "		clear		清屏\n"
		<< "		loginout	注销\n"
		<< "		exit		直接退出\n"
		<< "		help		查看帮助\n";
	cout << "在命令后输入?可查看命令使用方法，例如createdir?\n\n";
	Interface itface;
	itface.i_function();
}