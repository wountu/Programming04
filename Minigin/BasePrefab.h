#pragma once
#include <memory>

#include "GameObject.h"

class BasePrefab
{
public:
	virtual ~BasePrefab() = default;
	virtual std::shared_ptr<dae::GameObject> Create(glm::vec2 pos) = 0;
};

