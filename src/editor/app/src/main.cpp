#include <sge_editor.h>
#include <sge_render.h>

namespace sge {

class MainWin : public NativeUIWindow {
public:
	virtual void onCloseButton() override {
		NativeUIApp::current()->quit(0);
	}
};

class EditorApp : public NativeUIApp {
	using Base = NativeUIApp;
public:
	virtual void onCreate(CreateDesc& desc) override {
		Base::onCreate(desc);

		NativeUIWindow::CreateDesc winDesc;
		winDesc.isMainWindow = true;
		_mainWin.create(winDesc);
		_mainWin.setWindowTitle("SGE Editor_Shiro");

		// Create and Init Renderer after _main is created

		_renderer.create();
		_renderer.Init(_mainWin._hwnd);

	}

	virtual void onUpdate() override {
		Base::onUpdate();

		//Game Logic Update
	}

	virtual void onLateUpdate() override {
		Base::onLateUpdate();

		//Render when all logic is done
		_renderer.draw(); 
	}

	virtual void willQuit() override {
		// clean Renderer before app quit
		_renderer.clean();
	}

	virtual void onQuit() override {
		Base::onQuit();
	}

private:
	MainWin		_mainWin;
	Renderer	_renderer;
};

}

int main() {
	
	SGE_LOG("Test App Run");

	sge::EditorApp app;
	sge::EditorApp::CreateDesc desc;
	app.run(desc);


	return 0;
}
