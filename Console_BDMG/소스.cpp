#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#pragma disable(warning:4996)


using namespace std;

class Jungsuki{ // ��ü���� ����� �����͸� �Ҵ��ϴ� Ŭ����
protected:
	char *name; // ����
	char *phonenumber; // ��ȭ��ȣ
	int price; // ���ݾ�
	char *jungmodel; // ������ ���̸�
	char *start; // �����
	char *period; // ���Ⱓ
public:
	Jungsuki(){}; 
	Jungsuki(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_start, char *_period);
	Jungsuki(const Jungsuki &St);
	~Jungsuki();
	virtual void Show() const; // ��� �����Լ�
	char *GetName() const{ return name; };
	char *Getphonenumber() const{ return phonenumber; };
	int Getprice() const{ return price; };
	char *Getjungmodel() const{ return jungmodel; };
	char *Getstart() const{ return start; };
	char *Getperiod() const{ return period; }; // �ڷ���� ������ get������
};

Jungsuki::Jungsuki(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_start, char *_period)
{
	this->name = new char[strlen(_name) + 1];
	strcpy(name, _name);
	this->phonenumber = new char[strlen(_phonenumber) + 1];
	strcpy(phonenumber, _phonenumber);
	this->price = _price;
	this->jungmodel = new char[strlen(_jungmodel) + 1];
	strcpy(jungmodel, _jungmodel);
	this->start = new char[strlen(_start) + 1];
	strcpy(start, _start);
	this->period = new char[strlen(_period) + 1];
	strcpy(period, _period);
} // ���� ��� ������

Jungsuki::Jungsuki(const Jungsuki &p)
{
	this->name = new char[strlen(p.name) + 1];
	strcpy(name, p.name);
	this->phonenumber = new char[strlen(p.phonenumber) + 1];
	strcpy(phonenumber, p.phonenumber);
	this->price = p.price;
	this->jungmodel = new char[strlen(p.jungmodel) + 1];
	strcpy(jungmodel, p.jungmodel);
	this->start = new char[strlen(p.start) + 1];
	strcpy(start, p.start);
	this->period = new char[strlen(p.period) + 1];
	strcpy(period, p.period);
} // ���������

Jungsuki::~Jungsuki(){
	delete[]name;
	delete[]phonenumber;
	delete[]jungmodel;
	delete[]start;
	delete[]period;
} // �Ҹ���

void Jungsuki::Show() const{
	cout << phonenumber;
	cout.width(15);
	cout << name;
	cout.width(12);
	cout << price;
	cout.width(15);
	cout << jungmodel;
	cout.width(15);
	cout << start;
	cout.width(10);
	cout << period << endl;
} // ��� �Լ�

class Bidet : public Jungsuki // �⺻ �ڷḦ ��ӹ޾� ����� ����
{
	char *bidet; // ��� �𵨸�
public:
	Bidet(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_bidet, char *_start, char *_period); // �񵥸� �߰��� ������
	virtual void Show() const; // ��� ���� �Լ�
	char *Getbidet() const{ return bidet; }; // ��븦 �����ϴ� �Լ�
	void setJungsuki(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_start, char *_period, char *_bidet) // ������ �Է¹޴� set ������
	{
		this->bidet = new char[strlen(_bidet) + 1];
		strcpy(bidet, _bidet);
		this->name = new char[strlen(_name) + 1];
		strcpy(name, _name);
		this->phonenumber = new char[strlen(_phonenumber) + 1];
		strcpy(phonenumber, _phonenumber);
		this->price = _price;
		this->jungmodel = new char[strlen(_jungmodel) + 1];
		strcpy(jungmodel, _jungmodel);
		this->start = new char[strlen(_start) + 1];
		strcpy(start, _start);
		this->period = new char[strlen(_period) + 1];
		strcpy(period, _period);
	}
	void modify(); // �����ϴ� ���� �Լ�
};

Bidet::Bidet(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_bidet, char *_start, char *_period) : Jungsuki(_name, _phonenumber, _price, _jungmodel, _start, _period)
{
	this->bidet = new char[strlen(_bidet) + 1];
	strcpy(bidet, _bidet);
} // �񵥸� ���� �Է� �޴� ������


