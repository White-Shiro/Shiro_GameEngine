#pragma once

#include<sge_render/api/RenderSystem_D3D11.h>

namespace sge {

	//Foward Declare
	class RenderSystem;
	struct RenderSystem_CreateDesc;

	class Renderer : public NonCopyable {
	public:

		static Renderer* current() { return _current == nullptr? new Renderer() : _current; };

		enum class ApiType {
			None,
			DX11,
			OpenGL,
		};

		//ctor
		struct  CreateDesc {
			CreateDesc();
			ApiType		apiType;
			bool multithread : 1;
		};

		//create instance
		static Renderer* create(CreateDesc& desc);

		Renderer();
		virtual ~Renderer();

		RenderSystem* onCreateContext(RenderSystem_CreateDesc& desc) {}

		//---

		void Init(HWND Hwnd) { onInit(Hwnd, _currentRenderSystem); }
		void draw()  { onDraw (_currentRenderSystem); }
		void clean() { onClean(_currentRenderSystem); }

	private:
		static Renderer* _current;
		RenderSystem_D3D11* _currentRenderSystem = nullptr;

		//void onCreate(CreateDesc& desc) {};
		void onCreate() {}
		void onInit(HWND Hwnd,RenderSystem* renderSys_) { renderSys_->init3D(Hwnd); }
		void onDraw(RenderSystem* renderSys_) { renderSys_->render(); }
		void onClean(RenderSystem* renderSys_) { renderSys_->clean3D(); }
};

} //nacespace