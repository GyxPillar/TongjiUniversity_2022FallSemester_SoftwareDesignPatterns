#pragma once
#ifndef BUILDER_H
#define BUILDER_H
#endif

#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>

/*
* 建造者模式：
* 装配环节，分步骤创建复杂对象
*/
namespace tarq {
    class Product1 {
    public:
        std::vector<std::string> parts_;
        void ListParts()const {
            std::cout << "Product parts: ";
            for (size_t i = 0; i < parts_.size(); i++) {
                if (parts_[i] == parts_.back()) {
                    std::cout << parts_[i];
                }
                else {
                    std::cout << parts_[i] << ", ";
                }
            }
            std::cout << "\n\n";
        }
    };
    /*
     * The Builder interface specifies methods for creating the different parts of the Product objects
     */
    class Builder {
    public:
        virtual ~Builder() {}
        virtual void ProduceCPU() const = 0;
        virtual void ProduceGPU() const = 0;
        virtual void ProduceAMD() const = 0;
        /*virtual void ProduceRAM() const = 0;
        virtual void ProduceHDD() const = 0;
        virtual void ProduceFan() const = 0;
        virtual void ProducePower() const = 0;
        virtual void ProduceCase() const = 0;*/
    };
    
    class ConcreteBuilder1 : public Builder {
    private:
        Product1* product;
        /**
         * A fresh builder instance should contain a blank product object, which is used in further assembly.
         */
    public:
        ConcreteBuilder1() {
            this->Reset();
        }

        ~ConcreteBuilder1() {
            delete product;
        }

        void Reset() {
            this->product = new Product1();
        }
        /**
         * All production steps work with the same product instance.
         */

        void ProduceCPU()const override {
            this->product->parts_.push_back("CPU");
        }

        void ProduceGPU()const override {
            this->product->parts_.push_back("GPU");
        }

        void ProduceAMD()const override {
            this->product->parts_.push_back("AMD");
        }
        /*
        void ProduceHDD()const override {
            this->product->parts_.push_back("HDD");
        }

        void ProduceFan()const override {
            this->product->parts_.push_back("Fan");
        }

        void ProducePower()const override {
            this->product->parts_.push_back("Power");
        }

        void ProduceCase()const override {
            this->product->parts_.push_back("Case");
        }
        */
        Product1* GetProduct() {
            Product1* result = this->product;
            this->Reset();
            return result;
        }
    };

    /**
     * The Director is only responsible for executing the building steps in a
     * particular sequence. It is helpful when producing products according to a
     * specific order or configuration. Strictly speaking, the Director class is
     * optional, since the client can control builders directly.
     */
    class Director {
        /**
         * @var Builder
         */
    private:
        Builder* builder;
        /**
         * The Director works with any builder instance that the client code passes
         * to it. This way, the client code may alter the final type of the newly
         * assembled product.
         */

    public:

        void set_builder(Builder* builder) {
            this->builder = builder;
        }

        /**
         * The Director can construct several product variations using the same
         * building steps.
         */

        void BuildMinimalViableProduct() {
            this->builder->ProduceCPU();
        }

        void BuildFullFeaturedProduct() {
            this->builder->ProduceCPU();
            this->builder->ProduceGPU();
            this->builder->ProduceAMD();
        }
    };
    /**
     * The client code creates a builder object, passes it to the director and then
     * initiates the construction process. The end result is retrieved from the
     * builder object.
     */
    void ClientCode(Director& director)
    {
        ConcreteBuilder1* builder = new ConcreteBuilder1();
        director.set_builder(builder);
        std::cout << "Standard basic product:\n";
        director.BuildMinimalViableProduct();

        Product1* p = builder->GetProduct();
        p->ListParts();
        delete p;

        std::cout << "Standard full featured product:\n";
        director.BuildFullFeaturedProduct();

        p = builder->GetProduct();
        p->ListParts();
        delete p;

        // Remember, the Builder pattern can be used without a Director class.
        std::cout << "Custom product:\n";
        builder->ProduceCPU();
        builder->ProduceGPU();
        p = builder->GetProduct();
        p->ListParts();
        delete p;

        delete builder;
    }
}

