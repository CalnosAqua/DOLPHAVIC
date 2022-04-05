/**	@file	CDLCamera.hpp
 *	@brief	Dolphavic Library 用の三次元カメラ
 */
#pragma once
#include "math/EHandSide.hpp"
#include "math/EAxisType.hpp"
#include "math/CFRotation.hpp"
#include "math/CFMatrix4x4.hpp"
#include "math/CFVector4.hpp"
#include "math/CFVector3.hpp"
#include "math/CFQuaternion.hpp"

namespace dlav {
	/**	@class	EProjectiveMode
	 *	@brief	投影モード
	 */
	enum class EProjectiveMode : unsigned char {
		//!	@brief	透視投影
		PARSEPECTIVE,
		//!	@brief	平行投影
		PARALLEL
	};

	/**	@class	EFollowMode
	 *	@brief	追従モード
	 */
	enum class EFollowMode : unsigned char {
		//!	@brief	フリー
		FREE,
		//!	@brief	追従
		FOLLOW,
		//!	@brief	追尾
		TRACKING
	};

	/**	@class	CCamera
	 *	@brief	カメラ
	 */
	class CCamera final {
	public	:
		//!	@brief	注視位置
		CFVector3 m_lookat;
		//!	@brief	垂直画角 (x)
		float m_height;
		//!	@brief	水平画角 (y)
		float m_width;
		//!	@brief	前方クリップ位置 (z_min)
		float m_near;
		//!	@brief	後方クリップ位置 (z_max)
		float m_far;
		//!	@brief	投影位置 (d)
		float m_wndpos;

		//!	@brief	ムーブコンストラクタ
		CCamera(CCamera&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		CCamera(CCamera const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CCamera& operator=(CCamera&&) noexcept = default;
		//!	@brief	コピー代入演算子
		CCamera& operator=(CCamera const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CCamera() noexcept;
		//!	@brief	デストラクタ
		~CCamera() noexcept = default;

		//!	@brief	ワールド変換行列を生成する関数
		CFMatrix4x4 world_mtx(EHandSide const&) noexcept;

	private	:
		//!	@brief	カメラ位置
		CFVector3 m_eye;
		//!	@brief	姿勢
		CFQuaternion m_posture;
		//!	@brief	投影モード
		EProjectiveMode m_pmode;
		//!	@brief	追従モード
		EFollowMode m_fmode;
	};
}