#include "adapter.h"
#include "bridge.h"
#include "state.h"
#include "visitor.h"
#include <iostream>
#include <string>
using namespace lsr;


int main()
{
	std::cout << "----------state pattern----------\n";
	client_state();
	std::cout << "---------------------------------\n\n\n";

	std::cout << "---------adapter pattern---------\n";
	client_adapter();
	std::cout << "---------------------------------\n\n\n";

	std::cout << "---------visitor pattern---------\n";
	client_visitor();
	std::cout << "---------------------------------\n\n\n";

	std::cout << "----------bridge pattern---------\n";
	client_bridge();
	std::cout << "---------------------------------\n\n\n";
}