void Bidet::modify()
{
	cout << "====== ��� ���̽ʴϴ�. ======\n";
	cout << "���� �Է� : ";
	cin >> name;
	cout << "��ȭ��ȣ(-����) �Է� : ";
	cin >> phonenumber;
	cout << "��డ�� �Է� : ";
	cin >> price;
	cout << "������� �Է� : ";
	cin >> jungmodel;
	cout << "�����(Y/M/D) �Է� : ";
	cin >> start;
	cout << "���Ⱓ(����) �Է� : ";
	cin >> period;
	cout << "�񵥸� �Է� : ";
	cin >> bidet;
}

void Bidet::Show() const
{
	cout << this->GetName();
	cout.width(15);
	cout << this->Getphonenumber();
	cout.width(12);
	cout << this->Getprice();
	cout.width(15);
	cout << this->Getjungmodel();

	cout.width(15);
	cout << this->Getbidet();
	cout.width(12);
	cout << this->Getstart();
	cout.width(11);
	cout << this->Getperiod() << endl;
} // ��� �Լ�

class JungsukiManager{ // �޴� ���� Ŭ����
protected:
	int index;
	Bidet *JungP[50]; // �⺻���� 50�� ������ ����

public:
	JungsukiManager();
	void login();
	void input();
	void menu();
	void output();
	void modify();
	void deleted();
	void search();
	void save();
	void load();
	~JungsukiManager(){};
};

JungsukiManager::JungsukiManager() // �ʱ�ȭ ������
{
	index = 0;
}

void JungsukiManager::login() // �α��� �Լ�
{
	int i = 0;
	char _id[20], _pass[20], id[20], password[20], c = ' ';

	ifstream fin("identify.txt", ios::in, ios::trunc); // �α��� ���� ���� �ҷ�����
	fin >> _id;
	fin >> _pass;
	while (1)
	{
		cout << "\n\n-------------------W A T E R P U R I F I E R----------------------\n\n";
		cout << "                M A N A G E M E N T  S Y S T E M                \n\n\n\n";
		cout << "                   ID : ";
		cin >> id;
		cout << "\n\n             PASSWORD : ";
		while (c != 13)					// ��й�ȣ *�� ����ϴ� ����
		{

			c = getch();
			if ((c >= 'a'&& c <= 'z') || (c >= 'A'&&c <= 'Z') || (c >= '0'&& c <= '9'))
			{
				password[i] = c;
				i++;
				cout << '*';
			}
			if (c == '\b'&& i >= 1)
			{
				cout << "\b \b";
				i--;
				password[i] = '\0';
			}
			if (c == 13)
			{
				password[i] = '\0';
				break;
			}
		}
		if (strcmp(_id, id) == 0 && strcmp(_pass, password) == 0) // ����ó��
		{
			break;
		}
		else
		{
			system("cls");
			cout << "----------------ID�� PASSWORD�� �ٽ� �Է����ּ���.----------------\n";
			i = 0;
			c = ' ';
		}
	}
	fin.close(); // ���� ���� ����
}

void JungsukiManager::modify(){ // ���� ���� �Լ�
	char phonenumber[30];
	cout << "��ȭ��ȣ(-����) �Է� : "; // ��ȭ��ȣ�� �Է¹޾� ����
	cin >> phonenumber;
	for (int i = 0; i < index; i++) // �Է°� ��
	{
		if (strcmp(JungP[i]->Getphonenumber(), phonenumber) == 0)
		{
			JungP[i]->modify(); // �Է°� ������ ���� ���� �ҷ���
		}
	}
	cout << "====== ���������� ������ �ʴ´ٸ�, ��� ������ �����ϴ�. ======";
}

