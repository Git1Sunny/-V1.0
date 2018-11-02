#include "pch.h"
#include <iostream>
#include <stdlib.h>
#define MaxSize 5;
using namespace std;

typedef struct Parkinglot
{
	int CarNum[5];
	int Time[5];
	int Top;
}PCar;

typedef struct ParkingSteet
{
	int CarNum;
	struct ParkingSteet * Next;
}PSteet;

PSteet * inCar(PCar * pace, PSteet * Steet, PSteet * head);
void outCar(PCar * pace, PCar *Temp, PSteet *head);
int countTime(int x, int y);
int outSteet(PSteet * head);
int countnumber(PSteet * head);
int menu();

int main()
{
	PCar Park, Temp;
	PSteet *head, *Steet = (PSteet*)malloc(sizeof(PSteet));
	head = Steet;
	Steet->CarNum = 0;
	Steet->Next = NULL;
	Park.Top = -1;
	Temp.Top = -1;

	int x;
	while (1)
	{
		switch (menu())
		{
		case 1:Steet = inCar(&Park, Steet, head); break;
		case 2:outCar(&Park, &Temp, head); break;
		}

	}

}

int countnumber(PSteet * head)
{
	int count = 0;
	PSteet * temp;
	temp = head->Next;
	while (temp != NULL)
	{
		count++;
		temp = temp->Next;
	}
	return count;
}

int outSteet(PSteet * head)
{
	PSteet * temp = head;
	head = head->Next;
	int x = head->CarNum;
	free(temp);
	return x;
}

PSteet * inCar(PCar * pace, PSteet * Steet, PSteet * head)
{
	if (pace->Top == 5 - 1)
	{
		int time;
		PSteet *data = (PSteet*)malloc(sizeof(PSteet));
		cin >> data->CarNum >> time;
		data->Next = NULL;
		Steet->Next = data;
		Steet = Steet->Next;
		cout << "停车场已满 车已经停在路上目前排在第" << countnumber(head) << "号位置" << endl;
	}
	else
	{
		cin >> pace->CarNum[++pace->Top] >> pace->Time[pace->Top];
		cout << "已停车 车" << pace->CarNum[pace->Top] << "放在停车场 第" << pace->Top << "号停车位" << endl;
	}
	return Steet;
}

void outCar(PCar * pace, PCar *Temp, PSteet *head)
{
	int number, time, mark = 0;
	cin >> number >> time;
	while (pace->Top >= 0)
	{
		if (pace->CarNum[pace->Top] == number)
		{
			cout << "已取车 车" << pace->CarNum[pace->Top] << "共计停车" << countTime(time, pace->Time[pace->Top]) << "分钟 共计收费" << endl;
			pace->Top--;
			mark = 1;
			break;
		}
		else
		{
			Temp->Top++;
			Temp->CarNum[Temp->Top] = pace->CarNum[pace->Top];
			Temp->Time[Temp->Top] = pace->Time[pace->Top];
			pace->Top--;
		}
	}
	while (Temp->Top + 1)
	{
		pace->Top++;
		pace->CarNum[pace->Top] = Temp->CarNum[Temp->Top];
		pace->Time[pace->Top] = Temp->Time[Temp->Top];
		Temp->Top--;
	}
	if (mark == 0)
		cout << "请确认输入是否正确 没有找到对应车辆\n";
	else
	{
		pace->CarNum[++pace->Top] = outSteet(head);
		pace->Time[pace->Top] = time;
		cout << "已将等候车辆 " << pace->CarNum << " 放入车库 停在车库第" << pace->Top << "号 车位上";
	}
}

int countTime(int x, int y)
{
	int x1 = x / 100, x2 = x % 100;
	int y1 = y / 100, y2 = y % 100;
	x2 += x1 * 60;
	y2 += y1 * 60;
	return x2 - y2;
}

int menu()
{
	while (1)
	{
		cout << " __________________________________________________________" << endl;
		cout << "| 1.停车                                                   |" << endl;
		cout << "| 2.取车                                                   |" << endl;
		cout << "|__________________________________________________________|" << endl;
		int x;
		if (!scanf_s("%d", &x) || (x != 1 && x != 2))
		{
			cout << "输入数据错误 请重新输入" << endl;
			system("pause");
			system("cls");
		}
		else
			return x;
	}
}