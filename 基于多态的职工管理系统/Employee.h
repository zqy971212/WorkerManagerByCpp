#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
//��ͨԱ��
class Employee : public  Worker
{
public:
	//���캯��
	Employee(int id, string name, int dId);
	//��ʾ������Ϣ
	virtual void ShowInfo() ;

	//��ȡ��λ��Ϣ
	virtual string GetDeptInfo() ;
};