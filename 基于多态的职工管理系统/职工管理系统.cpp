#include <iostream>
using namespace std;
#include "WorkerManager.h"
//#include "Worker.h"
//#include "Employee.h"
//#include "Manager.h"
//#include "Boss.h"
int main()
{
	////���Դ���
	//Worker* w1 = NULL;
	//w1 = new Employee(1, "����", 1);
	//w1->ShowInfo();
	//delete w1;

	//w1 = new Manager(2, "����",2);
	//w1->ShowInfo();
	//delete w1;

	//w1 = new Boss(3, "����",3);
	//w1->ShowInfo();
	//delete w1;
	// 
	//ʵ����һ������ϵͳ�Ķ���
	WorkerManager wm;

	int choice = 0;
	while (true)
	{
		//��ʾ
		wm.Show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:     //�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1:    //����Ա��
			wm.AddEmp();
			break;
		case 2:    //��ʾԱ��
			wm.Show_Emp();
			break;
		case 3:    //ɾ��Ա��
			wm.Del_Emp();
			//���Դ���
			//wm.IsExist(1);
			break;
		case 4:    //�޸�Ա��
			wm.mod_Emp();
			break;
		case 5:    //����Ա��
			wm.find_Emp();
			break;
		case 6:    //����Ա��
			wm.Sort_Emp();
			break;
		case 7:    //���
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