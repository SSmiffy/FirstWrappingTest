#pragma once

#include "BasicAgentListener.h"
#include <AgentFactory.h>
#include <RegistrationAgent.h>
#include <PttAgent.h>
#include <LoggingAgent.h>
#include <ContactsAgent.h>
#include <ScanAgent.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;

namespace W7KWrapper {

	//public enum class 

	public ref class W7KSDKAPI_Settings
	{
	public:
		enum class SinginMode { MODE_DEVICEAUTH = Settings::SigninMode::MODE_DEVICEAUTH, MODE_ACCESSTOKEN = Settings::SigninMode::MODE_ACCESSTOKEN, MODE_USERAUTH = Settings::SigninMode::MODE_USERAUTH};
		enum class LogLevel { LOG_NONE = Settings::LogLevel::LOG_NONE, LOG_ERROR = Settings::LogLevel::LOG_ERROR, LOG_WARNING = Settings::LogLevel::LOG_WARNING, LOG_INFO = Settings::LogLevel::LOG_INFO, LOG_VERBOSE = Settings::LogLevel::LOG_VERBOSE };
		enum class LogDest {
			/// Logs are printed to <i>stdout</i>.
			LOG_STDOUT = Settings::LogDest::LOG_STDOUT,
			/// Logs are printed to <i>stderr</i>.
			LOG_STDERR = Settings::LogDest::LOG_STDERR,
			/**
			* Logs are raised as an event to a listener.
			*
			* When this option is set, the UA will raise logs as an event.
			* This allows the application to handle logs in a custom manner
			* e.g. pipe to a file or use a platform specific logging mechanism.
			*
			* @sa LoggingAgentListener::notifyLog()
			*/
			LOG_EVENT = Settings::LogDest::LOG_EVENT
		};

		enum class nconfigvalue:int { SIP_SERVER_IP = Settings::SIP_SERVER_IP, 
			SIP_SERVER_PORT_UDP = Settings::SIP_SERVER_PORT_UDP, 
			SIP_SERVER_PORT_RSA = Settings::SIP_SERVER_PORT_RSA,
			PTT_ID = Settings::PTT_ID,
			DEVICE_ID = Settings::DEVICE_ID,
			LOCAL_IP = Settings::LOCAL_IP,
			LOG_LEVEL = Settings::LOG_LEVEL,
			LOG_DEST = Settings::LOG_DEST,
			MAX_CALLS = Settings::MAX_CALLS,
			SIGNIN_MODE = Settings::SIGNIN_MODE };
	};

	/// <summary>
	/// Summary for UATest1
	/// </summary>
	public ref class UATest1
	{

		delegate void ManagedCallBack(int value);
		delegate void ManagedInfoCallBack(BasicAgentListener::BasicAgentListenerState UAState, String^ value);

	public:
	delegate String^ AccessTokenRequiredDelegate();
	delegate Void UAInformationDelegate(BasicAgentListener::BasicAgentListenerState UAState, String^ info);

	event AccessTokenRequiredDelegate^ AccessTokenRequired;
	event UAInformationDelegate^ UAInformation;

	protected:
		BasicAgentListener* BAL;
		UserAgent* UA;
		RegistrationAgent* regAgent;
		PttAgent* pttAgent;
		LoggingAgent* logAgent;
		ScanAgent* scanAgent;
		ContactsAgent* contactsAgent;

		Generic::Dictionary<int,String^>^ _setting;


	private:
		void FillSettings(Settings settings);



	public:
		UATest1();
		~UATest1();

		//property Generic::IDictionary<String^, String^> Settings {Generic::IDictionary<String^, String^> get(); };
		void AddSetting(int key, String^ value);

		void Initialise(String^ dataPath);

		delegate void BALCallBack(int value);

		void ThisOne(int number);
		void callbacktes1(int value);
		void InfoCallback(BasicAgentListener::BasicAgentListenerState UAState, String^ string);

		//static BasicAgentListener::callbackfunc callbacktes1;
		//typedef void(*callbackfunc)(int);
		//static callbackfunc callbacktes1;
	private:
		ManagedCallBack^ managedDelegate;
		IntPtr unmanagedDelegatePtr;

		ManagedInfoCallBack^ managedInfoDelegate;
		IntPtr unmanagedInfoDelegatePtr;

	};
}
