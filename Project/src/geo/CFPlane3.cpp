/**	@file	CFPlane3.cpp
 *	@brief	三次元平面方程式
 */
#include "geo/CFPlane3.hpp"
#include <memory>

namespace dlav {
    CFPlane3::CFPlane3() noexcept :
		m_mtx(),
		m_value()
	{}

	CFPlane3& CFPlane3::init(CFVector3 const& pt1, CFVector3 const& pt2, CFVector3 const& pt3) noexcept {
		CFVector3 vt21, vt23, n, t, b;

		vt21 = pt1 - pt2;
		vt23 = pt3 - pt2;

		n = cross(vt21, vt23);
		t = (vt21 + vt23);
		b = cross(n, t);

		m_value = -n.norm();

		m_mtx.row(0U, t);
		m_mtx.row(1U, b);
		m_mtx.row(2U, n);

		return *this;
	}

    CFVector3 const CFPlane3::normal() const noexcept {
		return m_mtx.row(2U);
	}

    CFVector3 const CFPlane3::binormal() const noexcept {
		return m_mtx.row(1U);
	}

    CFVector3 const CFPlane3::tangent() const noexcept {
		return m_mtx.row(0U);
	}

    CFMatrix3x3 const CFPlane3::getMatrix(EHandSide const& hs) const noexcept {
		switch (hs) {
		case EHandSide::RHS:
			return m_mtx.transpose();
		case EHandSide::LHS:
			return m_mtx;
		default:
			return ZERO_FMTX3x3;
		}
	}

    float const CFPlane3::getDValue() const noexcept {
		return m_value;
	}
}