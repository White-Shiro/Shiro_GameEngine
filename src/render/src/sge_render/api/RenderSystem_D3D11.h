#pragma once

#include <sge_render/api/RenderSystem.h>

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

namespace sge {

	class RenderSystem_D3D11 : public RenderSystem {
		using This = RenderSystem_D3D11;
		using Base = RenderSystem;

	protected:
		virtual void onInit3D(HWND& Hwnd)  override;
		virtual void onRender()  override;
		virtual void onClean3D() override;

	private:
		struct COLOR {
			union {
				struct { float r, g, b, a; };
				float data[4];
			};
			COLOR(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
		};
		struct VERTEX { FLOAT X, Y, Z; COLOR color; };

		//COM Objects, must be released when clean up
		IDXGISwapChain*			swapchain;		// the pointer to the swap chain interface
		ID3D11Device*			dev;			// the pointer to our Direct3D device interface
		ID3D11DeviceContext*	devcon;			// the pointer to our Direct3D device context
		ID3D11RenderTargetView*	backbuffer;		// the pointer to our BackBuffer

		ID3D11InputLayout*		pLayout;		// the pointer of inputLayer
		ID3D11Buffer*			pVBuffer;		// the pointer of vertex buffer

		// Shader
		ID3D11VertexShader*		pVS;			// the pointer of vertex shader
		ID3D11PixelShader*		pPS;			// the pointer of pixel shader

		void _initGraphics();
		void _initPipeline();
	};
}