#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#pragma disable(warning:4996)


using namespace std;

class Jungsuki{ // 전체적인 입출력 데이터를 할당하는 클래스
protected:
	char *name; // 성함
	char *phonenumber; // 전화번호
	int price; // 계약금액
	char *jungmodel; // 정수기 모델이름
	char *start; // 계약일
	char *period; // 계약기간
public:
	Jungsuki(){}; 
	Jungsuki(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_start, char *_period);
	Jungsuki(const Jungsuki &St);
	~Jungsuki();
	virtual void Show() const; // 출력 가상함수
	char *GetName() const{ return name; };
	char *Getphonenumber() const{ return phonenumber; };
	int Getprice() const{ return price; };
	char *Getjungmodel() const{ return jungmodel; };
	char *Getstart() const{ return start; };
	char *Getperiod() const{ return period; }; // 자료들을 꺼내는 get설정자
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
} // 정보 등록 생성자

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
} // 복사생성자

Jungsuki::~Jungsuki(){
	delete[]name;
	delete[]phonenumber;
	delete[]jungmodel;
	delete[]start;
	delete[]period;
} // 소멸자

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
} // 출력 함수

class Bidet : public Jungsuki // 기본 자료를 상속받아 기능을 넓힘
{
	char *bidet; // 비대 모델명
public:
	Bidet(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_bidet, char *_start, char *_period); // 비데모델 추가된 생성자
	virtual void Show() const; // 출력 가상 함수
	char *Getbidet() const{ return bidet; }; // 비대를 리턴하는 함수
	void setJungsuki(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_start, char *_period, char *_bidet) // 정보를 입력받는 set 설정자
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
	void modify(); // 수정하는 내용 함수
};

Bidet::Bidet(char *_name, char *_phonenumber, int _price, char *_jungmodel, char *_bidet, char *_start, char *_period) : Jungsuki(_name, _phonenumber, _price, _jungmodel, _start, _period)
{
	this->bidet = new char[strlen(_bidet) + 1];
	strcpy(bidet, _bidet);
} // 비데만 따로 입력 받는 생성자


void Bidet::modify()
{
	cout << "====== 계약 고객이십니다. ======\n";
	cout << "성함 입력 : ";
	cin >> name;
	cout << "전화번호(-없이) 입력 : ";
	cin >> phonenumber;
	cout << "계약가격 입력 : ";
	cin >> price;
	cout << "정수기모델 입력 : ";
	cin >> jungmodel;
	cout << "계약일(Y/M/D) 입력 : ";
	cin >> start;
	cout << "계약기간(개월) 입력 : ";
	cin >> period;
	cout << "비데모델 입력 : ";
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
} // 출력 함수

