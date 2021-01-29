#pragma once
#include <cstdint>
#include <glm\ext\vector_float3.hpp>
#include <glm\ext\matrix_float4x4.hpp>
#include <string_view>

struct ViewportSize {
public:
	ViewportSize() = default;
	ViewportSize(float width, float height) {
		this->width = width;
		this->height = height;
	}
	float width{};
	float height{};
};

struct CameraSpec {
public:
	CameraSpec() = default;
	CameraSpec(ViewportSize size, float FOV, float Near = 0.1f, float Far = 1000.0f) {
		this->viewport = size;
		this->fov = FOV;
		this->Near = Near;
		this->Far = Far;
	}
	ViewportSize viewport{};
	float fov{};
	float Near = 0.1f;
	float Far = 1000.0f;
};

class Camera {
public:
	Camera() = default;
	Camera(CameraSpec& spec);

	void ChangeViewport(uint32_t width,uint32_t height);
	void Update();
	const auto& getView() const { return this->m_View; }
	auto& getView() { return this->m_View; }
	const auto& getProjection() const { return this->m_Projection; }
	auto& getProjection() { return this->m_Projection; }

	void SetPosition(glm::vec3& position) { this->m_Position = position; }
	void SetRotation(glm::vec3& rotation) { this->m_Rotation = rotation; }
	const glm::vec3& getPosition() const { return this->m_Position; }
	glm::vec3& getPosition()  { return this->m_Position; }
	const glm::vec3& getRotation() const { return this->m_Rotation; }
	glm::vec3& getRotation() { return this->m_Rotation; }

	void Move(glm::vec3& dir);
	void Rotate(glm::vec3& rot);

	void Upload(uint32_t programID, std::string_view uProjection = "u_Projection", std::string_view uView = "u_View");
private:
	glm::vec3 m_VectorUP{};
	glm::vec3 m_VectorForward{};
	glm::vec3 m_Position{};
	glm::vec3 m_Rotation{};

	glm::mat4 m_Projection{};
	glm::mat4 m_View{};

	CameraSpec m_CameraSpec{};
};