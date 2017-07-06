#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>
#include "BasicAgentListener.h"
using namespace System;
using namespace std;
using namespace W7KWrapper;


BasicAgentListener::BasicAgentListener()
{

}


BasicAgentListener::~BasicAgentListener()
{
}

int BasicAgentListener::initialise()
{
	WSADATA wsaData;
	int wsa_err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	return wsa_err;

}

void BasicAgentListener::SetRegistrationAgentCallBack(RegistrationAgent * regAgent)
{
	InfoCallback(BasicAgentListenerState::Active, "Well now what");
	this->regAgent = regAgent;
}

void BasicAgentListener::notifyRegistered(AccessMode accessMode)
{
	BasicAgentListenerState accessState = BasicAgentListenerState::Registered_FullService;

	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyRegistered(AccessMode accessMode)");
	if (accessMode != AccessMode::FULL_SERVICE_ACCESS)
	{
		accessState = BasicAgentListenerState::Registered_LimitedService;
	}
	

//	Console::WriteLine(L"On Client Registered"); // TODO: output accessMode
	InfoCallback(accessState, "notifyRegistered");

}


void BasicAgentListener::notifyLog(Settings::LogLevel level, const char* eventLog)
{

}

void BasicAgentListener::notifyActive(Info & reason)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyActive(Info & reason)");

	//cout << "On Client Active " << reason.getMessage() << " , " << reason.getErrorCode() << endl;
	char str[100];
	sprintf_s(str, "Active results [%d] %s", reason.getErrorCode(), reason.getMessage());
	InfoCallback(BasicAgentListenerState::Active, str);
}

void BasicAgentListener::notifyDeactivated(Info & reason)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyDeactivated(Info & reason)");

	//cout << "On Client Deactivated " << reason.getMessage() << " , " << reason.getErrorCode() << endl;
	char str[100];
	sprintf_s(str, "Deactivated results [%d] %s", reason.getErrorCode(), reason.getMessage());
	InfoCallback(BasicAgentListenerState::Deactivated, str);
}

void BasicAgentListener::notifyUpdateSettings(const Settings & config)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyUpdateSettings(const Settings & config)");
	InfoCallback(BasicAgentListenerState::Undefined, "notifyUpdateSettings");

}


void BasicAgentListener::notifyScanListArchiveRestored(const ScanListArchive::AliasList & list)
{
	//cout << "BasicAgentListener::notifyScanListArchiveRestored" << endl;
}

bool BasicAgentListener::isConnectionTrusted(const char * authenticationMethod, const X509CertificateList & certificateList)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::isConnectionTrusted(const char * authenticationMethod, const X509CertificateList & certificateList)");

	return true;
}

void BasicAgentListener::notifyAccessTokenRequired()
{
	//cout << "BasicAgentListener::notifyAccessTokenRequired()" << endl;
	//auto ptrToken = (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Configuration::ConfigurationManager::AppSettings["TOKEN"]);
	//TODO: add the token back in
	//this->regAgent->setAccessToken(ptrToken);
	InfoCallback(BasicAgentListenerState::Event, "BasicAgentListener::notifyAccessTokenRequired");
	auto token = TokenCallback();

	char str[1100];
	sprintf_s(str, "Supplied Access token :%s", token);
	InfoCallback(BasicAgentListenerState::Event, str);

	this->regAgent->setAccessToken(token);
}

void BasicAgentListener::notifyCertificatePassphraseRequired()
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyCertificatePassphraseRequired()");

	this->regAgent->setCertificatePassphrase("5$w^3u^a2dcvfyf");
}

void BasicAgentListener::notifyEvent(int event, Info & info)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyEvent(int event, Info & info)");

	char str[100];
	sprintf_s(str, "notifyEvents [%d] [%d] %s", event, info.getErrorCode(),info.getMessage());
	InfoCallback(BasicAgentListenerState::Event, str);
}

void BasicAgentListener::notifyEvent(int event)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyEvent(int event)");

	char str[100];
	sprintf_s(str, "notifyEvents [%d]", event);
	InfoCallback(BasicAgentListenerState::Event, str);
}

void BasicAgentListener::intitialise()
{
	throw gcnew InvalidOperationException("No worky");
}

//void BasicAgentListener::SetCallBack(void(*func)(int))
void BasicAgentListener::SetTokenCallBack(TokenCallbackFunc func)
{
	TokenCallback = func;
}

void BasicAgentListener::SetInfoCallBack(InfoCallbackFunc func)
{
	InfoCallback = func;
}


