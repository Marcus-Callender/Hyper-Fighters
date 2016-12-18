#include "ExtraFighterData.h"


C_LanceCharge::C_LanceCharge()
{
	m_charged = 0;
}

void C_LanceCharge::charge()
{
	m_charged = 2;
}

void C_LanceCharge::uncharge()
{
	m_charged--;

	if (m_charged < 0)
		m_charged = 0;
}

bool C_LanceCharge::getCharged()
{
	if (m_charged > 0)
		return true;

	return false;
}

std::string C_LanceCharge::getChargeString()
{
	if (m_charged > 0)
	{
		return " (charged " + std::to_string(m_charged) + ")";
	}
	else
	{
		return " (uncharged)";
	}
}

C_RushHeatLevel::C_RushHeatLevel()
{
	m_heatLevel = 0;
	m_maxHeat = 5;
}

void C_RushHeatLevel::win()
{
	m_heatLevel++;

	if (m_heatLevel > m_maxHeat)
		m_heatLevel = m_maxHeat;
}

void C_RushHeatLevel::lose()
{
	m_heatLevel = 0;
}

float C_RushHeatLevel::focusMultiplyer()
{
	return 1.0f + (m_heatFocusGain * m_heatLevel);
}

int C_RushHeatLevel::getHeatLevel()
{
	return m_heatLevel;
}

std::string C_RushHeatLevel::getHeatString()
{
	return " (heat: " + std::to_string(m_heatLevel) + ")";
}

C_DSPD_017_Overload::C_DSPD_017_Overload()
{
	m_overloaded = false;
	m_heatCost = 20;
	m_overloadedDamage = 0.80f;
}

void C_DSPD_017_Overload::Overload()
{
	m_overloaded = true;
}

void C_DSPD_017_Overload::VentHeat()
{
	m_overloaded = false;
}

bool C_DSPD_017_Overload::Sustain(int & heat)
{
	if (m_overloaded)
	{
		heat -= m_heatCost;

		if (heat <= 0)
		{
			heat = 0;
			return false;
		}
	}

	return true;
}

bool C_DSPD_017_Overload::GetOverloaded()
{
	return m_overloaded;
}

float C_DSPD_017_Overload::GetDamageMultiplier()
{
	if (m_overloaded)
		return m_overloadedDamage;

	return 1.0f;
}

bool C_DSPD_017_Overload::CanUseHyper(int focus)
{
	if (focus >= m_heatCost)
		return true;

	return false;
}


