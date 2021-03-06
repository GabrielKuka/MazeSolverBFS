// C++ program to find the shortest path between 
// a given source cell to a destination cell. 

#include "pch.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// This class represents a node in the maze
class Node {
private:
	int x, y, distance;		// Each node has its coordinates: (x, y) and the distance from the source
public:
	Node() {
		distance = 0;
	}
	Node(int f, int s, int d = 0) {
		x = f;
		y = s;
		distance = d;
	}

	// Setters and getters
	void setX(int f) { x = f; }

	void setY(int s) { y = s; }

	int getX() { return x; }
	int getY() { return y; }
	int getDistance() { return distance; }
};

vector<vector<char>> mazeMatrix; // Create a 2D matrix maze
bool sourceSet = false;			 
bool destinationSet = false;
Node mazeSource, mazeExit;		


// Checks whether the current node is within the maze or not
bool isValid(int x, int y)
{
	return (x >= 0) && (x < mazeMatrix.size()) &&
		(y >= 0) && (y < mazeMatrix.size());
}

// The following arrays are used to get the location of the neighboring nodes
int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };


// Finds the source and assigns the coordinates
bool checkSource(vector<vector<char>>& matrix){
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			if(matrix[i][j] == 's'){			
				mazeSource.setX(i);
				mazeSource.setY(j);
				return true;
			}

		
		}
	}

	return false;
}

// Finds the exit and assigns the coordinates
bool checkExit(vector<vector<char>>& matrix){
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			if (matrix[i][j] == 'e') {
				mazeExit.setX(i);
				mazeExit.setY(j);
				return true;
			}
		}
	}

	return false;
}

// The algorithm that finds the paths to the exit of the maze 
int BFS(vector<vector<char>>& matrix)
{
		checkSource(matrix);
		checkExit(matrix);

		// This mazeMatrix is used to store the visited nodes
		vector<vector<bool>> visitedNodes;
		visitedNodes.assign(matrix.size(), vector<bool>(matrix.size(), false));

		

		// Marks the source cell as visited 
		visitedNodes[mazeSource.getX()][mazeSource.getY()] = true;

		
		// Create a queue for BFS 
		queue<Node> list;
		list.push(mazeSource); // push the source of the maze into the queue

		// For each node we scan the neighbors for possible routes to the exit
		while (!list.empty())
		{
			
			Node currentNode = list.front();

			// If we have reached the destination, we are done!
			if (currentNode.getX() == mazeExit.getX() && currentNode.getY() == currentNode.getY())
				return currentNode.getDistance();

			list.pop();

			for (int i = 0; i < 4; i++)
			{

				int rowN = currentNode.getX() + rowNum[i];
				int colN = currentNode.getY() + colNum[i];

				// If the neighboring node is vaild, can pass, and has not been visited, push it to the list 
				if (isValid(rowN, colN) && matrix[rowN][colN] && matrix[rowN][colN] != '0' &&
					!visitedNodes[rowN][colN])
				{
					if (matrix[rowN][colN] != 'e')
						matrix[rowN][colN] = '*';

					// Mark the node as visited
					visitedNodes[rowN][colN] = true;

					Node neighborNode(rowN, colN, currentNode.getDistance() + 1);				
					list.push(neighborNode);
				}
			}
		}
	
	//return -1 if exit is unreachable
	return -1;
}

bool validateCharInput(char input){
	if(input == '0' || input == '1' || input == 's' || input == 'e')
		return true;
	
	return false;
}

bool checkInput(char i) {
	while (!validateCharInput(i)) {
		cout << "Invalid data. Input must be either: 0, 1, s, e.\nEnter it again: ";
		return false;
	}

	while (i == 's') {
		if (!sourceSet) {
			sourceSet = true;
			break;
		}
		else {
			cout << "Source of the maze has already been set.";
			cout << "Enter again: ";
			return false;
		}
	}

	while (i == 'e') {
		if (!destinationSet) {
			destinationSet = true;
			break;
		}
		else {
			cout << "Exit of the maze has already been set.";
			cout << "Enter again: ";
			return false;
		}
	}

	return true;
}

int main()
{

	int size;
	cout << "Enter the size of the maze \n";
	do {
		cout << "Range should be: [3 - 100] ";
		cin >> size;
	} while (size < 3 || size > 100);


	cout << endl;
	
	// Assigns the maze to default nodes = 0
	mazeMatrix.assign(size, vector<char>(size, '0'));

	// Enter the maze
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cin >> mazeMatrix[i][j];
			while (!checkInput(mazeMatrix[i][j])) {
				cin >> mazeMatrix[i][j];
			}

		}
		
	}

	// Check whether there is source and exit or not
	if (!checkSource(mazeMatrix) || !checkExit(mazeMatrix)) {
		cout << "Source or destination can not be found." << endl;
		return 0;
	}


	cout << "\nThe maze you created: \n";

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << mazeMatrix[i][j] << " ";
		}

		cout << "\n";
	}

	int path = BFS(mazeMatrix);

	if (path != -1)
		cout << "Shortest Path is " << path << endl;
	else
		cout << "Destination can not be reached." << endl;

	cout << endl << "Solved maze: \n";
	
	// The solved maze
	for (int i = 0; i < mazeMatrix.size(); i++) {
		for (int j = 0; j < mazeMatrix.size(); j++) {
			cout << mazeMatrix[i][j] << " ";
		}

		cout << endl;
	}

	system("PAUSE");

	return 0;
}