void JungsukiManager::input() // �Է� �Լ�
{
	char name[20], phonenumber[20], jungmodel[20] = "�̰��", start[20], bidet[20] = "�̰��", period[20]; 
	int price = 0;
	int select;

	cout << "=====�뿩 ��ǰ �Է�=====" << endl;
	cout << "1. ������ �뿩" << endl;
	cout << "2. ��� �뿩" << endl;
	cout << "3. ������, ��� �뿩" << endl;
	cout << ">> ";
	cin >> select;
	if ((select >= 4) || (select <= 0)) // ����ó��
	{
		cout << "  �߸��� �Է��Դϴ� !!" << endl;
	}
	else
	{
		cout << "��ȭ��ȣ(-����) �Է� : ";
		cin >> phonenumber;
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getphonenumber(), phonenumber) == 0)
			{
				cout << "�ߺ� ����� �Ұ����մϴ�." << endl;
				return;
			}
		}
		if (select == 1) // �����⸸ �뿩
		{
			cout << "����, ��డ��, �������, �����(Y/M/D), ���Ⱓ �Է�(�������� ������ �ּ���.) : " << endl;
			cin >> name >> price >> jungmodel >> start >> period;
			JungP[index++] = new Bidet(name, phonenumber, price, jungmodel, bidet, start, period);
		}
		else if (select == 2) // �񵥸� �뿩
		{
			cout << "����, ��డ��, �񵥸�, �����(Y/M/D), ���Ⱓ �Է�(�������� ������ �ּ���.)" << endl;
			cin >> name >> price >> bidet >> start >> period;
			JungP[index++] = new Bidet(name, phonenumber, price, jungmodel, bidet, start, period);
		}
		else if (select == 3) // ������, �� �� �� �뿩
		{
			cout << "����, ��డ��, �������, �񵥸�, �����(Y/M/D), ���Ⱓ �Է�(�������� ������ �ּ���.)" << endl;
			cin >> name >> price >> jungmodel >> bidet >> start >> period;
			JungP[index++] = new Bidet(name, phonenumber, price, jungmodel, bidet, start, period);
		}
		else {
			cout << "�߸��� �Է��Դϴ�!" << endl;
		}
	}
}

void JungsukiManager::deleted() // ���� ���� �Լ�
{
	char phonenumber[20], sel;
	int i = 0,j = 0;
	cout << "��ȭ��ȣ(-����) �Է� : ";
	cin >> phonenumber;
	for (i = 0; i < index; i++) // ��ȭ��ȣ�� ����ó��
	{
		if (strcmp(JungP[i]->Getphonenumber(), phonenumber) == 0)
		{
			cout << "�� ������ ã�ҽ��ϴ�. ������ �����մϱ�?(Y/N)";
			cin >> sel;
			break;
		}
	}
	if (sel == 'Y' || sel == 'y')
	{
		if (i == (index - 1))
			index -= 1;
		else
		{
			for (j = i; j < index; j++)
				JungP[j] = JungP[j + 1];
			index -= 1;
		}
	}
	else if (sel == 'N' || sel == 'n')
	{
		cout << "====== �� ���� ������ ����մϴ�. ======";
	}
	else
		cout << "====== �߸��� �Է��Դϴ�. ======" << endl;
	cout << "====== ���� ������ ������ �ʴ´ٸ�, ��� ������ �����ϴ�. ======";
}


