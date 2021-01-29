#pragma once

#include <stb_image.h>
#include <cstdint>
#include <string_view>

class Texture {
public:
	Texture() = default;
	void Load(std::string_view Path);
	void Bind();
	uint32_t id{};
	int width{};
	int height{};
	int channels;
private:
	void Create(unsigned char* data);
};