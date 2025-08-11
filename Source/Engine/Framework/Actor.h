#pragma once
#include "Framework/Object.h"
#include "Math/Transform.h"
#include "Renderer/Model.h"
#include "Scene.h"
#include "Renderer/Texture.h"
#include "Component.h"

#include <memory>
#include <string>

namespace viper{
	class Component;
	class Actor : public Object {
	public:
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.2f };

		bool destroyed{ false };
		float lifespan{ 0 };


		Transform transform;
		Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor( const Transform transform) :
			transform{ transform }
			 {}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		//components
		void AddComponent(std::unique_ptr<Component> component);

	protected:
		std::vector<std::unique_ptr<Component>> m_components;
		
		
	};
}
