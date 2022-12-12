#include "memento.h"
#include "builder.h"
#include "composite.h"
#include "template.h"

using namespace tarq;

int main() {
	/*
	* ����¼ģʽ��
	* ��װ�价�ڣ���¼װ��ǰ��״̬��װ����״̬
	* ��װ����й��ϣ����ձ���¼���ص���һ����ֱ��״̬����
	*/
	std::cout << "----------Memento----------\n";
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	ClientCode();

	/*
	* ������ģʽ��
	* װ�价�ڣ��ֲ��贴�����Ӷ���
	*/
	std::cout << "\n----------Builder----------\n";
	Director* director = new Director();
	ClientCode(*director);
	delete director;

	/*
	* ���ģʽ��
	* װ�����ʱ��ÿ������Ƕ��󣬵�����һ���������
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
	* ģ�巽��ģʽ��
	* װ�����ʱ�ò�ͬ��������
	* ��װ��������ͬ����װ����ģ��
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

    getchar();
	return 0;
}