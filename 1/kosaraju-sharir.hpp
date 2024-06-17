#ifndef KOSARAJU_SHARIR_HPP
#define KOSARAJU_SHARIR_HPP

#include <vector>
#include <list>
#include <stack>

std::vector<std::vector<int>> findSCCs(const std::vector<std::list<int>>& graph, int numVertices);
void runKosarajuSharir();

#endif // KOSARAJU_SHARIR_HPP
