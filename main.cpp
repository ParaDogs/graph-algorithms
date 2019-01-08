#include <iostream>
#include "Graph.h"

int main()
{
    Graph graph;

    /*
     *     .
     *  /____\
     * |\   /|
     * \ \/ /
     *   .
     */
    
    graph.addEdge(1,4);
    graph.addEdge(1,5);
    graph.addEdge(4,3);
    graph.addEdge(4,6);
    graph.addEdge(4,5);
    graph.addEdge(5,6);
    graph.addEdge(5,2);
    graph.addEdge(3,6);
    graph.addEdge(2,6);

    /*другой граф*/
    /*graph.addEdge(5,4);
    graph.addEdge(5,2);
    graph.addEdge(4,6);
    graph.addEdge(4,3);
    graph.addEdge(2,6);
    graph.addEdge(2,3);
    graph.addEdge(2,1);
    graph.addEdge(6,3);
    graph.addEdge(3,1);*/

    /*кольцо*/
    /*graph.addEdge(1,2);
    graph.addEdge(2,3);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(5,6);
    graph.addEdge(6,7);
    graph.addEdge(7,8);
    graph.addEdge(8,1);*/


    graph.print();

    std::cout << graph.paint(1);

    return 0;
}