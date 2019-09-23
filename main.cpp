#include <iostream>
#include <string>
#include "graph.h"

int main()
{
    std::string gname = "mygraph1";
    Graphs::UndirectedGraph g1(gname);
    
    g1.addNode("lol");
    g1.addNode("kek");
    g1.addNode("Fraulene");
    
    g1.addEdge("lol", "kek");
    
    std::cout << Graphs::UndirectedGraphSerializer::serialize(g1) << std::endl;
    
    return 0;
}