class JungsukiManager{ // 메뉴 관련 클래스
protected:
	int index;
	Bidet *JungP[50]; // 기본으로 50개 정보를 받음

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

JungsukiManager::JungsukiManager() // 초기화 생성자
{
	index = 0;
}

void JungsukiManager::login() // 로그인 함수
{
	int i = 0;
	char _id[20], _pass[20], id[20], password[20], c = ' ';

	ifstream fin("identify.txt", ios::in, ios::trunc); // 로그인 정보 파일 불러오기
	fin >> _id;
	fin >> _pass;
	while (1)
	{
		cout << "\n\n-------------------W A T E R P U R I F I E R----------------------\n\n";
		cout << "                M A N A G E M E N T  S Y S T E M                \n\n\n\n";
		cout << "                   ID : ";
		cin >> id;
		cout << "\n\n             PASSWORD : ";
		while (c != 13)					// 비밀번호 *로 출력하는 구문
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
		if (strcmp(_id, id) == 0 && strcmp(_pass, password) == 0) // 예외처리
		{
			break;
		}
		else
		{
			system("cls");
			cout << "----------------ID와 PASSWORD를 다시 입력해주세요.----------------\n";
			i = 0;
			c = ' ';
		}
	}
	fin.close(); // 파일 열기 종료
}

void JungsukiManager::modify(){ // 내용 수정 함수
	char phonenumber[30];
	cout << "전화번호(-없이) 입력 : "; // 전화번호를 입력받아 수정
	cin >> phonenumber;
	for (int i = 0; i < index; i++) // 입력과 비교
	{
		if (strcmp(JungP[i]->Getphonenumber(), phonenumber) == 0)
		{
			JungP[i]->modify(); // 입력과 맞으면 수정 내용 불러옴
		}
	}
	cout << "====== 수정사항이 나오지 않는다면, 계약 내용이 없습니다. ======";
}

void JungsukiManager::input() // 입력 함수
{
	char name[20], phonenumber[20], jungmodel[20] = "미계약", start[20], bidet[20] = "미계약", period[20]; 
	int price = 0;
	int select;

	cout << "=====대여 물품 입력=====" << endl;
	cout << "1. 정수기 대여" << endl;
	cout << "2. 비대 대여" << endl;
	cout << "3. 정수기, 비대 대여" << endl;
	cout << ">> ";
	cin >> select;
	if ((select >= 4) || (select <= 0)) // 예외처리
	{
		cout << "  잘못된 입력입니다 !!" << endl;
	}
	else
	{
		cout << "전화번호(-없이) 입력 : ";
		cin >> phonenumber;
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getphonenumber(), phonenumber) == 0)
			{
				cout << "중복 계약은 불가능합니다." << endl;
				return;
			}
		}
		if (select == 1) // 정수기만 대여
		{
			cout << "성함, 계약가격, 정수기모델, 계약일(Y/M/D), 계약기간 입력(띄워쓰기로 구분해 주세요.) : " << endl;
			cin >> name >> price >> jungmodel >> start >> period;
			JungP[index++] = new Bidet(name, phonenumber, price, jungmodel, bidet, start, period);
		}
		else if (select == 2) // 비데만 대여
		{
			cout << "성함, 계약가격, 비데모델, 계약일(Y/M/D), 계약기간 입력(띄워쓰기로 구분해 주세요.)" << endl;
			cin >> name >> price >> bidet >> start >> period;
			JungP[index++] = new Bidet(name, phonenumber, price, jungmodel, bidet, start, period);
		}
		else if (select == 3) // 정수기, 비데 둘 다 대여
		{
			cout << "성함, 계약가격, 정수기모델, 비데모델, 계약일(Y/M/D), 계약기간 입력(띄워쓰기로 구분해 주세요.)" << endl;
			cin >> name >> price >> jungmodel >> bidet >> start >> period;
			JungP[index++] = new Bidet(name, phonenumber, price, jungmodel, bidet, start, period);
		}
		else {
			cout << "잘못된 입력입니다!" << endl;
		}
	}
}

