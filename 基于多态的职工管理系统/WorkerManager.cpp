#include "WorkerManager.h"

WorkerManager::WorkerManager()
{
	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  //���ļ�
	if (!ifs.is_open())
	{
		//cout << "�ļ�������!" << endl;

		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		//��ʼ�ļ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����ڣ����ļ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		//cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3���ļ����ڣ����Ҽ�¼������
	int num = this->getEmpNum();

	//���Դ���
	//cout << "ְ������Ϊ�� " << num<<endl;
	//��������
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ����ݴ浽������
	this->init_Emp();

	//���Դ���
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "ְ�����:" << this->m_EmpArray[i]->m_ID
	//		<< "ְ������:" << this->m_EmpArray[i]->m_Name
	//		<< "ְ�����ţ�" << this->m_EmpArray[i]->m_DeptID << endl;

	//}
}
//��ʾ
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "********* ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "************* 0.�˳�������� *************" << endl;
	cout << "************* 1.����ְ����Ϣ *************" << endl;
	cout << "************* 2.��ʾְ����Ϣ *************" << endl;
	cout << "************* 3.ɾ����ְְ�� *************" << endl;
	cout << "************* 4.�޸�ְ����Ϣ *************" << endl;
	cout << "************* 5.����ְ����Ϣ *************" << endl;
	cout << "************* 6.���ձ������ *************" << endl;
	cout << "************* 7.��������ĵ� *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
//���ְ��
void WorkerManager::AddEmp()
{
	cout << "��������Ҫ��ӵ�����" << endl;
	int addNum = 0;  //�����û�������
	cin >> addNum;
	if (addNum > 0)
	{
		//���
		//�������ӿռ��С
		int newSize = this->m_EmpNum + addNum;  //�¿ռ�=ԭ������+��������

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ������ݿ������¿ռ���      (�൱�ڽ�ԭ���ľ����ݿ�����һ������Ŀռ��У�Ȼ������������ݣ�
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;       //ID
			string name;   //����
			int dSelect;  //����ѡ��

			cout << "������� " << i + 1 << "����ְ�����" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			//�Լ��¼ӵĹ��ܣ�ID���޷��ظ�
			if (ret!=-1)
			{
				cout << "id�Ѵ��ڣ�" << endl;
				system("pause");
				system("cls");
				return;
			}
			else
			{

				cout << "������� " << i + 1 << "����ְ������" << endl;
				cin >> name;

				cout << "��ѡ���ְ����λ" << endl;
				cout << "1����ְͨ��" << endl;
				cout << "2������" << endl;
				cout << "3���ϰ�" << endl;
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
				//��������ְ��ָ�룬���浽������
				newSpace[this->m_EmpNum + i] = w1;
			}


		}
		//�ͷ�ԭ�пռ�   ��ΪҪ���¼�¼�µ�����
		delete[] this->m_EmpArray;

		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;

		//������ְ��Ա��
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//��ӳɹ�����
		cout << "�ɹ���� " << addNum << " ����ְ��" << endl;
		//���ñ����ļ��ĺ���
		this->Save();
	}
	else
	{
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");
}
//�����ļ�
void WorkerManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);  //������ķ�ʽд�ļ�
	//��ÿ�˵�д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	//�ر��ļ�
	ofs.close();
}
//ͳ���ļ��е�����
int WorkerManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int num = 0;
	//��������ͳ����������
	while (ifs >> id && ifs >> name && ifs >> dId)  //�����ݣ������᷵��false���Զ��˳�ѭ��
	{
		num++;
	}
	ifs.close();
	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;  //�±꣬��¼�������ݵ���
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* w1 = NULL;
		if (dId == 1)
		{
			//��ͨԱ��
			w1 = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			//����
			w1 = new Manager(id, name, dId);
		}
		else
		{
			//�ϰ�
			w1 = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = w1;
		index++;
	}
	ifs.close();
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//���ö�̬���ó���ӿ�
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "������Ҫɾ��Ա����ְ�����" << endl;
		int id=0;
		cin >> id;
		//���id�Ƿ����
		int index = this->IsExist(id);
		if (index != -1)
		{
			//����ǰ��  ���ݵ�ǰ�ı�ţ����������Ե�����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;  //����������Ա����
			this->Save();  //���浽�ļ���

			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//�ҵ�ְ��
			index = i;    ////��������� index=id  ����ID���ڴ���������� �Ų��˼���Сʱ��������
			//cout << "ְ������" << endl;
			break;
		}
	}
	return index;
}

//�޸�ְ��
void WorkerManager::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������Ҫ�޸ĵ�Ա����ְ����" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);

		if (ret != -1)
		{
			//�ҵ����ˣ���ɾ��ԭ�е�����
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName;
			int dSelect = 0;

			cout << "���ҵ���" << id << "��ְ�����������µ�ְ����" << endl;
			cin >> newId;

			cout << "�������޸ĺ������" << endl;
			cin >> newName;

			cout << "�������޸ĺ�ĸ�λ" << endl;
			cout << "1����ͨԱ��" << endl
				<< "2������" << endl
				<< "3���ϰ�" << endl;

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

			cout << "�޸ĳɹ�" << endl;
			this->m_EmpArray[ret] = w1;
			this->Save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1������ְ����Ų���" << endl;
		cout << "2������ְ����������" << endl;

		int select;
		cin >> select;

		if (select == 1)
		{
			//���ձ��
			int id;
			cout << "��������ҵı��" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְԱ��Ϣ����" << endl;
				//this->m_EmpArray[ret]->ShowInfo();
				this->m_EmpArray[ret]->ShowInfo();
			}
			else
			{
				cout << "���޴���" << endl;
			}
		}
		else if (select == 2)
		{
			//��������
			cout << "������Ҫ���ҵ�����" << endl;
			string name;
			cin >> name;

			//�����ж��Ƿ�鵽�ı�־
			bool flag = false; //Ĭ��Ϊδ�ҵ�


			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name==name)
				{
					cout << "�ҵ�Ա�����Ϊ " << this->m_EmpArray[i]->m_ID << " ��Ա����Ϣ����" << endl; 
					flag = true;
					this->m_EmpArray[i]->ShowInfo();
				}
			}
			if (flag==false)
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "��ѡ������ʽ:" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i; //������Сֵ �� ���ֵ
			for (int j = i+1; j < this->m_EmpNum; j++)
			{
				if (select==1)  //����
				{
					if (this->m_EmpArray[minOrMax]->m_ID>this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else  //����
				{
					if (this->m_EmpArray[minOrMax]->m_ID<this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}
			//�ж�һ��ʼ�϶� ��Сֵ�����ֵ �ǲ��� �������Сֵ�����ֵ��������� ��������
			if (i!=minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}

		}
	}

	cout << "����ɹ��������Ľ��Ϊ��" << endl;
	this->Save();  //ͬ������
	this->Show_Emp();//չʾְ��
}

void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;

	int select;
	cin >> select;

	if (select==1)
	{
		ofstream ofs(FILENAME, ios::trunc);  //ɾ���ļ������´���
		ofs.close();

		//�ٽ�����������ɾ������ָ��ָΪ��
		if (this->m_EmpArray!=NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
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