void JungsukiManager::search() // �˻� �޴�
{
	char text[20];
	char sel;
	int count = 0;
	cout << "1. �������� ���� �˻�" << endl;
	cout << "2. ��ȭ��ȣ ���� �˻�" << endl;
	cout << "3. ������ �𵨷� ���� �˻�" << endl;
	cout << "4. �� �𵨷� ���� �˻�" << endl;
	cout << "5. �����(Y/M/D)�� ���� �˻�" << endl;
	cout << "6. ���Ⱓ(����)���� ���� �˻�" << endl;
	cout << "Q. �޴��� ������" << endl;
	cout << "\n>>";
	cin >> sel;
	switch (sel)
	{
	case '1':
		cout << "������ �Է����ּ���.(����� �Ͻ� Y/M/D ���·� �˻�) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n ���� �뿩 ������ �˻��մϴ�.\n";
		cout << "\n===========================================================================================";
		cout << "\n ����      ��ȭ��ȣ     ��డ��     ������𵨸�    �񵥸𵨸�    �����     ���Ⱓ\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->GetName(), text) == 0) // �Է°� ���Ͽ� �´°͸� ���
			{
				JungP[i]->Show();
				count++;
			}
		}
		if (count == 0)
			cout << "  ã�� �ڷᰡ �����ϴ� !!";
		cout << "===========================================================================================\n";
		break;
	case '2':
		cout << "������ �Է����ּ���.(����� �Ͻ� Y/M/D ���·� �˻�) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n �� ��ȭ��ȣ ������ �뿩�� �˻��մϴ�.\n";
		cout << "\n===========================================================================================";
		cout << "\n ����      ��ȭ��ȣ     ��డ��     ������𵨸�    �񵥸𵨸�    �����     ���Ⱓ\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getphonenumber(), text) == 0)// �Է°� ���Ͽ� �´°͸� ���
			{
				JungP[i]->Show();
			}
			count++;
		}
	
		if (count == 0)
			cout << "  ã�� �ڷᰡ �����ϴ� !!";
		cout << "===========================================================================================\n";
		break;
	case '3':
		cout << "������ �Է����ּ���.(����� �Ͻ� Y/M/D ���·� �˻�) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n �� �𵨷� ���� �뿩�� �˻��մϴ�.\n";
		cout << "\n===========================================================================================";
		cout << "\n ����      ��ȭ��ȣ     ��డ��     ������𵨸�    �񵥸𵨸�    �����     ���Ⱓ\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getjungmodel(), text) == 0)// �Է°� ���Ͽ� �´°͸� ���
			{
				JungP[i]->Show();
				count++;
			}
		}
			if (count == 0)
				cout << "  ã�� �ڷᰡ �����ϴ� !!";
		cout << "===========================================================================================\n";
		break;
	case '4':
		cout << "������ �Է����ּ���.(����� �Ͻ� Y/M/D ���·� �˻�) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n �� �𵨷� ���� �뿩�� �˻��մϴ�.\n";
		cout << "\n===========================================================================================";
		cout << "\n ����      ��ȭ��ȣ     ��డ��     ������𵨸�    �񵥸𵨸�    �����     ���Ⱓ\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getbidet(), text) == 0)// �Է°� ���Ͽ� �´°͸� ���
			{
				JungP[i]->Show();
				count++;
			}
		}
			if (count == 0)
				cout << "  ã�� �ڷᰡ �����ϴ� !!";
		cout << "===========================================================================================\n";
		break;
	case '5':
		cout << "������ �Է����ּ���.(����� �Ͻ� Y/M/D ���·� �˻�) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n ��¥�� �뿩�� ������ �˻��մϴ�.\n";
		cout << "\n===========================================================================================";
		cout << "\n ����      ��ȭ��ȣ     ��డ��     ������𵨸�    �񵥸𵨸�    �����     ���Ⱓ\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getstart(), text) == 0)// �Է°� ���Ͽ� �´°͸� ���
			{
				JungP[i]->Show();
			}
			count++;
		}

		if (count == 0)
			cout << "  ã�� �ڷᰡ �����ϴ� !!";
		cout << "===========================================================================================\n";
		break;
	case '6':
		cout << "������ �Է����ּ���.(����� �Ͻ� Y/M/D ���·� �˻�) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n �� ���� ������ �˻��մϴ�.\n";
		cout << "\n===========================================================================================";
		cout << "\n ����      ��ȭ��ȣ     ��డ��     ������𵨸�    �񵥸𵨸�    �����     ���Ⱓ\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getperiod(), text) == 0)// �Է°� ���Ͽ� �´°͸� ���
			{
				JungP[i]->Show();
			}
			count++;
		}

		if (count == 0) // ����ó��
			cout << "  ã�� �ڷᰡ �����ϴ� !!";
		cout << "===========================================================================================\n";
		break;
	case 'Q':
	case 'q':
		break;
	default:
		cout << "====== �߸��� �Է��Դϴ�. ======" << endl;
		break;
	}
}

void JungsukiManager::load()
{
	char sel;
	cout << "���� �̹� �ڷᰡ �ִٸ� �������뿡 �߰��˴ϴ�. �׷��� �������ϱ�?(Y/N)";
	cin >> sel;
	if (sel == 'Y' || sel == 'y')
	{
		ifstream fin("list.txt", ios::in, ios::trunc); 
		//�������� �Է��� ��ǥ�� ������ �ҷ���
		char name[20], phonenumber[20], jungmodel[20], start[20], bidet[20], period[20];
		int price = 0;
		if (!fin)
		{
			cout << "====== �߸��� �� ����Ʈ �Դϴ�. ======" << endl;
			return;
		}
		while (fin.eof() == false)
		{
			fin >> name;
			fin >> phonenumber;
			fin >> price;
			fin >> jungmodel;
			fin >> bidet;
			fin >> start;
			fin >> period;
			JungP[index] = new Bidet(name, phonenumber, price, jungmodel, bidet, start, period);
			index++;
		}
		output();
		cout << "====== �� ����Ʈ�� �ҷ����µ� �����Ͽ����ϴ�. ======" << endl;
		fin.close();
	}
	else if (sel == 'N' || sel == 'n')
		cout << "====== �� ����Ʈ �ε带 ����Ͽ����ϴ�. ======" << endl;
	else
		cout << "====== �߸��� �Է��Դϴ�. ======" << endl;
}

