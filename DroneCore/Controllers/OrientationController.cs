using System;
using System.Collections.Generic;
using System.Text;
using Drone.Core.Interfaces;
using Drone.Wrapper.Dotnet;

namespace Drone.Core.Controllers
{
    public class OrientationController : IController
    {
        public void AddRoutes(WebServer webserver, Wrapper.Dotnet.Drone drone)
        {
            webserver.AddAction("GET", "/orientation", (context) =>
            {
                Orientation orientation = drone.Orientation;
                return new
                {
                    yaw = orientation.Yaw,
                    pitch = orientation.Pitch,
                    roll = orientation.Roll,
                };
            });

            webserver.AddAction("POST", "/orientation", (context) =>
            {
                drone.StartOrientationThread();
                return new
                {
                    message = "Orientation sensor enabled"
                };
            });

            webserver.AddAction("DELETE", "/orientation", (context) =>
            {
                drone.StartOrientationThread();
                return new
                {
                    message = "Orientation sensor disabled"
                };
            });

            webserver.AddAction("POST", "/orientationAssist", (context) =>
            {
                drone.StartOrientationAssist();
                return new
                {
                    message = "Orientation assist enabled"
                };
            });

            webserver.AddAction("DELETE", "/orientationAssist", (context) =>
            {
                drone.StopOrientationAssist();
                return new
                {
                    message = "Orientation assist disabled"
                };
            });
        }
    };
}