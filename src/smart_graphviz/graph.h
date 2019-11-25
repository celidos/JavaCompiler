#include <string>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::map;


namespace Graphs
{
    struct Node
    {
        Node(string node_name, string label): name(node_name), label(label) {}
        string name;
        string label;
    };

    struct Edge
    {
        Edge(string _from, string _to, string _label = "")
        {
            label = _label;
            from = _from;
            to = _to;
        }

        string label;
        string from;
        string to;
    };

    class UndirectedGraph
    {
    public:
        UndirectedGraph(string _name);
        ~UndirectedGraph();

        void getAllEdges(vector<Edge *> &edges) const;
        void getAllNodes(vector<Node *> &nodes) const;
        string getName() const;

        void addNode(string node_name, string label);
        void addEdge(string from, string to);

    private:
        string name;

        map<string, Node *> nodes;
        map<string, vector<Edge *> > edges;

        void freeNode(string _name);
    };

    class UndirectedGraphSerializer {
    public:
        static string serialize(const UndirectedGraph &graph);
        static void serialize(const UndirectedGraph& graph, std::ofstream &out);
    };

}
