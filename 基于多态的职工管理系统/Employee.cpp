#include "Employee.h"

//���캯��
Employee::Employee(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}
//��ʾ������Ϣ
void Employee::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->GetDeptInfo()
		<< "\t��λְ����ɾ�����������" << endl;
}

//��ȡ��λ��Ϣ
string Employee::GetDeptInfo()
{
	return string("Ա��");
}