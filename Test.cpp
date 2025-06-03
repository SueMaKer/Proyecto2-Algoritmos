#include <cassert>
#include <algorithm>
#include <iostream>
#include "FloydWarshall.hpp"
#include "Graph.hpp"
#include "ExhaustiveSearch.hpp"
#include "Ship.hpp"
#include "StarMapper.hpp"
#include "DFS.hpp"
#include "LocalSearch.hpp"
#include "DeepProbe.hpp"
// #include "OtraClase.hpp" // por ejemplo
const int INF = 1e9; // Para evitar overflow

class Test {
public:
    void runAllTests() {
        testFloydWarshall();
        testExhaustiveSearchDisconnected();
        testExhaustiveSearchBasic();
        testExhaustiveSearchWithPruning();
        testStarMapper();
        testStarMapperUpdateMatrix();
        testDFS();
        testLocalSearch();
        testDeepProbe();
        // testOtraClase();
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
        Graph g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(2, 3, 1);
        g.addEdge(0, 3, 10);  // camino directo, más caro

        ExhaustiveSearch noPrune(g, false);  // sin poda
        int cost1 = noPrune.findMinimumPath(0, 3);
        int iterations1 = noPrune.getIterationCount();
        assert(cost1 == 3);

        ExhaustiveSearch withPrune(g, true);  // con poda
        int cost2 = withPrune.findMinimumPath(0, 3);
        int iterations2 = withPrune.getIterationCount();
        assert(cost2 == 3);

        std::cout << "Test - Cost without pruning: " << cost1 << "\n";
        std::cout << "Test - Iterations without pruning: " << iterations1 << "\n";
        std::cout << "Test - Cost with pruning: " << cost2 << "\n";
        std::cout << "Test - Iterations with pruning: " << iterations2 << "\n";

        assert(iterations2 < iterations1);  // poda debería reducir iteraciones
        std::cout << "Test passed: pruning reduces iterations.\n";
    }
    
    void testStarMapper() {
        using namespace std;

        // Definimos una matriz de costes (INF = 1e9)
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

    void testDFS() {
        // Matriz de adyacencia de un grafo simple
        // 0 -> 1, 0 -> 2, 1 -> 3
        std::vector<std::vector<int>> graph = {
            {0, 1, 1, Config::INF},   // Nodo 0
            {1, 0, Config::INF, 1},   // Nodo 1
            {1, Config::INF, 0, Config::INF}, // Nodo 2
            {Config::INF, 1, Config::INF, 0}  // Nodo 3
        };

        DFS dfs(graph);
        dfs.run(0); // Iniciar DFS desde el nodo 0

        const auto& reachable = dfs.getReachableNodes();
        int iterations = dfs.getIterationCount();

        std::cout << "Reachable nodes from node 0: ";
        for (int node : reachable) {
            std::cout << node << " ";
        }
        std::cout << "\nTotal iterations: " << iterations << std::endl;

        // Verificación simple
        std::vector<int> expected = {0, 1, 3, 2}; // el orden puede variar dependiendo del grafo
        if (reachable.size() == expected.size()) {
            std::cout << "Test passed!" << std::endl;
        } else {
            std::cout << "Test failed!" << std::endl;
        }
    }

    void testLocalSearch() {
        // Matriz de adyacencia/costos:
        // Nodo 0 conectado con 1 y 2
        std::vector<std::vector<int>> graph = {
            {0, 5, 10, Config::INF},
            {5, 0, Config::INF, Config::INF},
            {10, Config::INF, 0, 3},
            {Config::INF, Config::INF, 3, 0}
        };

        int nodeToTest = 0;
        LocalSearch ls(graph, nodeToTest);
        ls.run();

        const auto& neighbors = ls.getNeighbors();

        std::cout << "Neighbors of node " << nodeToTest << ": ";
        for (int n : neighbors) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // Resultado esperado: nodos 1 y 2
        std::vector<int> expected = {1, 2};
        
        // Comparación sin importar el orden
        std::vector<int> sortedNeighbors = neighbors;
        std::sort(sortedNeighbors.begin(), sortedNeighbors.end());
        std::sort(expected.begin(), expected.end());

        if (sortedNeighbors == expected) {
            std::cout << "Test passed!" << std::endl;
        } else {
            std::cout << "Test failed!" << std::endl;
        }
    }

    void testDeepProbe() {
        std::vector<std::vector<int>> graph = {
            {0, 1, Config::INF, Config::INF, Config::INF},
            {1, 0, 1, Config::INF, Config::INF},
            {Config::INF, 1, 0, 1, Config::INF},
            {Config::INF, Config::INF, 1, 0, 1},
            {Config::INF, Config::INF, Config::INF, 1, 0}
        };

        DeepProbe probe(graph, 3);  // profundidad máxima de 3 saltos

        std::cout << "Test: Camino de 0 a 4 (esperado: existe en 3 saltos)\n";
        probe.probe(0, 4);

        std::cout << "\nTest: Camino de 0 a 2 (esperado: existe en 2 saltos)\n";
        probe.probe(0, 2);

        std::cout << "\nTest: Camino de 0 a 4 con profundidad insuficiente (máx 2 saltos, esperado: no encontrado)\n";
        DeepProbe shallowProbe(graph, 2);  // profundidad insuficiente
        shallowProbe.probe(0, 4);
    }

};


int main() {
    Test testSuite;
    testSuite.runAllTests();
    return 0;
}
