/**	@file	CD3D12PipelineState.hpp
 *	@brief	パイプラインステート
 */
#pragma once
#include "util/INoncopyable.hpp"
#include "CD3D12InputLayout.hpp"
#include "CD3D12RootSignature.hpp"
#include "CDSV.hpp"
#include <d3d12.h>

namespace dlav {
	/**	@struct	SPSODesc
	 *	@brief	パイプラインステート初期化用データ
	 */
	struct SPSODesc final {
		//!	@brief	インプットレイアウト
		CD3D12InputLayout* il;
		//!	@brief	ルートシグネチャポインタ
		CD3D12RootSignature* rs;
		//!	@brief	震度ステンシルポインタ
		CD3D12DepthStencil* ds;
		//!	@brief	【必須】頂点シェーダ
		D3D12_SHADER_BYTECODE vs;
		//!	@brief	【必須】ピクセルシェーダ
		D3D12_SHADER_BYTECODE ps;
	};

	/**	@class	CD3D12PipelineState
	 *	@brief	パイプラインステートクラス
	 */
	class CD3D12PipelineState final : public INoncopyable<CD3D12PipelineState> {
	public:
		//!	@brief	ムーブコンストラクタ
		CD3D12PipelineState(CD3D12PipelineState&&) noexcept;
		//!	@brief	ムーブ代入演算子
		CD3D12PipelineState& operator=(CD3D12PipelineState&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		CD3D12PipelineState() noexcept;
		//!	@brief	デストラクタ
		~CD3D12PipelineState() noexcept;

		//!	@brief	初期化関数
		bool const init(SPSODesc const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	参照演算子
		ID3D12PipelineState* get() const noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12PipelineState* operator->() const noexcept;

	private:
		//!	@brief	パイプラインステート
		ID3D12PipelineState* m_state;
	};
}