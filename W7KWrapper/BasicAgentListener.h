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
			Active,
			Registered_FullService,
			Registered_LimitedService,
			Event,
			Deactivated
		};

		typedef void(*callbackfunc)(int);
		typedef void (*InfoCallbackFunc)(BasicAgentListenerState state, char * info);

		callbackfunc mainCallback;
		InfoCallbackFunc InfoCallback;
		//void(*mainCallback)(int);

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



		virtual void notifyEvent(int event, Info& info);
		virtual void notifyEvent(int event);

		virtual void notifyLog(Settings::LogLevel level, const char* eventLog);

		//void SetCallBack(void(*func)(int));
		void SetCallBack(callbackfunc func);
		void SetInfoCallBack(InfoCallbackFunc func);

	};
}
