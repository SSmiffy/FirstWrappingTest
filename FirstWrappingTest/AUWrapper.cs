using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FirstWrappingTest
{
    public class AUWrapper
    {
        protected IntPtr UA;
        public AUWrapper()
        {
            UA = IntPtr.Zero;
            
        }


        [StructLayout(LayoutKind.Sequential)]
        public struct WSAData
        {
            public short version;
            public short highVersion;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 257)]
            public string description;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 129)]
            public string systemStatus;
            public short maxSockets;
            public short maxUdpDg;
            public IntPtr vendorInfo;
        }

        [DllImport("Ws2_32.dll")]
        public static extern Int32 WSAStartup(short wVersionRequested, ref WSAData wsaData);

        [DllImport("Ws2_32.dll")]
        public static extern Int32 WSACleanup();

        //public static void Test()
        //{
        //    WSAData dummy = new WSAData();
        //    NativeMethods.WSAStartup(0x0202, ref dummy);
        //    // TODO: more stuff
        //    NativeMethods.WSACleanup();
        //}

        //[DllImport("Ws2_32.dll")]
        //int wsa_err = WSAStartup(MAKEWORD(2, 2), &wsaData);
        //    if (wsa_err != 0)
        //{
        //    Console::WriteLine(L"WSAStartup Failed");
        //    return 1;
        //}

    public void initialise()
    {
        WSAData dummy = new WSAData();
        int wsa_err = WSAStartup(0x0202, ref dummy);
        if (wsa_err != 0)
        {
            throw new InvalidOperationException("Failed to initialise WSA socksts");
        }
    }

    //[DllImport("User32.dll", CharSet = CharSet.Unicode)]
    //[System.Runtime.InteropServices.DllImportAttribute("W7K_UA_SDK.DLL", EntryPoint = "?createInstance@UserAgentFactory@@SAPAVUserAgent@@PBD@Z", CallingConvention = CallingConvention.Winapi)]
    [DllImport("W7K_UA_SDK.DLL", EntryPoint = "?createInstance@UserAgentFactory@@SAPAVUserAgent@@PBD@Z",
            CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern IntPtr createInstance(string path);

        public void CreateUAInstance(string path)
        {
            UA = createInstance(path);
        }

        [DllImport("W7K_UA_SDK.DLL", EntryPoint = "?destroyInstance@UserAgentFactory@@SAXPAVUserAgent@@@Z",
            CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern IntPtr destroyInstance(IntPtr userAgent);

        public void DestroyUAInstance()
        {
            if (UA != IntPtr.Zero)
            {
                destroyInstance(UA);
            }
            
        }

     
        public void SetupConfig()
        {
            
        }

    }
}
