#pragma once
#include "Adjacency_list.h"

class Graph
{
private:
	AdjacencyList* adjacencyList;				// Adjacency list for a given graph
	size_t numberOfTops;						// Number of graph vertices

public:
	// Constructor of class Graph
	Graph();

	// Destructor of class Graph
	~Graph();

	// Reading data from the console
	void Parse();

	/*
		Reading data from a file
		const std::string nameFile -- the name of the file from which we will read information
	*/
	void Parse(const std::string& nameFile);

	// The method displays the generated adjacency list
	void PrintAdjacencyList();

	// The method returns the generated adjacency list
	std::string* GetAdjacencyList();

	/*
		Method that calls Dijkstra's algorithm to calculate the minimum cost of a trip between two given cities
		const std::string& from -- the city from which we are flying
		const std::string& to -- the city we are flying to
	*/
	std::string* LowestPrice(const std::string& from, const std::string& to);
};
