#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Graphs
{
    UndirectedGraph::UndirectedGraph(string _name):
        name(_name)
    {
    }

    UndirectedGraph::~UndirectedGraph()
    {
        for (auto node : nodes)
        {
            if (node.second != nullptr)
            {
                // std::cout << "Clean node!" << std::endl;
                delete node.second;
            }
        }

        for (auto node : nodes)
        {
            // std::cout << "Clean edges!" << std::endl;
            freeNode(node.first);
        }
    }

    void UndirectedGraph::freeNode(string _name)
    {
        if (edges.find(_name) != edges.end())
        {
            for (auto edge : edges.at(_name))
            {
                if (edge != nullptr)
                {
                    delete edge;
                }
            }
        }
    }

    void UndirectedGraph::addNode(string _name)
    {
        Node *node = new Node(_name);
        nodes[_name] = node;
    }

    void UndirectedGraph::addEdge(string from, string to)
    {
        Edge *edge = new Edge(from, to);
        edges[from].push_back(edge);
    }

    void UndirectedGraph::getAllNodes(vector<Node *> &_outNodes) const
    {
        _outNodes.clear();
        for (auto node : nodes)
        {
            _outNodes.push_back(node.second);
        }
    }

    void UndirectedGraph::getAllEdges(vector<Edge *> &_outEdges) const
    {
        _outEdges.clear();
        for (auto node : nodes)
        {
            if (edges.find(node.first) != edges.end())
                for (auto edge : edges.at(node.first))
                    _outEdges.push_back(edge);
        }
    }

    string UndirectedGraph::getName() const
    {
        return name;
    }

    string UndirectedGraphSerializer::serialize(const UndirectedGraph& graph)
    {
        vector<Edge *> edges;
        vector<Node *> nodes;

        graph.getAllEdges(edges);
        graph.getAllNodes(nodes);


        std::stringstream ss;
        ss << "graph " << graph.getName() << " {\n";

        for (auto node : nodes)
        {
            std::string name = node->name;
            auto index = name.find("__");
            if (index != std::string::npos) {
                name.replace(index, 2, " ");
            }
            name = name.substr(1, name.find("_") - 1);
            ss << node->name << '\t' << "[ label = \"" << name << "\"];" << '\n';
        }

        for (auto edge : edges)
        {
            ss << '\t' << edge->from << " -- " << edge->to << ";\n";
        }
        ss << "}\n";
        return ss.str();
    }

    void UndirectedGraphSerializer::serialize(const UndirectedGraph& graph, std::ofstream &out)
    {
        out << UndirectedGraphSerializer::serialize(graph);
    }

}
