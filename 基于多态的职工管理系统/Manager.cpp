#include "Manager.h"

//���캯��
Manager::Manager(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}
//��ʾ������Ϣ
void Manager::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->GetDeptInfo()
		<< "\t��λְ������ϰ彻�������񣬲��·��������ͨԱ��" << endl;
}

//��ȡ��λ��Ϣ
string Manager::GetDeptInfo()
{
	return string("����");
}