// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

struct FPacketInfo
{
	int32			Header;
	int32			Size;
	uint8			Packet[1016];
};

class EI_API CPacketQueue
{
public:
	CPacketQueue();
	~CPacketQueue();

private:
	FCriticalSection	mCrt;
	FPacketInfo			mQueue[201];
	int32				mHead;
	int32				mTail;
	int32				mSize;

public:
	void Push(int32 Header, int32 Length, uint8* Packet);
	void Pop(int32& Header, int32& Length, uint8* Packet);
	bool Empty();
	int32 Size();
	void Clear();
};
