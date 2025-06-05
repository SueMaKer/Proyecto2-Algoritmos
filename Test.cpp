#include <cassert>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include "FloydWarshall.hpp"
#include "Graph.hpp"
#include "ExhaustiveSearch.hpp"
#include "Ship.hpp"
#include "StarMapper.hpp"
#include "Pathfinder.hpp"
#include "Dijkstra.hpp"
#include "BFS.hpp"
#include "GreedySearch.hpp"
#include <iomanip>


const int INF = 1e9; //evitar overflow

class Test {
public:
    void runAllTests() {
        testFloydWarshall();
        testExhaustiveSearchDisconnected();
        testExhaustiveSearchBasic();
        testExhaustiveSearchWithPruning();
        testStarMapper();
        testStarMapperUpdateMatrix();
        testBFS();
        testDijkstra();
        testGreedySearch();
        

        
        cout << "All tests have passed successfully.\n";
    }

private:
    void testFloydWarshall() {
        FloydWarshall fw(4);
        fw.addEdge(0, 1, 5);
        fw.addEdge(1, 2, 3);
        fw.addEdge(2, 3, 1);
        fw.addEdge(0, 3, 10);
        fw.run();

        assert(fw.getDistance(0, 3) == 9);
        assert(fw.getDistance(3, 0) >= INF / 2);

        std::vector<int> expected = {0, 1, 2, 3};
        assert(fw.getPath(0, 3) == expected);
    }

    void testExhaustiveSearchBasic() {
        // Create a simple graph
        Graph graph(4);
        graph.addEdge(0, 1, 2);
        graph.addEdge(1, 2, 3);
        graph.addEdge(2, 3, 4);
        graph.addEdge(0, 3, 10); // direct but more expensive

        // Initialize search
        ExhaustiveSearch search(graph, false);

        // Just make sure the method works and returns a cost
        int cost = search.findMinimumPath(0, 3);
        cout << "Test - Minimum path cost from 0 to 3: " << cost << endl;
        assert(cost > 0); // Should be valid and positive

        // Check that findMinimumPath() does not crash
        vector<int> path = search.getBestPath();
        cout << "Test - Path size: " << path.size() << endl;
        assert(!path.empty());
    }

    void testExhaustiveSearchDisconnected() {
        Graph graph(3);
        graph.addEdge(0, 1, 5);
        // No path from 1 to 2

        ExhaustiveSearch search(graph, false);
        int cost = search.findMinimumPath(1, 2);
        cout << "Test - Cost from disconnected 1 to 2: " << cost << endl;

        // Should be "infinite" (no path), assuming INT_MAX
        assert(cost >= INT_MAX / 2 || cost == INT_MAX);
    }

    void testExhaustiveSearchWithPruning() {
    using namespace std;
    using namespace std::chrono;

    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(0, 3, 10);  // camino directo, más caro

    // Sin poda
    ExhaustiveSearch noPrune(g, false);
    auto start1 = high_resolution_clock::now();
    int cost1 = noPrune.findMinimumPath(0, 3);
    auto end1 = high_resolution_clock::now();
    int iterations1 = noPrune.getIterationCount();
    auto duration1 = duration_cast<microseconds>(end1 - start1).count();

    
    ExhaustiveSearch withPrune(g, true);
    auto start2 = high_resolution_clock::now();
    int cost2 = withPrune.findMinimumPath(0, 3);
    auto end2 = high_resolution_clock::now();
    int iterations2 = withPrune.getIterationCount();
    auto duration2 = duration_cast<microseconds>(end2 - start2).count();

    assert(cost1 == 3);
    assert(cost2 == 3);

    cout << "Test - Cost without pruning: " << cost1 << "\n";
    cout << "Test - Iterations without pruning: " << iterations1 << "\n";
    cout << "Test - Time without pruning (microseconds): " << duration1 << "\n";

    cout << "Test - Cost with pruning: " << cost2 << "\n";
    cout << "Test - Iterations with pruning: " << iterations2 << "\n";
    cout << "Test - Time with pruning (microseconds): " << duration2 << "\n";

    assert(iterations2 < iterations1);  // poda debería reducir iteraciones
    cout << "Test passed: pruning reduces iterations.\n";
}

    
    void testStarMapper() {
        using namespace std;

        // Define na matriz de costes (INF = 1e9)
        vector<vector<int>> costMatrix = {
            {0, 3, Config::INF, 7},
            {8, 0, 2, Config::INF},
            {5, Config::INF, 0, 1},
            {2, Config::INF, Config::INF, 0}
        };

        // Vector de planetas explorados: solo 0, 2 y 3 por ejemplo
        vector<int> exploredPlanets = {0, 2, 3};

        // Creamos StarMapper
        StarMapper mapper(&costMatrix, &exploredPlanets);

        // Probamos costes entre los planetas explorados usando floyd.getDistance()
        // Estos valores los calculamos con FloydWarshall o a mano
        int cost_0_to_3 = mapper.getCost(0, 3); // debería ser 7 o mejor
        int cost_2_to_3 = mapper.getCost(2, 3); // debería ser 1
        int cost_3_to_0 = mapper.getCost(3, 0); // debería ser 2

        cout << "Cost from 0 to 3: " << cost_0_to_3 << endl;
        cout << "Cost from 2 to 3: " << cost_2_to_3 << endl;
        cout << "Cost from 3 to 0: " << cost_3_to_0 << endl;

        // Asserts para validar los resultados esperados
        assert(cost_0_to_3 == 6);
        assert(cost_2_to_3 == 1);
        assert(cost_3_to_0 == 2);

        cout << "StarMapper test passed!" << endl;
    }
    void testStarMapperUpdateMatrix() {
        using namespace std;

        // Matriz inicial
        vector<vector<int>> costMatrix = {
            {0, 3, Config::INF, 7},
            {8, 0, 2, Config::INF},
            {5, Config::INF, 0, 1},
            {2, Config::INF, Config::INF, 0}
        };

        vector<int> exploredPlanets = {0, 2, 3};

        StarMapper mapper(&costMatrix, &exploredPlanets);

        // Verifico costo original de 0 a 3
        assert(mapper.getCost(0, 3) == 6);

        // Actualizo la matriz con nuevos valores
        vector<vector<int>> newCostMatrix = {
            {0, 1, Config::INF, 10},
            {1, 0, 5, Config::INF},
            {Config::INF, Config::INF, 0, 1},
            {Config::INF, Config::INF, Config::INF, 0}
        };

        // Actualizo el puntero a la matriz de costos y llamo a update
        mapper.updateRouteCostsMatrixPtr(&newCostMatrix);

        // Ahora la ruta más barata 0 -> 3 debería ser 1 + 5 + 1 = 7 (0->1->2->3)
        int newCost = mapper.getCost(0, 3);
        cout << "New cost from 0 to 3 after update: " << newCost << endl;

        assert(newCost == 7);

        cout << "StarMapper matrix update test passed!" << endl;
    }
    void testPathfinderWithAssert() {
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph = {
        {0, {{1, 3}, {2, 5}}},
        {1, {{0, 3}, {2, 2}, {3, 4}}},
        {2, {{0, 5}, {1, 2}, {4, 6}}},
        {3, {{1, 4}, {4, 1}}},
        {4, {{2, 6}, {3, 1}}}
    };

    Pathfinder pathfinder(graph);

    int source = 0;
    int target = 4;
    int expectedCost = 3 + 2 + 6; // 0 -> 1 -> 2 -> 4 = 11 (ajustá si tu implementación calcula diferente)

    int actualCost = pathfinder.findShortestPathCost(source, target);

    std::cout << "Testing Pathfinder from " << source << " to " << target << "...\n";
    std::cout << "Expected cost: " << expectedCost << ", Actual cost: " << actualCost << "\n";

    assert(actualCost == expectedCost && "Error: Coste incorrecto en Pathfinder.");
    std::cout << " Pathfinder test passed.\n\n";
}

