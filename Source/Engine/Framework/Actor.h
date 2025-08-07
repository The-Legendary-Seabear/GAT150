#pragma once
#include "Math/Transform.h"
#include "Renderer/Model.h"
#include "Scene.h"
#include "Renderer/Texture.h"
#include <memory>
#include <string>

namespace viper {
	class Actor {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.2f };

		bool destroyed{ false };
		float lifespan{ 0 };


		Transform transform;
		Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor( const Transform transform, res_t<Texture> texture) :
			transform{ transform },
			m_texture { texture } {}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

	protected:
		res_t<Texture> m_texture;
		//std::shared_ptr<Model> m_model;
		
	};
}
