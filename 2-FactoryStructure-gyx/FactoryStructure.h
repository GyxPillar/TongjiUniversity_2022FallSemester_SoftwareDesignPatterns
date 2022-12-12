#include <iostream>
#include <Windows.h>
#include <conio.h>
namespace gyx
{
    // 1.工厂模式（笔记本/台式电脑 工厂 生产 笔记本/台式电脑 产品）

    // 产品（电脑）接口
    class Computer
    {
    public:
        virtual ~Computer() {}
        virtual void showName() const = 0;
    };

    // 笔记本电脑类：产品接口实现
    class Laptop : public Computer
    {
    public:
        void showName() const override
        {
            std::cout << "This is a Laptop." << std::endl;
        }
    };

    // 台式电脑类：产品接口实现
    class Desktop : public Computer
    {
    public:
        void showName() const override
        {
            std::cout << "This is a Desktop." << std::endl;
        }
    };

    // 工厂基类
    class ComputerFactory
    {
    public:
        virtual ~ComputerFactory(){};
        virtual Computer *createComputer() const = 0;
    };

    // 笔记本电脑工厂：工厂基类实现
    class LaptopFactory : public ComputerFactory
    {
    public:
        Computer *createComputer() const override
        {
            auto ret = new Laptop();
            std::cout << "The computer factory produced a Laptop." << std::endl;
            ret->showName();
            return ret;
        }
    };

    // 台式电脑工厂：工厂基类实现
    class DesktopFactory : public ComputerFactory
    {
    public:
        Computer *createComputer() const override
        {
            auto ret = new Desktop();
            std::cout << "The computer factory produced a Desktop." << std::endl;
            ret->showName();
            return ret;
        }
    };

    // 2.抽象工厂

    // 键盘基类
    class Keyboard
    {
    public:
        virtual ~Keyboard(){};
        virtual void showName() const = 0;
    };

    // Win键盘：键盘基类实现
    class WinKeyboard : public Keyboard
    {
    public:
        void showName() const override
        {
            std::cout << "This is a WinKeyboard." << std::endl;
        }
    };

    // Mac键盘：键盘基类实现
    class MacKeyboard : public Keyboard
    {
    public:
        void showName() const override
        {
            std::cout << "This is a MacKeyboard." << std::endl;
        }
    };

    // 显示器基类
    class Monitor
    {
    public:
        virtual ~Monitor(){};
        virtual void showName() const = 0;
    };

    //  Win显示器：显示器基类实现
    class WinMonitor : public Monitor
    {
    public:
        void showName() const override
        {
            std::cout << "This is a WinMonitor." << std::endl;
        }
    };

    //  Mac显示器：显示器基类实现
    class MacMonitor : public Monitor
    {
    public:
        void showName() const override
        {
            std::cout << "This is a MacMonitor." << std::endl;
        }
    };

    // 外设工厂接口
    class PeripheralsFactory
    {
    public:
        virtual Keyboard *createKeyboard() const = 0;
        virtual Monitor *createMonitor() const = 0;
    };

    // Win工厂：外设工厂接口实现
    class WinFactory : public PeripheralsFactory
    {
    public:
        Keyboard *createKeyboard() const override
        {
            auto ret = new WinKeyboard();
            std::cout << "The peripherals factory produced a WinKeyboard." << std::endl;
            ret->showName();
            return ret;
        }
        Monitor *createMonitor() const override
        {
            auto ret = new WinMonitor();
            std::cout << "The peripherals factory produced a WinMonitor." << std::endl;
            ret->showName();
            return ret;
        }
    };

    // Mac工厂：外设工厂接口实现
    class MacFactory : public PeripheralsFactory
    {
    public:
        Keyboard *createKeyboard() const override
        {
            auto ret = new MacKeyboard();
            std::cout << "The peripherals factory produced a MacKeyboard." << std::endl;
            ret->showName();
            return ret;
        }
        Monitor *createMonitor() const override
        {
            auto ret = new MacMonitor();
            std::cout << "The peripherals factory produced a MacMonitor." << std::endl;
            ret->showName();
            return ret;
        }
    };

    // 交互 调用工厂模式（生产笔记本电脑/台式电脑）
    void function1()
    {
        LaptopFactory *laptopFactory = new LaptopFactory();
        DesktopFactory *desktopFactory = new DesktopFactory();
        while (1)
        {
            system("cls");
            std::cout << "Please select the type of computer you are producing:" << std::endl;
            std::cout << "1.Laptop" << std::endl;
            std::cout << "2.Desktop" << std::endl;
            std::cout << "3.Exit" << std::endl;
            std::cout << "[Type]:";

            int choice = 0;
            std::cin >> choice;
            if (choice == 1)
                laptopFactory->createComputer();
            else if (choice == 2)
                desktopFactory->createComputer();
            else if (choice == 3)
                break;
            else
                continue;

            std::cout << "Enter to continue...";
            while (getch() != 13)
                ;
        }
        delete laptopFactory;
        delete desktopFactory;
    }

    // 交互 调用工厂模式（生产笔记本电脑/台式电脑）
    void function2()
    {
        WinFactory *winFactory = new WinFactory();
        MacFactory *macFactory = new MacFactory();
        while (1)
        {
            system("cls");
            std::cout << "Please select the peripheral you are producing:" << std::endl;
            std::cout << "1.WinKeyboard" << std::endl;
            std::cout << "2.MacKeyboard" << std::endl;
            std::cout << "3.WinMonitor" << std::endl;
            std::cout << "4.MacMonitor" << std::endl;
            std::cout << "5.Exit" << std::endl;
            std::cout << "[Type]:";

            int choice = 0;
            std::cin >> choice;
            if (choice == 1)
                winFactory->createKeyboard();
            else if (choice == 2)
                macFactory->createKeyboard();
            else if (choice == 3)
                winFactory->createMonitor();
            else if (choice == 4)
                macFactory->createMonitor();
            else if (choice == 5)
                break;
            else
                continue;

            std::cout << "Enter to continue...";
            while (getch() != 13)
                ;
        }
        delete winFactory;
        delete macFactory;
    }
}
