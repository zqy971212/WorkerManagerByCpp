#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"

class Boss :public Worker
{
public:
	Boss(int id, string name, int dId);

	//显示个人信息
	virtual void ShowInfo();

	//获取岗位信息
	virtual string GetDeptInfo();
};