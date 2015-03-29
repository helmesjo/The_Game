#include <iostream>
#include <windows.h>

#include "PathNode.h"
#include "PathGraph.h"
#include "StarPlanner.h"
#include <memory>

void printMap(const std::string map[10][10]){
	for (int row = 0; row < 10; ++row){
		for (int column = 0; column < 10; ++column){
			std::string cunt = map[row][column];
			std::cout << cunt.c_str();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main(){

	std::string map[10][10] =
	{
		"[ ]", "[ ]", "[S]", "[ ]", "[+]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
		"[ ]", "[+]", "[+]", "[+]", "[+]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
		"[ ]", "[+]", "[E]", "[ ]", "[+]", "[ ]", "[+]", "[+]", "[+]", "[ ]",
		"[ ]", "[+]", "[ ]", "[ ]", "[ ]", "[ ]", "[+]", "[ ]", "[ ]", "[ ]",
		"[ ]", "[+]", "[+]", "[+]", "[+]", "[+]", "[+]", "[ ]", "[+]", "[ ]",
		"[ ]", "[+]", "[ ]", "[ ]", "[+]", "[ ]", "[+]", "[ ]", "[+]", "[+]",
		"[ ]", "[ ]", "[ ]", "[+]", "[+]", "[ ]", "[+]", "[ ]", "[ ]", "[ ]",
		"[ ]", "[+]", "[ ]", "[+]", "[ ]", "[ ]", "[+]", "[+]", "[ ]", "[ ]",
		"[ ]", "[+]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[+]", "[+]", "[ ]",
		"[ ]", "[ ]", "[ ]", "[+]", "[ ]", "[+]", "[ ]", "[ ]", "[ ]", "[ ]",
	};

	std::shared_ptr<PathNode> startNode = nullptr;
	std::shared_ptr<PathNode> endNode = nullptr;
	std::vector<std::shared_ptr<PathNode>> nodes;

	for (int column = 0; column < 10; ++column){
		for (int row = 0; row < 10; ++row){
			if (map[row][column] == "[S]")
				startNode = std::make_shared<PathNode>(column, row);
			else if (map[row][column] == "[E]")
				endNode = std::make_shared<PathNode>(column, row);
			else if (map[row][column] != "[+]")
				nodes.push_back(std::make_shared<PathNode>(column, row));
		}
	}
	nodes.insert(nodes.begin(), startNode);
	nodes.push_back(endNode);
	PathGraph graph(nodes);
	Planner::StarPlanner<PathNode, PathGraph> planner(graph);
	auto plan = planner.findPlan(*startNode, *endNode);

	printMap(map);
	for (int row = 0; row < 10; ++row){
		for (int column = 0; column < 10; ++column){
			for (auto node : plan){
				if (node->getX() == column && node->getY() == row && node != startNode.get() && node != endNode.get())
					map[row][column] = "[O]";
			}
		}
	}
	printMap(map);

	int a;
	std::cin >> a;

	return 0;
}