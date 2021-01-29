#include "Window.h"
#include <SFML/OpenGL.hpp>
#include <iostream>

Window::Window(std::string_view Title, Size2i windowSize, Size2i resolution, int argc, char** argv)
{
	sf::ContextSettings settings;
	settings.depthBits = 0;
	settings.stencilBits = 0;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	sf::Uint32 style = sf::Style::Default;
	
	mWindow.create(sf::VideoMode(windowSize.width, windowSize.height),Title.data(),style,settings);

	mWindow.setFramerateLimit(60);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.setActive();

	this->resolution = resolution;

	glViewport(0, 0, windowSize.width, windowSize.height);

}

void Window::Loop()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::EventType::MouseMoved:
			(*this->onMouseMove)(mDT, event.mouseMove.x, event.mouseMove.y,event);
			break;
		case sf::Event::EventType::KeyPressed:
			(*this->onKeyboard)(event.key.code , event.mouseMove.x,event.mouseMove.y,event);
			break;
		case sf::Event::EventType::Resized:
			(*this->onWindowResize)(event.size.width, event.size.height,event);
		case sf::Event::EventType::Closed:
			this->mWindow.close();
		}
	}

	(*this->onRender)(mDT);

	mWindow.display();
}

void Window::OnInit(void(*function)())
{
	this->onInit = function;
}

void Window::OnRender(void(*function)(Timestep& dt))
{
	this->onRender = function;
}

void Window::OnMouseMove(void(*function)(Timestep& dt, uint32_t x, uint32_t y,sf::Event event))
{
	this->onMouseMove = function;
}

void Window::OnKeyboard(void(*function)(unsigned char key, uint32_t x, uint32_t y,sf::Event event))
{
	this->onKeyboard = function;
}

void Window::OnWindowResize(void(*function)(uint32_t width, uint32_t height,sf::Event event))
{
	this->onWindowResize = function;
}

