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
            set => CppWrapper.SetTargetOrientation(value.Yaw, value.Pitch, value.Roll);
        }

        public float MotorThrottle
        {
            set => CppWrapper.SetThrottle(value);
        }



    }
}
