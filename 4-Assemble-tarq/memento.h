#pragma once
#ifndef MEMENTO_H
#define MEMENTO_H
#endif

#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>

/*
* 备忘录模式：
* 在装配环节，记录装配前的状态和装配后的状态
* 若装配后有故障，则按照备忘录返回到上一步，直到状态正常
*/
namespace tarq {
	/* 	
	* The Memento interface provides a way to retrieve the memento's metadata, such as creation date or name.
	* However, it doesn't expose the Originator's state.
	*/
	class Memento {
	public:
		virtual ~Memento() {}
		virtual std::string GetName() const = 0;
		virtual std::string date() const = 0;
		virtual std::string state() const = 0;
	};
	/*
	* The Concrete Memento contains the infrastructure for storing the Originator's state.
	*/
	class ConcreteMemento : public Memento {
	private:
		std::string state_;
		std::string date_;
	public:
		ConcreteMemento(std::string state) : state_(state) {
		this->state_ = state;
		std::time_t now = std::time(0);
		char str[26];
		ctime_s(str, sizeof str, &now);
		this->date_ = str;
		//this->date_ = std::ctime(&now);
		};
		/*
		* The Originator uses this method when restoring its state.
		*/
		std::string state() const override {
			return this->state_;
		}
		/*
		* The rest of the methods are used by the Caretaker to display metadata.
		*/
		std::string GetName() const override {
			return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
		}
		std::string date() const override {
			return this->date_;
		}
	};
	/*
	* The Originator holds some important state that may change over time. It also  
	* defines a method for saving the state inside a memento and another method for  
	* restoring the state from it.
	*/ 
	class Originator {
		/*
		* @var string For the sake of simplicity, the originator's state is stored inside a single variable.
		*/
	private:
		std::string state_;
		std::string GenerateRandomString(int& index) {
			const std::string subassembly[] = {
				"CPU",
				"GPU",
				"AMD",		//主板
				"RAM",
				"HDD",		//硬盘
				"Fan",		//散热
				"Power",	//电源
				"Case",		//机箱
			};
			std::string random_string = subassembly[index];
			return random_string;
		}
	public:
		Originator(std::string state) : state_(state) {
			std::cout << "Originator: The initial state is: " << this->state_ << "\n";
		}
		/*
		* The Originator's business logic may affect its internal state.
		* Therefore the client should backup the state before launching methods of the business logic via the save() method.
		*/
		void DoSomething(int& index) {
			std::cout << "Originator: The computer is being assembled...\n";
			this->state_ = this->GenerateRandomString(index);
			std::cout << "Originator: The current status is: " << this->state_ << "\n";
			index++;
		}
		/*
		* Saves the current state inside a memento.
		*/
		Memento* Save() {
			return new ConcreteMemento(this->state_);
		}
		/*
		* Restores the Originator's state from a memento object.
		*/
		void Restore(Memento* memento) {
			this->state_ = memento->state();
			std::cout << "Originator: Now, The status is: " << this->state_ << "\n";
		}
	};
	/*
	* The Caretaker doesn't depend on the Concrete Memento class. 
	* Therefore, it doesn't have access to the originator's state, stored inside the memento. 
	* It works with all mementos via the base Memento interface.
	*/
	class Caretaker {
	private:  
		std::vector<Memento*> mementos_;
		Originator* originator_;
	public:     
		Caretaker(Originator* originator) : originator_(originator) {      
		}
		~Caretaker() { 
			for (auto m : mementos_) delete m; 
		}
		void Backup() { 
			std::cout << "\nCaretaker: Saving Originator's state...\n";     
			this->mementos_.push_back(this->originator_->Save()); 
		}
		void Undo() {
			if (!this->mementos_.size()) {
				return;
			}
			Memento* memento = this->mementos_.back();
			this->mementos_.pop_back();
			std::cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
			try {
				this->originator_->Restore(memento);
			}
			catch (...) {
				this->Undo();
			}
		}
		void ShowHistory() const {
			std::cout << "Caretaker: Here's the list of mementos:\n";
			for (Memento* memento : this->mementos_) {
				std::cout << memento->GetName() << "\n";
			}
		}
	};
	/*
	* Client code.
	*/
	void ClientCode() {
		int stringLength = 5;
		int index = rand() % stringLength;

		Originator* originator = new Originator("Mac book 2000.");
		Caretaker* caretaker = new Caretaker(originator);
		caretaker->Backup();
		originator->DoSomething(index);
		caretaker->Backup();
		originator->DoSomething(index);
		caretaker->Backup();
		originator->DoSomething(index);
		std::cout << "\n";
		caretaker->ShowHistory();
		std::cout << "\nClient: Now, let's rollback!\n\n";
		caretaker->Undo();
		std::cout << "\nClient: Once more!\n\n";
		caretaker->Undo();

		delete originator;
		delete caretaker;
	}
}