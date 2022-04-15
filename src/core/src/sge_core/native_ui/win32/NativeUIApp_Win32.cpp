#include "NativeUIApp_Win32.h"
#include "../NativeUI.h"

#if SGE_OS_WINDOWS

namespace sge {

void NativeUIApp_Win32::onCreate(CreateDesc& desc) {
	Base::onCreate(desc);
}

void NativeUIApp_Win32::onRun() {
	Base::onRun();

	while (TRUE) {
		if (PeekMessage(&_win32_msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&_win32_msg);
			DispatchMessage(&_win32_msg);

			if (_win32_msg.message == WM_QUIT)
				break;
		} else {
			// Run game code here
			onUpdate();
			onLateUpdate();
		}
	}

	willQuit();
}



void NativeUIApp_Win32::onQuit() {
	Base::onQuit();

	::PostQuitMessage(_exitCode);
}

}

#endif
