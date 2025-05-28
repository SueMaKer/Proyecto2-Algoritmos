#include <cassert>
#include <iostream>
#include "FloydWarshall.hpp"
#include "Graph.hpp"
#include "ExhaustiveSearch.hpp"
#include "Ship.hpp"
// #include "OtraClase.hpp" // por ejemplo
const int INF = 1e9; // Para evitar overflow

class Test {
public:
    void runAllTests() {
        testFloydWarshall();
        testExhaustiveSearchDisconnected();
        testExhaustiveSearchBasic();
        testExhaustiveSearchWithPruning();
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
    
    // Añadir más funciones para probar otras clases o funcionalidades

    
};

int main() {
    Test testSuite;
    testSuite.runAllTests();
    return 0;
}
