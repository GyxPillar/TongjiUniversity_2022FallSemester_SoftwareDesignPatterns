#pragma once
#include <iostream> 
#include <time.h>
#include <stdlib.h>





/*设计模式：桥接模式
  功能：电脑检验，定义一个检验过程的接口类，子类提供实现*/

namespace lsr {
    // 实现类接口 Implementation（实现类接口）：检验模式
    class ExamineMode {
    public:
        virtual bool security() = 0;
    };

    // 具体实现类：检验零件
    class ExamineParts : public ExamineMode {
    public:
        bool security() override {
            std::cout << "PartExamined, ";
            //设置次品率为1/10
            return rand() % 10;
        }
    };

    // 具体实现类：检验电脑
    class ExaminePC : public ExamineMode {
    public:
        bool security() override {
            std::cout << "ComputerExamined, ";
            //设置次品率为1/9
            return rand() % 9;
        }
    };

    // 抽象化类：检验
    class Examinewithmode {
    public:
        Examinewithmode(ExamineMode* examineMode) {
            this->examineMode = examineMode;
        }

        virtual ~Examinewithmode() { delete examineMode; }

        virtual std::string examine() = 0;

        ExamineMode* examineMode;
    };

    // 扩展抽象化角色：检验零件
    class PartsExamine : public  Examinewithmode {
    public:
        PartsExamine(ExamineMode* examineMode) : Examinewithmode(examineMode) { }
        //扩展抽象类 实现了抽象类中定义的方法
        std::string examine() {
            bool security = examineMode->security();
            if (!security)
                return "not qualified";

            return "qualified";
        }
    };

    // 扩展抽象化角色：检验电脑
    class PCExamine : public  Examinewithmode {
    public:
        PCExamine(ExamineMode* examineMode) : Examinewithmode(examineMode) { }
        //扩展抽象类 实现了抽象类中定义的方法
        std::string examine() {
            bool security = examineMode->security();
            if (!security)
                return "not qualified";

            return "qualified";
        }
    };

    // 客户端使用
    void client_bridge() {
        srand((unsigned)time(NULL));
        Examinewithmode* CPUExamine = new PartsExamine(new ExamineParts());
        std::cout << "CPUExamine Result: " << CPUExamine->examine() << std::endl;
        Examinewithmode* GPUExamine = new PartsExamine(new ExamineParts());
        std::cout << "GPUExamine Result: " << GPUExamine->examine() << std::endl;
        Examinewithmode* MouseExamine = new PartsExamine(new ExamineParts());
        std::cout << "MouseExamine Result: " << MouseExamine->examine() << std::endl;
        Examinewithmode* KeyboardExamine = new PartsExamine(new ExamineParts());
        std::cout << "KeyboardExamine Result: " << KeyboardExamine->examine() << std::endl;

        Examinewithmode* ComputerExamine = new PCExamine(new ExaminePC());
        std::cout << "ComputerExamine Result: " << ComputerExamine->examine() << std::endl;
    }
}