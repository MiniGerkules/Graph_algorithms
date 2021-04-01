#include "Graph.h"
#include <iostream>

int main()
{
	try
	{
		Graph* graph = new Graph();

		graph->Parse("data4.txt");
		graph->PrintAdjacencyList();
		std::string* result = graph->LowestPrice("3", "1");

		std::cout << "Minimum distance -- " << result[0] << std::endl;
		std::cout << "Path: " << result[1] << std::endl;

		delete graph;
	}
	catch (std::bad_alloc error)
	{
		std::cerr << error.what() << std::endl;
	}
	catch (std::domain_error error)
	{
		std::cerr << error.what() << std::endl;
	}

	return 0;
}
