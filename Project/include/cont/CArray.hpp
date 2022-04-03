/**	@file	CArray.hpp
 *	@brief	静的配列
 */
#pragma once
#include <memory>

namespace dlav {
	/**	@file	CArray
	 *	@brief	静的配列
	 */
	template <typename T, size_t L>
	class CArray final {
	public	:
		//!	@brief	ムーブコンストラクタ
		CArray(CArray<T, L>&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CArray(CArray<T, L> const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CArray<T, L>& operator=(CArray<T, L>&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CArray<T, L>& operator=(CArray<T, L> const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CArray() noexcept;
		//!	@brief	コンストラクタ
		CArray(std::initializer_list<T> const&) noexcept;
		//!	@brief	デストラクタ
		~CArray() noexcept = default;

		//!	@brief	配列の先頭へのポインタ取得関数
		T* const begin() const noexcept;
		//!	@brief	配列の末端へのポインタ取得関数
		T* const end() const noexcept;

		//!	@brief	配列長取得関数
		size_t const size() const noexcept;

		//!	@brief	添え字演算子
		T const& operator[](size_t const&) const& noexcept;
		//!	@brief	添え字演算子
		T& operator[](size_t const&)& noexcept;
		//!	@brief	添え字演算子
		T operator[](size_t const&) const&& noexcept;

	private	:
		//!	@brief	配列
		T m_elems[L];
	};

	template<typename T, size_t L>
	inline CArray<T, L>::CArray() noexcept :
		m_elems{}
	{}
	
	template<typename T, size_t L>
	inline CArray<T, L>::CArray(std::initializer_list<T> const& args) noexcept :
		m_elems{}
	{
		size_t idx = 0;
		for (T const& arg : args) {
			if (idx >= args.size()) {
				break;
			}
			m_array[idx] = arg;
			++idx;
		}
	}

	template<typename T, size_t L>
	inline T* const CArray<T, L>::begin() const noexcept {
		return &m_elems[0U];
	}

	template<typename T, size_t L>
	inline T* const CArray<T, L>::end() const noexcept {
		return &m_elems[L];
	}
	template<typename T, size_t L>
	inline size_t const CArray<T, L>::size() const noexcept {
		return L;
	}

	template<typename T, size_t L>
	inline T const& CArray<T, L>::operator[](size_t const& idx) const& noexcept {
		return m_elems[idx];
	}

	template<typename T, size_t L>
	inline T& CArray<T, L>::operator[](size_t const& idx) & noexcept {
		return m_elems[idx];
	}

	template<typename T, size_t L>
	inline T CArray<T, L>::operator[](size_t const& idx) const&& noexcept {
		return move(m_elems[idx]);
	}
}