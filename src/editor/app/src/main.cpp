#include <sge_editor.h>
#include <sge_render.h>

namespace sge {

	class MainWin : public NativeUIWindow {
		using Base = NativeUIWindow;
	public:
		void onCreate(CreateDesc& desc) {

			Base::onCreate(desc);
			auto* renderer = Renderer::current();

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
			}  //Change Working Directory

			Base::onCreate(desc);

			//Renderer Create
			Renderer::CreateDesc renderDesc;
			Renderer::create(renderDesc);

			//MainWin Create
			NativeUIWindow::CreateDesc winDesc;
			winDesc.isMainWindow = true;
			_mainWin.create(winDesc);
			_mainWin.setWindowTitle("SGE Editor_Shiro");

		}

	private:
		MainWin			_mainWin;

	};

}

int main() {
	sge::EditorApp app;
	sge::EditorApp::CreateDesc desc;
	app.run(desc);

	return 0;
}
