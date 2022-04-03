/**	@file	CD3D12InputLayout.hpp
 *	@brief	入力レイアウト
 */
#pragma once
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

	/**	@class	CD3D12InputLayout
	 *	@brief	入力レイアウト
	 */
	class CD3D12InputLayout final {
	public	:
		//!	@brief	ムーブコンストラクタ
		CD3D12InputLayout(CD3D12InputLayout&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CD3D12InputLayout(CD3D12InputLayout const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CD3D12InputLayout& operator=(CD3D12InputLayout&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CD3D12InputLayout& operator=(CD3D12InputLayout const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CD3D12InputLayout() noexcept;
		//!	@brief	デストラクタ
		~CD3D12InputLayout() noexcept = default;

		//!	@brief	入力レイアウト追加関数
		CD3D12InputLayout& add(SInputLayoutDesc const&) noexcept;
		//!	@brief	入力レイアウト除去関数
		CD3D12InputLayout& remove(unsigned int const&) noexcept;
		//!	@brief	入力レイアウト全消去関数
		CD3D12InputLayout& clear() noexcept;

		//!	@brief	入力レイアウトのアドレス取得関数
		D3D12_INPUT_ELEMENT_DESC* getAddress() const noexcept;
		//!	@brief	入力レイアウトの数取得関数
		unsigned int const getCount() const noexcept;

	private	:
		//!	@brief	入力レイアウトデータ
		std::vector<D3D12_INPUT_ELEMENT_DESC> m_elems;
	};
}