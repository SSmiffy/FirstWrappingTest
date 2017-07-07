#pragma once
#include <AgentListener.h>
#include <RegistrationAgent.h>
//#include <iostream>
//#include <fstream>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;


namespace W7KWrapper {

	/// <summary>
	/// Summary for BasicAgentListener1
	/// </summary>
	public class BasicAgentListener : public AgentListener
	{
	protected:
		RegistrationAgent* regAgent;
		//std::ofstream* logStream;

	public:
		BasicAgentListener();

		~BasicAgentListener();

		void intitialise();

		enum BasicAgentListenerState
		{
			Undefined,
			LOG_NONE,
			LOG_ERROR,
			LOG_WARNING,
			LOG_INFO,
			LOG_VERBOSE,
			Active,
			Registered_FullService,
			Registered_LimitedService,
			Event,
			Deactivated,
		};

		typedef char* (*TokenCallbackFunc)(void);
		typedef void (*InfoCallbackFunc)(BasicAgentListenerState state, char * info);

		TokenCallbackFunc TokenCallback;
		InfoCallbackFunc InfoCallback;
		//void(*mainCallback)(int);

		int initialise();

		void SetRegistrationAgentCallBack(RegistrationAgent* regAgent);

		// Registration
		virtual void notifyRegistered(AccessMode accessMode);
		virtual void notifyActive(Info& reason);
		virtual void notifyDeactivated(Info& reason);
		virtual void notifyUpdateSettings(const Settings& config);
		virtual bool isConnectionTrusted(const char* authenticationMethod,
			const X509CertificateList& certificateList);

		virtual void notifyCertificatePassphraseRequired();
		virtual void notifyAccessTokenRequired();
		virtual void notifyScanListArchiveRestored(const ScanListArchive::AliasList & list);
		virtual void notifyUpdateGroupList(const ListEventData& data);



		virtual void notifyEvent(int event, Info& info);
		virtual void notifyEvent(int event);

		virtual void notifyLog(Settings::LogLevel level, const char* eventLog);

		//void SetCallBack(void(*func)(int));
		void SetTokenCallBack(TokenCallbackFunc func);
		void SetInfoCallBack(InfoCallbackFunc func);

	};
}
