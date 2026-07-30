// Copyright (c) 2026 Jonathan Embley-Riches. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// --- LEGAL DISCLAIMER ---
// UnrealRoboticsLab is an independent software plugin. It is NOT affiliated with,
// endorsed by, or sponsored by Epic Games, Inc. "Unreal" and "Unreal Engine" are
// trademarks or registered trademarks of Epic Games, Inc. in the US and elsewhere.
//
// This plugin incorporates third-party software: MuJoCo (Apache 2.0),
// CoACD (MIT), and libzmq (MPL 2.0). See ThirdPartyNotices.txt for details.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkManager.generated.h"

class UMjCamera;

/**
 * @class UMjNetworkManager
 * @brief Manages camera streaming. (ZMQ broadcaster + subscriber are
 *        bridge-style UObject transports owned by AAMjManager directly,
 *        not discovered through component iteration.)
 */
UCLASS(ClassGroup = (MuJoCo), meta = (BlueprintSpawnableComponent))
class URLAB_API UMjNetworkManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UMjNetworkManager();

	/** Enables rendering/readback for all registered UMjCameras. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MuJoCo|Network")
	bool bEnableAllCameras = true;

	/**
	 * Enables URLab's legacy per-camera ZMQ and SHM publishers while camera
	 * streaming is enabled. Applications with their own camera transport can
	 * disable this without disabling rendering or on-demand readback.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MuJoCo|Network")
	bool bEnableCameraBroadcast = true;

	void UpdateCameraStreamingState();

	// Thread-safe camera registry.
	void RegisterCamera(UMjCamera* Cam);
	void UnregisterCamera(UMjCamera* Cam);
	TArray<UMjCamera*> GetActiveCameras();

private:
	TArray<UMjCamera*> ActiveCameras;
	FCriticalSection CameraMutex;
};
