#pragma once
#include <iostream>
#include <string>

// Adjacency list class
class AdjacencyList
{
private:
	// Class describing the list item
	class Node
	{
	public:
		/*
			Node* next_ -- pointer to the next item in the list
			std::string name_ -- the name of the city we are flying to
			size_t cost_ -- flight cost
		*/
		Node(Node* next_, std::string name_, size_t cost_)
			:  next(next_), name(std::move(name_)), cost(cost_)
		{}

		Node* next;								// The pointer to next element of the list
		const std::string name;					// The name of the city we are flying to
		const size_t cost;						// Flight cost
	};

	Node** list;								// An array that stores adjacent vertices
	const size_t numberOfTops;					// Number of vertices in the graph

	/*
		A method that returns a pointer to the desired element of the adjacency list
		const std::string& toFind -- the name of the vertex to find in the adjacency list
	*/
	Node* Find(const std::string& toFind) const;

	/*
		A method that returns the index of the element to be searched for in the list array
		const std::string& toFind -- the name of the vertex to find in the adjacency list
	*/
	size_t GetIndex(const std::string& toFind) const;

public:
	/*
		Ñonstructor of class AdjacencyList
		unsigned short numberOfTops_ -- number of vertices in the graph
	*/
	AdjacencyList(size_t numberOfTops_);

	// Destructor of class AdjacencyList
	~AdjacencyList();
	
	/*
		Method that adds a new vertex to the list corresponding to the start pointer
		const std::string& mainName -- the top from which the edge comes
		const std::string name -- the name of the added vertex
		size_t cost -- graph edge weight
	*/
	void AddInList(const std::string& mainName, const std::string& name, size_t cost);

	// The method displays the generated adjacency list
	void PrintList() const;

	// The method returns the generated adjacency list
	std::string* GetList() const;

	/*
		Method implementing Dijkstra's algorithm
		const std::string& firstCity -- the name of the city we are departing from
		const std::string& secondCity -- the name of the city we are flying to
	*/
	std::string* Dijkstra(const std::string& firstCity, const std::string& secondCity) const;
};
