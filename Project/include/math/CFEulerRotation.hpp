/**	@file	CFEulerRotation.hpp
 *	@brief	単精度浮動小数点数型オイラー回転量
 */
#pragma once
#pragma warning(disable : 4201)
#include "CFRotation.hpp"
#include <initializer_list>

namespace dlav {
	/**	@class	CFEulerRotation
	 *	@brief	単精度浮動小数点数型三次元ベクトル
	 */
	class alignas(16) CFEulerRotation final{
	public:
		//!	@brief	成分数
		static unsigned int constexpr COUNT = 3U;
		union {
			//!	@brief	全成分
			CFRotation alignas(16) p[COUNT];
			struct {
				//!	@brief	ピッチ角
				CFRotation pitch;
				//!	@brief	ヨー角
				CFRotation yaw;
				//!	@brief	ロール角
				CFRotation roll;
			};
		};

		//!	@brief	ムーブコンストラクタ
		CFEulerRotation(CFEulerRotation&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CFEulerRotation(CFEulerRotation const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CFEulerRotation& operator=(CFEulerRotation&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CFEulerRotation& operator=(CFEulerRotation const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CFEulerRotation() noexcept;
		//!	@brief	デストラクタ
		~CFEulerRotation() noexcept = default;

		//!	@brief	複合加算演算子
		CFEulerRotation& operator+=(CFEulerRotation const&) noexcept;
		//!	@brief	複合減算演算子
		CFEulerRotation& operator-=(CFEulerRotation const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		CFEulerRotation& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		CFEulerRotation& operator/=(float const&) noexcept;

		//!	@brief	単項加算演算子
		CFEulerRotation const operator+() const noexcept;
		//!	@brief	単項減算演算子
		CFEulerRotation const operator-() const noexcept;
	};
	//!	@brief	加算演算子
	CFEulerRotation const operator+(CFEulerRotation const&, CFEulerRotation const&) noexcept;
	//!	@brief	減算演算子
	CFEulerRotation const operator-(CFEulerRotation const&, CFEulerRotation const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFEulerRotation const operator*(CFEulerRotation const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	CFEulerRotation const operator*(float const&, CFEulerRotation const&) noexcept;
	//!	@brief	スカラ割演算子
	CFEulerRotation const operator/(CFEulerRotation const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(CFEulerRotation const&, CFEulerRotation const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(CFEulerRotation const&, CFEulerRotation const&) noexcept;
}