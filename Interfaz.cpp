#include "Interfaz.hpp"
#include <random>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
#include "Config.hpp"

Interfaz::Interfaz() : window(sf::VideoMode(1200, 800), "Galaxy Map - Game") {
    if (!font.loadFromFile("OpenSans_Condensed-Italic.ttf")) {
        std::cerr << "Failed to load font\n";
        exit(1);
    }

    generateStars();

    menuBox.setSize({220, 110});
    menuBox.setFillColor(sf::Color(30, 30, 60, 230));
    menuBox.setOutlineThickness(2);
    menuBox.setOutlineColor(sf::Color::White);

    subMenuBox.setSize({220, 80});
    subMenuBox.setFillColor(sf::Color(30, 30, 60, 230));
    subMenuBox.setOutlineThickness(2);
    subMenuBox.setOutlineColor(sf::Color::Yellow);

    buildMenuOptions();

    selectedPlanetIndex = -1;
    showMenu = false;
    showSubMenu = false;
}

void Interfaz::generateStars() {
    std::mt19937 gen(1337);
    std::uniform_real_distribution<float> distX(0.f, window.getSize().x);
    std::uniform_real_distribution<float> distY(0.f, window.getSize().y);
    std::uniform_real_distribution<float> distR(1.f, 3.f);

    for (int i = 0; i < 150; ++i) {
        sf::CircleShape star(distR(gen));
        star.setPosition(distX(gen), distY(gen));
        star.setFillColor(sf::Color(255, 255, 255, 150));
        stars.push_back(star);
    }
}

void Interfaz::setSystem(PlanetSystem* newSystem) {
    currentSystem = newSystem;
    if (currentSystem) {
        currentUniverseName = currentSystem->getName();
        
        // Ensure at least one planet exists and is discovered
        if (currentSystem->getPlanetCount() > 0) {
            currentSystem->getPlanet(0).markVisited();
        }
        
        updatePlanetsFromSystem();
    }
}

void Interfaz::updatePlanetsFromSystem() {
    if (!currentSystem) return;

    planets.clear();
    auto positions = generatePositions(currentSystem->getPlanetCount(), window.getSize());

    for (int i = 0; i < currentSystem->getPlanetCount(); ++i) {
        auto& p = currentSystem->getPlanet(i);
        sf::Color planetColor = sf::Color::Green;
        if (p.getHealth() <= 0) planetColor = sf::Color::Red;
        else if (p.hasResourceSite()) planetColor = sf::Color::Cyan;

        // Mark first planet as discovered automatically
        bool discovered = (i == 0) ? true : p.wasVisited();
        
        planets.emplace_back(PlanetDisplay{
            p.getName(),
            positions[i],
            discovered,  // Modified this line
            p.getHealth(),
            p.hasResourceSite(),
            planetColor
        });

        // Ensure the planet system knows the first planet is discovered
        if (i == 0) {
            currentSystem->getPlanet(i).markVisited();
        }
    }

    updateAdjacencyFromSystem();
}

void Interfaz::updateAdjacencyFromSystem() {
    if (!currentSystem) return;
    
    const auto& systemMatrix = currentSystem->getAdjacencyMatrix();
    int n = systemMatrix.size();
    adjacency = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (systemMatrix[i][j] > 0 && 
                currentSystem->getPlanet(i).wasVisited() && 
                currentSystem->getPlanet(j).wasVisited()) {
                adjacency[i][j] = 1;
            }
        }
    }
}

std::vector<sf::Vector2f> Interfaz::generatePositions(int count, sf::Vector2u size) {
    std::vector<sf::Vector2f> pos;
    float cx = size.x / 2.f, cy = size.y / 2.f, r = 250.f;

    for (int i = 0; i < count; ++i) {
        float angle = 2 * 3.14159f * i / count;
        pos.emplace_back(cx + r * cos(angle), cy + r * sin(angle));
    }
    return pos;
}

void Interfaz::buildMenuOptions() {
    menuOptions.clear();
    mainMenuLabels = {"Activate Probes (BFS/DFS)", "Run Cartographers (Dijkstra/Floyd-Warshall)", "Attack"};
    for (int i = 0; i < mainMenuLabels.size(); ++i) {
        sf::Text t;
        t.setFont(font);
        t.setString(mainMenuLabels[i]);
        t.setCharacterSize(16);
        t.setFillColor(sf::Color::White);
        menuOptions.push_back(t);
    }
}

