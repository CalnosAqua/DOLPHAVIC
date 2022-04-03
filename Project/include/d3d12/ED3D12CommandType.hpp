/**	@file	ED3D12CommandType.hpp
 *	@brief	Direct3D12 用のコマンドの種類
 */
#pragma once

namespace dlav {
	/**	@enum	ED3D12CommandType
	 *	@brief	Direct3D12 用のコマンドの種類
	 */
	enum class ED3D12CommandType : unsigned char {
		//!	@brief	レンダリング用コマンド
		Direct = 0U,
		//!	@brief	バンドル生成用コマンド
		Bundle,
		//!	@brief	コンピュートシェーダ用コマンド
		Compute,
		//!	@brief	リソースコピー用コマンド
		Copy,
		//!	@brief	動画処理用コマンド
		VProcess,
		//!	@brief	動画デコード用コマンド
		VDecord,
		//!	@brief	動画エンコード用コマンド
		VEncord
	};
}