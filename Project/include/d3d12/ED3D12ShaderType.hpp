/**	@file	EShaderType.hpp
 *	@brief	シェーダータイプ
 */
#pragma once

namespace dlav {
	/**	@enum	EShaderType
	 *	@brief	シェーダータイプ
	 */
	enum class EShaderType : unsigned char {
		//!	@brief	頂点シェーダ
		VS = 0U,
		//!	@brief	ピクセルシェーダ
		PS,
		//!	@brief	ドメインシェーダ
		DS,
		//!	@brief	ジオメトリシェーダ
		GS,
		//!	@brief	フルシェーダ
		HS,
		//!	@brief	レイ生成シェーダ
		RGS,
		//!	@brief	ミスシェーダ
		MHS,
		//!	@brief	クローゼストヒットシェーダ
		CHS,
		//!	@brief	エニーヒットシェーダ
		AHS,
		//!	@brief	インターセクションシェーダ
		IS,
		//!	@brief	コーラブルシェーダ
		CS,
		//!	@brief	増幅シェーダ
		AS,
		//!	@brief	メッシュシェーダ
		MS
	};
}