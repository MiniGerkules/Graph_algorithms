#include "Adjacency_list.h"

//----------------------------------------------
// Private methods of class AdjacencyList
//----------------------------------------------
/*
	A method that returns a pointer to the desired element of the adjacency list
	const std::string& toFind -- the name of the vertex to find in the adjacency list
*/
AdjacencyList::Node* AdjacencyList::Find(const std::string& toFind) const
{
	for (size_t i = 0; i < numberOfTops; ++i)
		if (list[i] != nullptr)
		{
			if (toFind == list[i]->name)
				return list[i];
		}
		else
			return nullptr;

	throw std::domain_error("The list of cities has been formed and there is no city " + toFind + " in it!");
}

/*
	A method that returns the index of the element to be searched for in the list array
	const std::string& toFind -- the name of the vertex to find in the adjacency list
*/
size_t AdjacencyList::GetIndex(const std::string& toFind) const
{
	for (size_t i = 0; i < numberOfTops; ++i)
		if (toFind == list[i]->name)
			return i;
}

//----------------------------------------------
// Public methods of class AdjacencyList
//----------------------------------------------
/*
	Ñonstructor of class AdjacencyList
	unsigned short numberOfTops_ -- number of vertices in the graph
*/
AdjacencyList::AdjacencyList(size_t numberOfTops_) 
	: list(new Node*[numberOfTops_]), numberOfTops(numberOfTops_)
{
	for (size_t i = 0; i < numberOfTops_; ++i)
		list[i] = nullptr;
}

// Destructor of class AdjacencyList
AdjacencyList::~AdjacencyList()
{
	Node* current;								// Current item
	Node* deleted;								// The element to be removed

	for (size_t i = 0; i < numberOfTops; ++i)
	{
		current = list[i];
		while (current != nullptr)
		{
			deleted = current;
			current = current->next;
			delete deleted;
		}
	}

	delete[] list;
}

/*
	Method that adds a new vertex to the list corresponding to the start pointer
	const std::string& mainName -- the top from which the edge comes
	const std::string name -- the name of the added vertex
	size_t cost -- graph edge weight
*/
void AdjacencyList::AddInList(const std::string& mainName, const std::string& name, size_t cost)
{
	Node* current;								// The pointer that we go through the list
												
	current = Find(mainName);
	if (current != nullptr)
	{
		while (current->next != nullptr)
			current = current->next;

		current->next = new Node(nullptr, name, cost);
		if (Find(name) == nullptr)
		{
			for (size_t i = 1; i < numberOfTops; ++i)
				if (list[i] == nullptr)
				{
					list[i] = new Node(nullptr, name, 0);
					return;
				}
		}
	}
	else
	{
		for (size_t i = 0; i < numberOfTops; ++i)
			if (list[i] == nullptr)
			{
				list[i] = new Node(nullptr, mainName, 0);
				list[i]->next = new Node(nullptr, name, cost);
				if (Find(name) == nullptr)
				{
					for (size_t i = 1; i < numberOfTops; ++i)
						if (list[i] == nullptr)
						{
							list[i] = new Node(nullptr, name, 0);
							return;
						}
				}
				else
					return;
			}

		throw std::domain_error("More cities were introduced than predicted!");
	}
}

// The method displays the generated adjacency list
void AdjacencyList::PrintList() const
{
	Node* current;								// Current list item

	for (size_t i = 0; i < numberOfTops; ++i)
	{
		if (list[i] != nullptr)
		{
			current = list[i];
			std::cout << "There are routes from " << current->name << " to:" << std::endl;
 			current = current->next;

			while (current != nullptr)
			{
				std::cout << " * " << current->name << ". Cost -- " << current->cost << std::endl;
				current = current->next;
			}

			std::cout << std::endl;
		}
		else
			break;
	}
}

// The method returns the generated adjacency list
std::string* AdjacencyList::GetList() const
{
	Node* current;								// Current list item
	std::string* result;

	result = new std::string[numberOfTops];
	for (size_t i = 0; i < numberOfTops; ++i)
	{
		if (list[i] != nullptr)
		{
			current = list[i];
			result[i] = current->name + ": ";
			current = current->next;

			while (current != nullptr)
			{
				result[i] += current->name + ", ";
				current = current->next;
			}

			result[i].erase(result[i].length() - 2, 2);
		}
		else
			break;
	}

	return result;
}

/*
	Method implementing Dijkstra's algorithm
	const std::string& firstCity -- the name of the city we are departing from
	const std::string& secondCity -- the name of the city we are flying to
*/
std::string* AdjacencyList::Dijkstra(const std::string& firstCity, const std::string& secondCity) const
{
	std::string* result;						// Result of Dijkstra's algorithm
	size_t* unvisitedPeaks;						// Array of unvisited vertices
	size_t* ways;								// The array with which we will restore the path
	size_t* allCosts;							// Array of all prices
	Node* mainCurrent = nullptr;				// Main current item
	Node* current = nullptr;					// The current item that we are traversing through the linked list mainCurrent
	size_t counter = numberOfTops;				// Counter showing the number of unprocessed vertices

	// Checking the existence of the transferred cities and initializing the values
	allCosts = new size_t[numberOfTops];
	ways = new size_t[numberOfTops];
	for (size_t i = 0; i < numberOfTops; ++i)
	{
		if (list[i]->name == firstCity)
		{
			mainCurrent = list[i];
			allCosts[i] = 0;
			ways[i] = i;
		}
		else if (list[i]->name == secondCity)
		{
			current = list[i];
			allCosts[i] = std::numeric_limits<size_t>::max();
			ways[i] = std::numeric_limits<size_t>::max();
		}
		else
		{
			allCosts[i] = std::numeric_limits<size_t>::max();
			ways[i] = std::numeric_limits<size_t>::max();
		}
	}

	if (mainCurrent == nullptr)
		throw std::domain_error(firstCity + " doesn't exist!");
	if (current == nullptr)
		throw std::domain_error(secondCity + " doesn't exist!");

	result = new std::string[2]{ "", "" };
	unvisitedPeaks = new size_t[numberOfTops];
	for (size_t i = 0; i < numberOfTops; ++i)
		unvisitedPeaks[i] = i;
	size_t indexV;
	size_t indexW;

	while (true)
	{
		current = mainCurrent->next;
		indexW = GetIndex(mainCurrent->name);
		while (current != nullptr)
		{
			indexV = GetIndex(current->name);
			if (allCosts[indexV] > (current->cost + allCosts[indexW]))
			{
				allCosts[indexV] = current->cost + allCosts[indexW];
				ways[indexV] = indexW;
			}

			current = current->next;
		}

		unvisitedPeaks[indexW] = std::numeric_limits<size_t>::max();
		--counter;
		size_t min = std::numeric_limits<size_t>::max();

		if (counter != 0)
		{
			// Choosing the next vertex
			for (size_t i = 0; i < numberOfTops; ++i)
				if (unvisitedPeaks[i] != std::numeric_limits<size_t>::max())
					if (min > allCosts[i])
					{
						min = allCosts[i];
						mainCurrent = list[i];
					}
		}
		else
			break;
	}
	
	// Forming the result
	size_t index = GetIndex(secondCity);
	size_t indexSource = GetIndex(firstCity);
	result[0] = std::to_string(allCosts[index]);
	if (allCosts[index] != std::numeric_limits<size_t>::max())
	{
		result[1] += secondCity;
		while (ways[index] != indexSource)
		{
			index = ways[index];
			result[1] += " <- " + list[index]->name;
		}

		result[1] += " <- " + list[indexSource]->name;
	}
	else
		result[1] = "Impossible to get there!";

	return result;
}
