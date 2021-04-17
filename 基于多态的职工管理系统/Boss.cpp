#include "Boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

//显示个人信息
void Boss::ShowInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->GetDeptInfo()
		<< "\t岗位职责：管理公司所有的事物" << endl;
}

//获取岗位信息
string Boss::GetDeptInfo()
{
	return string("老板");
}