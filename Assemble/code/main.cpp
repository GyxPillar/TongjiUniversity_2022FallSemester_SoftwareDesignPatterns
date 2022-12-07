#include "memento.h"
#include "builder.h"
#include "composite.h"
#include "template.h"

using namespace tarq;

int main() {
	/*
	* 备忘录模式：
	* 在装配环节，记录装配前的状态和装配后的状态
	* 若装配后有故障，则按照备忘录返回到上一步，直到状态正常
	*/
	std::cout << "----------Memento----------\n";
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	ClientCode();

	/*
	* 建造者模式：
	* 装配环节，分步骤创建复杂对象
	*/
	std::cout << "\n----------Builder----------\n";
	Director* director = new Director();
	ClientCode(*director);
	delete director;

	/*
	* 组合模式：
	* 装配电脑时，每个组件是对象，电脑是一个整体对象
	*/
    std::cout << "\n----------Composite----------\n";
    Component* simple = new CPU;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";

    Component* tree = new Composite;
    Component* branch1 = new Composite;

    Component* leaf_1 = new CPU;
    Component* leaf_2 = new GPU;
    Component* leaf_3 = new AMD;
    Component* leaf_4 = new RAM;
    Component* leaf_5 = new HDD;
    Component* leaf_6 = new Fan;
    Component* leaf_7 = new Power;
    Component* leaf_8 = new Case;
    Component* leaf_9 = new Keyboard;
    Component* leaf_10 = new Mouse;
    branch1->Add(leaf_2);
    branch1->Add(leaf_3);
    branch1->Add(leaf_4);
    branch1->Add(leaf_5);
    branch1->Add(leaf_6);
    branch1->Add(leaf_7);
    Component* branch2 = new Composite;
    branch2->Add(leaf_8);
    Component* branch3 = new Composite;
    branch3->Add(leaf_9);
    branch3->Add(leaf_10);
    tree->Add(branch1);
    tree->Add(branch2);
    tree->Add(branch3);
    std::cout << "Client: Now I've got a composite computere:\n";
    ClientCode(tree);
    std::cout << "\n\n";

    std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(tree, simple);
    std::cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

	/*
	* 模板方法模式：
	* 装配电脑时用不同种类的零件
	* 组装电脑用相同的组装方法模版
	*/
    std::cout << "\n----------Template----------\n";
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1* concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    std::cout << "\n";
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2* concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;

	return 0;
}