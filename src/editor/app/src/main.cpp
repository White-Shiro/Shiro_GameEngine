#include <sge_editor.h>
#include <sge_render.h>

namespace sge {

class MainWin : public NativeUIWindow {
	using Base = NativeUIWindow;
public:
	void onCreate(CreateDesc& desc) {
		Base::onCreate(desc);
	}

	virtual void onCloseButton() override {
		NativeUIApp::current()->quit(0);
	}
};

class EditorApp : public NativeUIApp {
	using Base = NativeUIApp;
public:
	virtual void onCreate(CreateDesc& desc) override {
		{
			String file = getExecutableFilename();
			String path = FilePath::getDir(file);

			auto testdir = getCurrentDir();
			SGE_LOG("dir = {}", testdir);

			path.append("../../../../../../../");
			setCurrentDir(path);

			auto dir = getCurrentDir();
			SGE_LOG("dir = {}", dir);
		} //Change Working Directory

		Base::onCreate(desc);

		NativeUIWindow::CreateDesc winDesc;
		winDesc.isMainWindow = true;
		_mainWin.create(winDesc);
		_mainWin.setWindowTitle("SGE Editor_Shiro");

		//Atleast Working :(
		_renderer = new RenderSystem_D3D11();
		_renderer->init3D(_mainWin._hwnd);

	}

	virtual void onUpdate() override {
		Base::onUpdate();
		//Game Logic Update
	}

	virtual void onLateUpdate() override {
		Base::onLateUpdate();

		//Render when all logic is done
		_renderer->render();
	}

	virtual void willQuit() override {
		// clean Renderer before app quit
		_renderer->clean3D();
	}

	virtual void onQuit() override {
		Base::onQuit();
	}

private:
	MainWin			_mainWin;
	RenderSystem*	_renderer;
	//Renderer*		_renderer;
};

}

int main() {
	sge::EditorApp app;
	sge::EditorApp::CreateDesc desc;
	app.run(desc);

	return 0;
}
