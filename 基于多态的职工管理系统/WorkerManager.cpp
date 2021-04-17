#include "WorkerManager.h"

WorkerManager::WorkerManager()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  //读文件
	if (!ifs.is_open())
	{
		//cout << "文件不存在!" << endl;

		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		//初始文件为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在，但文件内容为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		//cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3、文件存在，并且记录着数据
	int num = this->getEmpNum();

	//测试代码
	//cout << "职工人数为： " << num<<endl;
	//更新人数
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件数据存到数组中
	this->init_Emp();

	//测试代码
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "职工编号:" << this->m_EmpArray[i]->m_ID
	//		<< "职工姓名:" << this->m_EmpArray[i]->m_Name
	//		<< "职工部门：" << this->m_EmpArray[i]->m_DeptID << endl;

	//}
}
//显示
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "********* 欢迎使用职工管理系统！ **********" << endl;
	cout << "************* 0.退出管理程序 *************" << endl;
	cout << "************* 1.增加职工信息 *************" << endl;
	cout << "************* 2.显示职工信息 *************" << endl;
	cout << "************* 3.删除离职职工 *************" << endl;
	cout << "************* 4.修改职工信息 *************" << endl;
	cout << "************* 5.查找职工信息 *************" << endl;
	cout << "************* 6.按照编号排序 *************" << endl;
	cout << "************* 7.清空所有文档 *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
//添加职工
void WorkerManager::AddEmp()
{
	cout << "请输入你要添加的人数" << endl;
	int addNum = 0;  //保存用户的输入
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算增加空间大小
		int newSize = this->m_EmpNum + addNum;  //新空间=原来人数+新增人数

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下数据拷贝到新空间下      (相当于将原来的旧数据拷贝到一个更大的空间中，然后再添加新数据）
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;       //ID
			string name;   //姓名
			int dSelect;  //部门选择

			cout << "请输入第 " << i + 1 << "个新职工编号" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			//自己新加的功能，ID号无法重复
			if (ret!=-1)
			{
				cout << "id已存在！" << endl;
				system("pause");
				system("cls");
				return;
			}
			else
			{

				cout << "请输入第 " << i + 1 << "个新职工姓名" << endl;
				cin >> name;

				cout << "请选择该职工岗位" << endl;
				cout << "1、普通职工" << endl;
				cout << "2、经理" << endl;
				cout << "3、老板" << endl;
				cin >> dSelect;

				Worker* w1 = NULL;
				switch (dSelect)
				{
				case 1:
					w1 = new Employee(id, name, 1);
					break;
				case 2:
					w1 = new Manager(id, name, 2);
					break;
				case 3:
					w1 = new Boss(id, name, 3);
					break;
				default:
					break;
				}
				//将创建的职工指针，保存到数组中
				newSpace[this->m_EmpNum + i] = w1;
			}


		}
		//释放原有空间   因为要重新记录新的数据
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更新新职工员数
		this->m_EmpNum = newSize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;

		//添加成功提醒
		cout << "成功添加 " << addNum << " 名新职工" << endl;
		//调用保存文件的函数
		this->Save();
	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");
}
//保存文件
void WorkerManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);  //用输出的方式写文件
	//将每人的写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	//关闭文件
	ofs.close();
}
//统计文件中的人数
int WorkerManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int num = 0;
	//读数据来统计人数变量
	while (ifs >> id && ifs >> name && ifs >> dId)  //读数据，读完后会返回false，自动退出循环
	{
		num++;
	}
	ifs.close();
	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;  //下标，记录存入数据的人
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* w1 = NULL;
		if (dId == 1)
		{
			//普通员工
			w1 = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			//经理
			w1 = new Manager(id, name, dId);
		}
		else
		{
			//老板
			w1 = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = w1;
		index++;
	}
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//利用多态调用程序接口
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入要删除员工的职工编号" << endl;
		int id=0;
		cin >> id;
		//检测id是否存在
		int index = this->IsExist(id);
		if (index != -1)
		{
			//数据前移  根据当前的编号，将后面所以的数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;  //更新数组人员个数
			this->Save();  //保存到文件中

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//找到职工
			index = i;    ////这里我填成 index=id  返回ID，内存出错！！！！ 排查了几个小时！！！！
			//cout << "职工存在" << endl;
			break;
		}
	}
	return index;
}

//修改职工
void WorkerManager::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		cout << "请输入你要修改的员工的职工号" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);

		if (ret != -1)
		{
			//找到此人，并删除原有的数据
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName;
			int dSelect = 0;

			cout << "查找到：" << id << "号职工，请输入新的职工号" << endl;
			cin >> newId;

			cout << "请输入修改后的姓名" << endl;
			cin >> newName;

			cout << "请输入修改后的岗位" << endl;
			cout << "1、普通员工" << endl
				<< "2、经理" << endl
				<< "3、老板" << endl;

			cin >> dSelect;

			Worker* w1 = NULL;
			switch (dSelect)
			{
			case 1:
				w1 = new Employee(newId, newName, dSelect);
				break;
			case 2:
				w1 = new Manager(newId, newName, dSelect);
				break;
			case 3:
				w1 = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			cout << "修改成功" << endl;
			this->m_EmpArray[ret] = w1;
			this->Save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1、按照职工编号查找" << endl;
		cout << "2、按照职工姓名查找" << endl;

		int select;
		cin >> select;

		if (select == 1)
		{
			//按照编号
			int id;
			cout << "请输入查找的编号" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				//找到职工
				cout << "查找成功，该职员信息如下" << endl;
				//this->m_EmpArray[ret]->ShowInfo();
				this->m_EmpArray[ret]->ShowInfo();
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			//按照姓名
			cout << "请输入要查找的姓名" << endl;
			string name;
			cin >> name;

			//加入判断是否查到的标志
			bool flag = false; //默认为未找到


			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name==name)
				{
					cout << "找到员工编号为 " << this->m_EmpArray[i]->m_ID << " 的员工信息如下" << endl; 
					flag = true;
					this->m_EmpArray[i]->ShowInfo();
				}
			}
			if (flag==false)
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "请选择排序方式:" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i; //声明最小值 或 最大值
			for (int j = i+1; j < this->m_EmpNum; j++)
			{
				if (select==1)  //升序
				{
					if (this->m_EmpArray[minOrMax]->m_ID>this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else  //降序
				{
					if (this->m_EmpArray[minOrMax]->m_ID<this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}
			//判断一开始认定 最小值或最大值 是不是 计算的最小值或最大值，如果不是 交换数据
			if (i!=minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}

		}
	}

	cout << "排序成功！排序后的结果为：" << endl;
	this->Save();  //同步更新
	this->Show_Emp();//展示职工
}

void WorkerManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1、确定" << endl;
	cout << "2、取消" << endl;

	int select;
	cin >> select;

	if (select==1)
	{
		ofstream ofs(FILENAME, ios::trunc);  //删除文件后重新创建
		ofs.close();

		//再将堆区的数据删除并将指针指为空
		if (this->m_EmpArray!=NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
	
}


WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}