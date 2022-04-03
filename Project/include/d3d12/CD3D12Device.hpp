/**	@file	CD3D12Device.hpp
 *	@brief	Direct3D12 用のデバイスクラス
 */
#pragma once
#include "util/ISingleton.hpp"
#include <d3d12.h>

namespace dlav {
	/**	@class	CD3D12Device
	 *	@brief	Direct3D12 用のデバイスクラス
	 */
	class CD3D12Device final :
		public ISingleton<CD3D12Device>
	{
	public	:
		//!	@brief	デフォルトコンストラクタ
		CD3D12Device() noexcept;
		//!	@brief	デストラクタ
		~CD3D12Device() noexcept;

		//!	@brief	初期化関数
		bool const init() noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	メンバアクセス演算子
		ID3D12Device8* operator->() const noexcept;

	private	:
		//!	@brief	デバイス
		ID3D12Device8* m_device;
	};

	/**	@brief COM オブジェクト解放関数
	 *	@param[in] ptr COM オブジェクト
	 */
	template<typename T>
	inline void safe_release(T*& ptr) noexcept {
		if (ptr != nullptr) {
			ptr->Release();
			ptr = nullptr;
		}
	}

	/**	@brief オブジェクト解放関数
	 *	@param[in] ptr オブジェクト
	 */
	template<typename T>
	inline void safe_delete(T*& ptr) noexcept {
		if (ptr != nullptr) {
			delete ptr;
			ptr = nullptr;
		}
	}
}