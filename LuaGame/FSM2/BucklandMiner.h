#pragma once

#include "BucklandStateMachine.h"
#include "BucklandEntity.h"

namespace Buckland
{
	class Miner : public Entity
	{
	private:
		StateMachine<Miner>* m_stateMachine;
		int m_gold;
		int m_fatigue;
	public:

		Miner(std::string name) : Entity(name), m_gold(0), m_fatigue(0)
		{
			m_stateMachine = new StateMachine<Miner>(this);
		}

		~Miner() { delete m_stateMachine; }

		void Update()
		{
			m_stateMachine->Update();
		}

		int GetGold()const { return m_gold; }
		void SetGold(int val) { m_gold = val; }
		void AddGold(int val) { m_gold += val; }

		bool Fatigued()const { return m_fatigue > 4; }
		void DecreaseFatigue() { m_fatigue -= 1; }
		void IncreaseFatigue() { m_fatigue += 1; }

		StateMachine<Miner>* GetFSM()const { return m_stateMachine; }
	};
}