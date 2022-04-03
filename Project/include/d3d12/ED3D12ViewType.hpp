/**	@file	EViewType.hpp
 *	@brief	ビュータイプ
 */
#pragma once

namespace dlav {
	/**	@enum	EViewType
	 *	@brief	ビュータイプ
	 */
	enum class ED3D12ViewType : unsigned char {
		//!	@brief	レンダーターゲットビュー
		RTV = 0U,
		//!	@brief	深度バッファビュー
		DSV,
		//!	@brief	頂点バッファビュー
		VBV,
		//!	@brief	インデックスバッファビュー
		IBV,
		//!	@brief	定数バッファビュー
		CBV,
		//!	@brief	順序無しアクセスビュー
		UAV,
		//!	@brief	シェーダリソースビュー
		SRV,
		//!	@brief	アクセラレーションストラクションビュー
		ASV,
		//!	@brief	サンプラビュー
		Sampler,
	};
}