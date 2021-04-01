#include "CppUnitTest.h"
#include "../Graph_algorithms/Graph.h"
#include <string>
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(ParseTest)
		{
			Graph* graph = new Graph();
			std::string absResult[] = { "1: 8, 9, 3, 5", "8: 5, 1", "9: 3, 1", "3: 4, 7, 5, 9, 1", "5: 6, 8, 1, 3, 7",
												"2: 4, 6, 7", "4: 3, 2, 7", "6: 2, 5, 7", "7: 3, 4, 2, 6, 5" };
			graph->Parse("C:\\Users\\Евгений\\OneDrive\\Рабочий стол\\Лабораторные работы\\4 семестр\\АиСД\\Lab3\\Graph_algorithms\\Graph_algorithms\\data3.txt");
			std::string* methodResult = graph->GetAdjacencyList();
			for (size_t i = 0; i < 9; ++i)
				Assert::AreEqual(methodResult[i], absResult[i]);

			delete graph;
		}

		TEST_METHOD(LowestPriceTest1)
		{
			Graph* graph = new Graph();
			graph->Parse("C:\\Users\\Евгений\\OneDrive\\Рабочий стол\\Лабораторные работы\\4 семестр\\АиСД\\Lab3\\Graph_algorithms\\Graph_algorithms\\data1.txt");

			std::string* result = graph->LowestPrice("Saint-Petersburg", "Khabarovsk");
			Assert::AreEqual(result[0], (std::string)"14");
			Assert::AreEqual(result[1], (std::string)"Khabarovsk <- Saint-Petersburg");

			delete graph;
		}

		TEST_METHOD(LowestPriceTest2)
		{
			Graph* graph = new Graph();
			graph->Parse("C:\\Users\\Евгений\\OneDrive\\Рабочий стол\\Лабораторные работы\\4 семестр\\АиСД\\Lab3\\Graph_algorithms\\Graph_algorithms\\data2.txt");

			std::string* result = graph->LowestPrice("7", "2");
			Assert::AreEqual(result[0], (std::string)"6");
			Assert::AreEqual(result[1], (std::string)"2 <- 3 <- 7");

			result = graph->LowestPrice("8", "6");
			Assert::AreEqual(result[0], (std::string)"6");
			Assert::AreEqual(result[1], (std::string)"6 <- 4 <- 1 <- 8");

			result = graph->LowestPrice("8", "6");
			Assert::AreEqual(result[0], (std::string)"6");
			Assert::AreEqual(result[1], (std::string)"6 <- 4 <- 1 <- 8");

			result = graph->LowestPrice("5", "7");
			Assert::AreEqual(result[0], (std::string)"6");
			Assert::AreEqual(result[1], (std::string)"7 <- 4 <- 1 <- 5");

			delete graph;
		}

		TEST_METHOD(LowestPriceTest3)
		{
			Graph* graph = new Graph();
			graph->Parse("C:\\Users\\Евгений\\OneDrive\\Рабочий стол\\Лабораторные работы\\4 семестр\\АиСД\\Lab3\\Graph_algorithms\\Graph_algorithms\\data3.txt");

			std::string* result = graph->LowestPrice("2", "5");
			Assert::AreEqual(result[0], (std::string)"11");
			Assert::AreEqual(result[1], (std::string)"5 <- 6 <- 2");

			result = graph->LowestPrice("7", "9");
			Assert::AreEqual(result[0], (std::string)"9");
			Assert::AreEqual(result[1], (std::string)"9 <- 3 <- 7");

			result = graph->LowestPrice("4", "8");
			Assert::AreEqual(result[0], (std::string)"9");
			Assert::AreEqual(result[1], (std::string)"8 <- 5 <- 3 <- 4");

			result = graph->LowestPrice("6", "1");
			Assert::AreEqual(result[0], (std::string)"10");
			Assert::AreEqual(result[1], (std::string)"1 <- 5 <- 6");

			delete graph;
		}

		TEST_METHOD(LowestPriceTest4)
		{
			Graph* graph = new Graph();
			graph->Parse("C:\\Users\\Евгений\\OneDrive\\Рабочий стол\\Лабораторные работы\\4 семестр\\АиСД\\Lab3\\Graph_algorithms\\Graph_algorithms\\data4.txt");

			std::string* result = graph->LowestPrice("1", "6");
			Assert::AreEqual(result[0], (std::string)"9");
			Assert::AreEqual(result[1], (std::string)"6 <- 5 <- 3 <- 2 <- 1");

			result = graph->LowestPrice("2", "4");
			Assert::AreEqual(result[0], (std::string)"5");
			Assert::AreEqual(result[1], (std::string)"4 <- 3 <- 2");

			result = graph->LowestPrice("3", "1");
			Assert::AreEqual(result[0], (std::string)"9");
			Assert::AreEqual(result[1], (std::string)"1 <- 2 <- 4 <- 3");

			result = graph->LowestPrice("6", "4");
			Assert::AreEqual(result[0], std::to_string(std::numeric_limits<size_t>::max()));
			Assert::AreEqual(result[1], (std::string)"Impossible to get there!");

			delete graph;
		}

		TEST_METHOD(AddInListTest1)
		{
			AdjacencyList* list = new AdjacencyList(5);
			std::string absResult[] = { "1: 2", "2: 1", "4: 5", "5", "3: 2" };

			list->AddInList("1", "2", 5);
			list->AddInList("2", "1", 5);
			list->AddInList("4", "5", 3);
			list->AddInList("3", "2", 1);

			std::string* methodResult = list->GetList();
			for (size_t i = 0; i < 5; ++i)
				Assert::AreEqual(methodResult[i], absResult[i]);
		}

		TEST_METHOD(AddInListTest2)
		{
			AdjacencyList* list = new AdjacencyList(6);
			
			list->AddInList("7", "3", 3);
			std::string* methodResult = list->GetList();
			Assert::AreEqual((std::string)"7: 3", methodResult[0]);

			list->AddInList("7", "4", 4);
			methodResult = list->GetList();
			Assert::AreEqual((std::string)"7: 3, 4", methodResult[0]);

			list->AddInList("7", "5", 5);
			methodResult = list->GetList();
			Assert::AreEqual((std::string)"7: 3, 4, 5", methodResult[0]);

			list->AddInList("3", "2", 6);
			methodResult = list->GetList();
			Assert::AreEqual((std::string)"3: 2", methodResult[1]);

			list->AddInList("3", "3", 6);
			methodResult = list->GetList();
			Assert::AreEqual((std::string)"3: 2, 3", methodResult[1]);

			list->AddInList("2", "1", 6);
			methodResult = list->GetList();
			Assert::AreEqual((std::string)"4", methodResult[2]);
		}
	};
}
