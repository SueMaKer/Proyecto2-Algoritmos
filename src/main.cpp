/* #include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <random>
#include <queue>

struct Planeta {
    std::string nombre;
    sf::Vector2f pos;
    bool descubierto;
    int vida;
    int eterium;
};

const int NUM_PLANETAS = 20;
const float RADIO_PLANETA = 25.f;

std::vector<sf::Vector2f> generarPosiciones(int n, sf::Vector2u ventanaSize) {
    std::vector<sf::Vector2f> posiciones;
    std::mt19937 gen(42);
    std::uniform_real_distribution<float> distX(100.f, ventanaSize.x - 400.f);
    std::uniform_real_distribution<float> distY(100.f, ventanaSize.y - 100.f);

    for (int i = 0; i < n; ++i) {
        sf::Vector2f pos;
        bool valida;
        int intentos = 0;

        do {
            pos = {distX(gen), distY(gen)};
            valida = true;
            for (const auto& p : posiciones) {
                float dx = pos.x - p.x;
                float dy = pos.y - p.y;
                if (std::sqrt(dx*dx + dy*dy) < RADIO_PLANETA * 4.f) {
                    valida = false;
                    break;
                }
            }
            intentos++;
            if (intentos > 100) break;
        } while (!valida);

        posiciones.push_back(pos);
    }
    return posiciones;
}

std::vector<std::vector<int>> generarAdyacencia(const std::vector<Planeta>& planetas) {
    int n = planetas.size();
    std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            float dx = planetas[i].pos.x - planetas[j].pos.x;
            float dy = planetas[i].pos.y - planetas[j].pos.y;
            float dist = std::sqrt(dx*dx + dy*dy);
            if (dist < 250.f) {
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
        }
    }
    return adj;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Mapa Galáctico - Juego");

    sf::Font font;
    if (!font.loadFromFile("OpenSans_Condensed-Italic.ttf")) {
        std::cerr << "Error al cargar fuente OpenSans.ttf\n";
        return -1;
    }

    std::vector<Planeta> planetas(NUM_PLANETAS);
    auto posiciones = generarPosiciones(NUM_PLANETAS, window.getSize());

    for (int i = 0; i < NUM_PLANETAS; ++i) {
        planetas[i].nombre = "Planeta_" + std::to_string(i+1);
        planetas[i].pos = posiciones[i];
        planetas[i].descubierto = false;
        planetas[i].vida = 100 + (i * 5);
        planetas[i].eterium = 50 + (i * 3);
    }

    planetas[0].descubierto = true;
    auto adyacencia = generarAdyacencia(planetas);

    std::vector<sf::CircleShape> estrellas;
    std::mt19937 gen(1337);
    std::uniform_real_distribution<float> distX(0.f, window.getSize().x);
    std::uniform_real_distribution<float> distY(0.f, window.getSize().y);
    std::uniform_real_distribution<float> distR(1.f, 3.f);
    for (int i = 0; i < 150; ++i) {
        sf::CircleShape estrella(distR(gen));
        estrella.setPosition(distX(gen), distY(gen));
        estrella.setFillColor(sf::Color(255, 255, 255, 150));
        estrellas.push_back(estrella);
    }

    int planetaSeleccionado = -1;
    bool mostrarMenu = false;
    sf::RectangleShape menuOpciones(sf::Vector2f(220, 120));
    menuOpciones.setFillColor(sf::Color(30, 30, 60, 230));
    menuOpciones.setOutlineThickness(2);
    menuOpciones.setOutlineColor(sf::Color::White);

    std::vector<sf::Text> opciones(3);
    std::vector<std::string> etiquetas = {
        "1. Activar sondas (BFS)",
        "2. Ejecutar cartografos",
        "3. Atacar"
    };
    for (int i = 0; i < 3; ++i) {
        opciones[i].setFont(font);
        opciones[i].setCharacterSize(16);
        opciones[i].setString(etiquetas[i]);
        opciones[i].setFillColor(sf::Color::White);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

                if (mostrarMenu) {
                    for (int i = 0; i < 3; ++i) {
                        if (opciones[i].getGlobalBounds().contains(mousePos)) {
                            if (i == 0 && planetaSeleccionado != -1) {
                                std::vector<bool> visitado(NUM_PLANETAS, false);
                                std::queue<std::pair<int, int>> cola;
                                cola.push({planetaSeleccionado, 0});
                                visitado[planetaSeleccionado] = true;

                                while (!cola.empty()) {
                                    auto [actual, nivel] = cola.front(); cola.pop();

                                    if (nivel >= 3) continue;

                                    for (int j = 0; j < NUM_PLANETAS; ++j) {
                                        if (adyacencia[actual][j] == 1 && !visitado[j]) {
                                            visitado[j] = true;
                                            cola.push({j, nivel + 1});
                                            if (!planetas[j].descubierto) {
                                                planetas[j].descubierto = true;
                                                std::cout << "Sonda descubrió (nivel " << nivel + 1 << "): " << planetas[j].nombre << "\n";
                                            }
                                        }
                                    }
                                }
                            }
                            mostrarMenu = false;
                            break;
                        }
                    }
                } else {
                    for (int i = 0; i < NUM_PLANETAS; ++i) {
                        if (!planetas[i].descubierto) continue;
                        float dx = mousePos.x - planetas[i].pos.x;
                        float dy = mousePos.y - planetas[i].pos.y;
                        float dist = std::sqrt(dx*dx + dy*dy);
                        if (dist < RADIO_PLANETA) {
                            planetaSeleccionado = i;
                            mostrarMenu = true;
                            menuOpciones.setPosition(planetas[i].pos.x + 40.f, planetas[i].pos.y - 40.f);
                            for (int j = 0; j < 3; ++j) {
                                opciones[j].setPosition(menuOpciones.getPosition().x + 10, menuOpciones.getPosition().y + 10 + j * 30);
                            }
                            break;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(15, 15, 40));
        for (auto& estrella : estrellas) window.draw(estrella);

        for (int i = 0; i < NUM_PLANETAS; ++i) {
            if (!planetas[i].descubierto) continue;
            for (int j = i + 1; j < NUM_PLANETAS; ++j) {
                if (!planetas[j].descubierto) continue;
                if (adyacencia[i][j] == 1) {
                    sf::Vertex linea[] = {
                        sf::Vertex(planetas[i].pos, sf::Color(100, 150, 255, 180)),
                        sf::Vertex(planetas[j].pos, sf::Color(100, 150, 255, 180))
                    };
                    window.draw(linea, 2, sf::Lines);
                }
            }
        }

        for (int i = 0; i < NUM_PLANETAS; ++i) {
            if (!planetas[i].descubierto) continue;
            sf::CircleShape circulo(RADIO_PLANETA);
            circulo.setFillColor(sf::Color(80, 180, 255));
            circulo.setOutlineThickness(3.f);
            circulo.setOutlineColor(sf::Color(200, 220, 255));
            circulo.setOrigin(RADIO_PLANETA, RADIO_PLANETA);
            circulo.setPosition(planetas[i].pos);
            window.draw(circulo);

            float x_text = planetas[i].pos.x + RADIO_PLANETA + 10.f;
            float y_text = planetas[i].pos.y - 15.f;

            sf::Text textoNombre(planetas[i].nombre, font, 20);
            textoNombre.setFillColor(sf::Color::White);
            textoNombre.setPosition(x_text, y_text);
            window.draw(textoNombre);

            sf::Text textoVida("Vida: " + std::to_string(planetas[i].vida), font, 16);
            textoVida.setFillColor(sf::Color::Green);
            textoVida.setPosition(x_text, y_text + 22.f);
            window.draw(textoVida);

            sf::Text textoEterium("Eterium: " + std::to_string(planetas[i].eterium), font, 16);
            textoEterium.setFillColor(sf::Color::Cyan);
            textoEterium.setPosition(x_text, y_text + 42.f);
            window.draw(textoEterium);
        }

        int vidaTotal = 0, eteriumTotal = 0;
        for (const auto& p : planetas) {
            if (p.descubierto) {
                vidaTotal += p.vida;
                eteriumTotal += p.eterium;
            }
        }

        sf::RectangleShape hudBg(sf::Vector2f(280.f, 75.f));
        hudBg.setFillColor(sf::Color(0, 0, 0, 180));
        hudBg.setPosition(10.f, 10.f);
        window.draw(hudBg);

        sf::Text hudVida("Vida total: " + std::to_string(vidaTotal), font, 20);
        hudVida.setFillColor(sf::Color::Green);
        hudVida.setPosition(20.f, 18.f);
        window.draw(hudVida);

        sf::Text hudEterium("Eterium total: " + std::to_string(eteriumTotal), font, 20);
        hudEterium.setFillColor(sf::Color::Cyan);
        hudEterium.setPosition(20.f, 45.f);
        window.draw(hudEterium);

        if (mostrarMenu) {
            window.draw(menuOpciones);
            for (auto& txt : opciones) window.draw(txt);
        }

        window.display();
    }

    return 0;
}
 */



 
#include "Interfaz.hpp"
#include "CSVReader.hpp"
#include "Universe.hpp"
#include <iostream>

int main() {
    Universe universe;
    CSVReader reader;
    if (!reader.loadUniverseFromCSV("data/Universe.csv", universe)) {
        std::cerr << "Error cargando universo.\n";
        return -1;
    }

    if (universe.getSystemCount() == 0) {
        std::cerr << "No hay sistemas cargados.\n";
        return -1;
    }

    PlanetSystem* firstSystem = &universe.getSystem(0);

    Interfaz interfaz;
    interfaz.setSystem(firstSystem);
    interfaz.run();

    return 0;
}
