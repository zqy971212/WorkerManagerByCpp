#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"

class Boss :public Worker
{
public:
	Boss(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual void ShowInfo();

	//��ȡ��λ��Ϣ
	virtual string GetDeptInfo();
};