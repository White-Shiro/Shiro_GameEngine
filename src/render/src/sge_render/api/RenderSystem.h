#pragma once


namespace sge {

	//Abstract Class / Interface for switching 3D API
	class RenderSystem {

	public:

		void init3D(HWND& Hwnd)	{ onInit3D(Hwnd); }
		void render()			{ onRender(); }
		void clean3D()			{ onClean3D(); }

	protected:

		virtual void onInit3D(HWND& Hwnd);
		virtual void onRender();
		virtual void onClean3D();
};
} // namespace