void Interfaz::buildSubMenuOptions(const std::vector<std::string>& labels) {
    subMenuOptions.clear();
    for (const auto& label : labels) {
        sf::Text t;
        t.setFont(font);
        t.setString(label);
        t.setCharacterSize(16);
        t.setFillColor(sf::Color::Yellow);
        subMenuOptions.push_back(t);
    }
}

void Interfaz::drawMenu() {
    window.draw(menuBox);
    for (auto& opt : menuOptions) window.draw(opt);
}

void Interfaz::drawSubMenu() {
    window.draw(subMenuBox);
    for (auto& opt : subMenuOptions) window.draw(opt);
}

void Interfaz::handleClick(const sf::Vector2f& pos) {
    if (showSubMenu) {
        for (int i = 0; i < subMenuOptions.size(); ++i) {
            if (subMenuOptions[i].getGlobalBounds().contains(pos)) {
                auto selectedOption = subMenuOptions[i].getString().toAnsiString();

                if (selectedOption == "RapidSight (BFS)") {
                    activateProbesBFS(selectedPlanetIndex);
                } else if (selectedOption == "DeepProbe (DFS)") {
                    activateProbesDFS(selectedPlanetIndex);
                } else if (selectedOption == "Pathfinder (Dijkstra)") {
                    runDijkstra(selectedPlanetIndex);
                } else if (selectedOption == "StarMapper (Floyd-Warshall)") {
                    runFloydWarshall(selectedPlanetIndex);
                } else if (selectedOption == "Confirm Attack") {
                    attackPlanet(selectedPlanetIndex);
                }

                showSubMenu = false;
                showMenu = false;
                return;
            }
        }
    }

    if (showMenu) {
        for (int i = 0; i < menuOptions.size(); ++i) {
            if (menuOptions[i].getGlobalBounds().contains(pos)) {
                if (i == 0)
                    buildSubMenuOptions({"RapidSight (BFS)", "DeepProbe (DFS)"});
                else if (i == 1)
                    buildSubMenuOptions({"Pathfinder (Dijkstra)", "StarMapper (Floyd-Warshall)"});
                else
                    buildSubMenuOptions({"Confirm Attack"});

                subMenuBox.setPosition(menuBox.getPosition() + sf::Vector2f(0, menuBox.getSize().y + 5));
                for (int j = 0; j < subMenuOptions.size(); ++j)
                    subMenuOptions[j].setPosition(subMenuBox.getPosition() + sf::Vector2f(10, 10 + j * 25));

                showSubMenu = true;
                return;
            }
        }
    }

    // Click on discovered planet to show menu
    for (int i = 0; i < planets.size(); ++i) {
        if (!planets[i].discovered) continue;
        sf::Vector2f p = planets[i].position;
        if (std::hypot(pos.x - p.x, pos.y - p.y) < 20.f) {
            selectedPlanetIndex = i;
            showMenu = true;
            showSubMenu = false;
            menuBox.setPosition(p + sf::Vector2f(30, -10));
            for (int j = 0; j < menuOptions.size(); ++j)
                menuOptions[j].setPosition(menuBox.getPosition() + sf::Vector2f(10, 10 + j * 25));
            return;
        }
    }

    // Click outside closes menus
    showMenu = false;
    showSubMenu = false;
}

void Interfaz::activateProbesBFS(int planetIndex) {
    if (!currentSystem || planetIndex < 0 || planetIndex >= planets.size()) return;
    
    std::queue<int> q;
    std::vector<bool> discovered(planets.size(), false);
    
    // Start with the selected planet
    q.push(planetIndex);
    discovered[planetIndex] = true;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        // Only reveal planets that are actually connected
        for (int neighbor = 0; neighbor < planets.size(); ++neighbor) {
            if (currentSystem->getConnectionWeight(current, neighbor) > 0 && 
                !discovered[neighbor]) {
                discovered[neighbor] = true;
                planets[neighbor].discovered = true;
                currentSystem->getPlanet(neighbor).markVisited();
                q.push(neighbor);
                
                // Visual feedback for each discovery
                std::cout << "Probe revealed: " << planets[neighbor].name << "\n";
            }
        }
    }
    
    updateAdjacencyFromSystem();
}

