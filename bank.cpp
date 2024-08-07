#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queue.h"
const int MIN_PER_HR = 60;

bool newcustomer(double x);

int main()
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios_base;
	std::srand(std::time(0)); // rand() 무작위 초기화

	cout << "사례 연구: 히서 은행의 ATM\n";
	cout << "큐의 최대 길이를 입력하세요: ";
	int qs;
	cin >> qs;
	Queue line(qs);

	cout << "시뮬레이션 시간 수를 입력하세요: ";
	int hours;
	cin >> hours;
	// 시뮬레이션은 1분에 1주기를 실행한다.
	long cyclelimit = MIN_PER_HR * hours;

	cout << "시간당 평균 고객 수를 입력하세요: ";
	double perhour;
	cin >> perhour;
	double min_per_cust; // 평균 고객 도착 간격(분 단위)
	min_per_cust = MIN_PER_HR / perhour;

	Item temp;          // 새 고객 데이터!
	long turnaways = 0; // 큐가 가득차서 발길을 돌린 고객 수
	long customers = 0; // 큐에 줄을 선 고객 수
	long served = 0;    // 시뮬레이션에서 거래를 처리한 고객 수
	long sum_line = 0;  // 큐의 누적 길이
	int wait_time = 0;  // ATM이 빌 때까지 대기하는 시간
	long line_wait = 0; // 고객들이 줄을 서서 대기한 누적 시간

	// 시뮬레이션 실행
	for (int cycle = 0; cycle < cyclelimit; cycle++)
	{
		if (newcustomer(min_per_cust))
		{
			if (line.isfull())
				turnaways++;
			else
			{
				customers++;
				temp.set(cycle);    // 도착한 시간 저장
				line.enqueue(temp); // 큐에 새 고객 추가
			}

			// 처리할 준비가 됬는지 체크
			if (wait_time <= 0 && !line.isempty())
			{
				// 다음 고객을 받기 위해 처리 과정
				line.dequeue(temp);               
				wait_time = temp.ptime();
				line_wait += cycle - temp.when();
				served++;
			}

			if (wait_time > 0)
				wait_time--;

			sum_line += line.queuecount();
		}

		if (customers > 0)
		{
			cout << "큐에 줄을 선 고객 수: " << customers << endl;
			cout << "거래를 처리한 고객 수: " << served << endl;
			cout << " 발길을 돌린 고객 수: " << turnaways << endl;
			cout << "		평균 큐의 길이: ";
			cout.precision(2);
			cout.setf(ios_base::fixed, ios_base::floatfield);
			cout.setf(ios_base::showpoint);
			cout << (double)sum_line / cyclelimit << endl;
			cout << "		평균 대기 시간: " << (double)line_wait / served << "분\n";
		}
		else
			cout << "고객이 한 명도 없습니다.\n";
		cout << "완료!\n";
	}

	return 0;
}

// x는 고객 간의 평균 시간 간격(분 단위)
// 이 시간 내에 고객이 도착하면 true
bool newcustomer(double x)
{
	return (std::rand() * x / RAND_MAX < 1);
}