/**	@file	CWindow.hpp
 *	@brief	Windows 用ウィンドウ管理クラス定義ファイル
 */
#pragma once

#if !defined(NOMINMAX)
#	define NOMINMAX
#endif

#include "util/INoncopyable.hpp"
#include <Windows.h>

namespace dlav {
	/**	@enum	MessageState
	 *	@brief	メッセージの状態一覧
	 */
	enum class MessageState {
		//!	@brief	メッセージを受け取りました。
		RECEIVED,
		//!	@brief	メッセージが届いていませんでした。
		NOTFOUND,
		//!	@brief	終了メッセージを受け取りました。
		END
	};

	/**	@enum	SWindowsWindowDesc
	 *	@brief	ウィンドウ管理クラス初期化用データ一式
	 */
	struct SWindowsWindowDesc final {
		//!	@brief	インスタンスハンドル
		HINSTANCE		ins_handler;
		//!	@brief	ウィンドウプロシージャ
		WNDPROC			wnd_proc;
		//!	@brief	クラス名
		LPCSTR			cls_name;
		//!	@brief	ウィンドウ名
		LPCSTR			wnd_name;
		//!	@brief	横幅
		unsigned int	width;
		//!	@brief	縦幅
		unsigned int	height;
		//!	@brief	拡縮
		bool			scalable;
	};

	/**	@class	CWindow
	 *	@brief	WINDOWS 用のウィンドウ
	 */
	class CWindow final :
		INoncopyable<CWindow>
	{
	public:
		//!	@brief	コピーコンストラクタ
		CWindow(CWindow&&) noexcept;
		//!	@brief	コピー代入演算子
		CWindow& operator=(CWindow&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		CWindow() noexcept;
		//!	@brief	デストラクタ
		~CWindow() noexcept;

		//!	@brief	初期化処理関数
		bool const init(SWindowsWindowDesc const&) noexcept;
		//!	@brief	終了処理関数
		void uninit() noexcept;

		//!	@brief	ウィンドウステータス表示処理関数
		void showWindowStatus() noexcept;
		//!	@brief	クラス専属ウィンドウプロシージャ
		LRESULT const WindowProcedure(
			HWND const& hWnd,
			UINT const& iMsg,
			WPARAM const& wParam,
			LPARAM const& lParam
		);
		//!	@brief	メッセージ受理処理関数
		MessageState const receivingMessage() noexcept;

		//!	@brief	矩形生成関数
		RECT const getRectangle() const noexcept;

		//!	@brief	ウィンドウハンドル取得関数
		HWND const& getWindowHandle() const noexcept;
		//!	@brief	インスタンスハンドル取得関数
		HINSTANCE const getInstanceHandle() const noexcept;
		//!	@brief	横幅取得関数
		unsigned int const getWidth() const noexcept;
		//!	@brief	縦幅取得関数
		unsigned int const getHeight() const noexcept;

	private:
		//!	@brief	ウィンドウハンドル
		HWND		m_hWnd;
		//!	@brief	ウィンドウ名
		LPCSTR		m_wndName;
		//!	@brief	ウィンドウクラス
		WNDCLASSEXA	m_wndClass;
		//!	@brief	初期化済みかどうか
		bool		m_inited;
	};
}