void Interfaz::activateProbesDFS(int planetIndex) {
    if (!currentSystem || planetIndex < 0 || planetIndex >= planets.size()) return;

    std::vector<bool> visited(planets.size(), false);
    
    std::function<void(int)> dfs = [&](int current) {
        visited[current] = true;
        
        // Explore connected neighbors
        for (int neighbor = 0; neighbor < planets.size(); ++neighbor) {
            if (currentSystem->getConnectionWeight(current, neighbor) > 0 && 
                !visited[neighbor]) {
                planets[neighbor].discovered = true;
                currentSystem->getPlanet(neighbor).markVisited();
                dfs(neighbor);
                
                // Visual feedback for each discovery
                std::cout << "Probe revealed: " << planets[neighbor].name << "\n";
            }
        }
    };
    
    // Start DFS from selected planet
    dfs(planetIndex);
    updateAdjacencyFromSystem();
}
void Interfaz::runDijkstra(int planetIndex) {
    if (!currentSystem || planetIndex < 0 || planetIndex >= planets.size()) return;
    
    auto distances = currentSystem->dijkstra(planetIndex);
    
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] != Config::INF && i < planets.size()) {
            planets[i].discovered = true;
            currentSystem->getPlanet(i).markVisited();
        }
    }
    
    updateAdjacencyFromSystem();
    
    // Visualize distances (optional)
    for (int i = 0; i < distances.size(); ++i) {
        if (i < planets.size()) {
            planets[i].name = currentSystem->getPlanet(i).getName() + " (" + 
                             (distances[i] == Config::INF ? "∞" : std::to_string(distances[i])) + ")";
        }
    }
}

void Interfaz::runFloydWarshall(int planetIndex) {
    if (!currentSystem) return;
    
    auto allPairs = currentSystem->floydWarshall();
    updateAdjacencyFromSystem();
    
    // Update planet names with distances from selected planet
    if (planetIndex >= 0 && planetIndex < allPairs.size()) {
        for (int i = 0; i < allPairs[planetIndex].size(); ++i) {
            if (i < planets.size()) {
                planets[i].name = currentSystem->getPlanet(i).getName() + " (" + 
                                 (allPairs[planetIndex][i] == Config::INF ? "∞" : std::to_string(allPairs[planetIndex][i])) + ")";
            }
        }
    }
}

void Interfaz::attackPlanet(int planetIndex) {
    if (!currentSystem || planetIndex < 0 || planetIndex >= planets.size()) return;
    
    auto& p = currentSystem->getPlanet(planetIndex);
    p.takeDamage(25);
    
    if (planetIndex < planets.size()) {
        planets[planetIndex].health = p.getHealth();
        planets[planetIndex].color = (p.getHealth() <= 0) ? sf::Color::Red : 
                                    (p.hasResourceSite() ? sf::Color::Cyan : sf::Color::Green);
    }
}

void Interfaz::run() {
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
                handleClick(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }

        window.clear(sf::Color::Black);
        
        // Draw stars
        for (auto& star : stars) window.draw(star);
        
        // Draw connections
        for (int i = 0; i < planets.size(); ++i) {
            for (int j = i + 1; j < planets.size(); ++j) {
                if (adjacency[i][j] && planets[i].discovered && planets[j].discovered) {
                    sf::Vertex line[] = {
                        sf::Vertex(planets[i].position, sf::Color(100, 100, 255)),
                        sf::Vertex(planets[j].position, sf::Color(100, 100, 255))
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }
        
        // Draw planets
        for (int i = 0; i < planets.size(); ++i) {
            const auto& p = planets[i];
            if (!p.discovered) continue;
            
            sf::CircleShape planetCircle(20);
            planetCircle.setOrigin(20, 20);
            planetCircle.setPosition(p.position);
            planetCircle.setFillColor(p.color);
            planetCircle.setOutlineThickness(2);
            
            // Make first planet stand out with a thicker outline
            if (i == 0) {
                planetCircle.setOutlineThickness(4);
                planetCircle.setOutlineColor(sf::Color::Yellow);
            } else {
                planetCircle.setOutlineColor(sf::Color::White);
            }
            
            window.draw(planetCircle);
            
            // Draw planet name and health
            sf::Text planetText(p.name, font, 12);
            planetText.setFillColor(sf::Color::White);
            planetText.setPosition(p.position.x - 20, p.position.y + 25);
            window.draw(planetText);
        }
        
        // Draw system info
        sf::Text systemText("System: " + currentUniverseName, font, 20);
        systemText.setPosition(20, 20);
        systemText.setFillColor(sf::Color::Cyan);
        window.draw(systemText);
        
        // Draw menus
        if (showMenu) drawMenu();
        if (showSubMenu) drawSubMenu();

        window.display();
    }
}