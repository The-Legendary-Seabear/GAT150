#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include "SDL3_image/SDL_image.h"
#include <iostream>

namespace viper {
	class Renderer {
	public:
		friend class Texture;
		Renderer() = default;

		bool Initialize();
		bool CreateWindow(const std::string& name, int width, int height);

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void SetColor(float r, float g, float b, float a = 255);
		void Clear();
		void Present();
		void Shutdown();
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x, float y);
		void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);
		
		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

	private:

		int m_width{ 0 };
		int m_height{ 0 };

		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		friend class Text;
	};

}
