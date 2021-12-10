// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#pragma once

#include "Widgets/SWindow.h"
#include <optional>

class ACesium3DTileset;

class CesiumIonTokenTroubleshooting : public SWindow {
  SLATE_BEGIN_ARGS(CesiumIonTokenTroubleshooting) {}
  /**
   * The tileset being troubleshooted.
   */
  SLATE_ARGUMENT(ACesium3DTileset*, Tileset)

  /** Whether this troubleshooting panel was opened in response to an error,
   * versus opened manually by the user. */
  SLATE_ARGUMENT(bool, TriggeredByError)
  SLATE_END_ARGS()

public:
  static void Open(ACesium3DTileset* pTileset, bool triggeredByError);
  void Construct(const FArguments& InArgs);

private:
  static TMap<ACesium3DTileset*, TSharedRef<CesiumIonTokenTroubleshooting>>
      _existingPanels;

  struct TokenState {
    FString name;
    FString token;
    std::optional<bool> isValid;
    std::optional<bool> allowsAccessToAsset;
    std::optional<bool> associatedWithUserAccount;
  };

  TokenState _assetTokenState{};
  TokenState _projectDefaultTokenState{};

  TSharedRef<SWidget>
  createTokenPanel(ACesium3DTileset* pTileset, TokenState& state);
};
