/**	@file	CD3D12GraphicsPipeline.hpp
 *	@brief	グラフィックスパイプライン
 */
#pragma once
#include "util/INoncopyable.hpp"
#include "CD3D12CommandList.hpp"
#include "CD3D12Shader.hpp"
#include "CDSV.hpp"
#include <d3d12.h>
#include <vector>

namespace dlav {
	/**	@struct	SInputLayoutDesc
	 *	@brief	入力レイアウト記述子構造体
	 */
	struct SInputLayoutDesc final {
		//!	@brief	セマンティック名
		LPSTR name;
		//!	@brief	セマンティック番号
		UINT index;
		//!	@brief	セマンティックフォーマット
		DXGI_FORMAT format;
	};

	/**	@struct	SGraphicsPipelineDesc
	 *	@brief	グラフィックスパイプライン初期化用データ一式
	 */
	struct SGraphicsPipelineDesc final {
		//!	@brief	震度ステンシルビュー
		CD3D12DepthStencil* dsv;
		//!	@brief	【必須】頂点シェーダ
		CD3D12Shader* vs;
		//!	@brief	【必須】ピクセルシェーダ
		CD3D12Shader* ps;
		//!	@brief	フルシェーダ
		CD3D12Shader* hs;
		//!	@brief	ジオメトリシェーダ
		CD3D12Shader* gs;
		//!	@brief	ドメインシェーダ
		CD3D12Shader* ds;
	};

	/**	@class	CD3D12GraphicsPipeline
	 *	@brief	グラフィックスパイプライン
	 */
	class CD3D12GraphicsPipeline final :
		public INoncopyable<CD3D12GraphicsPipeline>
	{
	public	:
		//!	@brief	ムーブコンストラクタ
		CD3D12GraphicsPipeline(CD3D12GraphicsPipeline&&) noexcept;
		//!	@brief	ムーブ代入演算子
		CD3D12GraphicsPipeline& operator=(CD3D12GraphicsPipeline&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		CD3D12GraphicsPipeline() noexcept;
		//!	@brief	デストラクタ
		~CD3D12GraphicsPipeline() noexcept;

		//!	@brief	初期化関数
		bool const init(SGraphicsPipelineDesc const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	入力レイアウト追加関数
		CD3D12GraphicsPipeline& add(SInputLayoutDesc const&) noexcept;
		//!	@brief	入力レイアウト除去関数
		CD3D12GraphicsPipeline& remove(unsigned int const&) noexcept;
		//!	@brief	入力レイアウト全消去関数
		CD3D12GraphicsPipeline& clear() noexcept;

		//!	@brief	コマンドリストに登録する関数
		void setCmdList(CD3D12CommandList&) noexcept;

	private	:
		//!	@brief	インプットレイアウト
		std::vector<D3D12_INPUT_ELEMENT_DESC> m_layout;
		//!	@brief	ルートパラメータ
		std::vector<D3D12_ROOT_PARAMETER> m_params;
		//!	@brief	ルートシグネチャ
		ID3D12RootSignature* m_signature;
		//!	@brief	パイプラインステート
		ID3D12PipelineState* m_state;
		//!	@brief	シグネチャフラグ
		D3D12_ROOT_SIGNATURE_FLAGS m_flags;
	};
}