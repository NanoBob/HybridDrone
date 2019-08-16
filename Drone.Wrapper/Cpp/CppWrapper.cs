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
        public static extern void SetPitch(float value);

        [DllImport(dllName, EntryPoint = "setRoll")]
        public static extern void SetRoll (float value);

        [DllImport(dllName, EntryPoint = "setThrottle")]
        public static extern void SetThrottle(float value);

        [DllImport(dllName, EntryPoint = "getMotorThrottles")]
        public static extern void GetMotorThrottles(out float frontLeft, out float frontRight, out float rearLeft, out float rearRight);

        [DllImport(dllName, EntryPoint = "runTest")]
        public static extern void RunTest(float value);

        [DllImport(dllName, EntryPoint = "enableMotors")]
        public static extern void EnableMotors();

        [DllImport(dllName, EntryPoint = "disableMotors")]
        public static extern void DisableMotors();


        // Orientation

        [DllImport(dllName, EntryPoint = "startOrientationThread")]
        public static extern void StartOrientationThread();

        [DllImport(dllName, EntryPoint = "stopOrientationThread")]
        public static extern void StopOrientationThread();

        [DllImport(dllName, EntryPoint = "startOrientationAssist")]
        public static extern void StartOrientationAssist();

        [DllImport(dllName, EntryPoint = "stopOrientationAssist")]
        public static extern void StopOrientationAssist();

        [DllImport(dllName, EntryPoint = "setTargetOrientation")]
        public static extern void SetTargetOrientation(float yaw, float pitch, float roll);

        [DllImport(dllName, EntryPoint = "getOrientation")]
        public static extern void GetOrientation(out float yaw, out float pitch, out float roll);



    }

}
