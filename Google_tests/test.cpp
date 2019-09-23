//
// Created by sofya on 23.09.2019.
//

#include <gtest/gtest.h>
#include "graph.h"

TEST(GraphTesting, AddNode) {
  std::string gname = "mygraph";
  Graphs::UndirectedGraph g1(gname);

  g1.addNode("mynode1");
  g1.addNode("mynode2");

  std::vector<Graphs::Node *> nodes;
  g1.getAllNodes(nodes);

  std::vector<std::string> result;
  result.reserve(nodes.size());
  for (auto node: nodes) {
    result.push_back(node->name);
  }
  std::vector<std::string> expected = {"mynode1", "mynode2"};
  EXPECT_EQ(result, expected);
}

TEST(GraphTesting, AddEdge) {
  std::string gname = "mygraph1";
  Graphs::UndirectedGraph g1(gname);

  g1.addNode("lol");
  g1.addNode("kek");
  g1.addNode("cheburek");

  g1.addEdge("lol", "kek");

  std::vector<Graphs::Edge *> edges;
  g1.getAllEdges(edges);

  std::vector<std::pair<std::string, std::string>> result;
  result.reserve(edges.size());
  for (auto edge: edges) {
    result.emplace_back(std::make_pair(edge->from, edge->to));
  }
  std::vector<std::pair<std::string, std::string>> expected = {std::make_pair("lol", "kek")};
  EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
