#include "Chase.h"

#include <iostream>

void dae::Chase::Initialize(AIComponent* ai)
{
    m_AI = ai;
}

void dae::Chase::OnEnter()
{
    std::cout << "Chase\n";
}

dae::State* dae::Chase::Update()
{
    return nullptr;
}

void dae::Chase::OnExit()
{
}
