#ifndef __XJX_H__
#define __XJX_H__
#include <vector>
#include <string>
using namespace std;

namespace xjx
{
	class Mediator;
	class Company;
	class Outlet;
	class Advertisement;
	class Client;
	class Salesman;
	class Decoder;
	class Factory;
	class Application;
	
	class Mediator
	{
	public:
		const string name;
		Mediator(const char* n) : name(n) {}
		~Mediator() {}
		void communicate(Outlet* from, Outlet* to, string content);
		void communicate(Outlet* from, Company* to, string content);
		void communicate(Company* from, Outlet* to, string content);
	};
	
	class Company
	{
	private:
		Mediator* mediator;
	public:
		const string name;
		Company(const char* n, Mediator* m) : name(n), mediator(m) {}
		~Company() {}
		void send(Outlet* outlet, string content);
		void receive(Outlet* outlet, string content);
	};
	
	class Outlet
	{
	private:
		Mediator* mediator;
	public:
		const string name;
		Outlet(const char* n, Mediator* m) : name(n), mediator(m) {}
		~Outlet() {}
		void send(Outlet* outlet, string content);
		void send(Company* company, string content);
		void receive(Outlet* outlet, string content);
		void receive(Company* company, string content);
		void trade();
	};
	
	class Advertisement
	{
	private:
		vector<Client*> client_list;
	public:
		const string title;
		const string content;
		Advertisement(string t, string c, vector<Client*> c_l) : title(t), content(c), client_list(c_l) {}
		~Advertisement() {}
		void advertise();
	};
	
	class Client
	{
	private:
		Salesman* salesman;
	public:
		const string name;
		Client(const char* n, Salesman* s) : name(n), salesman(s) {}
		~Client() {}
		void receive(Advertisement* ad);
		void purchase();
		void notify(string content);
	};
	
	class Salesman
	{
	private:
		Outlet* outlet;
		vector<Factory*> factory_list;
	public:
		const string name;
		Salesman(const char* n, Outlet* o, vector<Factory*> f) : name(n), outlet(o), factory_list(f) {}
		~Salesman() {}
		void trade();
		void notify(string content);
	};
	
	class Decoder
	{
	private:
		const string code;
	public:
		int cpu;
		int memory;
		int resolution[2];
		Decoder(string c) : code(c)
		{
			cpu = 0;
			memory = 0;
			resolution[0] = resolution[1] = 0;
		}
		~Decoder() {}
		void decode();
		void print();
	};
	
	class Factory
	{
	public:
		const string name;
		Factory(const char* n) : name(n) {}
		~Factory() {}
		void response(string content);
	};
	
	class Application
	{
	private:
		static void xjxMediatorPattern();
		static void xjxPrototypePattern();
		static void xjxProxyPattern();
		static void xjxInterpreterPattern();
		static void xjxObserverPattern();
	public:
		static void run();
	};
}
#endif
