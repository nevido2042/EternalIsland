// Fill out your copyright notice in the Description page of Project Settings.


#include "ReceiveThread.h"
#include "NetworkSession.h"
#include "PacketQueue.h"
#include "NetworkManager.h"

CReceiveThread::CReceiveThread()    :
    mSession(nullptr),
    mQueue(nullptr)
{
}

CReceiveThread::~CReceiveThread()
{
    mQueue->Clear();
}

bool CReceiveThread::Init()
{
    CThreadBase::Init();

    FString QueueName = mName + TEXT("_Queue");

    CNetworkManager::GetInst()->CreatePacketQueue(QueueName);

    mQueue = CNetworkManager::GetInst()->FindPacketQueue(QueueName);

    return true;
}

// ��� ������ ������ �ؾ��Ѵ�.
uint32 CReceiveThread::Run()
{
    do
    {
        if (mSession)
        {
            uint8   Packet[1024] = {};
            int32   Header = 0, Length = 0;

            if (!mSession->Receive(Header, Length, Packet))
                return 0;

            mQueue->Push(Header, Length, Packet);
        }
    } while (mLoop);


    return 0;
}

void CReceiveThread::Stop()
{
    CThreadBase::Stop();
}

void CReceiveThread::Exit()
{
    CThreadBase::Exit();

    mLoop = false;
}
