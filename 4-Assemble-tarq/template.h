#pragma once
#ifndef COMPOSITE_H
#define COMPOSITE_H
#endif

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <stdio.h>

/*
* 模板方法模式：
* 装配电脑时用不同种类的零件
* 组装电脑用相同的组装方法模版
*/
namespace tarq {
    class AbstractClass {
        /**
         * The template method defines the skeleton of an algorithm.
         */
    public:
        void TemplateMethod() const {
            this->BaseOperation1();
            this->RequiredOperations1();
            this->BaseOperation2();
            this->Hook1();
            this->RequiredOperation2();
            this->BaseOperation3();
            this->Hook2();
        }
        /**
         * These operations already have implementations.
         */
    protected:
        void BaseOperation1() const {
            std::cout << "AbstractClass: Install CPU\n";
        }
        void BaseOperation2() const {
            std::cout << "AbstractClass: Install GPU\n";
        }
        void BaseOperation3() const {
            std::cout << "AbstractClass: Install AMD\n";
        }
        /**
         * These operations have to be implemented in subclasses.
         */
        virtual void RequiredOperations1() const = 0;
        virtual void RequiredOperation2() const = 0;
        /**
         * These are "hooks." Subclasses may override them, but it's not mandatory
         * since the hooks already have default (but empty) implementation. Hooks
         * provide additional extension points in some crucial places of the
         * algorithm.
         */
        virtual void Hook1() const {}
        virtual void Hook2() const {}
    };
    /**
     * Concrete classes have to implement all abstract operations of the base class.
     * They can also override some operations with a default implementation.
     */
    class ConcreteClass1 : public AbstractClass {
    protected:
        void RequiredOperations1() const override {
            std::cout << "ConcreteClass1: Install intel CORE i7 7th Gen\n";
        }
        void RequiredOperation2() const override {
            std::cout << "ConcreteClass1: Install GTX 1080\n";
        }
    };
    /**
     * Usually, concrete classes override only a fraction of base class' operations.
     */
    class ConcreteClass2 : public AbstractClass {
    protected:
        void RequiredOperations1() const override {
            std::cout << "ConcreteClass2: Install AMD A6-3650 APU\n";
        }
        void RequiredOperation2() const override {
            std::cout << "ConcreteClass2: Install GTX 980 TI\n";
        }
        void Hook1() const override {
            std::cout << "ConcreteClass2 says: Overridden Hook1\n";
        }
    };
    /**
     * The client code calls the template method to execute the algorithm. Client
     * code does not have to know the concrete class of an object it works with, as
     * long as it works with objects through the interface of their base class.
     */
    void ClientCode(AbstractClass* class_) {
        // ...
        class_->TemplateMethod();
        // ...
    }
}
