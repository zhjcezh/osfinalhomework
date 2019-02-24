#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H
#include"Dir.h"
class Interface
{
public:
	Interface();
	~Interface();
	void i_login();//用户登录界面
	void i_main();//欢迎主界面
	void i_function();//功能界面
	void i_help();//帮助文档	
};

#endif