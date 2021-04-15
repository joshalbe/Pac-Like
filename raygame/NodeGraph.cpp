#include "NodeGraph.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	//Finds a path from start to end
	std::deque<Node*> path;

	//Checks if start and end is null
	if (!start || !end)
		//Returns an empty list
		return std::deque<Node*>();

	//Creates a node that points to iterator for the graph
	Node* iter = nullptr;
	//Creates an open list 
	std::deque<Node*> openList;
	//Creates a closed list
	std::deque<Node*> closedList;

	//Adds push front of start to the open list
	openList.push_front(start);
	start->gScore = 0;

	//Loops the open list is not empty
	while (openList.size() > 0)
	{
		//Sorts the open list items by the g score
		for (int i = 0; i < openList.size(); i++)
		{
			for (int j = openList.size(); j > i; j--)
			{
				if (openList[i] > openList[j - 1])
				{
					Node* temp = openList[i];
					openList[i] = openList[j - 1];
					openList[j - 1] = temp;
				}
			}
		}

		//Sets the iterator to the front of the open list
		iter = openList.front();

		//Checks if the pointing to the end node
		if (iter == end)
			break;

		//Pops the front items of the open list
		openList.pop_front();

		//Adds the front items to the closed list
		closedList.push_front(iter);

		//Loops for all edges for the iterator
		for (int i = 0; i < iter->connections.size(); i++)
		{
			//Creates a node pointer to the other end of the edge
			Node* other = nullptr;
			if (iter->connections[i].target != iter)
				other = iter->connections[i].target;

			//Checks if node at the end is in the closed list
			if (std::find(closedList.begin(), closedList.end(), other) != closedList.end()) {
				continue;
			}

			//Sets g score to the iterator with the cost of the edge
			float gScore = iter->gScore + iter->connections[i].cost;
			float hScore = (other->position - end->position).getMagnitude();
			float fScore = gScore + hScore;

			//Checks if node at the end is in the open list
			if (std::find(openList.begin(), openList.end(), other) == openList.end())
			{

				//Sets the other nodes g/h score to g/h score early
				other->gScore = gScore;
				other->hScore = hScore;


				//Sets the nodes previous to be the iterator
				other->previous = iter;

				//Adds the node to the open list front
				openList.push_front(other);
			}

			//If the g score is less than the node at the end of g score
			else if (gScore < other->gScore)
			{
				//Sets the other nodes g/h score to g/h score early
				other->gScore = gScore;
				other->hScore = hScore;

				//Sets the previous node to iterator
				other->previous = iter;
			}

		}
	}
	//While iterator is not at start
	while (iter != start)
	{
		//Sets the iterator at the path's front
		path.push_front(iter);
		//Sets iterator to its previous
		iter = iter->previous;
	}
	//Returns the path
	return path;
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}
