////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "timerclass.h"
#include "shadermanagerclass.h"
#include "positionclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "modelclass.h"
#include "bumpmodelclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"
#include "RenderTextureClass.h"
#include "ReflectionShaderClass.h"
#include "firemodelclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	//bool Render(float);
	//Xu
	bool HandleMovementInput(float);
	bool Render();
	//bool RenderToTexture();
	int xMouseDelta;
	int yMouseDelta;

private:
	float mouseX;
	float mouseY;
	bool startWarp;
	InputClass* m_Input;
	D3DClass* m_D3D;
	TimerClass* m_Timer;
	ShaderManagerClass* m_ShaderManager;
	PositionClass* m_Position;
	CameraClass* m_Camera;
	LightClass* m_Light;
	ModelClass* m_MoonOrbit;
	FireModelClass* m_DeathStar;
	BumpModelClass* m_CWShipOrbit;
	BumpModelClass* m_ACWShipOrbit;
	ModelClass* m_PlanetOrbit;
	ModelClass* m_SpaceSphere;
	ModelClass* m_WarpShip1;
	ModelClass* m_WarpShip2;
	ModelClass* m_MoonSat;
	ModelClass* m_OddOrbit;

	RenderTextureClass* m_RenderTexture;
	TextureShaderClass* m_TextureShader;

	ParticleShaderClass* m_ParticleShader;
	particlesystemclass* m_ParticleSystem;
	ReflectionShaderClass* m_ReflectionShader;
};

#endif