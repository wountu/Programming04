#pragma once
#include "GameObject.h"

class GameObject;
class Command
{
public:
	explicit Command(GameObject* pObject);
	virtual ~Command() = default;
	virtual void Execute() = 0;
protected:
	GameObject* GetActor() const { return m_pObject; }
private:
	GameObject* m_pObject{ nullptr };
};

class Movement : public Command
{
public:
	void Execute() override{}
};

