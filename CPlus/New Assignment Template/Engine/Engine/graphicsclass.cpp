////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <math.h> 

GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;
	//Background Moon
	m_Model1 = 0;
	//Deathstar
	m_Model2 = 0;
	//Clockwise Ship
	m_Model3 = 0;
	//Anticlockwise Ship
	m_Model4 = 0;
	//Background Planet
	m_Model5 = 0;
	//Background Sky
	m_Model6 = 0;
	//Passing Ship
	m_Model7 = 0;
	//Moon Satellite
	m_Model8 = 0;
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
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

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
	m_Model1 = new ModelClass;
	if(!m_Model1)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/stone.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the second model object.
	m_Model2 = new ModelClass;
	if(!m_Model2)
	{
		return false;
	}

	// Initialize the second model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/deathstar.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the third bump model object for models with normal maps and related vectors.
	m_Model3 = new BumpModelClass;
	if(!m_Model3)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_Model3->Initialize(m_D3D->GetDevice(), "../Engine/data/viper.txt", L"../Engine/data/metal.dds", 
								  L"../Engine/data/metal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}

	//Create fourth bump model
	m_Model4 = new BumpModelClass;
	if (!m_Model4)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_Model4->Initialize(m_D3D->GetDevice(), "../Engine/data/viper.txt", L"../Engine/data/marble.dds",
		L"../Engine/data/stone.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fourth model object.", L"Error", MB_OK);
		return false;
	}
	//Create the 5th model object
	m_Model5 = new ModelClass;
	if (!m_Model5)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model5->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/marble.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fifth model object.", L"Error", MB_OK);
		return false;
	}
	//Create the 6th model object
	m_Model6 = new ModelClass;
	if (!m_Model6)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model6->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/metal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sixth model object.", L"Error", MB_OK);
		return false;
	}
	m_Model7 = new ModelClass;
	if (!m_Model7)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model7->Initialize(m_D3D->GetDevice(), "../Engine/data/viper.txt", L"../Engine/data/metal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the seventh model object.", L"Error", MB_OK);
		return false;
	}

	m_Model8 = new ModelClass;
	if (!m_Model8)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model8->Initialize(m_D3D->GetDevice(), "../Engine/data/planet.txt", L"../Engine/data/stone.dds");
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
	if(m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	if(m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	if(m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}
	if (m_Model4)
	{
		m_Model4->Shutdown();
		delete m_Model4;
		m_Model4 = 0;
	}
	if (m_Model5)
	{
		m_Model5->Shutdown();
		delete m_Model5;
		m_Model5 = 0;
	}
	if (m_Model6)
	{
		m_Model6->Shutdown();
		delete m_Model6;
		m_Model6 = 0;
	}
	if (m_Model7)
	{
		m_Model7->Shutdown();
		delete m_Model7;
		m_Model7 = 0;
	}
	if (m_Model8)
	{
		m_Model8->Shutdown();
		delete m_Model8;
		m_Model8 = 0;
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
	float mouseH = m_Input->getMouseDeltaX();
	float mouseV = m_Input->getMouseDeltaY();
	//rotX += mouseV;
	//rotY += mouseH;
	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

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

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();
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
	translateMatrix = XMMatrixTranslation(((cos(rotation/4) * 20)-(sin(rotation/2)*4)), 5.0f, (sin(rotation/4)*20)-(cos(rotation/2)*4));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model1->GetTexture());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the second model. Foreground Planet Death Star
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	worldMatrix *= XMMatrixRotationX(64);
	worldMatrix *= XMMatrixRotationY(rotation);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 0.0f));

	// Render the second model using the light shader.
	m_Model2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									   m_Model2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
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
	translateMatrix = XMMatrixTranslation(cos(rotation) * 6,0.5f, sin(rotation) * 6);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the third model using the bump map shader. ACW Orbiting ship
	m_Model3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model3->GetColorTexture(), m_Model3->GetNormalMapTexture(), m_Light->GetDirection(), 
												  m_Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	//Set up fourth model Close orbiting ship
	m_Model4->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model4->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model4->GetColorTexture(), m_Model4->GetNormalMapTexture(), m_Light->GetDirection(),
		m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}
	//Model4 positions
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.5f, 0.5f, 0.5f));
	worldMatrix *= XMMatrixRotationY(2*rotation);
	worldMatrix *= XMMatrixRotationZ(-sin(2*rotation));
	worldMatrix *= XMMatrixRotationX(cos(2*rotation));
	translateMatrix = XMMatrixTranslation(-sin(2 * rotation)*4,-0.5f, -cos(2 * rotation)*4);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the fourth model using the bump map shader. CW Orbiting Ship
	m_Model4->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model4->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model4->GetColorTexture(), m_Model4->GetNormalMapTexture(), m_Light->GetDirection(),
		m_Light->GetDiffuseColor());

	// Setup the rotation and translation of the fifth model. Background Planet
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.0f, 1.0f, 1.0f));

	worldMatrix *= XMMatrixRotationZ(rotation);
	worldMatrix *= XMMatrixRotationY(rotation);

	worldMatrix *= XMMatrixTranslation((cos(rotation / 4) * 20), 5.0f, (sin(rotation / 4) * 20));

	// Render the fifth model using the texture shader. Background Planet
	m_Model5->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model5->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model5->GetTexture());
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
	m_Model6->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model6->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model6->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the seventh model. Warping XWing
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.4f, 0.4f, 0.4f));
	worldMatrix *= XMMatrixTranslation(-tan(rotation/2-150), 2.5f, 10.0f);
	
	// Render the sixth model using the texture shader. Warping XWing
	m_Model7->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model7->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model7->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the eigth model. Background Moon Satellite
	worldMatrix = XMMatrixScaling(0.25f, 0.25f, 0.25f);
	worldMatrix *= XMMatrixRotationY(rotation / 4);
	worldMatrix *= XMMatrixRotationZ(rotation / 4);
	translateMatrix = XMMatrixTranslation(((cos(rotation / 4) * 20) - (sin(rotation / 2) * 4)), sin(rotation)+5, (sin(rotation / 4) * 20) - (cos(rotation / 2) * 4)-cos(rotation));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the eigth model using the texture shader. Background Moon Satellite
	m_Model8->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model8->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model8->GetTexture());
	if (!result)
	{
		return false;
	}
	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}