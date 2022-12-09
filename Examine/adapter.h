#pragma once
#include <iostream>
#include <string>

/*设计模式：适配器模式
  功能：检验过程中，对不同型号电脑的零件提供检验访问接口*/

namespace lsr {
    class Examine
    {
    public:
        std::string Examine_result;

        Examine(std::string examine_result) : Examine_result(examine_result) {}

        // 现实中实际有的方法
        void examine_cpu()
        {
            std::cout << "examine cpu of " << Examine_result << std::endl;
        }

        void examine_gpu()
        {
            std::cout << "examine gpu of " << Examine_result << std::endl;
        }

    };

    // 这里就是实际的类，不再是接口
    class ExamineWithAdapter
    {
    public:
        virtual void examineCpu()
        {

        }
        virtual void examineGpu()
        {

        }
        virtual ~ExamineWithAdapter() = default;
    };

    // 中间的适配器类,单继承一个目标类，使用组合的方式实现
    class Adapter : public ExamineWithAdapter
    {
    private:
        Examine* examine; // 组合

    public:
        Adapter(std::string Examine_result)
        {
            this->examine = new Examine(Examine_result);
        }

        void examineCpu() override
        {
            std::cout << "with Adapter,";
            examine->examine_cpu();
        }

        void examineGpu() override
        {
            std::cout << "with Adapter,";
            examine->examine_gpu();
        }

        ~Adapter() = default;
    };


    void client_adapter()
    {
        Examine examine("Computer model 1");
        examine.examine_cpu();
        examine.examine_gpu();

        ExamineWithAdapter* adapter = new Adapter("Computer model 2");
        adapter->examineCpu();
        adapter->examineGpu();
    }
}