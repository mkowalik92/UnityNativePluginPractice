#include <d3d11.h>

#include "Debug.h"

#include "UnityPluginAPI/IUnityGraphics.h"
#include "UnityPluginAPI/IUnityInterface.h"
#include "UnityPluginAPI/IUnityGraphicsD3D11.h"

int count = 0;

// Uncomment the includes below if not including Debug.h
//#include <stdio.h>
//#include <string>
//#include <sstream>

static IUnityInterfaces* s_UnityInterfaces = nullptr;
static IUnityGraphics* s_Graphics = nullptr;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;
static ID3D11Device* m_Device;

// Directx11

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
	s_UnityInterfaces = unityInterfaces;
	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	switch (eventType)
	{
	case kUnityGfxDeviceEventInitialize:
	{
		s_DeviceType = s_Graphics->GetRenderer();
		//IUnityGraphicsD3D11* d3d = s_UnityInterfaces->Get<IUnityGraphicsD3D11>();
		//m_Device = d3d->GetDevice();
		break;
	}
	case kUnityGfxDeviceEventShutdown:
	{
		s_DeviceType = kUnityGfxRendererNull;
		break;
	}
	case kUnityGfxDeviceEventBeforeReset:
	{
		break;
	}
	case kUnityGfxDeviceEventAfterReset:
	{
		break;
	}
	}
}

void AddToCount()
{
	count++;
}

static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	//std::ostringstream output;
	//output << "OnRenderEvent Count = " << count;
	//count++;
	//Debug::Log(output.str(), Color::Green);
	Debug::Log("LOL", Color::Orange);

	//AddToCount();
}

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
	return OnRenderEvent;
}