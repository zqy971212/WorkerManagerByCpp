#include "Employee.h"

//构造函数
Employee::Employee(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}
//显示个人信息
void Employee::ShowInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->GetDeptInfo()
		<< "\t岗位职责：完成经理交给的任务" << endl;
}

//获取岗位信息
string Employee::GetDeptInfo()
{
	return string("员工");
}