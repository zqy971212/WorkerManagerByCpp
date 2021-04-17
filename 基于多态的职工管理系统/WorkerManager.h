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

	//显示函数
	void Show_Menu();

	//退出系统函数
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void AddEmp();

	//保存文件
	void Save();

	//判断文件是否为空
	bool m_FileIsEmpty;

	//统计文件中的人数
	int getEmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//判断职工是否存在
	int IsExist(int id);

	//修改职工
	void mod_Emp();

	//查找职工
	void find_Emp();

	//按照编号排序函数
	void Sort_Emp();

	//清空数据
	void Clean_File();

	~WorkerManager();
};