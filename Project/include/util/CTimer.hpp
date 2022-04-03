/**	@file avtimer.hpp
 *	@brief タイマー
 */
#pragma once
#include <chrono>

using namespace std::chrono;
namespace dlav {
	/**	@class CTimer
	 *	@brief タイマー
	 */
	class CTimer {
	private:
		//! @brief 初期化時の時間
		time_t m_Start;
		//! @brief 更新前の時間
		time_t m_Before;
		//! @brief 更新後の時間
		time_t m_Latest;

	public:
		//! @brief デストラクタ
		~CTimer() noexcept = default;
		//! @brief ムーブコンストラクタ
		CTimer(CTimer&&) noexcept = default;
		//! @brief コピーコンストラクタ
		CTimer(const CTimer&) noexcept = default;
		//! @brief ムーブ代入演算子
		CTimer& operator=(CTimer&&) noexcept = default;
		//! @brief コピー代入演算子
		CTimer& operator=(const CTimer&) noexcept = default;

		//! @brief デフォルトコンストラクタ
		CTimer() noexcept;
		//! @brief 初期化関数
		CTimer& init() noexcept;
		//! @brief 更新関数
		CTimer& update() noexcept;
		//! @brief 終了関数
		CTimer& uninit() noexcept;

		//! @brief 単精度浮動小数点数型のデルタ時間取得関数
		float const FDeltaTime() const noexcept;
		//! @brief 単精度浮動小数点数型の経過時間取得関数
		float const FDifferenceTime() const noexcept;

		//! @brief 倍精度浮動小数点数型のデルタ時間取得関数
		double const DDeltaTime() const noexcept;
		//! @brief 倍精度浮動小数点数型の経過時間取得関数
		double const DDifferenceTime() const noexcept;
	};
}