void JungsukiManager::deleted() // 정보 삭제 함수
{
	char phonenumber[20], sel;
	int i = 0,j = 0;
	cout << "전화번호(-없이) 입력 : ";
	cin >> phonenumber;
	for (i = 0; i < index; i++) // 전화번호로 예외처리
	{
		if (strcmp(JungP[i]->Getphonenumber(), phonenumber) == 0)
		{
			cout << "고객 정보를 찾았습니다. 정말로 삭제합니까?(Y/N)";
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
		cout << "====== 고객 정보 삭제를 취소합니다. ======";
	}
	else
		cout << "====== 잘못된 입력입니다. ======" << endl;
	cout << "====== 삭제 질문이 나오지 않는다면, 계약 내용이 없습니다. ======";
}


void JungsukiManager::search() // 검색 메뉴
{
	char text[20];
	char sel;
	int count = 0;
	cout << "1. 성함으로 정보 검색" << endl;
	cout << "2. 전화번호 정보 검색" << endl;
	cout << "3. 정수기 모델로 정보 검색" << endl;
	cout << "4. 비데 모델로 정보 검색" << endl;
	cout << "5. 계약일(Y/M/D)로 정보 검색" << endl;
	cout << "6. 계약기간(개월)으로 정보 검색" << endl;
	cout << "Q. 메뉴로 나가기" << endl;
	cout << "\n>>";
	cin >> sel;
	switch (sel)
	{
	case '1':
		cout << "정보를 입력해주세요.(계약일 일시 Y/M/D 형태로 검색) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n 님의 대여 내용을 검색합니다.\n";
		cout << "\n===========================================================================================";
		cout << "\n 성함      전화번호     계약가격     정수기모델명    비데모델명    계약일     계약기간\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->GetName(), text) == 0) // 입력과 비교하여 맞는것만 출력
			{
				JungP[i]->Show();
				count++;
			}
		}
		if (count == 0)
			cout << "  찾는 자료가 없습니다 !!";
		cout << "===========================================================================================\n";
		break;
	case '2':
		cout << "정보를 입력해주세요.(계약일 일시 Y/M/D 형태로 검색) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n 의 전화번호 정보로 대여를 검색합니다.\n";
		cout << "\n===========================================================================================";
		cout << "\n 성함      전화번호     계약가격     정수기모델명    비데모델명    계약일     계약기간\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getphonenumber(), text) == 0)// 입력과 비교하여 맞는것만 출력
			{
				JungP[i]->Show();
			}
			count++;
		}
	
		if (count == 0)
			cout << "  찾는 자료가 없습니다 !!";
		cout << "===========================================================================================\n";
		break;
	case '3':
		cout << "정보를 입력해주세요.(계약일 일시 Y/M/D 형태로 검색) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n 의 모델로 계약된 대여를 검색합니다.\n";
		cout << "\n===========================================================================================";
		cout << "\n 성함      전화번호     계약가격     정수기모델명    비데모델명    계약일     계약기간\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getjungmodel(), text) == 0)// 입력과 비교하여 맞는것만 출력
			{
				JungP[i]->Show();
				count++;
			}
		}
			if (count == 0)
				cout << "  찾는 자료가 없습니다 !!";
		cout << "===========================================================================================\n";
		break;
	case '4':
		cout << "정보를 입력해주세요.(계약일 일시 Y/M/D 형태로 검색) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n 의 모델로 계약된 대여를 검색합니다.\n";
		cout << "\n===========================================================================================";
		cout << "\n 성함      전화번호     계약가격     정수기모델명    비데모델명    계약일     계약기간\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getbidet(), text) == 0)// 입력과 비교하여 맞는것만 출력
			{
				JungP[i]->Show();
				count++;
			}
		}
			if (count == 0)
				cout << "  찾는 자료가 없습니다 !!";
		cout << "===========================================================================================\n";
		break;
	case '5':
		cout << "정보를 입력해주세요.(계약일 일시 Y/M/D 형태로 검색) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n 날짜에 대여된 정보를 검색합니다.\n";
		cout << "\n===========================================================================================";
		cout << "\n 성함      전화번호     계약가격     정수기모델명    비데모델명    계약일     계약기간\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getstart(), text) == 0)// 입력과 비교하여 맞는것만 출력
			{
				JungP[i]->Show();
			}
			count++;
		}

		if (count == 0)
			cout << "  찾는 자료가 없습니다 !!";
		cout << "===========================================================================================\n";
		break;
	case '6':
		cout << "정보를 입력해주세요.(계약일 일시 Y/M/D 형태로 검색) >>";
		cin >> text;
		system("cls");
		cout << text << "\n\n 로 계약된 정보를 검색합니다.\n";
		cout << "\n===========================================================================================";
		cout << "\n 성함      전화번호     계약가격     정수기모델명    비데모델명    계약일     계약기간\n";
		cout << "===========================================================================================\n";
		for (int i = 0; i < index; i++)
		{
			if (strcmp(JungP[i]->Getperiod(), text) == 0)// 입력과 비교하여 맞는것만 출력
			{
				JungP[i]->Show();
			}
			count++;
		}

		if (count == 0) // 예외처리
			cout << "  찾는 자료가 없습니다 !!";
		cout << "===========================================================================================\n";
		break;
	case 'Q':
	case 'q':
		break;
	default:
		cout << "====== 잘못된 입력입니다. ======" << endl;
		break;
	}
}

