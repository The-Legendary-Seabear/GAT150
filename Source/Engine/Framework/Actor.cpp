#include "Actor.h"
#include"../Renderer/Renderer.h"
#include "components/RendererComponent.h"

namespace viper {

void viper::Actor::Update(float dt) {
	if (destroyed) return;

	if (lifespan > 0) {
		lifespan -= dt;
		if (lifespan <= 0) {
			destroyed = true;
			return;
		}
	}

	//update all components
	for (auto& component : m_components) {
		if (component->active) component->Update(dt);
	}
}

void viper::Actor::Draw(Renderer& renderer) {
	if (destroyed) return;

	for (auto& component : m_components) {
		if (component->active) { 
			auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent) {
				rendererComponent->Draw(renderer);
			}
			//rendererComponent->Draw(renderer);
		}
	}

	//renderer.DrawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	
}

void Actor::AddComponent(std::unique_ptr<Component> component) {
	component->owner = this;
	m_components.push_back(std::move(component));
}

}
