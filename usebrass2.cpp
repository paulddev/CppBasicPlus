#include <iostream>
#include <string>
#include "brass.h"
const int CLIMITS = 4;

int main()
{
	using std::cin;
	using std::cout;
	using std::endl;

	Brass* p_clients[CLIMITS];
	std::string temp;
	long tempnum;
	double tempbal;
	char kind;

	for (int i = 0; i < CLIMITS; ++i)
	{
		cout << "고객의 이름을 입력하세요: ";
		getline(cin, temp);
		cout << "고객의 계좌 번호를 입력하세요: ";
		cin >> tempnum;
		cout << "계좌 개설 잔액을 입력하세요: $";
		cin >> tempbal;
		cout << "Brass 계좌는 1, BrassPlus 계좌는 2를 입력하세요: ";
		while (cin >> kind && (kind != '1' && kind != '2'))
			cout << "1 아니면 2, 둘 중 하나를 입력하세요: ";
		if (kind == '1')
			p_clients[i] = new Brass(temp, tempnum, tempbal);
		else
		{
			double tmax, trate;
			cout << "당좌 대월 한도를 입력하세요: $";
			cin >> tmax;
			cout << "당좌 대월 이자율을 소수점 형식으로 입력하세요: ";
			cin >> trate;
			p_clients[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
		}

		while (cin.get() != '\n')
			continue;
	}
	cout << endl;

	for (int i = 0; i < CLIMITS; ++i)
	{
		p_clients[i]->ViewAcct();
		cout << endl;
	}

	for (int i = 0; i < CLIMITS; ++i)
	{
		delete p_clients[i];
	}
	cout << "프로그램을 종료합니다.\n";
	return 0;
}