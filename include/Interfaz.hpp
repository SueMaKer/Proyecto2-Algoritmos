#ifndef INTERFAZ_HPP
#define INTERFAZ_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "PlanetSystem.hpp"

struct PlanetDisplay {
    std::string name;
    sf::Vector2f position;
    bool discovered;
    int health;
    bool hasResource;
    sf::Color color;
};

class Interfaz {
private:
    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::CircleShape> stars;
    std::vector<PlanetDisplay> planets;
    std::vector<std::vector<int>> adjacency;
    PlanetSystem* currentSystem;
    std::string currentUniverseName;

    // Menu system
    sf::RectangleShape menuBox;
    sf::RectangleShape subMenuBox;
    std::vector<sf::Text> menuOptions;
    std::vector<sf::Text> subMenuOptions;
    std::vector<std::string> mainMenuLabels;
    int selectedPlanetIndex;
    bool showMenu;
    bool showSubMenu;

    void generateStars();
    void updateAdjacencyFromSystem();
    void buildMenuOptions();
    void buildSubMenuOptions(const std::vector<std::string>& labels);
    void drawMenu();
    void drawSubMenu();
    std::vector<sf::Vector2f> generatePositions(int count, sf::Vector2u size);

public:
    Interfaz();
    void setSystem(PlanetSystem* newSystem);
    void updatePlanetsFromSystem();
    void handleClick(const sf::Vector2f& pos);
    void run();

    // Action methods
    void activateProbesBFS(int planetIndex);
    void activateProbesDFS(int planetIndex);
    void runDijkstra(int planetIndex);
    void runFloydWarshall(int planetIndex);
    void attackPlanet(int planetIndex);
};

#endif // INTERFAZ_HPP