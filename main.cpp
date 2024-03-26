#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Network.hpp>

#include <PointToSphere.h>
#include <widget.h>

#include <thread>
#include <vector>
#include <string>

PointToSphere pts1;
std::vector<Point3D> points1 = {
    // {-58.02, -18.38, -79.35},
    // {-21.61, -97.22, -9.07},
    // {-78.05, -58.80, -21.21},
    // {-22.25, -6.45, -97.28},
    // {-19.63, 10.21, 97.52},
    // {-16.45, -21.45, 96.28},
    // {-5.87, 2.43, 99.80},
    // {39.03, -31.56, -86.49},
    // {62.52, -14.53, -76.68},
    // {-29.53, 26.55, -91.78}
    {100, 0, 0},             //1
    {0, 100, 0},             //1
    // {0, 0, 100},             //2
    // {-100, 0, 0},            //1
    // {0, -100, 0},            //1
    // {0, 0, -100},            //3
};

float angle1 = 0;
float angle2 = 0;

void display(ImVec2 size)
{
    ImGui::Begin("Example1");
    ImGui::Button("Button1");
    ImGui::VisualizationOfPoints("Example1", pts1, {200, 200}, {0,0,0, 1}, {0.5, 0.5, 0.5, 1}, {1,1,1,1}, false, angle1, angle2);
    ImGui::SliderFloat("Angle1", &angle1, -180, 180);
    ImGui::SliderFloat("Angle2", &angle2, -180, 180);
    ImGui::End();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Arduino UDP");
    window.setFramerateLimit(60);

    pts1.loadFromList(points1);

    if(ImGui::SFML::Init(window))
    {
        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(window, event);
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            ImGui::SFML::Update(window, deltaClock.restart());

            display({(float)window.getSize().x, (float)window.getSize().y});
            

            window.clear();
            ImGui::SFML::Render(window);
            window.display();
        }
        ImGui::SFML::Shutdown();
    }
    return 0;
}
