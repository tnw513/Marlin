#include "TemperatureManager.h"
#include "temperature.h"

TemperatureManager::TemperatureManager()
	: Subject<float>()
	, m_current_temperature(0)
	, m_target_temperature(0)
{
#ifdef FAN_BOX_PIN
	pinMode(FAN_BOX_PIN, OUTPUT);
	digitalWrite(FAN_BOX_PIN, HIGH);
#endif //FAN_BOX_PIN

#ifdef FAN_BLOCK_PIN
	pinMode(FAN_BLOCK_PIN, OUTPUT);
	digitalWrite(FAN_BLOCK_PIN, HIGH);
#endif //FAN_BLOCK_PIN
}

void TemperatureManager::updateCurrentTemperature(float temp)
{
	if (m_current_temperature != temp)
	{
		m_current_temperature = temp;
		notify();
	}
}

void TemperatureManager::setTargetTemperature(uint16_t target)
{
	m_target_temperature = target;
	target_temperature[0] = m_target_temperature;
}

uint16_t TemperatureManager::getTargetTemperature()
{
	return m_target_temperature;
}

void TemperatureManager::notify()
{
	if (this->m_observer != 0)
	{
		this->m_observer->update(m_current_temperature);
	}
}