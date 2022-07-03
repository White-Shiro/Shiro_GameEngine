#pragma once

namespace sge {

enum class RenderStateType {
	None,
	Rasterizer,
	DepthStencil,
	Blend,
};

enum class RenderFillMode {
	WireFrame,
	Solid,
};

enum class RenderCullMode {
	None, //RenderBothSide?
	Front,
	Back,
};

enum class BlendType {
	Zero,
	One,

	Src_Color, 
	InvSrc_Color,
	Src_Alpha,
	InvSrc_Alpha,

	Dest_Alpha,
	InvDest_Alpha,
	Dest_Color,
	InvDest_Color,

	Src_Alpha_Sat,
	BlendFactor,
	InvBlendFactor,

	Src1_Color ,
	InvSrc1_Color,
	Src1_Alpha,
	Inv_Src1_Alpha,
};

enum class Blend_Operation {
	None,
	Add,
	Subtract,
	Rev_subtract,
	Min,
	Max,
};

enum class Stencil_Operation {
	None,
	Keep,
	Zero,
	Replace,
	Incr_sat,
	Decr_sat,
	Invert,
	Incr,
	Decr,
};

enum class DepthComparisonMode {
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always,
};

enum class DepthWriteMask { Zero, All, };

struct RenderTargetBlend {
	bool				blendEnable;
	BlendType			srcBlend;
	BlendType			destBlend;
	Blend_Operation		blendOp;
	BlendType			srcBlendAlpha;
	BlendType			destBlendAlpha;
	Blend_Operation		blendOpAlpha;
	u8					renderTargetWriteMask;
};

struct DepthStencil_OperationDesc {
	Stencil_Operation stencilFailOp;
	Stencil_Operation stencilDepthFailOp;
	Stencil_Operation stencilPassOp;
};

struct RenderState {
public: 
	virtual RenderStateType getRenderStateType() = 0;
};

struct RenderState_Rasterizer : RenderState {
public:
	RenderFillMode	fillMode;
	RenderCullMode	cullMode;
	bool			frontCounterClockwise;
	int				depthBias;
	float			depthBiasClamp;
	float			slopeScaledDepthBias;
	bool			depthClipEnable;
	bool			scissorEnable;
	bool			multisampleEnable;
	bool			antialiasedLineEnable;

	RenderStateType getRenderStateType() override { return RenderStateType::Rasterizer; }
};

struct RenderState_DepthStencil : RenderState {
public:
	bool						depthEnable;
	DepthWriteMask				depthWriteMask;
	DepthComparisonMode			depthMode;
	bool						stencilEnable;
	u8							stencilReadMask;
	u8							stencilWriteMask;
	DepthStencil_OperationDesc	frontFace;
	DepthStencil_OperationDesc	backFace;

	RenderStateType getRenderStateType() override { return RenderStateType::DepthStencil; }
};

struct RenderState_Blend : public RenderState {
public:
	bool				alphaToCoverageEnable;
	bool				independentBlendEnable;
	//Struct
	RenderTargetBlend	renderTarget[8];

	RenderStateType getRenderStateType() override { return RenderStateType::Blend; }

};



} //namespace
