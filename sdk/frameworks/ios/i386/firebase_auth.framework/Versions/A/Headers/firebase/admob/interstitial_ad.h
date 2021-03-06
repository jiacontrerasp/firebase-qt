// Copyright 2016 Google Inc. All Rights Reserved.

#ifndef FIREBASE_ADMOB_CLIENT_CPP_INCLUDE_FIREBASE_ADMOB_INTERSTITIAL_AD_H_
#define FIREBASE_ADMOB_CLIENT_CPP_INCLUDE_FIREBASE_ADMOB_INTERSTITIAL_AD_H_

#include "firebase/admob/types.h"
#include "firebase/future.h"

namespace firebase {
namespace admob {

// Predeclarations.
struct InterstitialAdData;

/// @brief Loads and displays AdMob interstitial ads.
///
/// @ref InterstitialAd is a single-use object that can load and show a
/// single AdMob interstitial ad.
///
/// InterstitialAd objects maintain a presentation state that indicates whether
/// or not they're currently onscreen, but otherwise provide information about
/// their current state through Futures. @ref Initialize, @ref LoadAd, and
/// @ref Show each have a corresponding @ref Future from which you can determine
/// result of the previous call.
///
/// In addition, applications can create their own subclasses of
/// @ref InterstitialAd::Listener, pass an instance to the @ref SetListener
/// method, and receive callbacks whenever the presentation state changes.
///
/// Here's how one might initialize, load, and show an interstitial ad while
/// checking against the result of the previous action at each step:
///
/// @code
/// namespace admob = ::firebase::admob;
/// admob::InterstitialAd* interstitial = new admob::InterstitialAd();
/// interstitial->Initialize(ad_parent, "YOUR_AD_UNIT_ID")
/// @endcode
///
/// Then, later:
///
/// @code
/// if (interstitial->InitializeLastResult().Status() ==
///     ::firebase::kFutureStatusComplete &&
///     interstitial->InitializeLastResult().Error() ==
///     firebase::admob::kAdMobErrorNone) {
///   interstitial->LoadAd(my_ad_request);
/// }
/// @endcode
///
/// And after that:
///
/// @code
/// if (interstitial->LoadAdLastResult().Status() ==
///     ::firebase::kFutureStatusComplete &&
///     interstitial->LoadAdLastResult().Error() ==
///     firebase::admob::kAdMobErrorNone)) {
///   interstitial->Show();
/// }
/// @endcode
class InterstitialAd {
 public:
  /// The presentation states of an @ref InterstitialAd.
  enum PresentationState {
    /// InterstitialAd is not currently being shown.
    kPresentationStateHidden = 0,
    /// InterstitialAd is being shown or has caused focus to leave the
    /// application (for example, when opening an external browser during a
    /// clickthrough).
    kPresentationStateCoveringUI,
  };

  /// A listener class that developers can extend and pass to an
  /// @ref InterstitialAd objects's @ref SetListener method to be
  /// notified of presentation state changes. This is useful for changes caused
  /// by user interaction, such as when the user closes an interstitial.
  class Listener {
   public:
    /// This method is called when the @ref InterstitialAd object's presentation
    /// state changes.
    virtual void OnPresentationStateChanged(InterstitialAd* interstitial_ad,
                                            PresentationState new_state) = 0;
    virtual ~Listener();
  };

  /// Creates an uninitialized @ref InterstitialAd object.
  /// @ref Initialize must be called before the object is used.
  InterstitialAd();

  ~InterstitialAd();

  /// Initialize the @ref InterstitialAd object.
  /// @param[in] parent The platform-specific UI element that will host the ad.
  /// @param[in] ad_unit_id The ad unit ID to use in loading the ad.
  Future<void> Initialize(AdParent parent, const char* ad_unit_id);

  /// Returns a @ref Future containing the status of the last call to
  /// @ref Initialize.
  Future<void> InitializeLastResult() const;

  /// Begins an asynchronous request for an ad. The
  /// @ref InterstitialAd::GetPresentationState method can be used to track the
  /// progress of the request.
  /// @param[in] request An AdRequest struct with information about the request
  ///                    to be made (such as targeting info).
  Future<void> LoadAd(AdRequest request);

  /// Returns a @ref Future containing the status of the last call to
  /// @ref LoadAd.
  Future<void> LoadAdLastResult() const;

  /// Shows the @ref InterstitialAd. This should not be called unless an ad has
  /// already been loaded.
  Future<void> Show();

  /// Returns a @ref Future containing the status of the last call to @ref Show.
  Future<void> ShowLastResult() const;

  /// Returns the current presentation state of the @ref InterstitialAd.
  ///
  /// @return The current presentation state.
  PresentationState GetPresentationState() const;

  /// Sets the @ref Listener for this @ref InterstitialAd.
  /// @param[in] listener A valid InterstititalAd::Listener to receive
  ///                     callbacks.
  void SetListener(Listener* listener);

 private:
  InterstitialAdData* data_;
};

}  // namespace admob
}  // namespace firebase

#endif  // FIREBASE_ADMOB_CLIENT_CPP_INCLUDE_FIREBASE_ADMOB_INTERSTITIAL_AD_H_
