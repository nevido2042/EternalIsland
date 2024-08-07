// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketQueue.h"

CPacketQueue::CPacketQueue()
{
	mHead = 0;
	mTail = 0;
	mSize = 0;
}

CPacketQueue::~CPacketQueue()
{
}

void CPacketQueue::Push(int32 Header, int32 Length, uint8* Packet)
{
	FScopeLock	lock(&mCrt);

	if (mSize == 200)
		return;

	mTail = (mTail + 1) % 201;

	mQueue[mTail].Header = Header;
	mQueue[mTail].Size = Length;

	FMemory::Memcpy(mQueue[mTail].Packet, Packet, Length);

	++mSize;
}

void CPacketQueue::Pop(int32& Header, int32& Length, uint8* Packet)
{
	FScopeLock	lock(&mCrt);

	if (mSize == 0)
		return;

	mHead = (mHead + 1) % 201;

	Header = mQueue[mHead].Header;
	Length = mQueue[mHead].Size;

	FMemory::Memcpy(Packet, mQueue[mHead].Packet, Length);

	--mSize;
}

bool CPacketQueue::Empty()
{
	return mSize == 0;
}

int32 CPacketQueue::Size()
{
	return mSize;
}

void CPacketQueue::Clear()
{
	mSize = 0;
	mHead = 0;
	mTail = 0;
}
