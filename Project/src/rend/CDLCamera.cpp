/**	@file	CDLCamera.cpp
 *	@brief	Dolphavic Library 用の三次元カメラ
 */
#include "rend/CDLCamera.hpp"
#include "math/FMathUtil.hpp"

namespace dlav {
	CCamera::CCamera() noexcept :
		m_eye(),
		m_lookat(),
		m_posture(UNIT_FQT),
		m_height(),
		m_width(),
		m_near(),
		m_far(),
		m_wndpos(),
		m_pmode(EProjectiveMode::PARSEPECTIVE),
		m_fmode(EFollowMode::FREE)
	{}

	CFMatrix4x4 CCamera::world_mtx(EHandSide const& hs) noexcept {
		switch (hs) {
		case EHandSide::RHS:
			return makeTransit(EHandSide::RHS, m_eye) * makeRotate(EHandSide::RHS, m_posture);
		case EHandSide::LHS:
			return makeRotate(EHandSide::LHS, m_posture) * makeTransit(EHandSide::LHS, m_eye);
		}
	}
}