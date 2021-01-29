#include <iostream>
#include <SFML/Window.hpp>
#include <glcore/glcore.h>
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include <glm\ext\matrix_transform.hpp>
#include "ChunkController.h"
#include "Texture.h"
#include "Util.h"
#include <filesystem>
#include "World.h"

using namespace glcore;

int dirX = 0, dirZ = 0, dirY = 0;
Camera camera = Camera(CameraSpec({ 1280,720 },45,0.1f,1000.0f));
bool firstMouse = true;
glm::vec2 lastMousePos{1280.0f/2.0f,720.0f/2.0f};
float yaw = 90.0f;
float pitch = 0;
bool mouseClicked = false;
Timestep dt;

static void error_callback(int error, const char* description)
{
	fprintf(stderr,"ERROR: %c",description);
}

Texture texture;
glcore::shader_program shaders;
World world;
glm::mat4 u_Model = glm::translate(glm::mat4(1.0f), { 0,0,0 })
					* glm::scale(glm::mat4(1.0f), { 1,1,1 });
void OnRender(Timestep& dt) {
	Renderer::ClearScreen({ 0.258f, 0.807f, 0.960f });

	camera.Update();

	texture.Bind();
	shaders.bind();
	shaders.upload_uniformMat4("u_Projection", glm::value_ptr(camera.getProjection()));
	shaders.upload_uniformMat4("u_View", glm::value_ptr(camera.getView()));
	shaders.upload_uniformMat4("u_Model", glm::value_ptr(u_Model));
	shaders.upload_uniform3f("u_Light_Pos", camera.getPosition().x, 25, camera.getPosition().z);
	shaders.upload_uniform3f("u_Camera_Pos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

	Renderer::Render(world.getChunkController());
}
void OnMouseMove(Timestep& dt, uint32_t x, uint32_t y, sf::Event event) {
	if (firstMouse) {
		lastMousePos = { (float)x / 2.0f,(float)y / 2.0f };
		firstMouse = false;
	}
	float xoffset = (float)x - lastMousePos.x;
	float yoffset = (float)y - lastMousePos.y;
	lastMousePos = { x,y };

	float cameraSpeed = 0.1;
	if (mouseClicked) {
		yaw += (float)xoffset * (float)cameraSpeed * (float)dt.toMillis();
		pitch += (float)yoffset * (float)cameraSpeed * (float)dt.toMillis();
		camera.SetRotation(glm::vec3{ pitch,yaw,0 });
	}
	if (pitch > 89) {
		pitch = 89;
	}
	else if (pitch < -89) {
		pitch = -89;
	}
}
void OnKeyboard(unsigned char key, uint32_t x, uint32_t y, sf::Event event) {
	switch (event.key.code) {
	case sf::Keyboard::W: // W
		dirX += 1;
		break;
	case sf::Keyboard::S: // S
		dirX -= 1;
		break;
	case sf::Keyboard::A: // A
		dirZ -= 1;
		break;
	case sf::Keyboard::D: //D
		dirZ += 1;
		break;
	case sf::Keyboard::F:
		mouseClicked = !mouseClicked;
		break;
	case sf::Keyboard::Space:
		dirY += 1;
		break;
	case sf::Keyboard::LShift:
		dirY -= 1;
		break;
	}
	camera.Move(glm::vec3{ dirX, dirY,dirZ });
	dirX = 0;
	dirZ = 0;
	dirY = 0;
}
void OnWindowResize(uint32_t width, uint32_t height, sf::Event event) {
	camera.ChangeViewport(width, height);
	glViewport(0, 0, width, height);
}
int main() {

	Window window("BlockCraft", { 1280,800 }, { 1280,800 });
	window.OnRender(OnRender);
	window.OnMouseMove(OnMouseMove);
	window.OnKeyboard(OnKeyboard);
	window.OnWindowResize(OnWindowResize);

	Renderer::Init(nullptr);

	bool TerminateWindow = 0;

	shaders = glcore::shader_program("Basic", {
		{ glcore::shader_type::vertex, "assets/shaders/basic_vert.glsl" },
		{ glcore::shader_type::fragment, "assets/shaders/basic_frag.glsl" }
		});

	texture.Load("assets/textures/texture_atlas.png");

	camera.SetPosition(glm::vec3{ -6,22,0 });
	camera.SetRotation(glm::vec3{ pitch,yaw,0 });


	WorldInfo info;
	info.Name = "Test";	
	info.WorldPath = "assets/";
	info.Seed = 12345;
	info.Size = 8;
	info.Type = WorldType::Normal;
	//world.Create(info);
	//world.Save();
	world.Load("assets/Test.wrld");

	Timestep current = 0;
	Timestep last = current;

	while (true) {
		window.Loop();

		current = 0;
		dt = current - last;
		last = current;
	}
	
	return 0;
}