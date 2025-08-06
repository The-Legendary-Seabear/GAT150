#pragma once
#include "Core/StringHelper.h"
#include "Resource.h"

#include <string>
#include <map>
#include <memory>
#include <iostream>

namespace viper {
	class ResourceManager {
	public:
		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& name, TArgs&& ... args);

		static inline ResourceManager& Instance() {
			static ResourceManager instance;
			return instance;
		}


	private:

		ResourceManager() = default;

		std::map<std::string, res_t<Resource>> m_resources;


	};

		
	
	template<typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& name, TArgs&& ... args) {
		std::string key = toLower(name);

		auto iter = m_resources.find(key);
		//check if exists
		if (iter != m_resources.end()) {
			//get value in iterator
			auto base = iter->second;
			//cast to data type T
			auto derived = std::dynamic_pointer_cast<T>(base);
			//check if cas was successful
			if (derived == nullptr) {
				std::cerr << "Resource type mismatch: " << key << std::endl;
				return res_t<T>();
			}
			//return resource
			return derived;

		}

		//load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(key, std::forward<TArgs>(args) ...) == false) {
			std::cerr << "Could not load resource: " << key << std::endl;
			return res_t<T>();
		}
		//add resource to resource manager
		m_resources[key] = resource;

		return resource;
	}

		
	
}