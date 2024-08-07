// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "ThreadBase.h"

struct FThreadInfo
{
	CThreadBase*		Worker;
	FRunnableThread*	Thread;
};


class EI_API CNetworkManager
{
private:
	CNetworkManager();
	~CNetworkManager();

private:
	TMap<FString, class CNetworkSession*>	mSessionMap;
	TMap<FString, class CPacketQueue*>	mPacketQueueMap;
	TMap<FString, FThreadInfo*>	mThreadMap;

	EServerType		mCurrentServerType;

public:
	void SetServerType(EServerType Type)
	{
		mCurrentServerType = Type;
	}

public:
	bool Init();
	bool CheckSession(const FString& Name);
	bool Connect(const FString& Name, const FString& IPAddr,
		int32 Port);
	bool Close(const FString& Name);
	class CNetworkSession* FindSession(const FString& Name);
	bool RemoveSession(const FString& Name);
	bool Send(const FString& SessionName, int32 Header, int32 Length,
		uint8* Packet);
	bool Receive(const FString& SessionName, int32& Header, int32& Length,
		uint8* Packet);
	bool SendServerType(const FString& SessionName);

	bool CreatePacketQueue(const FString& Name);
	class CPacketQueue* FindPacketQueue(const FString& Name);

	bool SuspendThread(const FString& Name, bool Pause);
	bool RemoveThread(const FString& Name);

public:
	template <typename T>
	FThreadInfo* CreateThread(const FString& Name)
	{
		if (mThreadMap.Contains(Name))
			return nullptr;

		FThreadInfo* Info = new FThreadInfo;

		Info->Worker = new T;
		Info->Worker->SetName(Name);

		Info->Worker->Init();

		Info->Thread = FRunnableThread::Create(Info->Worker, *Name);
		// ������� �ϴ� �Ͻ����� �صд�.
		Info->Thread->Suspend();

		mThreadMap.Emplace(Name, Info);

		return Info;
	}

private:
	static CNetworkManager* mInst;

public:
	static CNetworkManager* GetInst()
	{
		if (!mInst)
			mInst = new CNetworkManager;

		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};
