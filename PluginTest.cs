using AOT; // MonopInvokeCallback
using System;
using System.Runtime.InteropServices;
using UnityEngine;

public class PluginTest : MonoBehaviour
{

    private delegate void DebugCallback(IntPtr message, int color, int size);

    [DllImport("PluginPractice", CallingConvention = CallingConvention.Cdecl)]
    private static extern void RegisterDebugCallback(DebugCallback callback);

    [DllImport("PluginPractice")]
    private static extern IntPtr GetRenderEventFunc();


    void OnEnable()
    {
        RegisterDebugCallback(DebugLog);

    }

    void Update()
    {
        GL.IssuePluginEvent(GetRenderEventFunc(), 1);
    }
    
    void OnADestroy()
    {
        RegisterDebugCallback(null);
    }

    enum Color { red, green, blue, black, white, yellow, orange };
    //[MonoPInvokeCallback(typeof(DebugCallback))] // Needed for iOS
    private static void DebugLog(IntPtr message, int color, int size)
    {
        string debugString = Marshal.PtrToStringAnsi(message, size);
        debugString = String.Format("{0}{1}{2}{3}{4}",
                                    "<color=",
                                    ((Color)color).ToString(),
                                    ">",
                                    debugString,
                                    "</color>"
                                    );
        Debug.Log(debugString);
    }
}
