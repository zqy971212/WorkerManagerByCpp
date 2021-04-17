#include <iostream>
using namespace std;
#include "WorkerManager.h"
//#include "Worker.h"
//#include "Employee.h"
//#include "Manager.h"
//#include "Boss.h"
int main()
{
	////测试代码
	//Worker* w1 = NULL;
	//w1 = new Employee(1, "张三", 1);
	//w1->ShowInfo();
	//delete w1;

	//w1 = new Manager(2, "李四",2);
	//w1->ShowInfo();
	//delete w1;

	//w1 = new Boss(3, "周生",3);
	//w1->ShowInfo();
	//delete w1;
	// 
	//实例化一个管理系统的对象
	WorkerManager wm;

	int choice = 0;
	while (true)
	{
		//显示
		wm.Show_Menu();
		cout << "请输入你的选择" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:     //退出系统
			wm.ExitSystem();
			break;
		case 1:    //增加员工
			wm.AddEmp();
			break;
		case 2:    //显示员工
			wm.Show_Emp();
			break;
		case 3:    //删除员工
			wm.Del_Emp();
			//测试代码
			//wm.IsExist(1);
			break;
		case 4:    //修改员工
			wm.mod_Emp();
			break;
		case 5:    //查找员工
			wm.find_Emp();
			break;
		case 6:    //排序员工
			wm.Sort_Emp();
			break;
		case 7:    //清空
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}