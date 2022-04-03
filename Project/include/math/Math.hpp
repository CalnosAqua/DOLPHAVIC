/**	@file	avmath.hpp
 *	@brief	数学関数群
 */
#pragma once
#include <initializer_list>

namespace dlav {
	//!	@brief	円周率
	template <typename T>
	static T constexpr PI = static_cast<T>(3.141592653589793238462643383279L);

	//!	@brief	ネイピア数
	template <typename T>
	static T constexpr NAPIER = static_cast<T>(2.718281828459045235360287471352L);

	/**	@brief	比較関数
	 *	@param[in] lhs 左辺の値
	 *	@param[in] rhs 右辺の値
	 *	@retval +1 左辺の値の方が大きい
	 *	@retval  0 等しい
	 *	@retval -1 左辺の値の方が小さい
	 */
	template <typename T>
	int const compare(T const& lhs, T const& rhs) noexcept;

	/**	@brief	総和関数
	 *	@param[in] args 対象データ
	 *	@return 総和結果
	 */
	template <typename T>
	T const sum(std::initializer_list<T> const& args) noexcept;

	/**	@brief	総和関数
	 *	@param[in] args 対象データの先頭ポインタ
	 *	@param[in] size 対象データの個数
	 *	@return 総和結果
	 */
	template <typename T>
	T const sum(T const* const args, size_t const& size) noexcept;

	/**	@brief	平方根関数
	 *	@param[in] arg 対象データ
	 *	@return 平方根結果
	 */
	template <typename T>
	T const sqrt(T const& arg) noexcept;

	/**	@brief	剰余関数
	 *	@param[in] lhs 左辺の値
	 *	@param[in] rhs 右辺の値
	 *	@return 剰余
	 */
	template <typename T>
	T const mod(T const& lhs, T const& rhs) noexcept;

	/**	@brief	商関数
	 *	@param[in] lhs 左辺の値
	 *	@param[in] rhs 右辺の値
	 *	@return 商
	 */
	template <typename T>
	T const quot(T const& lhs, T const& rhs) noexcept;

	/* 実装 */

	template <typename T>
	inline T const sum(std::initializer_list<T> const& args) noexcept {
		return sum(args.begin(), args.size());
	}
}