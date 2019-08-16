using Drone.Wrapper.Cpp;
using System;
using System.Collections.Generic;
using System.Text;

namespace Drone.Wrapper.Dotnet
{
    public class Drone
    {
        public Orientation Orientation
        {
            get
            {
                CppWrapper.GetOrientation(out float yaw, out float pitch, out float roll);
                return new Orientation(yaw, pitch, roll);
            }
        }

        private Orientation targetOrientation = new Orientation(0, 0, 0);
        public Orientation TargetOrientation
        {
            get => targetOrientation;
            set
            {
                targetOrientation = value;
                CppWrapper.SetTargetOrientation(value.Yaw, value.Pitch, value.Roll);
            }
        }

        public Tuple<float, float, float, float> GetMotorThrottles()
        {
            CppWrapper.GetMotorThrottles(out float frontLeft, out float frontRight, out float rearLeft, out float rearRight);
            return new Tuple<float, float, float, float>(frontLeft, frontRight, rearLeft, rearRight);
        }

        public float MotorThrottle
        {
            set => CppWrapper.SetThrottle(value);
        }

        public Drone()
        {

        }

        public void Init() => CppWrapper.Init();

        public void StartOrientationThread() => CppWrapper.StartOrientationThread();

        public void StopOrientationThread() => CppWrapper.StopOrientationThread();

        public void StartOrientationAssist() => CppWrapper.StartOrientationAssist();

        public void StopOrientationAssist() => CppWrapper.StopOrientationAssist();

        public void RunTest(float value) => CppWrapper.RunTest(value);

        public void EnableMotors() => CppWrapper.EnableMotors();

        public void DisableMotors() => CppWrapper.DisableMotors();

    }
}
