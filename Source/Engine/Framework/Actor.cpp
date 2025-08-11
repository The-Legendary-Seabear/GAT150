#include "Actor.h"
#include"../Renderer/Renderer.h"
#include "components/RendererComponent.h"

namespace viper {

void viper::Actor::Update(float dt) {
	if (destroyed) return;

	if (lifespan != 0) {
		lifespan -= dt;
		destroyed = lifespan <= 0;
	}

	for (auto& component : m_components) {
		if (component->active) component->Update(dt);
	}

	transform.position += velocity * dt;
	velocity *= (1.0f / (1.0f + damping * dt));
}

void viper::Actor::Draw(Renderer& renderer) {
	if (destroyed) return;

	for (auto& component : m_components) {
		if (component->active) { 
			auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent) {
				rendererComponent->Draw(renderer);
			}
			rendererComponent->Draw(renderer);
		}
	}

	//renderer.DrawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	
}

float Actor::GetRadius() {
	return 50.0f; //(m_texture) ? (m_texture->GetSize().Length() * 0.5f) * transform.scale * 0.9f : 0;
}

void Actor::AddComponent(std::unique_ptr<Component> component) {
	component->owner = this;
	m_components.push_back(std::move(component));
}

}
