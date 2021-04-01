#include "Graph.h"
#include <fstream>
#include <string>

//----------------------------------------------
// Public methods of class AdjacencyList
//----------------------------------------------

// Constructor of class Graph
Graph::Graph()
	: adjacencyList(nullptr), numberOfTops(0)
{}

// Destructor of class Graph
Graph::~Graph()
{
	delete adjacencyList;
}

// Reading data from the console
void Graph::Parse()
{
	std::string data[4];						// One line of user input, split at ';'
	size_t numberOfRecords;						// Number of records in data

	std::cout << "Enter the number of records -- ";
	std::cin >> numberOfRecords;
	std::cout << "Enter the number of cities -- ";
	std::cin >> numberOfTops;
	if (numberOfTops == 0)
		throw std::domain_error("Invalid number of cities!");

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	adjacencyList = new AdjacencyList(numberOfTops);

	std::cout << "\nEnter " << numberOfRecords << " records:" << std::endl;
	for (size_t i = 0; i < numberOfRecords; ++i)
	{
		getline(std::cin, data[0], ';');
		getline(std::cin, data[1], ';');
		getline(std::cin, data[2], ';');
		getline(std::cin, data[3]);

		if (data[2] != "N/A")
			adjacencyList->AddInList(data[0], data[1], std::stoi(data[2]));

		if (data[3] != "N/A")
			adjacencyList->AddInList(data[1], data[0], std::stoi(data[3]));
	}
}

/*
	Reading data from a file
	const std::string nameFile -- the name of the file from which we will read information
*/
void Graph::Parse(const std::string& nameFile)
{
	std::ifstream file(nameFile);				// File for reading

	if (file.is_open())
	{
		std::string data[4];					// One line of data from a file
		size_t numberOfRecords;					// Number of records in data

		file >> numberOfRecords;
		file >> numberOfTops;
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		adjacencyList = new AdjacencyList(numberOfTops);
		for (size_t i = 0; i < numberOfRecords; ++i)
		{
			getline(file, data[0], ';');
			getline(file, data[1], ';');
			getline(file, data[2], ';');
			getline(file, data[3]);

			if (data[2] != "N/A")
				adjacencyList->AddInList(data[0], data[1], std::stoi(data[2]));

			if (data[3] != "N/A")
				adjacencyList->AddInList(data[1], data[0], std::stoi(data[3]));
		}

		file.close();
	}
	else
		throw std::domain_error("Unable to open file!");
}

// The method displays the generated adjacency list
void Graph::PrintAdjacencyList()
{
	if ((adjacencyList == nullptr) || (numberOfTops == 0))
		throw std::domain_error("No data on cities!");

	adjacencyList->PrintList();
}

// The method returns the generated adjacency list
std::string* Graph::GetAdjacencyList()
{
	if ((adjacencyList == nullptr) || (numberOfTops == 0))
		throw std::domain_error("No data on cities!");

	return adjacencyList->GetList();
}

/*
	Method that calls Dijkstra's algorithm to calculate the minimum cost of a trip between two given cities
	const std::string& from -- the city from which we are flying
	const std::string& to -- the city we are flying to
*/
std::string* Graph::LowestPrice(const std::string& from, const std::string& to)
{
	if ((adjacencyList == nullptr) || (numberOfTops == 0))
		throw std::domain_error("No data on cities!");
		
	return adjacencyList->Dijkstra(from, to);
}
