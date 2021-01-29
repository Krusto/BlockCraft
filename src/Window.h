#pragma once
#include <SFML/Window.hpp>
#include <string>
#include <string_view>
#include "Timestep.h"
#include <functional>
struct Size2i {
public:
	uint32_t width;
	uint32_t height;
};

class Window {
public:
	Window() = default;
	Window(std::string_view Title, Size2i windowSize, Size2i resolution, int argc = 0, char** argv = nullptr);
	
	~Window() = default;

	void Loop();

	void OnInit(void (*function)());
	void OnRender(void (*function)(Timestep& dt));
	void OnMouseMove(void (*function)(Timestep& dt,uint32_t x,uint32_t y, sf::Event event));
	void OnKeyboard(void (*function)(unsigned char key, uint32_t x, uint32_t y, sf::Event event));
	void OnWindowResize(void (*function)(uint32_t width, uint32_t height, sf::Event event));
	auto& getDeltaTime() { return this->mDT; }
	const auto& getDeltaTime() const { return this->mDT; }

	void setDeltaTime(double value) {
		mDT.setTime(value);
	}

	auto& getHandle() { return mWindow; }
	const auto& getHandle() const{ return mWindow; }

	Size2i resolution{};
private:
	void(*onInit)() = 0;
	void(*onRender)(Timestep& dt) = 0;
	void(*onMouseMove)(Timestep& dt, uint32_t x, uint32_t y,sf::Event event) = 0;
	void(*onKeyboard)(unsigned char key, uint32_t x, uint32_t y, sf::Event event) = 0;
	void(*onWindowResize)(uint32_t width, uint32_t height, sf::Event event) = 0;

	sf::Window mWindow;
	Timestep mDT;
};