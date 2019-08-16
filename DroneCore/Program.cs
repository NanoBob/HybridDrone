﻿using Drone.Core.AuthorizationHandlers;
using Drone.Core.Controllers;
using Drone.Core.Interfaces;
using Drone.Wrapper.Dotnet;
using System;
using System.IO;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;

namespace Drone.Core
{
    class Program
    {
        private readonly WebServer webserver;
        private readonly Wrapper.Dotnet.Drone drone;

        public Program()
        {
            try
            {
                this.drone = new Wrapper.Dotnet.Drone();

                webserver = new WebServer("http", "*", 6606);

                AddActions();

                drone.Init();
                drone.StartOrientationThread();

                webserver.AddAuthorizationMethod(new TimeBasedHmacAuthorizationHandler("mySecret", new TimeSpan(0, 0, 3), 1));
                webserver.Start();
            } catch (Exception exception)
            {
                Console.WriteLine($"{exception.Message}\n{exception.StackTrace}");
            }
        }

        private void AddActions()
        {
            Console.WriteLine("Adding actions");

            var targetInterface = typeof(IController);
            var types = AppDomain.CurrentDomain.GetAssemblies()
                .SelectMany(s => s.GetTypes())
                .Where(p => targetInterface.IsAssignableFrom(p) && !p.IsInterface && !p.IsAbstract);

            foreach (Type type in types)
            {
                Console.WriteLine($"Loading {type.Name}");
                IController controller = (IController)Activator.CreateInstance(type);
                controller.AddRoutes(webserver, drone);
            }
        }

        static void Main(string[] args)
        {
            try
            {
                new Program();

                Thread.Sleep(-1);
            } catch (Exception e)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(e.Message);
                Console.WriteLine(e.StackTrace);
                Console.ForegroundColor = ConsoleColor.Gray;
            }
        }
    }
}
