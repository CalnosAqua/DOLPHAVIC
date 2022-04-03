/**	@file	CBezierCurves.hpp
 *	@brief	Ｎ次ベジエ曲線
 */
#pragma once
#include <vector>

namespace dlav {
	/**	@file	CBezierCurves
	 *	@brief	Ｎ次ベジエ曲線
	 */
	template <typename T>
	class CBezierCurves final {
	public	:
		template <typename T>
		struct Vertex final {
			//!	@brief	頂点
			T& vertex;
			//!	@brief	重み
			float& weight;
		};
		//!	@brief	ムーブコンストラクタ
		CBezierCurves<T>(CBezierCurves<T>&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CBezierCurves<T>(CBezierCurves<T> const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CBezierCurves<T>& operator=(CBezierCurves<T>&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CBezierCurves<T>& operator=(CBezierCurves<T> const&) noexcept = default;

		//! @brief デフォルトコンストラクタ
		CBezierCurves() noexcept;
		//! @brief デストラクタ
		~CBezierCurves() noexcept = default;

		//!	@brief	頂点追加関数
		CBezierCurves<T>& add(unsigned int const& index, T const& vertex, float const& weight) noexcept;
		//!	@brief	頂点除去関数
		CBezierCurves<T>& remove(unsigned int const& index) noexcept;

		//!	@brief	添え字演算子
		Vertex<T> const operator[](unsigned int const&) const noexcept;
		//!	@brief	添え字演算子
		Vertex<T> operator[](unsigned int const&) noexcept;

		//!	@brief	補間値取得関数
		T const interpolate(float const&) noexcept;

	private	:
		//!	@brief	頂点
		std::vector<T> m_vertices;
		//!	@brief	重み
		std::vector<float> m_rate;

		//!	@brief	バーンシュタイン多項式計算関数
		float const bern(const unsigned int& n, const unsigned int& k, const float& t) noexcept;
	};

	/* 実装 */

	template<typename T>
	inline CBezierCurves<T>& CBezierCurves<T>::add(unsigned int const& index, T const& vertex, float const& weight) noexcept {
		m_vertices.insert(m_vertices.begin() + index, vertex);
		m_rate.insert(m_rate.begin() + index, weight);
		return *this;
	}

	template<typename T>
	inline CBezierCurves<T>& CBezierCurves<T>::remove(unsigned int const& index) noexcept {
		m_vertices.erase(m_vertices.begin() + index);
		m_rate.erase(m_rate.begin() + index);
		return *this;
	}

	template<typename T>
	inline CBezierCurves<T>::Vertex<T> const CBezierCurves<T>::operator[](unsigned int const& idx) const noexcept {
		CBezierCurves<T>::Vertex<T> result;
		result.vertex = m_vertices[idx];
		result.weight = m_rate[idx];
		return result;
	}

	template<typename T>
	inline CBezierCurves<T>::Vertex<T> CBezierCurves<T>::operator[](unsigned int const& idx) noexcept {
		CBezierCurves<T>::Vertex<T> result;
		result.vertex = m_vertices[idx];
		result.weight = m_rate[idx];
		return result;
	}

	template<typename T>
	inline T const CBezierCurves<T>::interpolate(float const& rate) noexcept {
		if (rate <= 0.0f) {
			return m_vertices[0];
		}
		if (rate >= 1.0f) {
			return m_vertices[mContents.size() - 1];
		}

		T vertex;
		float weight, temp;
		CBezierCurves<T>::Vertex<T> arg;
		//	ベルンシュタイン多項式を利用して座標を求める。
		for (unsigned int idx = 0; idx < mContents.size(); idx++) {
			arg = (*this)[idx];
			temp = arg.weight * bern(m_vertices.size(), idx, t);
			vertex += arg.vertex * temp;
			weight += temp;
		}

		return vertex / weight;
	}

	template<typename T>
	inline float const CBezierCurves<T>::bern(const unsigned int& n, const unsigned int& k, const float& t) noexcept {
		if (k > n) {
			return 1.0f;
		}
		
		//	組み合わせを求める。
		unsigned int tmp = 1U;
		for (unsigned int i = 1U; i < k; i++) {
			tmp *= (n + 1 - i) / i;
		}

		//	組み合わせからベルンシュタイン多項式を求める。
		return static_cast<float>(tmp)
			* powf(t, static_cast<float>(k))
			* powf((1.0f - t), static_cast<float>(n - k));
	}
}