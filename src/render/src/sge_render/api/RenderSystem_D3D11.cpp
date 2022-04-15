#include "RenderSystem_D3D11.h"

//Private Func
void sge::RenderSystem_D3D11::_initPipeline() {
	// load and compile the two shaders

	SGE_LOG("Initing PipeLine");

	ID3D10Blob* VS, * PS;

	D3DCompileFromFile(L"sge_render/api/shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &VS, 0);
	D3DCompileFromFile(L"sge_render/api/shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &PS, 0);

	SGE_LOG("FoundShader");

	// encapsulate both shaders into shader objects
	dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	// set the shader objects
	devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	devcon->IASetInputLayout(pLayout);

	SGE_LOG("D3D11 Render PipeLine initialized...\n");
}

void sge::RenderSystem_D3D11::_initGraphics() {
	// create a triangle using the VERTEX struct
	VERTEX OurVertices[] = {
		{0.0f, 0.5f, 0.0f,		COLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{0.45f, -0.5, 0.0f,		COLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{-0.45f, -0.5f, 0.0f,	COLOR(0.0f, 0.0f, 1.0f, 1.0f)}
	};

	// create the vertex buffer 
	D3D11_BUFFER_DESC bd;
	SGE_Bzero(bd);

	bd.Usage = D3D11_USAGE_DYNAMIC;                // CPU Write Only , GPU Read Only
	bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer

	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	SGE_Bzero(ms);

	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
	devcon->Unmap(pVBuffer, NULL);                                      // unmap the buffer

	SGE_LOG("D3D11 Graphics initialized\n");
}

//override Func
void sge::RenderSystem_D3D11::onInit3D(HWND& Hwnd) {

	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;
	SGE_Bzero(scd);

	int ScreenW = 800; //TODO GetFromCurrentWinWidth
	int ScreenH = 600; //TODO GetFromCurrentWinHeight

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferDesc.Width = ScreenW;							// set the back buffer width
	scd.BufferDesc.Height = ScreenH;						// set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = Hwnd;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);

	// get the address of the back buffer
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	SGE_Bzero(viewport);

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width	= ScreenW;
	viewport.Height	= ScreenH;

	devcon->RSSetViewports(1, &viewport);

	SGE_LOG("SwapChain and Viewport Initialzied...\n");

	_initPipeline();
	_initGraphics();
}

void sge::RenderSystem_D3D11::onRender() {
	// clear the back buffer to a deep blue
	devcon->ClearRenderTargetView(backbuffer, COLOR(0.0f, 0.2f, 0.4f, 1.0f).data);

	// select which vertex buffer to display
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

	// select which primtive type we are using
	devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the vertex buffer to the back buffer
	devcon->Draw(3, 0);

	// switch the back buffer and the front buffer
	swapchain->Present(0, 0);
}

void sge::RenderSystem_D3D11::onClean3D() {

	// switch to windowMode
	swapchain->SetFullscreenState(FALSE, NULL);

	// close and release all existing COM objects
	pLayout->Release();
	pVBuffer->Release();

	pVS->Release();
	pPS->Release();

	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();

	SGE_LOG("D3D11 Memeory Released...\n");
}