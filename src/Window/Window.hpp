#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

namespace co
{
    /**
     * @brief Starts the window.
     *
     * Throws std::runtime_error if ImGui window fails to init.
     *
     * @param width Width of the window
     * @param height Height of the window
     */
    void Run(const int width, const int height, const char* title);

    /**
     * @brief Input handling step of main loop.
     *
     * Called by co::Run().
     *
     * @param window RenderWindow reference of main window
     * @param deltaClock Clock reference of main window
     */
    void Input(sf::RenderWindow& window, sf::Clock& deltaClock);

    /**
     * @brief Update step of main loop. Where the logic should reside.
     *
     * Called by co::Run().
     *
     * @param window RenderWindow reference of main window
     * @param deltaClock Clock reference of main window
     */
    void Update(sf::RenderWindow& window, sf::Clock& deltaClock);

    /**
     * @brief Draw handling step of main loop.
     *
     * Called by co::Run().
     *
     * @param window RenderWindow reference of main window
     * @param deltaClock Clock reference of main window
     */
    void Draw(sf::RenderWindow& window, sf::Clock& deltaClock);

    /**
     * @brief Default table setup meant to be used in co::Update().
     *
     * Called by co::Update().
     *
     * Contains no data.
     */
    void TableDefault();
} // namespace co

#endif // WINDOW_H
