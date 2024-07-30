#include "CLobbyGameMode.h"
#include "../OSS.h"

void ACLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	++NumberOfPlayers;

	LogOnScreen(this, "Current Players : " + FString::FromInt(NumberOfPlayers));

	if (NumberOfPlayers >= 3)
	{
		LogOnScreen(this, "Reached 3 Player");
	}
}

void ACLobbyGameMode::LogOut(APlayerController* Exiting)
{
	--NumberOfPlayers;
}
