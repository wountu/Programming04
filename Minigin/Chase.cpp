#include "Chase.h"

#include <iostream>

void dae::Chase::Initialize(AIComponent* ai)
{
    m_AI = ai;
}

void dae::Chase::OnEnter()
{
}

dae::State* dae::Chase::Update()
{
    return nullptr;
}

void dae::Chase::OnExit()
{
}
