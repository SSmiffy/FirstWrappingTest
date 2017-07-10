#include "stdafx.h"
#include "UATest1.h"
//#include <WinSock2.h>

using namespace System::Runtime::InteropServices;

namespace W7KWrapper
{
	UATest1::UATest1()
	{
		this->regAgent = nullptr;
		this->UA = nullptr;

		this->BAL = new BasicAgentListener();
		_setting = gcnew Generic::Dictionary<int, String^>();
	}


	UATest1::~UATest1()
	{
	}

	void UATest1::AddSetting(int key, String^ value)
	{
		if (_setting->ContainsKey(key))
		{
			_setting[key] = value;
		}
		else
		{
			_setting->Add(key, value);
		}
	}
	//Generic::IDictionary<String^, String^> UATest1::Settings::get() {
	//		return _setting;
	//	}


	void UATest1::Initialise(String^ dataPath )
	{

	/*	WSADATA wsaData;
		int wsa_err = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (wsa_err != 0)
		{
			UAInformation(BasicAgentListener::BasicAgentListenerState::Undefined, "WSAStartup Failed");
			return;
		}
*/
		auto initRes = BAL->initialise();

		if (initRes != 0)
		{
			return;
		}

		auto path = (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(dataPath);
		UA = UserAgentFactory::createInstance(path);

		Settings settings;
		FillSettings(settings);


		if (UA != nullptr)
		{
			this->managedTokenDelegate = gcnew ManagedAccessTokenCallBack(this, &UATest1::TokenCallBack);
			this->unmanagedTokenDelegatePtr = Marshal::GetFunctionPointerForDelegate(this->managedTokenDelegate);
			BAL->SetTokenCallBack((BasicAgentListener::TokenCallbackFunc) unmanagedTokenDelegatePtr.ToPointer());

			this->managedInfoDelegate = gcnew ManagedInfoCallBack(this, &UATest1::InfoCallback);
			this->unmanagedInfoDelegatePtr = Marshal::GetFunctionPointerForDelegate(this->managedInfoDelegate);
			BAL->SetInfoCallBack((BasicAgentListener::InfoCallbackFunc) unmanagedInfoDelegatePtr.ToPointer());

			regAgent = UA->getRegistrationAgent();
			BAL->SetRegistrationAgentCallBack(regAgent);

			pttAgent = UA->getPttAgent();
			logAgent = UA->getLoggingAgent();
			scanAgent = UA->getScanAgent();
			contactsAgent = UA->getContactsAgent();

			regAgent->attachListener(BAL);
			pttAgent->attachListener(BAL);
			logAgent->attachListener(BAL);
			contactsAgent->attachListener(BAL);
			scanAgent->attachListener(BAL);

			auto inf = UA->pushSettings(settings);

			//auto ptrToken = (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Configuration::ConfigurationManager::AppSettings["TOKEN"]);

			//regAgent->setAccessToken(ptrToken);
			auto regInfo = regAgent->activateAndRegister();

		}
	}

	void UATest1::TearDown()
	{
		if (this->regAgent != nullptr)
		{
			auto tearDownres = regAgent->deregisterAndDeactivate();
		}

		if (this->UA != nullptr)
		{
			UserAgentFactory::destroyInstance(UA);
		}
	}

	void UATest1::AddTalkgroupToMonitor(String^ tg)
	{
		// get current scan list and add the new one.
		auto sl = ScanList();

		ScanListArchive* sla = scanAgent->getScanListArchive();
		ScanListArchive::AliasList list = sla->getAliasList();
		for (int i = 0; i < list.size(); i++)
		{
			const char* name = list.get(i);
			String^ TGAlias = gcnew String(name);
			UAInformation(BasicAgentListener::BasicAgentListenerState::Undefined,TGAlias);
			// Add the alias to a list that the user will see in some UI.
			//addToUIList(list.get(i));
		}

		auto info = scanAgent->selectScanList(sl);

	}

	void UATest1::FillSettings(Settings settings)
	{
		for each (auto var in _setting)
		{
			auto configValue = (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(var.Value);
			settings.add(var.Key, configValue);
		}
	}

	String^ UATest1::TokenCallBack()
	{
		auto returnedToken = AccessTokenRequired();
		UAInformation(BasicAgentListener::BasicAgentListenerState::Undefined, returnedToken);
		return returnedToken;
	}

	void UATest1::InfoCallback(BasicAgentListener::BasicAgentListenerState UAState, String^ strinfo)
	{
		UAInformation(UAState, strinfo);
		//System::Diagnostics::Debug::WriteLine("Well that's somthing");
	}


}

