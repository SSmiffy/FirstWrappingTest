#include "stdafx.h"
#include "UATest1.h"

using namespace System::Runtime::InteropServices;

namespace W7KWrapper
{
	UATest1::UATest1()
	{
		this->BAL = new BasicAgentListener();
		_setting = gcnew Generic::Dictionary<int, String^>();
	}


	UATest1::~UATest1()
	{
	}

	void UATest1::ThisOne(int number)
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
		auto path = (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(dataPath);
		UA = UserAgentFactory::createInstance(path);

		Settings settings;
		FillSettings(settings);


		if (UA != nullptr)
		{
			this->managedDelegate = gcnew ManagedCallBack(this, &UATest1::callbacktes1);
			this->unmanagedDelegatePtr = Marshal::GetFunctionPointerForDelegate(this->managedDelegate);


			BAL->SetCallBack((BasicAgentListener::callbackfunc) unmanagedDelegatePtr.ToPointer());
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

	void UATest1::FillSettings(Settings settings)
	{
		for each (auto var in _setting)
		{
			auto configValue = (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(var.Value);
			settings.add(var.Key, configValue);
		}
	}

	void UATest1::callbacktes1(int value)
	{
		System::Diagnostics::Debug::WriteLine("Well that's somthing");
	}

}