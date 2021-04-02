#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);


int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();
    std::cout << "Explored positions" << std::endl;
    exploredPositions->printNodeList();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);
    std::cout << "Solution" << std::endl;
    solution->printNodeList();

    // printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env) {
    for (int row = 0; row < ENV_DIM && !std::cin.eof(); row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cin >> env[row][col];
        }
    }
}

void printEnvStdout(Env env, NodeList* solution) {
    //currNode and nextNode's memory will be handled when delete solution is called
    Node* currNode;
    Node* nextNode;
    //Solution assumes startNode and goalNode are included
    //i = 1 to start at node after startNode
    //getLength() - 1 to stop the iteration 1 node short of goalNode
    for (int i = 1; i < solution->getLength() - 1; i++)
    {
        //decide which character to assign env[row][col]
        currNode = solution->getNode(i);
        nextNode = solution->getNode(i + 1);

        if (nextNode->getRow() - currNode->getRow() == -1) {
            env[currNode->getRow()][currNode->getCol()] = SYMBOL_UP;
        }
        else if (nextNode->getRow() - currNode->getRow() == 1) {
            env[currNode->getRow()][currNode->getCol()] = SYMBOL_DOWN;
        }
        else if (nextNode->getCol() - currNode->getCol() == 1) {
            env[currNode->getRow()][currNode->getCol()] = SYMBOL_RIGHT;
        }
        else if (nextNode->getCol() - currNode->getCol() == -1) {
            env[currNode->getRow()][currNode->getCol()] = SYMBOL_LEFT;
        }
        else {
            std::cout << "Error: Unprintable Direction" << std::endl;
        }
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
    nodeList->printNodeList();

    delete nodeList;
}