#include "stdafx.h"
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

void BasicAgentListener::SetRegistrationAgentCallBack(RegistrationAgent * regAgent)
{
	this->regAgent = regAgent;
}

void BasicAgentListener::notifyRegistered(AccessMode accessMode)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyRegistered(AccessMode accessMode)");

	Console::WriteLine(L"On Client Registered"); // TODO: output accessMode

}


void BasicAgentListener::notifyLog(Settings::LogLevel level, const char* eventLog)
{

}

void BasicAgentListener::notifyActive(Info & reason)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyActive(Info & reason)");

	//cout << "On Client Active " << reason.getMessage() << " , " << reason.getErrorCode() << endl;
}

void BasicAgentListener::notifyDeactivated(Info & reason)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyDeactivated(Info & reason)");

	//cout << "On Client Deactivated " << reason.getMessage() << " , " << reason.getErrorCode() << endl;
}

void BasicAgentListener::notifyUpdateSettings(const Settings & config)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyUpdateSettings(const Settings & config)");

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
	mainCallback(234);
}

void BasicAgentListener::notifyCertificatePassphraseRequired()
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyCertificatePassphraseRequired()");

	this->regAgent->setCertificatePassphrase("5$w^3u^a2dcvfyf");
}

void BasicAgentListener::notifyEvent(int event, Info & info)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyEvent(int event, Info & info)");
}

void BasicAgentListener::notifyEvent(int event)
{
	System::Diagnostics::Trace::WriteLine("BasicAgentListener::notifyEvent(int event)");
}

void BasicAgentListener::intitialise()
{
	throw gcnew InvalidOperationException("No worky");
}

//void BasicAgentListener::SetCallBack(void(*func)(int))
void BasicAgentListener::SetCallBack(callbackfunc func)
{
	mainCallback = func;
}

