using System;
using System.Collections.Generic;
using System.Text;

namespace Drone.Wrapper.Dotnet
{
    public struct Position
    {
        public float Longitude { get; set; }
        public float Latitude { get; set; }

        public Position(float longitude, float latitude)
        {
            this.Longitude = longitude;
            this.Latitude = latitude;
        }
    }
}
