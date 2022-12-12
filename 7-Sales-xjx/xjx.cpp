#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include "xjx.h"

void xjx::Mediator::communicate(Outlet* from, Outlet* to, string content)
{
	cout << this->name << " received the message successfully!" << endl;
	Sleep(1000);
	cout << this->name << " sent the message successfully!" << endl;
	Sleep(1000);
	to->receive(from, content);
}

void xjx::Mediator::communicate(Outlet* from, Company* to, string content)
{
	cout << this->name << " received the message successfully!" << endl;
	Sleep(1000);
	cout << this->name << " sent the message successfully!" << endl;
	Sleep(1000);
	to->receive(from, content);
}

void xjx::Mediator::communicate(Company* from, Outlet* to, string content)
{
	cout << this->name << " received the message successfully!" << endl;
	Sleep(1000);
	cout << this->name << " sent the message successfully!" << endl;
	Sleep(1000);
	to->receive(from, content);
}

void xjx::Company::send(Outlet* outlet, string content)
{
	cout << this->name << " sent the message successfully!" << endl;
	Sleep(1000);
	this->mediator->communicate(this, outlet, content);
}

void xjx::Company::receive(Outlet* outlet, string content)
{
	cout << this->name << " received the message successfully!" << endl;
	Sleep(1000);
	cout << "The content is:" << endl;
	cout << content << endl;
	Sleep(1000);
	cout << endl;
}

void xjx::Outlet::send(Outlet* outlet, string content)
{
	cout << this->name << " sent the message successfully!" << endl;
	Sleep(1000);
	this->mediator->communicate(this, outlet, content);
}

void xjx::Outlet::send(Company* company, string content)
{
	cout << this->name << " sent the message successfully!" << endl;
	Sleep(1000);
	this->mediator->communicate(this, company, content);
}

void xjx::Outlet::receive(Outlet* outlet, string content)
{
	cout << this->name << " received the message successfully!" << endl;
	Sleep(1000);
	cout << "The content is:" << endl;
	cout << content << endl;
	Sleep(1000);
	cout << endl;
}

void xjx::Outlet::receive(Company* company, string content)
{
	cout << this->name << " received the message successfully!" << endl;
	Sleep(1000);
	cout << "The content is:" << endl;
	cout << content << endl;
	Sleep(1000);
	cout << endl;
}

void xjx::Client::receive(Advertisement* ad)
{
	cout << this->name << " received the advertisement successfully!" << endl;
	Sleep(1000);
	cout << "The title is:" << endl;
	cout << ad->title << endl;
	Sleep(1000);
	cout << "The content is:" << endl;
	cout << ad->content << endl;
	Sleep(1000);
	cout << endl;
}

void xjx::Advertisement::advertise()
{
	for (int i = 0; i < this->client_list.size(); i++)
	{
		Advertisement* ad = new Advertisement(*this);
		cout << "The advertisement was sent to " << this->client_list[i]->name << endl;
		Sleep(1000);
		this->client_list[i]->receive(ad);
	}
}

void xjx::Outlet::trade()
{
	cout << "The trade was done!" << endl;
	Sleep(1000);
	cout << endl;
}

void xjx::Salesman::trade()
{
	cout << this->name << " worked as the proxy for " << this->outlet->name << "!" << endl;
	Sleep(1000);
	this->outlet->trade();
}

void xjx::Client::purchase()
{
	cout << this->name << " started the trade!" << endl;
	Sleep(1000);
	this->salesman->trade();
}

void xjx::Decoder::decode()
{
	int j = 0;
	for (int i = 0; i < this->code.length(); i++)
	{
		if (this->code[i] >= '0' && this->code[i] <= '9')
			this->resolution[j] = this->resolution[j] * 10 + this->code[i] - '0';
		else if (!j)
		{
			cpu = this->code[i] - 'A' + 1;
			j++;
		}
		else
			memory = pow(2, this->code[i] - 'A' + 1);
	}
	cout << "Decoding was finished successfully!" << endl;
	Sleep(1000);
}

void xjx::Decoder::print()
{
	cout << "Product Info:" << endl;
	cout << "CPU : " << this->cpu << " Core(s)" << endl;
	cout << "MEM : " << this->memory << ".00G" << endl;
	cout << "Resolution : " << resolution[0] << "*" << resolution[1] << endl;
	Sleep(1000);
	cout << endl;
}

void xjx::Client::notify(string content)
{
	cout << this->name << " sent the notification successfully!" << endl;
	Sleep(1000);
	this->salesman->notify(content);
}

void xjx::Salesman::notify(string content)
{
	cout << this->name << " received the notification successfully!" << endl;
	Sleep(1000);
	cout << endl;
	cout << this->name << " sent the notification successfully!" << endl;
	Sleep(1000);
	cout << endl;
	for (int i = 0; i < this->factory_list.size(); i++)
	{
		this->factory_list[i]->response(content);
	}
}

