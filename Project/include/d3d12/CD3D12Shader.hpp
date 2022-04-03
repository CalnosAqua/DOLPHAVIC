/**	@file	CD3D12Shader.hpp
 *	@brief	シェーダ
 */
#pragma once
#include "util/INoncopyable.hpp"
#include <d3d12.h>
#include <d3dcompiler.h>

namespace dlav {
	/**	@class	CD3D12Shader
	 *	@brief	シェーダクラス
	 */
	class CD3D12Shader final :
		public INoncopyable<CD3D12Shader>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		CD3D12Shader(CD3D12Shader&&) noexcept;
		//!	@brief	ムーブ代入演算子
		CD3D12Shader& operator=(CD3D12Shader&&) noexcept;
		
		//!	@brief	デフォルトコンストラクタ
		CD3D12Shader() noexcept;
		//!	@brief	デストラクタ
		~CD3D12Shader() noexcept;

		//!	@brief	初期化関数
		bool const init(LPCWSTR const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	設定用データ出力関数
		D3D12_SHADER_BYTECODE const get() const noexcept;

	private:
		//!	@brief	シェーダの塊
		ID3DBlob* m_shader;
	};
}