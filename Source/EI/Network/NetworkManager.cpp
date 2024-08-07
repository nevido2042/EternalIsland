// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"
#include "NetworkSession.h"
#include "PacketQueue.h"

CNetworkManager* CNetworkManager::mInst = nullptr;

CNetworkManager::CNetworkManager()
{
}

CNetworkManager::~CNetworkManager()
{
	for (auto& Thread : mThreadMap)
	{
		Thread.Value->Worker->Exit();
	}

	for (auto& Session : mSessionMap)
	{
		Session.Value->Close();
	}

	for (auto& Thread : mThreadMap)
	{
		Thread.Value->Thread->Kill();

		Thread.Value->Thread->WaitForCompletion();

		delete Thread.Value->Thread;
		delete Thread.Value->Worker;
		delete Thread.Value;
	}

	for (auto& Session : mSessionMap)
	{
		delete Session.Value;
	}

	for (auto& Queue : mPacketQueueMap)
	{
		delete Queue.Value;
	}
}

bool CNetworkManager::Init()
{
	return true;
}

bool CNetworkManager::CheckSession(const FString& Name)
{
	return mSessionMap.Contains(Name);
}

bool CNetworkManager::Connect(const FString& Name, const FString& IPAddr, 
	int32 Port)
{
	CNetworkSession* Session = nullptr;

	if (!CheckSession(Name))
	{
		Session = new CNetworkSession;

		Session->SetName(Name);

		mSessionMap.Emplace(Name, Session);
	}

	else
		Session = FindSession(Name);

	if (Session->IsConnect())
		return false;

	return Session->Connect(IPAddr, Port);
}

bool CNetworkManager::Close(const FString& Name)
{
	if (!CheckSession(Name))
		return false;

	CNetworkSession* Session = FindSession(Name);

	if (!Session->IsConnect())
		return false;

	Session->Close();

	return true;
}

CNetworkSession* CNetworkManager::FindSession(const FString& Name)
{
	if (!mSessionMap.Contains(Name))
		return nullptr;

	return mSessionMap.FindRef(Name);

	return nullptr;
}

bool CNetworkManager::RemoveSession(const FString& Name)
{
	if (!CheckSession(Name))
		return false;

	CNetworkSession* Session = FindSession(Name);

	delete Session;

	mSessionMap.Remove(Name);

	return true;
}

bool CNetworkManager::Send(const FString& SessionName, int32 Header, 
	int32 Length, uint8* Packet)
{
	if (!CheckSession(SessionName))
		return false;

	CNetworkSession* Session = FindSession(SessionName);

	if (!Session->IsConnect())
		return false;

	return Session->Send(Header, Length, Packet);
}

bool CNetworkManager::Receive(const FString& SessionName, int32& Header, 
	int32& Length, uint8* Packet)
{
	if (!CheckSession(SessionName))
		return false;

	CNetworkSession* Session = FindSession(SessionName);

	if (!Session->IsConnect())
		return false;

	return Session->Receive(Header, Length, Packet);
}

bool CNetworkManager::SendServerType(const FString& SessionName)
{
	if (!CheckSession(SessionName))
		return false;

	CNetworkSession* Session = FindSession(SessionName);

	if (!Session->IsConnect())
		return false;

	uint8	Packet[1016] = {};
	int32	ServerType = (int32)mCurrentServerType;

	FMemory::Memcpy(Packet, &ServerType, 4);
	return Session->Send((int32)EPacketHeader::SessionType, 4, Packet);
}

bool CNetworkManager::CreatePacketQueue(const FString& Name)
{

	if (mPacketQueueMap.Contains(Name))
		return false;

	CPacketQueue* Queue = new CPacketQueue;

	mPacketQueueMap.Emplace(Name, Queue);

	return true;
}

CPacketQueue* CNetworkManager::FindPacketQueue(const FString& Name)
{
	if (!mPacketQueueMap.Contains(Name))
		return nullptr;

	return mPacketQueueMap.FindRef(Name);
}

bool CNetworkManager::SuspendThread(const FString& Name, bool Pause)
{
	if (!mThreadMap.Contains(Name))
		return false;

	mThreadMap.FindRef(Name)->Thread->Suspend(Pause);

	return true;
}

bool CNetworkManager::RemoveThread(const FString& Name)
{
	if (!mThreadMap.Contains(Name))
		return false;

	mThreadMap.FindRef(Name)->Worker->Exit();

	mThreadMap.FindRef(Name)->Thread->Kill();
	mThreadMap.FindRef(Name)->Thread->WaitForCompletion();

	delete mThreadMap.FindRef(Name)->Worker;
	delete mThreadMap.FindRef(Name)->Thread;
	delete mThreadMap.FindRef(Name);

	mThreadMap.Remove(Name);

	return true;
}
