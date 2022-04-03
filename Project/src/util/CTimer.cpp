#include "util/CTimer.hpp"

namespace dlav {
	CTimer::CTimer() noexcept :
		m_Start(0),
		m_Before(0),
		m_Latest(0)
	{}

	CTimer& CTimer::init() noexcept {
		time_t tmp = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
		m_Start = tmp;
		m_Latest = tmp;
		return *this;
	}

	CTimer& CTimer::exit() noexcept {
		m_Start = 0;
		m_Before = 0;
		m_Latest = 0;
		return *this;
	}

	CTimer& CTimer::update() noexcept{
		if(!m_Start) {
			return *this;
		}
		time_t tmp = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
		m_Before = m_Latest;
		m_Latest = tmp;
		return *this;
	}

	float const CTimer::FDeltaTime() const noexcept {
		if(!m_Start) {
			return 0.0f;
		}
		return static_cast<float>(m_Latest - m_Before) / 1.0E+9f;
	}

	float const CTimer::FDifferenceTime() const noexcept {
		if(!m_Start) {
			return 0.0f;
		}
		return static_cast<float>(m_Latest - m_Start) / 1.0E+9f;
	}

	double const CTimer::DDeltaTime() const noexcept {
		if(!m_Start) {
			return 0.0;
		}
		return static_cast<double>(m_Latest - m_Before) / 1.0E+9;
	}

	double const CTimer::DDifferenceTime() const noexcept {
		if(!m_Start) {
			return 0.0;
		}
		return static_cast<double>(m_Latest - m_Start) / 1.0E+9;
	}
}