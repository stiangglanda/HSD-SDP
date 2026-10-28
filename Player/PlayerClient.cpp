#include "PlayerClient.h"

void PlayerClient::SetPlayer(Player *player)
{
	mPlayer = player;
}

void PlayerClient::Play()
{
	mPlayer->Play();
}

void PlayerClient::VolInc()
{
	mPlayer->VolInc();
}

void PlayerClient::VolDec()
{
	mPlayer->VolDec();
}

void PlayerClient::Stop()
{
	mPlayer->Stop();
}

void PlayerClient::Next()
{
	mPlayer->Next();
}

void PlayerClient::Prev()
{
	mPlayer->Prev();
}

void PlayerClient::Select(std::string const& name)
{
	mPlayer->Select(name);
}
