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
* 组合模式：
* 装配电脑时，每个组件是对象，电脑是一个整体对象
*/
namespace tarq {
    /**
    * The base Component class declares common operations for both simple and
    * complex objects of a composition.
    */
    class Component {
        /**
         * @var Component
         */
    protected:
        Component* parent_;
        /**
         * Optionally, the base Component can declare an interface for setting and
         * accessing a parent of the component in a tree structure. It can also
         * provide some default implementation for these methods.
         */
    public:
        virtual ~Component() {}
        void SetParent(Component* parent) {
            this->parent_ = parent;
        }
        Component* GetParent() const {
            return this->parent_;
        }
     
        virtual void Add(Component* component) {}
        virtual void Remove(Component* component) {}
        virtual bool IsComposite() const {
            return false;
        }
        virtual std::string Operation() const = 0;
    };
  
    class CPU : public Component {
    public:
        std::string Operation() const override {
            return "CPU";
        }
    };

    class GPU : public Component {
    public:
        std::string Operation() const override {
            return "GPU";
        }
    };

    class AMD : public Component {
    public:
        std::string Operation() const override {
            return "AMD";
        }
    };

    class RAM : public Component {
    public:
        std::string Operation() const override {
            return "RAM";
        }
    };

    class HDD : public Component {
    public:
        std::string Operation() const override {
            return "HDD";
        }
    };

    class Fan : public Component {
    public:
        std::string Operation() const override {
            return "Fan";
        }
    };

    class Power : public Component {
    public:
        std::string Operation() const override {
            return "Power";
        }
    };

    class Case : public Component {
    public:
        std::string Operation() const override {
            return "Case";
        }
    };

    class Keyboard : public Component {
    public:
        std::string Operation() const override {
            return "Keyboard";
        }
    };

    class Mouse : public Component {
    public:
        std::string Operation() const override {
            return "Mouse";
        }
    };
    /**
     * The Composite class represents the complex components that may have children.
     * Usually, the Composite objects delegate the actual work to their children and
     * then "sum-up" the result.
     */
    class Composite : public Component {
        /**
         * @var \SplObjectStorage
         */
    protected:
        std::list<Component*> children_;

    public:
        /**
         * A composite object can add or remove other components (both simple or
         * complex) to or from its child list.
         */
        void Add(Component* component) override {
            this->children_.push_back(component);
            component->SetParent(this);
        }
       
        void Remove(Component* component) override {
            children_.remove(component);
            component->SetParent(nullptr);
        }
        bool IsComposite() const override {
            return true;
        }
        /**
         * The Composite executes its primary logic in a particular way. It traverses
         * recursively through all its children, collecting and summing their results.
         * Since the composite's children pass these calls to their children and so
         * forth, the whole object tree is traversed as a result.
         */
        std::string Operation() const override {
            std::string result;
            for (const Component* c : children_) {
                if (c == children_.back()) {
                    result += c->Operation();
                }
                else {
                    result += c->Operation() + "+";
                }
            }
            return "Branch(" + result + ")";
        }
    };
    /**
     * The client code works with all of the components via the base interface.
     */
    void ClientCode(Component* component) {
        // ...
        std::cout << "RESULT: " << component->Operation();
        // ...
    }

    /**
     * Thanks to the fact that the child-management operations are declared in the
     * base Component class, the client code can work with any component, simple or
     * complex, without depending on their concrete classes.
     */
    void ClientCode2(Component* component1, Component* component2) {
        // ...
        if (component1->IsComposite()) {
            component1->Add(component2);
        }
        std::cout << "RESULT: " << component1->Operation();
    }
}