void JungsukiManager::save()
{
	char sel;
	cout << "������ ������ �ƴϸ�, ������ �ִ� ������ ���� �� �� �ֽ��ϴ�. �������ϱ�?(Y/N)";
	cin >> sel;
	if (sel == 'Y' || sel == 'y')
	{
		ofstream fout("list.txt", ios::out); 
		// �������� ����� ��ǥ�� ������ �ҷ���
		if (!fout)
		{
			cout << "====== �߸��� �� ����Ʈ �Դϴ�. ======";
		}
		for (int i = 0; i < index; i++)
		{
			fout << JungP[i]->GetName() << " ";
			fout << JungP[i]->Getphonenumber() << " ";
			fout << JungP[i]->Getprice() << " ";
			fout << JungP[i]->Getjungmodel() << " ";
			fout << JungP[i]->Getbidet() << " ";
			fout << JungP[i]->Getstart() << " ";
			if (i == (index - 1))
				fout << JungP[i]->Getperiod();
			else
				fout << JungP[i]->Getperiod() << " ";
		}
		cout << "====== �� ����Ʈ�� �����ϴµ� �����Ͽ����ϴ�. ======" << endl;
		fout.close();
	}
	else if (sel == 'N' || sel == 'n')
		cout << "====== �� ����Ʈ ���̺긦 ����Ͽ����ϴ�. ======" << endl;
	else
		cout << "====== �߸��� �Է��Դϴ�. ======" << endl;
}

void JungsukiManager::menu() // �޴� ���
{
	cout << "\n----------------------�޴�--------------------\n" << endl;
	cout << "         1. �뿩 �� ���� �Է�(�뿩)" << endl;
	cout << "         2. �뿩 �� ����Ʈ Ȯ��" << endl;
	cout << "         3. �뿩 �� ���� ����" << endl;
	cout << "         4. �뿩 �� ���� ����" << endl;
	cout << "         5. �뿩 �� ���� �˻�\n" << endl;
	cout << "         Q. ���α׷� ����\n" << endl;
	cout << "\n------------------������ ����-----------------\n" << endl;
	cout << "         9. �� ����Ʈ ����" << endl;
	cout << "         0. �� ����Ʈ �ҷ�����" << endl;
	cout << "\n----------------------------------------------\n" << endl;
	cout << "���ϴ� �޴� ��ȣ�� �Է��ϼ��� >> ";
}

void JungsukiManager::output() // ���� ��� �Լ�
{
	cout << "===========================================================================================";
	cout << "\n ����      ��ȭ��ȣ     ��డ��     ������𵨸�    �񵥸𵨸�    �����     ���Ⱓ\n";
	cout << "===========================================================================================\n";
	for (int i = 0; i < index; i++)
	{
		JungP[i]->Show();
	}
	cout << "===========================================================================================\n";
}

int main(void)
{
	system("mode con:cols=66 lines=25"); // âũ�� ����
	JungsukiManager manager;
	char choice;
	manager.login(); // �α��� �Լ� ȣ��
	system("mode con:cols=100 lines=40"); // âũ�� ����
	system("cls");
	while (1)
	{
		cout << "\n\n�ݰ����ϴ�. DEU.CHOI �����ڴ�\n\n";
		manager.menu();
		cin >> choice;
		switch (choice)
		{
		case '1': //�Է�
			system("cls");
			manager.input();
			break;
		case '2': //���
			system("cls");
			manager.output();
			break;
		case '3': //����
			system("cls");
			manager.modify();
			break;
		case '4': //����
			system("cls");
			manager.deleted();
			break;
		case '5': //�˻�
			system("cls");
			manager.search();
			break;
		case '9': //��������
			system("cls");
			manager.save();
			break;
		case '0': //���Ϻҷ�����
			system("cls");
			manager.load();
			break;
		case 'Q':
		case 'q': //����
			system("cls");
			system("mode con:cols=66 lines=25"); // âũ�� ����
			cout << "\n\n-------------------W A T E R P U R I F I E R----------------------\n\n";
			cout << "              M A N A G E R M E N T  S Y S T E M                \n\n\n\n";
			cout << "\n\n==================== ���α׷��� �����մϴ�. ======================\n\n\n\n\n";
			return 0;
		default: //����
			system("cls");
			cout << "�߸��� �Է��Դϴ�." << endl;
			break;
		}
	}
}