void JungsukiManager::load()
{
	char sel;
	cout << "만약 이미 자료가 있다면 기존내용에 추가됩니다. 그래도 괜찮습니까?(Y/N)";
	cin >> sel;
	if (sel == 'Y' || sel == 'y')
	{
		ifstream fin("list.txt", ios::in, ios::trunc); 
		//내용으로 입력을 목표로 파일을 불러옴
		char name[20], phonenumber[20], jungmodel[20], start[20], bidet[20], period[20];
		int price = 0;
		if (!fin)
		{
			cout << "====== 잘못된 고객 리스트 입니다. ======" << endl;
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
		cout << "====== 고객 리스트를 불러오는데 성공하였습니다. ======" << endl;
		fin.close();
	}
	else if (sel == 'N' || sel == 'n')
		cout << "====== 고객 리스트 로드를 취소하였습니다. ======" << endl;
	else
		cout << "====== 잘못된 입력입니다. ======" << endl;
}

void JungsukiManager::save()
{
	char sel;
	cout << "기입한 내용이 아니면, 기존에 있던 내용은 삭제 될 수 있습니다. 괜찮습니까?(Y/N)";
	cin >> sel;
	if (sel == 'Y' || sel == 'y')
	{
		ofstream fout("list.txt", ios::out); 
		// 내용으로 출력을 목표로 파일을 불러옴
		if (!fout)
		{
			cout << "====== 잘못된 고객 리스트 입니다. ======";
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
		cout << "====== 고객 리스트를 저장하는데 성공하였습니다. ======" << endl;
		fout.close();
	}
	else if (sel == 'N' || sel == 'n')
		cout << "====== 고객 리스트 세이브를 취소하였습니다. ======" << endl;
	else
		cout << "====== 잘못된 입력입니다. ======" << endl;
}

void JungsukiManager::menu() // 메뉴 출력
{
	cout << "\n----------------------메뉴--------------------\n" << endl;
	cout << "         1. 대여 고객 정보 입력(대여)" << endl;
	cout << "         2. 대여 고객 리스트 확인" << endl;
	cout << "         3. 대여 고객 정보 수정" << endl;
	cout << "         4. 대여 고객 정보 삭제" << endl;
	cout << "         5. 대여 고객 정보 검색\n" << endl;
	cout << "         Q. 프로그램 종료\n" << endl;
	cout << "\n------------------데이터 관리-----------------\n" << endl;
	cout << "         9. 고객 리스트 저장" << endl;
	cout << "         0. 고객 리스트 불러오기" << endl;
	cout << "\n----------------------------------------------\n" << endl;
	cout << "원하는 메뉴 번호를 입력하세요 >> ";
}

void JungsukiManager::output() // 정보 출력 함수
{
	cout << "===========================================================================================";
	cout << "\n 성함      전화번호     계약가격     정수기모델명    비데모델명    계약일     계약기간\n";
	cout << "===========================================================================================\n";
	for (int i = 0; i < index; i++)
	{
		JungP[i]->Show();
	}
	cout << "===========================================================================================\n";
}

int main(void)
{
	system("mode con:cols=66 lines=25"); // 창크기 지정
	JungsukiManager manager;
	char choice;
	manager.login(); // 로그인 함수 호출
	system("mode con:cols=100 lines=40"); // 창크기 지정
	system("cls");
	while (1)
	{
		cout << "\n\n반갑습니다. DEU.CHOI 관리자님\n\n";
		manager.menu();
		cin >> choice;
		switch (choice)
		{
		case '1': //입력
			system("cls");
			manager.input();
			break;
		case '2': //출력
			system("cls");
			manager.output();
			break;
		case '3': //수정
			system("cls");
			manager.modify();
			break;
		case '4': //삭제
			system("cls");
			manager.deleted();
			break;
		case '5': //검색
			system("cls");
			manager.search();
			break;
		case '9': //파일저장
			system("cls");
			manager.save();
			break;
		case '0': //파일불러오기
			system("cls");
			manager.load();
			break;
		case 'Q':
		case 'q': //종료
			system("cls");
			system("mode con:cols=66 lines=25"); // 창크기 지정
			cout << "\n\n-------------------W A T E R P U R I F I E R----------------------\n\n";
			cout << "              M A N A G E R M E N T  S Y S T E M                \n\n\n\n";
			cout << "\n\n==================== 프로그램을 종료합니다. ======================\n\n\n\n\n";
			return 0;
		default: //예외
			system("cls");
			cout << "잘못된 입력입니다." << endl;
			break;
		}
	}
}