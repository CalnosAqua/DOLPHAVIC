/**	@file	CD3D12RootSignature.hpp
 *	@brief	ルートシグネチャ
 */
#pragma once
#include <d3d12.h>
#include <vector>
#include "util/INoncopyable.hpp"

namespace dlav {
	/**	@file	CD3D12RootSignature
	 *	@brief	ルートシグネチャ
	 */
	class CD3D12RootSignature final : public INoncopyable<CD3D12RootSignature> {
	public:
		//!	@brief	ムーブコンストラクタ
		CD3D12RootSignature(CD3D12RootSignature&&) noexcept;
		//!	@brief	ムーブ代入演算子
		CD3D12RootSignature& operator=(CD3D12RootSignature&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		CD3D12RootSignature() noexcept;
		//!	@brief	デストラクタ
		~CD3D12RootSignature() noexcept;

		//!	@brief	初期化関数
		bool const init(std::vector<D3D12_ROOT_PARAMETER> const&, D3D12_ROOT_SIGNATURE_FLAGS const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	取得関数
		ID3D12RootSignature*& get() const noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12RootSignature* operator->() const noexcept;
	private:
		//!	@brief	ルートシグネチャ
		ID3D12RootSignature* m_signature;
	};
}