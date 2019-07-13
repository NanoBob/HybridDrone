using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace Drone.Wrapper.Cpp
{
    internal static class CppWrapper
    {
        private const string dllName = "DroneCpp";

        [DllImport(dllName, EntryPoint = "init")]
        public static extern void Init();

        // Motors

        [DllImport(dllName, EntryPoint = "setYaw")]
        public static extern void SetYaw(float value);

        [DllImport(dllName, EntryPoint = "setPitch")]
        public static extern void setPitch(float value);

        [DllImport(dllName, EntryPoint = "setRoll")]
        public static extern void SetRoll (float value);

        [DllImport(dllName, EntryPoint = "setThrottle")]
        public static extern void SetThrottle(float value);


        // Orientation

        [DllImport(dllName, EntryPoint = "startOrientationThread")]
        public static extern void StartOrientationThread();

        [DllImport(dllName, EntryPoint = "stopOrientationThread")]
        public static extern void StopOrientationThread();

        [DllImport(dllName, EntryPoint = "setTargetOrientation")]
        public static extern void SetTargetOrientation(float yaw, float pitch, float roll);

        [DllImport(dllName, EntryPoint = "getOrientation")]
        public static extern void GetOrientation(out float yaw, out float pitch, out float roll);



    }

}
