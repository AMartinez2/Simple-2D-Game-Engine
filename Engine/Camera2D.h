#pragma once

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

namespace Engine {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int _screenWidth, int _screenHeight);
		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
		void update();

		//Setters
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true;}
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true;}

		//Getters
		glm::vec2 getPosition() { return _position;  }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
	};
}
