// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UMyGameInstance::UMyGameInstance() {

}

void UMyGameInstance::Init()
{
	Super::Init();

	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get()) {
		SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid()) {
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(
				this, &UMyGameInstance::OnCreateSessionComplete
			);

			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(
				this, &UMyGameInstance::OnFindSessionComplete
			);

			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(
				this, &UMyGameInstance::OnJoinSessionComplete
			);
		}
	}
}

void UMyGameInstance::OnCreateSessionComplete(FName SessionName, bool Succeeded)
{
	if (Succeeded) {
		GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

void UMyGameInstance::OnFindSessionComplete(bool Succeeded)
{
	if (Succeeded) {
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

		const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();

		for (auto ss : SearchResults) {
			UE_LOG(LogTemp, Warning, TEXT("SessionName : %s"), *(ss.Session.GetSessionIdStr()));
		}

		UE_LOG(LogTemp, Warning, TEXT("NUMBER OF SESSSIONS FOUND : %d"), SearchResults.Num());
		if (SearchResults.Num()) {
			UE_LOG(LogTemp, Warning, TEXT("SESSION FOUND"));
			FOnlineSessionSearchResult Res = SearchResults[0];
			UE_LOG(LogTemp, Warning, TEXT("SESSION ID IS : %s"), *Res.GetSessionIdStr());
			SessionInterface->JoinSession(*localPlayer->GetPreferredUniqueNetId(), FName("SteamExpirement Session"), SearchResults[0]);
		}
	}
}

void UMyGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (APlayerController* PController = GetWorld()->GetFirstPlayerController()) {
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		UE_LOG(LogTemp, Warning, TEXT("JoinAddress is : %s"), *JoinAddress);

		if (JoinAddress != "") {
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UMyGameInstance::CreateServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Create Server"));
	FOnlineSessionSettings SessionSettings;

	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL") ? false : true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;

	SessionInterface->CreateSession(0, FName("SteamExpirement Session"), SessionSettings);
}

void UMyGameInstance::JoinServer()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	SessionSearch->bIsLanQuery = (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL") ? false : true;
	SessionSearch->MaxSearchResults = 1000;
	SessionSearch->QuerySettings.Set("SEARCH_PRESENCE", false, EOnlineComparisonOp::Equals);
	//SessionSearch->QuerySettings.Set("SEARCH_KEYWORDS", FString::FString("SteamExpirement Session"), EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}
