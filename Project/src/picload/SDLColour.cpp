/**	@file	SDLColour.cpp
 *	@brief	色構造体
 */
#include "picload/SDLColour.hpp"

namespace dlav {
	void optimize(SFAlphaColour& prm) noexcept {
		for (unsigned int idx = 0U; idx < SFAlphaColour::COUNT; ++idx) {
			if (prm.p[idx] > 1.0f) {
				prm.p[idx] = 1.0f;
			}
			else if (prm.p[idx] < 0.0f) {
				prm.p[idx] = 0.0f;
			}
		}
	}

	void optimize(SFColour& prm) noexcept {
		for (unsigned int idx = 0U; idx < SFColour::COUNT; ++idx) {
			if (prm.p[idx] > 1.0f) {
				prm.p[idx] = 1.0f;
			}
			else if (prm.p[idx] < 0.0f) {
				prm.p[idx] = 0.0f;
			}
		}
	}
}