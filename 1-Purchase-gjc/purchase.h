#pragma once
#include<iostream>
#include <deque>
#include <vector>
using namespace std;



namespace Purchase
{
	class BaseComponent;
	class Mediator {
	public:
		virtual void Notify(BaseComponent* sender,string event) const = 0;
	};

	/**
	 * The Base Component provides the basic functionality of storing a mediator's
	 * instance inside component objects.
	 */
	class BaseComponent {
	protected:
		Mediator* mediator_;

	public:
		BaseComponent(Mediator* mediator = nullptr) : mediator_(mediator) {
		}
		void set_mediator(Mediator* mediator) {
			this->mediator_ = mediator;
		}
	};

	/**
	 * Concrete Components implement various functionality. They don't depend on
	 * other components. They also don't depend on any concrete mediator classes.
	 */
	class Component1 : public BaseComponent {
	public:
		void DoA() {
			cout << "Purchaser 1 contacts brand A.\n";
			this->mediator_->Notify(this, "A");
		}
		void DoB() {
			cout << "Purchaser 1 contacts brand B.\n";
			this->mediator_->Notify(this, "B");
		}
	};

	class Component2 : public BaseComponent {
	public:
		void DoC() {
			cout << "Purchaser 2 contacts brand C.\n";
			this->mediator_->Notify(this, "C");
		}
		void DoD() {
			cout << "Purchaser 2 contacts brand D.\n";
			this->mediator_->Notify(this, "D");
		}
	};

	/**
	 * Concrete Mediators implement cooperative behavior by coordinating several
	 * components.
	 */
	class ConcreteMediator : public Mediator {
	private:
		Component1* component1_;
		Component2* component2_;

	public:
		ConcreteMediator(Component1* c1, Component2* c2) : component1_(c1), component2_(c2) {
			this->component1_->set_mediator(this);
			this->component2_->set_mediator(this);
		}
		void Notify(BaseComponent* sender, string event) const override {
			if (event == "A") {
				cout << "Mediator reacts on A and triggers following operations:\n";
				this->component2_->DoC();
			}
			if (event == "D") {
				cout << "Mediator reacts on D and triggers following operations:\n";
				this->component1_->DoB();
				this->component2_->DoC();
			}
		}
	};




	/**
     责任链模式,选择不同商家
 */
	class Handler {
	public:
		virtual Handler* SetNext(Handler* handler) = 0;
		virtual string Handle(string request) = 0;
	};
	/**
	 * The default chaining behavior can be implemented inside a base handler class.
	 */
	class AbstractHandler : public Handler {
		/**
		 * @var Handler
		 */
	private:
		Handler* next_handler_;

	public:
		AbstractHandler() : next_handler_(nullptr) {
		}
		Handler* SetNext(Handler* handler) override {
			this->next_handler_ = handler;
			// Returning a handler from here will let us link handlers in a convenient
			// way like this:
			// $monkey->setNext($squirrel)->setNext($dog);
			return handler;
		}
		 string Handle(string request) override {
			if (this->next_handler_) {
				return this->next_handler_->Handle(request);
			}

			return {};
		}
	};
	/**
	 * All Concrete Handlers either handle a request or pass it to the next handler
	 * in the chain.
	 */
	class MetalHandler : public AbstractHandler {
	public:
		string Handle(string request) override {
			if (request == "A") {
				return "Metal will be bought from  " + request + ".\n";
			}
			else {
				return AbstractHandler::Handle(request);
			}
		}
	};
	class PlasticHandler : public AbstractHandler {
	public:
		string Handle(string request) override {
			if (request == "B") {
				return "Plastic will be bought from " + request + ".\n";
			}
			else {
				return AbstractHandler::Handle(request);
			}
		}
	};
	class CarbonFiberHandler : public AbstractHandler {
	public:
		string Handle(string request) override {
			if (request == "C") {
				return "CarbonFiber will be bought from " + request + ".\n";
			}
			else {
				return AbstractHandler::Handle(request);
			}
		}
	};
	/**
	 * The client code is usually suited to work with a single handler. In most
	 * cases, it is not even aware that the handler is part of a chain.
	 */
	void ClientCode(Handler& handler) {
		vector<string> brand = { "A", "B", "C" };
		for (const string& f : brand) {
			cout << f << " will offer one kind of   raw metarials " << endl;
			const string result = handler.Handle(f);
			if (!result.empty()) {
				std::cout << "  " << result;
			}
			else {
				cout << "  " << f << " was left untouched.\n";
			}
		}
	}

	//
	//抽象构件：原料
	class rawMaterial
	{
	public:
		virtual void showStatus() {}
	};

	//具体构件：塑料
	class Plastic : public rawMaterial
	{
	public:
		virtual void showStatus()
		{
			cout << "Make your plastic purchase now!" << endl;
		}
	};

	//抽象装饰：复合塑料
	class CompositePlastic : public rawMaterial
	{
	public:
		rawMaterial * magicbook;
		CompositePlastic(rawMaterial* MagicBook) {
			this->magicbook = MagicBook;
		}

		virtual void showStatus() {}

	};

	//具体装饰：ABS工程塑料
	class ABS : public CompositePlastic
	{
	public:
		ABS(rawMaterial* magicbook) : CompositePlastic(magicbook) {}
		//增加额外装饰
		void ABSplastic()
		{
		
			cout << "Buy ABS engineering plastic!" << endl;
		}
		void showStatus()
		{
			cout << "Make your plastic purchase now!" << endl;
			ABSplastic();
		}
	};

	//具体装饰：增强改性PC材料
	class PC : public CompositePlastic
	{
	public:
		PC(rawMaterial* magicbook) : CompositePlastic(magicbook) {}
		//增加额外装饰
		void PCplastic()
		{
		

			cout << "Buy PC plastic!" << endl;
		}
		void showStatus()
		{
			cout << "Make your plastic purchase now!" << endl;
			PCplastic();
		}
	};

	


	//抽象观察者
	class AbstractViewer
	{
	public:
		virtual void Update() = 0;
	};

	//具体观察者：采购者
	class company : public AbstractViewer
	{
	public:
		company()
		{
			cout << "I am the company and I am waiting for the purchased goods to be dispatched and shipped to" << endl;
		}

		void Update()
		{
			cout << "The purchased goods have arrived!" << endl;
		}
	};

	//具体观察者：供货商
	class seller : public AbstractViewer
	{
	public:
		seller()
		{
			cout << "I am a seller and I need goods to start shipping!" << endl;
		}

		void Update()
		{
			cout << "The buyer received the goods, I hope he will come back next time to purchase" << endl;
		}
	};
	//抽象主题
	class AbstractTell
	{
	public:
		virtual void addViewer(AbstractViewer* receiver) = 0;
		virtual void removeViewer(AbstractViewer* receiver) = 0;
		virtual void tellAllViewer() = 0;
	};

	//具体主题：logStatus
	class tell : public AbstractTell
	{
	public:
		void addViewer(AbstractViewer* receiver)
		{
			Viewers.push_back(receiver);
		}

		void removeViewer(AbstractViewer* receiver)
		{
			auto it = find(Viewers.begin(), Viewers.end(), receiver);
			if (it != Viewers.end())
				Viewers.erase(it);
		}

		void tellAllViewer()
		{
			deque<AbstractViewer*>::iterator i = Viewers.begin();
			while (i != Viewers.end())
			{
				(*i++)->Update();
			}
		}

	private:
		deque<AbstractViewer*> Viewers;
	};




}