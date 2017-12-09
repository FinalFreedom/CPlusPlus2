////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <math.h> 

GraphicsClass::GraphicsClass()
{
	startWarp = false;

	mouseX = 0;
	mouseY = 0;
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;

	//Rendered objects
	m_MoonOrbit = 0;
	m_DeathStar = 0;
	m_CWShipOrbit = 0;
	m_ACWShipOrbit = 0;
	m_PlanetOrbit = 0;
	m_SpaceSphere = 0;
	m_WarpShip1 = 0;
	m_WarpShip2 = 0;
	m_MoonSat = 0;
	m_OddOrbit = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	// Create the model object.
	m_MoonOrbit = new ModelClass;
	if(!m_MoonOrbit)
	{
		return false;
	}

	// Initialize the model object.
	result = m_MoonOrbit->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/marble.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the second model object.
	m_DeathStar = new ModelClass;
	if(!m_DeathStar)
	{
		return false;
	}

	// Initialize the second model object.
	result = m_DeathStar->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/deathstar.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the third bump model object for models with normal maps and related vectors.
	m_CWShipOrbit = new BumpModelClass;
	if(!m_CWShipOrbit)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_CWShipOrbit->Initialize(m_D3D->GetDevice(), "../Engine/data/viper.txt", L"../Engine/data/stone.dds", 
								  L"../Engine/data/normal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}

	//Create fourth bump model
	m_ACWShipOrbit = new BumpModelClass;
	if (!m_ACWShipOrbit)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_ACWShipOrbit->Initialize(m_D3D->GetDevice(), "../Engine/data/viper.txt", L"../Engine/data/metal.dds",
		L"../Engine/data/stone.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fourth model object.", L"Error", MB_OK);
		return false;
	}
	//Create the 5th model object
	m_PlanetOrbit = new ModelClass;
	if (!m_PlanetOrbit)
	{
		return false;
	}

	// Initialize the model object.
	result = m_PlanetOrbit->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/plainworld.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fifth model object.", L"Error", MB_OK);
		return false;
	}
	//Create the 6th model object
	m_SpaceSphere = new ModelClass;
	if (!m_SpaceSphere)
	{
		return false;
	}

	// Initialize the model object.
	result = m_SpaceSphere->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/stars6.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sixth model object.", L"Error", MB_OK);
		return false;
	}
	m_WarpShip1 = new ModelClass;
	if (!m_WarpShip1)
	{
		return false;
	}
	m_WarpShip2 = new ModelClass;
	if (!m_WarpShip2)
	{
		return false;
	}
	m_OddOrbit = new ModelClass;
	if (!m_OddOrbit)
	{
		return false;
	}

	// Initialize the model object.
	result = m_OddOrbit->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/stone.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fifth model object.", L"Error", MB_OK);
		return false;
	}
	// Initialize the model object.
	result = m_WarpShip1->Initialize(m_D3D->GetDevice(), "../Engine/data/xwing2.txt", L"../Engine/data/stone.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the seventh model object.", L"Error", MB_OK);
		return false;
	}

	result = m_WarpShip2->Initialize(m_D3D->GetDevice(), "../Engine/data/xwing2.txt", L"../Engine/data/marble.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the seventh model object.", L"Error", MB_OK);
		return false;
	}

	m_MoonSat = new ModelClass;
	if (!m_MoonSat)
	{
		return false;
	}

	// Initialize the model object.
	result = m_MoonSat->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/marble.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the eigth model object.", L"Error", MB_OK);
		return false;
	}
	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model objects.
	if(m_MoonOrbit)
	{
		m_MoonOrbit->Shutdown();
		delete m_MoonOrbit;
		m_MoonOrbit = 0;
	}

	if(m_DeathStar)
	{
		m_DeathStar->Shutdown();
		delete m_DeathStar;
		m_DeathStar = 0;
	}

	if(m_CWShipOrbit)
	{
		m_CWShipOrbit->Shutdown();
		delete m_CWShipOrbit;
		m_CWShipOrbit = 0;
	}
	if (m_ACWShipOrbit)
	{
		m_ACWShipOrbit->Shutdown();
		delete m_ACWShipOrbit;
		m_ACWShipOrbit = 0;
	}
	if (m_PlanetOrbit)
	{
		m_PlanetOrbit->Shutdown();
		delete m_PlanetOrbit;
		m_PlanetOrbit = 0;
	}
	if (m_SpaceSphere)
	{
		m_SpaceSphere->Shutdown();
		delete m_SpaceSphere;
		m_SpaceSphere = 0;
	}
	if (m_WarpShip1)
	{
		m_WarpShip1->Shutdown();
		delete m_WarpShip1;
		m_WarpShip1 = 0;
	}
	if (m_WarpShip2)
	{
		m_WarpShip2->Shutdown();
		delete m_WarpShip2;
		m_WarpShip2 = 0;
	}
	if (m_MoonSat)
	{
		m_MoonSat->Shutdown();
		delete m_MoonSat;
		m_MoonSat = 0;
	}
	if (m_OddOrbit)
	{
		m_OddOrbit->Shutdown();
		delete m_OddOrbit;
		m_OddOrbit = 0;
	}
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime) //INPUT
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;
	//rotX += mouseV;
	//rotY += mouseH;
	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsAPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsDPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsSpacePressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsLShiftPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	mouseY = m_Input->getMouseDeltaY();
	mouseX = m_Input->getMouseDeltaX();

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	keyDown = m_Input->IsEPressed();
	if (keyDown)
	{
		startWarp = true;
	}
	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;

	static float rotation = 0.0f;


	static float trigger = 0.0f;
	static float pressed = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	if (m_Input->IsQPressed())
	{
		pressed += (float)XM_PI * 0.0005f * m_Timer->GetTime();
	}

	//There is a SLIGHT jump in the animation as the ship re-enters the scene to stationary
	if (tan(trigger / 2 - 150) <= 0.001 && tan(trigger / 2 - 150) >= -0.001)
	{
		startWarp = false;
		trigger = 0;
	}
	//trigger only updates while the warp effect is wanted
	if (startWarp)
	{
		trigger += (float)XM_PI * 0.0005f * m_Timer->GetTime();
	}
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);


	// Setup the rotation and translation of the first model. Background Orbiting Moon
	worldMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	worldMatrix *= XMMatrixRotationZ(rotation/2);
	worldMatrix *= XMMatrixRotationX(rotation/2);
	translateMatrix = XMMatrixTranslation(((cos(rotation/4) * 20)-(sin(rotation/2)*8)), 5.0f, (sin(rotation/4)*20)-(cos(rotation/2)*7));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_MoonOrbit->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_MoonOrbit->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_MoonOrbit->GetTexture());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the second model. Foreground Planet Death Star
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(2.0f, 2.0f, 2.0f));
	worldMatrix *= XMMatrixRotationX(-30);
	worldMatrix *= XMMatrixRotationY(rotation/4+pressed/4);
	worldMatrix *= XMMatrixTranslation(0.0f, sin(rotation)/4, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 0.0f));

	// Render the second model using the light shader.
	m_DeathStar->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_DeathStar->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									   m_DeathStar->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
									   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the third model. Far orbiting ship
	m_D3D->GetWorldMatrix(worldMatrix);
	//Previously would only rotate or scale, multiplying the two matricies fixes this
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.25f, 0.25f, 0.25f));
	worldMatrix *= XMMatrixRotationY(90-rotation);
	worldMatrix *= XMMatrixRotationZ(sin(90-rotation));
	worldMatrix *= XMMatrixRotationX(-cos(90-rotation));
	translateMatrix = XMMatrixTranslation(cos(rotation) * 5,0.5f, sin(rotation) * 5);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the third model using the bump map shader. ACW Orbiting ship
	m_CWShipOrbit->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_CWShipOrbit->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_CWShipOrbit->GetColorTexture(), m_CWShipOrbit->GetNormalMapTexture(), m_Light->GetDirection(), 
												  m_Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	//Set up fourth model Close orbiting ship
	m_ACWShipOrbit->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_ACWShipOrbit->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ACWShipOrbit->GetColorTexture(), m_ACWShipOrbit->GetNormalMapTexture(), m_Light->GetDirection(),
		m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}
	//ACWShipOrbit positions
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.5f, 0.5f, 0.5f));
	worldMatrix *= XMMatrixRotationY(rotation/2);
	worldMatrix *= XMMatrixRotationZ(-sin(rotation/2));
	worldMatrix *= XMMatrixRotationX(cos(rotation/2));
	translateMatrix = XMMatrixTranslation(-sin(rotation/2)*8,-0.5f, -cos(rotation/2)*8);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the fourth model using the bump map shader. CW Orbiting Ship
	m_ACWShipOrbit->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_ACWShipOrbit->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ACWShipOrbit->GetColorTexture(), m_ACWShipOrbit->GetNormalMapTexture(), m_Light->GetDirection(),
		m_Light->GetDiffuseColor());

	// Setup the rotation and translation of the fifth model. Background Planet
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(2.50f, 2.50f, 2.50f));
	worldMatrix *= XMMatrixRotationX(90);
	worldMatrix *= XMMatrixRotationY(rotation);

	worldMatrix *= XMMatrixTranslation((cos(rotation / 4) * 20), 5.0f, (sin(rotation / 4) * 20));

	// Render the fifth model using the texture shader. Background Planet
	m_PlanetOrbit->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_PlanetOrbit->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_PlanetOrbit->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the sixth model. Star skybox
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(-50.0f, -50.0f, -50.0f));
	worldMatrix *= XMMatrixRotationX(90);
	worldMatrix *= XMMatrixRotationY(rotation/50);
	worldMatrix *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	// Render the sixth model using the texture shader. Star skysphere
	m_SpaceSphere->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_SpaceSphere->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SpaceSphere->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the seventh model. Warping XWing
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.4f, 0.4f, 0.4f));
	worldMatrix *= XMMatrixRotationZ(sin(rotation)/16);
	worldMatrix *= XMMatrixRotationY(165);

	worldMatrix *= XMMatrixTranslation(10- tan(trigger / 2 - 150), 2 + sin(-rotation) / 16, 10 + cos(rotation) / 32);
	
	// Render the eigth model using the texture shader. Warping XWing
	m_WarpShip1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_WarpShip1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_WarpShip1->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.4f, 0.4f, 0.4f));
	worldMatrix *= XMMatrixRotationZ(cos(rotation/2) / 16);
	worldMatrix *= XMMatrixRotationY(165);

	worldMatrix *= XMMatrixTranslation(11 - tan(trigger / 2 - 150)/2, 1 + sin(-rotation) / 32, 11 + cos(-rotation) / 16);

	// Render the eigth model using the texture shader. Warping XWing
	m_WarpShip2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_WarpShip2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_WarpShip2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the ninth model. Background Moon Satellite
	worldMatrix = XMMatrixScaling(.25f, .25f, 0.25f);
	worldMatrix *= XMMatrixRotationY(rotation / 4);
	worldMatrix *= XMMatrixRotationZ(rotation / 4);
	translateMatrix = XMMatrixTranslation(((cos(rotation / 4) * 20) - (sin(rotation / 2) * 8)+cos(rotation)*2), sin(rotation)+5,
		(sin(rotation / 4) * 20) - (cos(rotation / 2) * 7)-cos(rotation));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the ninth model using the texture shader. Background Moon Satellite
	m_MoonSat->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_MoonSat->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_MoonSat->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the ninth model. Background Planet
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.50f, 0.50f, 0.50f));
	worldMatrix *= XMMatrixRotationX(90);
	worldMatrix *= XMMatrixRotationY(rotation);

	worldMatrix *= XMMatrixTranslation((cos(90+rotation / 4) * 20), sin(rotation/4)*10, (sin(90+rotation / 4) * 20));

	// Render the fifth model using the texture shader. Background Planet
	m_OddOrbit->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_OddOrbit->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_OddOrbit->GetTexture());
	if (!result)
	{
		return false;
	}
	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}