    void testBFS() {
    // Grafo de prueba:
    // 0 -> 1, 0 -> 2
    // 1 -> 3
    std::unordered_map<int, std::vector<int>> graph = {
        {0, {1, 2}},
        {1, {0, 3}},
        {2, {0}},
        {3, {1}}
    };

    BFS bfs(graph);
    std::vector<int> neighbors = bfs.getNeighborsWithTimer(0);

    std::cout << "Neighbors of node 0: ";
    for (int n : neighbors) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::cout << "Iterations: " << bfs.getIterationCount() << std::endl;
    std::cout << "Duration: " << std::fixed << std::setprecision(3)
              << bfs.getElapsedTimeMs() << " ms" << std::endl;

    // Vecinos esperados (orden no importa): 1, 2, 3
    std::vector<int> expected = {1, 2, 3};

    std::sort(neighbors.begin(), neighbors.end());
    std::sort(expected.begin(), expected.end());

    if (neighbors == expected) {
        std::cout << "BFS test passed!" << std::endl;
    } else {
        std::cout << "BFS test failed!" << std::endl;
    }
}

    void testDijkstra() {
        std::unordered_map<int, std::vector<std::pair<int, int>>> graph = {
            {0, {{1, 4}, {2, 1}}},
            {1, {{3, 1}}},
            {2, {{1, 2}, {3, 5}}},
            {3, {}}
        };

        int start = 0;
        int end = 3;

        int cost = dijkstraShortestPathCost(graph, start, end);
        std::vector<int> path = dijkstraShortestPath(graph, start, end);

        std::cout << "Test Dijkstra - Shortest path from " << start << " to " << end << ":\n";
        std::cout << "Expected cost: 6\n";
        std::cout << "Actual cost: " << cost << "\n";

        std::cout << "Path: ";
        for (int node : path) std::cout << node << " ";
        std::cout << "\n";

        std::cout << "Iterations: " << getDijkstraIterationCount() << "\n";
        std::cout << "Duration: " << std::fixed << std::setprecision(3)
                  << getDijkstraDurationMs() << " ms\n";

        // Verificación de valores esperados
        assert(cost == 4);  // Camino óptimo: 0 -> 2 -> 1 -> 3
        std::vector<int> expectedPath = {0, 2, 1, 3};
        assert(path == expectedPath);

        std::cout << "Dijkstra test passed!\n";
    }
        void testGreedySearch() {
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph = {
        {0, {{1, 2}, {2, 5}}},
        {1, {{0, 2}, {2, 1}, {3, 7}}},
        {2, {{0, 5}, {1, 1}, {3, 1}}},
        {3, {{1, 7}, {2, 1}}}
    };

    GreedySearch greedy(graph);
    std::vector<int> path = greedy.findPath(0, 3);

    std::cout << "Test Greedy Search - Path from 0 to 3:\n";
    std::cout << "Path: ";
    for (int node : path) {
        std::cout << node << " ";
    }
    std::cout << "\nIterations: " << greedy.getIterationCount() << std::endl;
    std::cout << "Duration: " << std::fixed << std::setprecision(3)
              << greedy.getElapsedTimeMs() << " ms" << std::endl;

    // Validar que llegó al destino
    if (!path.empty() && path.front() == 0 && path.back() == 3) {
        std::cout << "Greedy Search test passed!\n";
    } else {
        std::cout << "Greedy Search test failed!\n";
    }
}
};

int main() {
    Test testSuite;
    testSuite.runAllTests();
    return 0;
}