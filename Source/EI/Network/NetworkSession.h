// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"

/**
 * 
 */
class EI_API CNetworkSession
{
public:
	CNetworkSession();
	~CNetworkSession();

private:
	FString		mName;
	FSocket*	mSocket;
	bool		mConnect;
	uint8		mReceivePacket[1024];
	uint8		mSendPacket[1024];

public:
	bool IsConnect()	const
	{
		return mConnect;
	}

	const FString& GetName()	const
	{
		return mName;
	}

	void SetName(const FString& Name)
	{
		mName = Name;
	}

	bool Connect(const FString& IPAddr, int32 Port);
	void Close();
	bool Receive(int32& PacketHeader, int32& Length, uint8* Packet);
	bool Send(int32 PacketHeader, int32 Length, uint8* Packet);
};
