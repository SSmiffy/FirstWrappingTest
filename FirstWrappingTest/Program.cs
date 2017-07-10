using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using W7KWrapper;


namespace FirstWrappingTest
{
    class Program
    {
        private static TextWriter logStream;
        static void Main(string[] args)
        {
            logStream = new  StreamWriter(@"C:\Users\ssmith\Desktop\FileWrapper.txt") ;
            logStream.WriteLine($"************** log file opened {System.DateTime.Now.ToLocalTime()} **************");
            logStream.Flush();
            //var UA = new AUWrapper();
            //var AU = new AUWrapper();
            var UA = new UATest1();

            PopulateSettings(UA);

            try
            {
                UA.AccessTokenRequired += UA_token;
                UA.UAInformation += UA_UAInformation; ;
                UA.Initialise(Settings1.Default.Path);
                //UA.initialise();

                //var groupsToScan = new List<string>();
                //groupsToScan.Add("grpnice01");
                //groupsToScan.Add("grpnice02");
                //UA.SetupScanList(groupsToScan);

                UA.AddTalkgroupToMonitor("grpnice01");
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine(e);
                throw;
            }
            //UA.CreateUAInstance(Settings1.Default.Path);

            Console.WriteLine("Hit retrun to quit.....");
            Console.ReadLine();

            //UA.DestroyUAInstance();
            try
            {
                UA.TearDown();
                //UA.initialise();
                UA.AccessTokenRequired -= UA_token;
                UA.UAInformation -= UA_UAInformation; ;
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine(e);
                throw;
            }

            logStream.Dispose();
        }

        private static void UA_UAInformation(BasicAgentListener.BasicAgentListenerState uaState, string info)
        {
            logStream.WriteLine(info);
            logStream.Flush();
            //if (uaState == BasicAgentListener.BasicAgentListenerState .LOG_WARNING)
            //{
                
            //}
            Console.WriteLine($"** string info -> {info}");
        }

        private static string UA_token()
        {
            return Settings1.Default.LoginToken;
        }

        private static void PopulateSettings(UATest1 ua)
        {

            ua.AddSetting((int)W7KSDKAPI_Settings.nconfigvalue.SIP_SERVER_IP,Settings1.Default.SIP_SERVER_IP);
            ////settings.add(Settings::SIP_SERVER_PORT_UDP, "5060"); // default
            ////settings.add(Settings::SIP_SERVER_PORT_RSA, "443"); // default

            ua.AddSetting((int)W7KSDKAPI_Settings.nconfigvalue.PTT_ID,Settings1.Default.PTT_ID);
            //ua.AddSetting(Settings::PTT_ID, (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Configuration::ConfigurationManager::AppSettings["PTT_ID"]));
            ////settings.add(Settings::DEVICE_ID, (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Configuration::ConfigurationManager::AppSettings["DEVICE_ID"]));
            ua.AddSetting((int)W7KSDKAPI_Settings.nconfigvalue.DEVICE_ID, "00000000000000000000000000000000000000000000000000");
            ////settings.add(Settings::LOCAL_IP, (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Configuration::ConfigurationManager::AppSettings["LOCAL_IP"]));

            ua.AddSetting((int)W7KSDKAPI_Settings.nconfigvalue.LOG_LEVEL, W7KSDKAPI_Settings.LogLevel.LOG_VERBOSE.ToString());
            ua.AddSetting((int)W7KSDKAPI_Settings.nconfigvalue.LOG_DEST, W7KSDKAPI_Settings.LogDest.LOG_EVENT.ToString());

            ////settings.add(Settings::MAX_CALLS, "1"); // default
            ua.AddSetting((int) W7KSDKAPI_Settings.nconfigvalue.SIGNIN_MODE,W7KSDKAPI_Settings.SinginMode.MODE_ACCESSTOKEN.ToString());
        }
    }
}
