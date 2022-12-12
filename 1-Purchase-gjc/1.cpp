#include<iostream>
#include< conio.h >
#include<Windows.h>
#include"purchase.h"
using namespace Purchase;
using namespace std;

int main()
{
	cout << "The first part is  procurement!" << endl;
	Sleep(1000);
	system("cls");
	//�н�ģʽѡ��ͬ��purchaser���糧�Ҳɹ�ԭ����
	Component1* c1 = new Component1;
	Component2* c2 = new Component2;
	ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
	cout << "====== Contact with different raw materials brands by intermediaries(purchasers)======" << endl;
	cout << "Press 1 to contact brand A for supply ; press 2 to contact brand D for supply,  press 3 to exit" << endl;
	while (1)
	{
		char a;
		a = _getch();
		if (a == '1')
		{
			cout << "contact brand A for supply.\n";
			c1->DoA();
		}
		else if (a == '2')
		{
			cout << "contact brand D for supply.\n";
			c2->DoD();
		}
		else if (a == '3')
			break;
		else
			cout << "you type the wrong letter!" << endl;
	}
	
	
	/*
 ������ѡ��ͬ�̼ҹ���ͬԭ��
 */

	MetalHandler* Metal = new MetalHandler;
	PlasticHandler* Plastic = new PlasticHandler;
	CarbonFiberHandler* CarbonFiber = new CarbonFiberHandler;
	Metal->SetNext(Plastic)->SetNext(CarbonFiber);

	cout << endl;
	cout << "======Select different brands to provide different raw materials======" << endl;
	cout << "Chain: Metal > Plastic> CarbonFiber" << endl;
	ClientCode(*Metal);
	cout << "\n";
	//std::cout << "Subchain: Squirrel > Dog\n\n";
	//ClientCode(*Plastic);


	//װ����ģʽ��������ԭ��
	cout << "======About to purchase plastic raw materials======" << endl;

	rawMaterial* buy = new rawMaterial;
	buy->showStatus();

	cout << "Press 1 to buy ABS; press 2 to buy PC,  press 3 to exit" << endl;
	while (1) {
		char a;
		a = _getch();
		if (a == '1')
		{
			buy = new ABS(buy);
			buy->showStatus();
		}
		else if (a == '2')
		{
			buy = new PC(buy);
			buy->showStatus();
		}
		else if (a == '3')
			break;
		else
			cout << "you type the wrong letter!" << endl;
	}
	
	cout << endl;
	//�۲���Ϊ�ɹ�˫��֪ͨ�ɹ���Ϣ
	cout << "======Procurement in progress, timely notification of procurement information for both sides of the transaction======" << endl;
	AbstractTell* View = new tell;
	cout << "Press 1 to join seller; press 2 to join company, press 3 to notify, press 4 to exit" << endl;
	while (1){
		char a;
	a = _getch();
	if (a == '1')
		View->addViewer(new seller);
	else if (a == '2')
		View->addViewer(new company);
	else if (a == '3')
		View->tellAllViewer();
	else if (a == '4')
		break;
	else
		cout << "you type the wrong letter!" << endl;
	}
	system("cls");
	return 0;
}