void xjx::Factory::response(string content)
{
	cout << this->name << " received the notification successfully!" << endl;
	Sleep(1000);
	cout << "The content is:" << endl;
	cout << content << endl;
	Sleep(1000);
	cout << endl;
}

void xjx::Application::xjxMediatorPattern()
{
	system("cls");
	cout << "=== Mediator Pattern ===" << endl;
	Sleep(1000);
	cout << endl;
	
	xjx::Mediator* mediator = new xjx::Mediator("Mediator");
	xjx::Company* company = new xjx::Company("Company", mediator);
	xjx::Outlet* outlet1 = new xjx::Outlet("Outlet1", mediator);
	xjx::Outlet* outlet2 = new xjx::Outlet("Outlet2", mediator);
	string message1 = "The goods have been sold out!!!";
	outlet1->send(company, message1);
	string message2 = "Please transport some goods to Outlet1!!!";
	company->send(outlet2, message2);
	string message3 = "Please get ready to receive the goods!!!";
	outlet2->send(outlet1, message3);
	
	system("pause");
}

void xjx::Application::xjxPrototypePattern()
{
	system("cls");
	cout << "=== Prototype Pattern ===" << endl;
	Sleep(1000);
	cout << endl;
	
	xjx::Client* client1 = new xjx::Client("Client1", NULL);
	xjx::Client* client2 = new xjx::Client("Client2", NULL);
	vector<xjx::Client*> client_list;
	client_list.push_back(client1);
	client_list.push_back(client2);
	string title = "Prototype Pattern";
	string content = "Prototype Pattern is used to create duplicate objects while ensuring performance. ";
	content += "This type of design pattern is a creation pattern, which provides the best way to create objects. ";
	content += "This pattern implements a prototype interface that is used to create a clone of the current object. ";
	content += "This pattern is used when the cost of directly creating objects is high. ";
	content += "For example, an object needs to be created after a costly database operation. ";
	content += "We can cache the object, return its clone on the next request, and update the database when necessary to reduce database calls.";
	xjx::Advertisement* ad = new xjx::Advertisement(title, content, client_list);
	ad->advertise();
	
	system("pause");
}

void xjx::Application::xjxProxyPattern()
{
	system("cls");
	cout << "=== Proxy Pattern ===" << endl;
	Sleep(1000);
	cout << endl;
	
	xjx::Outlet* outlet3 = new xjx::Outlet("Outlet3", NULL);
	vector<xjx::Factory*> null_list;
	xjx::Salesman* salesman1 = new xjx::Salesman("Salesman1", outlet3, null_list);
	xjx::Client* client3 = new xjx::Client("Client3", salesman1);
	client3->purchase();
	
	system("pause");
}

void xjx::Application::xjxInterpreterPattern()
{
	system("cls");
	cout << "=== Interpreter Pattern ===" << endl;
	Sleep(1000);
	cout << endl;
	
	string code = "1920A1080C";
	xjx::Decoder* decoder = new xjx::Decoder(code);
	decoder->decode();
	decoder->print();
	
	system("pause");
}

void xjx::Application::xjxObserverPattern()
{
	system("cls");
	cout << "=== Observer Pattern ===" << endl;
	Sleep(1000);
	cout << endl;
	
	xjx::Factory* factory1 = new xjx::Factory("Factory1");
	xjx::Factory* factory2 = new xjx::Factory("Factory2");
	vector<xjx::Factory*> factory_list;
	factory_list.push_back(factory1);
	factory_list.push_back(factory2);
	xjx::Salesman* salesman2 = new xjx::Salesman("Salesman2", NULL, factory_list);
	xjx::Client* client4 = new xjx::Client("Client4", salesman2);
	string notification = "There must be some quality problems with the battery!!!";
	client4->notify(notification);
	
	system("pause");
}

void xjx::Application::run()
{
	void (*oper[5])();
	oper[0] = xjx::Application::xjxMediatorPattern;
	oper[1] = xjx::Application::xjxPrototypePattern;
	oper[2] = xjx::Application::xjxProxyPattern;
	oper[3] = xjx::Application::xjxInterpreterPattern;
	oper[4] = xjx::Application::xjxObserverPattern;
	
	while (1)
	{
		system("cls");
		cout << "=== 销售和售后 ===" << endl;
		cout << endl;
		cout << "1. 销售网点与总公司的联系(Mediator Pattern)" << endl;
		cout << "2. 向顾客投放广告(Prototype Pattern)" << endl;
		cout << "3. 销售人员代理销售网点与顾客交易(Proxy Pattern)" << endl;
		cout << "4. 解析电脑产品型号码(Interpreter Pattern)" << endl;
		cout << "5. 顾客向销售人员反馈问题(Observer Pattern)" << endl;
		cout << "0. 退出" << endl;
		cout << endl;
		cout << "Input the corresponding number to simulate the process : ";
		
		char num = _getch();
		while (num < '0' || num > '5')
			num = _getch();
		
		if (num == '0')
			break;
		else
			oper[num - '0' - 1]();
	}
	
	cout << endl;
}
