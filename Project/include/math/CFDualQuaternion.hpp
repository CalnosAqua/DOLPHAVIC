/**	@file	CFDualQuaternion.hpp
 *	@brief	双対四元数
 */
#pragma once
#include "CFQuaternion.hpp"

namespace dlav {
	/**	@file	CFDualQuaternion
	 *	@brief	双対四元数
	 */
	class CFDualQuaternion final {
	public:
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 2U;
		union {
			//!	@brief	全成分
			CFQuaternion p[COUNT];
			struct {
				//!	@brief	実数成分
				CFQuaternion re;
				//!	@brief	虚数成分
				CFQuaternion im;
			};
		};
		//!	@brief	ムーブコンストラクタ
		CFDualQuaternion(CFDualQuaternion&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFDualQuaternion(CFDualQuaternion const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFDualQuaternion& operator=(CFDualQuaternion&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFDualQuaternion& operator=(CFDualQuaternion const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFDualQuaternion() noexcept;
		//!	@brief	デストラクタ
		~CFDualQuaternion() noexcept = default;

		//!	@brief	コンストラクタ
		constexpr CFDualQuaternion(CFQuaternion const& x, CFQuaternion const& y) noexcept :
			p{ x, y }
		{}
		//!	@brief	コンストラクタ
		explicit CFDualQuaternion(std::initializer_list<CFQuaternion> const&) noexcept;

		//!	@brief	複合加算演算子
		CFDualQuaternion& operator+=(CFDualQuaternion const&) noexcept;
		//!	@brief	複合減算演算子
		CFDualQuaternion& operator-=(CFDualQuaternion const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFDualQuaternion& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFDualQuaternion& operator/=(float const&) noexcept;

		//!	@brief	正規化関数
		CFDualQuaternion const normalize() const noexcept;
		//!	@brief	共役生成関数
		CFDualQuaternion const conj() const noexcept;
		//!	@brief	逆元生成関数
		CFDualQuaternion const inv() const noexcept;
		//!	@brief	ノルム二乗関数
		float const sqnorm() const noexcept;
		//!	@brief	ノルム関数
		float const norm() const noexcept;

		//!	@brief	単項加算演算子
		CFDualQuaternion const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFDualQuaternion const operator-() const noexcept;
	};
	//!	@brief	加算演算子
	CFDualQuaternion const operator+(CFDualQuaternion const&, CFDualQuaternion const&) noexcept;
	//!	@brief	減算演算子
	CFDualQuaternion const operator-(CFDualQuaternion const&, CFDualQuaternion const&) noexcept;
	//!	@brief	乗算演算子
	CFDualQuaternion const operator*(CFDualQuaternion const&, CFDualQuaternion const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFDualQuaternion const operator*(CFDualQuaternion const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFDualQuaternion const operator*(float const&, CFDualQuaternion const&) noexcept;
	//!	@brief	除算演算子
	CFDualQuaternion const operator/(CFDualQuaternion const&, CFDualQuaternion const&) noexcept;
	//!	@brief	スカラ割演算子
	CFDualQuaternion const operator/(CFDualQuaternion const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	CFDualQuaternion const operator/(float const&, CFDualQuaternion const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFDualQuaternion const&, CFDualQuaternion const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFDualQuaternion const&, CFDualQuaternion const&) noexcept;

	//!	@brief	単精度浮動小数点数型の零双対四元数
	static CFDualQuaternion constexpr ZERO_FDQT = CFDualQuaternion(ZERO_FQT, ZERO_FQT);
	//!	@brief	単精度浮動小数点数型の単位双対四元数
	static CFDualQuaternion constexpr UNIT_FDQT = CFDualQuaternion(UNIT_FQT, ZERO_FQT);
}