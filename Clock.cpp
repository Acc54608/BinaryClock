// Binary Clock "Widget" w/ Various Colors and support for picture background
// Uses SFML library for building the GUI - https://www.sfml-dev.org/
// Built by Alex Casper

#include <cstdio>
#include <bitset>
#include <ctime>
#include <cmath>
#include <String>
#include <SFML/Graphics.hpp>

int main() {
    // Initialize Window, Timer to update things, and get font
    sf::RenderWindow window(sf::VideoMode(400, 100), "BinaryClock", sf::Style::Close);
    sf::Clock timer;
    sf::Font font;
    if (!font.loadFromFile("DS-DIGIB.ttf")) {
        puts("DS-DIGITAL font not found!");
        return 1;
    }

    // Initialize text to display the time and set some properties
    sf::Text time;
    time.setFont(font);
    time.setCharacterSize(44);
    //time.setStyle(sf::Text::Bold);
    time.setPosition(20.f, 20.f);

    // Create std strings for each part of the time
    std::string hour;
    std::string min;
    std::string sec;

    sf::Time timeC = sf::milliseconds(100);
    int colorVal = 0;
    bool picture = false;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
            // If key C is pressed and window has focus, increment colorVal to change colors
            /* Also check to see if it has been more than 300 miliseconds from the
            last time C has been pressed to prevent it from changing too fast */
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && window.hasFocus()) {
                if (timer.getElapsedTime().asMilliseconds() >= timeC.asMilliseconds() + 300) {
                    if (colorVal < 3)
                        colorVal++;
                    else
                        // Set colorVal to 0 if it is at 3 so it can reset back to base colors
                        colorVal = 0;
                    timeC = timer.getElapsedTime();
                }
            }

            // Switch statement that changes the window and text color based on int colorVal
            switch (colorVal) {
            case 0:
                time.setFillColor(sf::Color(220, 20, 60, 255));
                window.clear(sf::Color::Black);
                break;
            case 1:
                time.setFillColor(sf::Color(255, 153, 18, 255));
                window.clear(sf::Color(40, 0, 255, 255));
                break;
            case 2:
                time.setFillColor(sf::Color(67, 251, 4, 255));
                window.clear(sf::Color(188, 4, 251, 255));
                break;
            case 3:
                time.setFillColor(sf::Color(200, 0, 265, 255));
                window.clear(sf::Color(0, 255, 90, 255));
                break;
            }
            // Get system time to have time for clock
            std::time_t t = std::time(0);
            std::tm* now = std::localtime(&t);

            // Get time and put it as a string to the text object
            // Bitset will convert time to binary before to string converts to string
            hour = std::bitset<8>(now->tm_hour).to_string();
            // Strip leading zeros off if resulting bits aren't just 0, otherwise just leave the last digit
            if (hour != "00000000")
                hour.erase(0, hour.find_first_not_of('0'));
            else
                hour.erase(0, 7);
            min = std::bitset<8>(now->tm_min).to_string();
            if (min != "00000000")
                min.erase(0, min.find_first_not_of('0'));
            else
                min.erase(0, 7);
            sec = std::bitset<8>(now->tm_sec).to_string();
            if (sec != "00000000")
                sec.erase(0, sec.find_first_not_of('0'));
            else
                sec.erase(0, 7);
            time.setString(hour + " : " + min + " : " + sec);

            window.draw(time);
            window.display();
    }

	return 0;
}