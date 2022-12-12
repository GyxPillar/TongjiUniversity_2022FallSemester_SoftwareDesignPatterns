#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <stdio.h>


/*设计模式：访问者模式
  功能：不同的测试者针对不同配件或整体电脑进行质量评估或功能评估*/
namespace lsr {
    class Element;
    class CPU;
    class GPU;
    class Mouse;

    class Visitor {
    public:
        Visitor(std::string name) {
            visitorName = name;
        }
        virtual void examineCPU(CPU* cpu) {};
        virtual void examineGPU(GPU* cpu) {};
        virtual void examineMouse(Mouse* mouse) {};

        std::string getName() {
            return this->visitorName;
        };
    private:
        std::string visitorName;
    };

    class Element {
    public:
        Element(std::string name) {
            eleName = name;
        }
        virtual void accept(Visitor* visitor) {};

        virtual std::string getName() {
            return this->eleName;
        }
    private:
        std::string eleName;
    };

    class CPU : public Element {
    public:
        CPU(std::string name) : Element(name) {}

        void accept(Visitor* visitor) {
            visitor->examineCPU(this);
        }
    };

    class GPU : public Element {
    public:
        GPU(std::string name) : Element(name) {}

        void accept(Visitor* visitor) {
            visitor->examineGPU(this);
        }
    };

    class Mouse : public Element {
    public:
        Mouse(std::string name) : Element(name) {}

        void accept(Visitor* visitor) {
            visitor->examineMouse(this);
        }
    };

    class CircuitDetector : public Visitor {
    public:
        CircuitDetector(std::string name) : Visitor(name) {}

        // checking cpu
        void examineCPU(CPU* cpu) {
            std::cout << Visitor::getName() << " checks CPU's quality.(" << cpu->getName() << ")" << std::endl;
        }

        // checking GPU
        void examineGPU(GPU* GPU) {
            std::cout << Visitor::getName() << " checks GPU's quality.(" << GPU->getName() << ")" << std::endl;
        }

        // checking Mouse
        void examineMouse(Mouse* Mouse) {
            std::cout << Visitor::getName() << " checks Mouse's quality.(" << Mouse->getName() << ")" << std::endl;
        }

    };

    class FunctionDetector : public Visitor {
    public:
        FunctionDetector(std::string name) : Visitor(name) {}
        virtual void examineCPU(CPU* cpu) {
            std::cout << Visitor::getName() << " checks CPU's function." << std::endl;
        }

        // checking GPU
        void examineGPU(GPU* GPU) {
            std::cout << Visitor::getName() << " checks GPU's function." << std::endl;
        }

        // checking Mouse
        void examineMouse(Mouse* Mouse) {
            std::cout << Visitor::getName() << " checks Mouse's function." << std::endl;
        }
    };


    class Computer {
    public:
        Computer(CPU* cpu,
            GPU* gpu,
            Mouse* mouse) {
            elementList.push_back(cpu);
            elementList.push_back(gpu);
            elementList.push_back(mouse);
        };
        void Accept(Visitor* visitor) {
            for (std::vector<Element*>::iterator i = elementList.begin(); i != elementList.end(); i++)
            {
                (*i)->accept(visitor);
            }
        };
    private:
        std::vector<Element*> elementList;
    };

    void client_visitor() {
        CPU* cpu = new CPU("CPU");
        GPU* gpu = new GPU("video card");
        Mouse* mouse = new Mouse("Mouse");
        Computer* myComputer = new Computer(cpu, gpu, mouse);

        CircuitDetector* circuitDetector = new CircuitDetector("Visitor1(CircuitDetector)");
        FunctionDetector* functionDetector = new FunctionDetector("Visitor2(FunctionDetector)");

        std::cout << "\nStep 1:\n" << circuitDetector->getName() << " begin to check the quality of computer's circuits:" << std::endl;
        myComputer->Accept(circuitDetector);

        std::cout << "\nStep 2:\n" << functionDetector->getName() << " begin to check checks computer's functions:" << std::endl;
        myComputer->Accept(functionDetector);
    }
}
#pragma once
