#include "Boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

//��ʾ������Ϣ
void Boss::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->GetDeptInfo()
		<< "\t��λְ�𣺹���˾���е�����" << endl;
}

//��ȡ��λ��Ϣ
string Boss::GetDeptInfo()
{
	return string("�ϰ�");
}