// Dragons rule ok


#include "FTDUIResources.h"

void FTDUIResources::Initialize() {
	if (!TDUIResources.IsValid()) {
		TDUIResources = Create();
		FSlateStyleRegistry::UnRegisterSlateStyle(*TDUIResources);
		FSlateStyleRegistry::RegisterSlateStyle(*TDUIResources);
		UE_LOG(LogTemp, Warning, TEXT("Resources initialised"));
	}
}

TSharedPtr<FSlateGameResources> FTDUIResources::GetSlateGameResources() {
	return TDUIResources;
}

TSharedRef<class FSlateGameResources> FTDUIResources::Create() {
	return FSlateGameResources::New(FName("TDUIResources"), m_Path, m_Path);
}

/*Unregister resources/styles with Slate, cleanup, free memory*/
void FTDUIResources::Shutdown() {
	//Unregister *MyUIResources with Slate
	FSlateStyleRegistry::UnRegisterSlateStyle(*TDUIResources);

	//Debugging
	ensure(TDUIResources.IsUnique());

	//Removes reference to resources, decrements refcount, destroys resources if refcount=0
	//Do this to all SharedPtrs on Shutdown() or SomethingSimilar() to avoid memory leak
	TDUIResources.Reset();
}