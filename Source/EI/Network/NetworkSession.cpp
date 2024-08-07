// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkSession.h"

CNetworkSession::CNetworkSession()	:
	mSocket(nullptr),
	mConnect(false),
	mReceivePacket{},
	mSendPacket{}
{
}

CNetworkSession::~CNetworkSession()
{
	Close();
}

bool CNetworkSession::Connect(const FString& IPAddr, int32 Port)
{
	mSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(
		NAME_Stream, TEXT("Default"), false);

	FIPv4Address	ip;
	FIPv4Address::Parse(IPAddr, ip);

	TSharedRef<FInternetAddr>	Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	Addr->SetIp(ip.Value);
	Addr->SetPort(Port);

	mConnect = mSocket->Connect(*Addr);

	return mConnect;
}

void CNetworkSession::Close()
{
	if (mConnect)
	{
		mSocket->Close();
		delete mSocket;

		mSocket = nullptr;

		mConnect = false;
	}
}

bool CNetworkSession::Receive(int32& PacketHeader, int32& Length, uint8* Packet)
{
	if (!mConnect)
		return false;

	bool Result = mSocket->Recv(mReceivePacket, 1024, Length);

	if (!Result || Length == 0)
		return false;

	FMemory::Memcpy(&PacketHeader, mReceivePacket, 4);
	FMemory::Memcpy(&Length, mReceivePacket + 4, 4);
	FMemory::Memcpy(Packet, mReceivePacket + 8, Length);

	return true;
}

bool CNetworkSession::Send(int32 PacketHeader, int32 Length, uint8* Packet)
{
	if (!mConnect)
		return false;

	FMemory::Memcpy(mSendPacket, &PacketHeader, 4);
	FMemory::Memcpy(mSendPacket + 4, &Length, 4);
	FMemory::Memcpy(mSendPacket + 8, Packet, Length);

	return mSocket->Send(mSendPacket, Length + 8, Length);
}
