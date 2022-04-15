#pragma once

#include<sge_render/api/RenderSystem_D3D11.h>

namespace sge {

	class Renderer {
	public:

		//ctor
		struct  CreateDesc {
			CreateDesc() {};
		};

		//create instance
		static Renderer* current() {return _current;};
		Renderer() { _current = this; }

		
		//Renderer create(CreateDesc& desc) {}
		Renderer create() { onCreate(); return Renderer(); }

		void Init(HWND& Hwnd) { onInit(Hwnd, _renderSystem); }
		void draw() { onDraw(_renderSystem); }
		void clean() { onClean(_renderSystem);}

	private:

		static Renderer* _current;

		//Change to #define?
		RenderSystem_D3D11 _renderSystem; //hard-coded right now

		//void onCreate(CreateDesc& desc) {};
		void onCreate() { _renderSystem = RenderSystem_D3D11(); }
		void onInit(HWND& Hwnd,RenderSystem& renderSys_) { renderSys_.init3D(Hwnd); }
		void onDraw(RenderSystem& renderSys_) { renderSys_.render(); }
		void onClean(RenderSystem& renderSys_) { renderSys_.clean3D(); }
};

} //nacespace