#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"
#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	WorkerManager();

	//��ʾ����
	void Show_Menu();

	//�˳�ϵͳ����
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;

	//���ְ��
	void AddEmp();

	//�����ļ�
	void Save();

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ��е�����
	int getEmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�ְ���Ƿ����
	int IsExist(int id);

	//�޸�ְ��
	void mod_Emp();

	//����ְ��
	void find_Emp();

	//���ձ��������
	void Sort_Emp();

	//�������
	void Clean_File();

	~WorkerManager();
};