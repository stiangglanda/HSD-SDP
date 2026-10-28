#include "PlayerClient.h"
#include <iostream>

void PlayerClient::SetPlayer(Player& player)
{
    mPlayer = &player;
}

void PlayerClient::Play()
{
    if (mPlayer != nullptr)
    {
        mPlayer->Play();
    }
}

void PlayerClient::VolInc()
{
    if (mPlayer != nullptr)
    {
        mPlayer->VolInc();
    }
}

void PlayerClient::VolDec()
{
    if (mPlayer != nullptr)
    {
        mPlayer->VolDec();
    }
}

void PlayerClient::Stop()
{
    if (mPlayer != nullptr)
    {
        mPlayer->Stop();
    }
}

void PlayerClient::Next()
{
    if (mPlayer != nullptr)
    {
        mPlayer->Next();
    }
}

void PlayerClient::Prev()
{
    if (mPlayer != nullptr)
    {
        mPlayer->Prev();
    }
}

void PlayerClient::Select(std::string const& name)
{
    if (mPlayer != nullptr)
    {
        mPlayer->Select(name);
    }
}