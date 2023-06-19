// Example from github https://github.com/xianhuey/word-RPG/tree/main/lilGame by xianhuey
// This is part of a game and is not a complete program (no main) but implements the S pattern without using the word

#include "StateMachine.h"
#include <iostream>
StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
	delete(m_currentState);
	m_currentState = nullptr;

	ClearStateList();
}

void StateMachine::ClearStateList()
{
	m_stateMap.clear();
}

IState* StateMachine::GetCurrentState()
{
	return m_currentState;
}

StateMachine* StateMachine::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new StateMachine();
	}
	return s_Instance;
}

void StateMachine::DestroyInstance()
{
	if (s_Instance == nullptr)
	{
		return;
	}
	delete(s_Instance);
	s_Instance = nullptr;
}

bool StateMachine::AddState(StateType type, IState* state)
{
	auto iter = m_stateMap.find(type);

	if (iter != m_stateMap.end())
	{
		std::cout << "StateMachine::AddState failed !!!!!?" << std::endl;
		return false;
	}

	m_stateMap.insert(std::make_pair(type, state));
	return true;
}

bool StateMachine::Transit(StateType stateType)
{
	if (m_currentState != nullptr
		&& stateType == m_currentState->GetStateType()) return;

	auto iter = m_stateMap.find(stateType);
	if (iter == m_stateMap.end())
	{
		std::cout << "Transit failed !!!!!???" << std::endl;
		return false;
	}

	if (m_currentState != nullptr) m_currentState->OnExit();

	m_currentState = iter->second;
	m_currentState->OnEnter();
	return true;
}

void StateMachine::Tick()
{
	m_currentState->Tick();
}

StateMachine* StateMachine::s_Instance = nullptr;