/**	@file	CVector.hpp
 *	@brief	動的配列
 */
#pragma once
#include <memory>

namespace dlav {
	/**	@file	CVector
	 *	@brief	静的配列
	 */
	template <typename T>
	class CVector final {
	public:
		//!	@brief	ムーブコンストラクタ
		CVector(CVector<T>&&) noexcept;
		//!	@brief	コピーコンストラクタ
		CVector(CVector<T> const&) noexcept;
		//!	@brief	ムーブ代入演算子
		CVector<T>& operator=(CVector<T>&&) noexcept;
		//!	@brief	コピー代入演算子
		CVector<T>& operator=(CVector<T> const&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		CVector() noexcept;
		//! @brief	コンストラクタ
		explicit Vector(size_t const&) noexcept;
		//!	@brief	コンストラクタ
		CVector(std::initializer_list<T> const&) noexcept;
		//!	@brief	デストラクタ
		~CVector() noexcept = default;

		//!	@brief	配列の先頭へのポインタ取得関数
		T* const begin() const noexcept;
		//!	@brief	配列の末端へのポインタ取得関数
		T* const end() const noexcept;

		//!	@brief	配列長取得関数
		size_t const size() const noexcept;

		//!	@brief	添え字演算子
		T const& operator[](size_t const&) const& noexcept;
		//!	@brief	添え字演算子
		T& operator[](size_t const&) & noexcept;
		//!	@brief	添え字演算子
		T operator[](size_t const&) const&& noexcept;

		//! @brief 末端に要素を追加する関数
		CVector<T>& push_back(T const&) noexcept;
		//! @brief 先頭に要素を追加する関数
		CVector<T>& push_front(T const&) noexcept;
		//! @brief 任意の場所に要素を追加する関数
		CVector<T>& insert(size_t const&, T const&) noexcept;

		//! @brief 末端から要素を取り出す関数
		CVector<T>& pop_back() noexcept;
		//! @brief 先頭から要素を取り出す関数
		CVector<T>& pop_front() noexcept;
		//! @brief 任意の場所から要素を取り出す関数
		CVector<T>& remove(size_t const&) noexcept;

		//! @brief 要素初期化関数
		CVector<T>& clear() noexcept;
		//! @brief 配列サイズ調節関数
		CVector<T>& reflesh() noexcept;

	private:
		//!	@brief	配列
		T* m_elems;
		//! @brief 配列の成分数
		size_t m_size;
		//! @brief 確保済み配列長
		size_t m_allocSize;
		//! @brief 拡縮基準長
		size_t m_allocRate;

		//! @brief 配列サイズ変更関数
		void scaling(size_t const&) noexcept;
		//! @brief 配列サイズ拡張関数
		void scale_up() noexcept;
		//! @brief 配列サイズ正規化関数
		void scale_normalize() noexcept;
	};

	template <typename T>
	inline CVector<T>::CVector(CVector<T>&& args) noexcept :
		CVector()
	{
		m_size = args.m_size;

		m_ptr = args.m_ptr;
		args.m_ptr = nullptr;
	}

	template <typename T>
	inline CVector<T>::CVector(CVector<T> const& args) noexcept :
		CVector()
	{
		m_size = args.m_size;

		m_ptr = new T[m_size];
		memcpy(m_ptr, args.m_ptr, sizeof(T) * args.m_size);
	}

	template <typename T>
	inline CVector<T>& CVector<T>::operator=(CVector<T>&& rhs) noexcept {
		if (m_ptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}
		m_size = rhs.m_size;

		m_ptr = rhs.m_ptr;
		rhs.m_ptr = nullptr;
		return *this;
	}

	template <typename T>
	inline CVector<T>& CVector<T>::operator=(CVector<T> const& rhs) noexcept {
		if (m_ptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}
		m_size = rhs.m_size;

		m_ptr = new T[m_size];
		memcpy(m_ptr, rhs.m_ptr, sizeof(T) * m_size);
		return *this;
	}

	template<typename T>
	inline CVector<T>::CVector() noexcept :
		m_elems{}
	{}

	template<typename T>
	inline CVector<T>::CVector(std::initializer_list<T> const& args) noexcept :
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

	template<typename T>
	inline T* const CVector<T>::begin() const noexcept {
		return &m_elems[0U];
	}

	template<typename T>
	inline T* const CVector<T>::end() const noexcept {
		return &m_elems[L];
	}
	template<typename T>
	inline size_t const CVector<T>::size() const noexcept {
		return L;
	}

	template<typename T>
	inline T const& CVector<T>::operator[](size_t const& idx) const& noexcept {
		return m_elems[idx];
	}

	template<typename T>
	inline T& CVector<T>::operator[](size_t const& idx) & noexcept {
		return m_elems[idx];
	}

	template<typename T>
	inline T CVector<T>::operator[](size_t const& idx) const&& noexcept {
		return move(m_elems[idx]);
	}

	template<typename T>
	inline CVector<T>& CVector<T>::push_back(T const& dt) noexcept {
		if (m_allocSize < m_size + 1U) {
			scale_up();
		}
		*(m_ptr + m_size) = dt;
		++m_size;
		return *this;
	}

	template<typename T>
	inline CVector<T>& CVector<T>::push_front(T const& dt) noexcept {
		if (m_allocSize < m_size + 1U) {
			scale_up();
		}
		memmove(m_ptr, m_ptr + 1U, sizeof(T) * m_size);
		*m_ptr = dt;
		++m_size;
		return *this;
	}

	template<typename T>
	inline CVector<T>& CVector<T>::insert(size_t const& idx, T const& dt) noexcept {
		if (idx >= m_size) {
			return push_back(dt);
		}

		if (m_allocSize < m_size + 1U) {
			scale_up();
		}
		memmove(m_ptr + idx + 1U, m_ptr + idx, sizeof(T) * (m_size - idx - 1U));
		*(m_ptr + idx) = dt;
		++m_size;
		return *this;

	}

	template<typename T>
	inline CVector<T>& CVector<T>::pop_back() noexcept {
		if (m_size == 0U) {
			return *this;
		}

		--m_size;
		return *this;
	}

	template<typename T>
	inline CVector<T>& CVector<T>::pop_front() noexcept {
		if (m_size == 0U) {
			return *this;
		}

		memmove(m_ptr, m_ptr + 1U, sizeof(T) * (m_size - 1U));
		--m_size;
		return *this;
	}

	template<typename T>
	inline CVector<T>& CVector<T>::remove(size_t const& idx) noexcept {
		if (idx >= m_size) {
			return pop_back();
		}

		if (m_size == 0) {
			return *this;
		}
		memmove(m_ptr + idx, m_ptr + idx + 1U, sizeof(T) * (m_size - idx));
		--m_size;
		return *this;
	}

	template<typename T>
	inline CVector<T>& CVector<T>::clear() noexcept {
		m_size = 0U;
		return *this;
	}

	template<typename T>
	inline CVector<T>& CVector<T>::reflesh() noexcept {
		scale_normalize();
		return *this;
	}

	template<typename T>
	inline void CVector<T>::scaling(size_t const& capasity) noexcept {
		T* ptr = new T[capasity];
		memcpy(ptr, m_ptr, sizeof(T) * m_size);
		if (m_ptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}
		m_allocSize = capasity;
		m_ptr = ptr;
		ptr = nullptr;
	}

	template<typename T>
	inline void CVector<T>::scale_up() noexcept {
		scaling(m_allocSize + m_allocRate);
	}

	template<typename T>
	inline void CVector<T>::scale_normalize() noexcept {
		scaling(lcm(m_size, m_allocRate));
	}
}