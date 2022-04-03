/**	@file	CWindow.cpp
 *	@brief	Windows 用ウィンドウ管理クラス定義ファイル
 */
#if !defined(_CRT_SECURE_NO_WARNINGS)
#	define _CRT_SECURE_NO_WARNINGS
#endif

#if !defined(_CRT_NON_CONFORMING_SWPRINTFS)
#	define _CRT_NON_CONFORMING_SWPRINTFS
#endif

#include "win/CWindow.hpp"
#include <numeric>
#include <tchar.h>

namespace dlav {
	CWindow::CWindow(CWindow&& arg) noexcept :
		CWindow()
	{
		m_hWnd = arg.m_hWnd;
		m_wndName = arg.m_wndName;
		arg.m_hWnd = nullptr;
		arg.m_wndName = nullptr;

		m_inited = arg.m_inited;

		memcpy(&m_wndClass, &arg.m_wndClass, sizeof(WNDCLASSEXA));
	}
	
	CWindow& CWindow::operator=(CWindow&& rhs) noexcept {
		uninit();

		m_hWnd = rhs.m_hWnd;
		m_wndName = rhs.m_wndName;
		rhs.m_hWnd = nullptr;
		rhs.m_wndName = nullptr;

		m_inited = rhs.m_inited;

		memcpy(&m_wndClass, &rhs.m_wndClass, sizeof(WNDCLASSEXA));
		return *this;
	}

	CWindow::CWindow() noexcept :
		m_hWnd(nullptr),
		m_wndName(nullptr),
		m_wndClass(),
		m_inited(false)
	{}

	CWindow::~CWindow() noexcept {
		uninit();
	}

	bool const CWindow::init(SWindowsWindowDesc const& data) noexcept {
		if (m_inited) {
			return m_inited;
		}

#if defined(DEBUG) || defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
		m_wndClass.cbSize = sizeof(tagWNDCLASSEXA);
		m_wndClass.style = data.scalable ? (CS_HREDRAW | CS_VREDRAW) : 0;
		m_wndClass.lpfnWndProc = data.wnd_proc;
		m_wndClass.cbClsExtra = 0;
		m_wndClass.cbWndExtra = 0;
		m_wndClass.hInstance = data.ins_handler;
		m_wndClass.hIcon = nullptr;
		m_wndClass.hCursor = nullptr;
		m_wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		m_wndClass.lpszMenuName = nullptr;
		m_wndClass.lpszClassName = data.cls_name;
		m_wndClass.hIconSm = nullptr;

		bool state = RegisterClassExA(&m_wndClass);
		if (!state) {
			OutputDebugStringA("Error : Failed Register Window Class.\n");
			return m_inited;
		}

		m_hWnd = CreateWindowExA(
			0,
			data.cls_name,
			data.wnd_name,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<int>(data.width),
			static_cast<int>(data.height),
			nullptr,
			nullptr,
			data.ins_handler,
			nullptr
		);

		if (!m_hWnd) {
			OutputDebugStringA("Error : Failed Create Window.\n");
			return m_inited;
		}

		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		UpdateWindow(m_hWnd);
		SetFocus(m_hWnd);

		m_wndName = data.wnd_name;

		m_inited = true;
		return m_inited;
	}

	void CWindow::uninit() noexcept {
		if (m_inited) {
			char temp[100];
			memset(temp, 0, 100);
			GetClassNameA(m_hWnd, temp, 100);
			UnregisterClassA(temp, getInstanceHandle());
			m_hWnd = nullptr;
			m_inited = false;
		}
	}

	void CWindow::showWindowStatus() noexcept {
		static _LARGE_INTEGER start;
		static char view[100];
		static int frame = 0;
		double passtime, microsec;
		_LARGE_INTEGER end;
		_LARGE_INTEGER frq;

		QueryPerformanceFrequency(&frq);

		passtime = 0;
		microsec = 1.0E+6 / static_cast<double>(frq.QuadPart);

		frame++;

		QueryPerformanceCounter(&end);
		passtime = (end.QuadPart - start.QuadPart) * microsec;
		if (passtime > 1.0E+6) {
			QueryPerformanceCounter(&start);

			memset(view, 0, 100);
			sprintf(view, "%s [FPS=%d W=%d H=%d]", m_wndName, frame, getWidth(), getHeight());
			SetWindowTextA(m_hWnd, view);
			frame = 0;
		}
	}

	LRESULT const CWindow::WindowProcedure(HWND const& hWnd, UINT const& uMsg, WPARAM const& wParam, LPARAM const& lParam) {
		int id = 0;
		switch (uMsg) {
		case WM_CLOSE:
			id = MessageBoxA(hWnd, "終了しますか？", "確認", MB_YESNO | MB_ICONINFORMATION);
			if (id == IDYES) {
				DestroyWindow(hWnd);
			}
			break;
		case WM_KEYDOWN:
			if (GetKeyState(VK_ESCAPE) < 0) {
				id = MessageBoxA(hWnd, "終了しますか？", "確認", MB_YESNO | MB_ICONINFORMATION);
				if (id == IDYES) {
					DestroyWindow(hWnd);
				}
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcA(hWnd, uMsg, wParam, lParam);
			break;
		}

		return 0;
	}

	MessageState const CWindow::receivingMessage() noexcept {
		MSG msg;
		memset(&msg, 0, sizeof(MSG));
		if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return MessageState::END;
			}
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
			return MessageState::RECEIVED;
		}
		return MessageState::NOTFOUND;
	}

	RECT const CWindow::getRectangle() const noexcept {
		RECT result;
		GetClientRect(m_hWnd, &result);
		return result;
	}

	HWND const& CWindow::getWindowHandle() const noexcept {
		return m_hWnd;
	}

	HINSTANCE const CWindow::getInstanceHandle() const noexcept {
		HINSTANCE result = reinterpret_cast<HINSTANCE>(static_cast<LONGLONG>(GetWindowLongA(m_hWnd, GWLP_HINSTANCE)));
		return result;
	}

	unsigned int const CWindow::getWidth() const noexcept {
		RECT temp = getRectangle();
		return static_cast<unsigned int>(labs(temp.right - temp.left));
	}

	unsigned int const CWindow::getHeight() const noexcept {
		RECT temp = getRectangle();
		return static_cast<unsigned int>(labs(temp.bottom - temp.top));
	}
}