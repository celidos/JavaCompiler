#include <iostream>
#include <string>
#include <fstream>

#include "graph.h"

int main(int argc, char** argv)
{
    if (argc < 2) 
    {
        std::cout << "Incorrect format: usage gviz []" << std::endl;
    } 
    else 
    {
        std::string gname = "mygraph1";
        Graphs::UndirectedGraph g1(gname);
        
        g1.addNode("lol");
        g1.addNode("kek");
        g1.addNode("Frauline");
        
        g1.addEdge("lol", "kek");
        
        std::ofstream outFile(argv[1]);
        
        Graphs::UndirectedGraphSerializer::serialize(g1, outFile);
    }
        
    return 0;
}
