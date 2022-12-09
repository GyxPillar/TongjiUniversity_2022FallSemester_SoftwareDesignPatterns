#pragma once
#include <iostream> 
#include <time.h>
#include <stdlib.h>

/*设计模式：状态模式
  功能：测试部件不同状态的转换*/
namespace lsr {
	// 状态类基类
	class Part;
	class State
	{
	public:
		virtual void Qualified() {}
		virtual void NotQualified() {}
		virtual void NotExamined() {}
		virtual void CurrentState(Part* part) {}
	};
	//零件
	class  Part
	{
	private:
		State* examine_state;  //目前状态
		int examine_result;
	public:
		Part(State* state) : examine_state(state), examine_result(0) {}
		~Part() { delete examine_state; }
		int GetExamineResult() { return examine_result; }
		void SetExamineResult(int  result) { examine_result = result; }
		void SetState(State* state) { delete examine_state; examine_state = state; }
		void GetState() { examine_state->CurrentState(this); }
	};

	// 具体的状态类
	//合格
	class QualifiedState : public State
	{
	public:
		void Qualified(Part* part)
		{
			std::cout << "零件检验结果：合格" << std::endl;
		}
		void CurrentState(Part* part) { Qualified(part); }
	};
	//不合格
	class NotQualifiedState : public State
	{
	public:
		void NotQualified(Part* part)
		{
			std::cout << "零件检验结果：不合格" << std::endl;
		}
		void CurrentState(Part* part) { NotQualified(part); }
	};

	//未检测
	class NotExaminedState : public State
	{
	public:
		void NotExamined(Part* part)
		{
			if (part->GetExamineResult() == 0)
				std::cout << "零件当前状态：尚未检验！" << std::endl;
			else if (part->GetExamineResult() == 1)
			{
				part->SetState(new QualifiedState());
				part->GetState();
			}
			else if (part->GetExamineResult() == -1)
			{
				part->SetState(new NotQualifiedState());
				part->GetState();
			}
		}
		void CurrentState(Part* part) { NotExamined(part); }
	};


	//测试案例
	void client_state()
	{
		std::cout << "-----state pattern test begin----" << std::endl;
		Part* part1 = new Part(new NotExaminedState());
		part1->GetState();
		std::cout << "-------parts examine begin-------" << std::endl;
		std::cout << "please input examine result\n1:qualified;2:not qualified   ";
		char result = getchar();
		if (result == '1')
		{
			part1->SetExamineResult(1);
			part1->GetState();
		}
		else if (result == '2')
		{
			part1->SetExamineResult(-1);
			part1->GetState();
		}
	}
}