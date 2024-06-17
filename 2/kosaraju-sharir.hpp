#ifndef KOSARAJU_SHARIR_HPP
#define KOSARAJU_SHARIR_HPP

#include <vector>
#include <list>
#include <deque>

// Function prototypes for SCC finding algorithms
std::vector<std::vector<int>> findSCCsWithList(const std::vector<std::list<int>>& graph, int numVertices);
std::vector<std::vector<int>> findSCCsWithDeque(const std::vector<std::deque<int>>& graph, int numVertices);
std::vector<std::vector<int>> findSCCsWithListOfLists(const std::list<std::list<int>>& graph, int numVertices);
std::vector<std::vector<int>> findSCCsWithVectorOfVectors(const std::vector<std::vector<int>>& graph, int numVertices);

void runKosarajuSharirWithList();
void runKosarajuSharirWithDeque();
void runKosarajuSharirWithListOfLists();
void runKosarajuSharirWithVectorOfVectors();

#endif // KOSARAJU_SHARIR_HPP
