using System;
using System.Collections.Generic;
using System.Text;

namespace Drone.Wrapper.Dotnet
{
    public struct Orientation
    {
        public float Yaw { get; set; }
        public float Pitch { get; set; }
        public float Roll { get; set; }

        public Orientation(float yaw, float pitch, float roll)
        {
            this.Yaw = yaw;
            this.Pitch = pitch;
            this.Roll = roll;
        }
    }
}
