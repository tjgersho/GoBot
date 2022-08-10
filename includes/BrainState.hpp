//
//  BrainState.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/1/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef BrainState_hpp
#define BrainState_hpp

#include <stdio.h>

enum BrainState {
      Quit,
      Dreaming,
      Awake,
      Learning,
	  AwaitingFeedback,
      NoChange,
	  IncrementViewNet,
	  DecrementViewNet,
	  RightButton,
	  LeftButton,
	  SpaceButton,
	  SaveBrain,
	  LoadBrain
};

static const char * BrainStateStrings[] = {"Quit", "Dreaming", "Awake", "Learning", "AwaitingFeedback" };


#endif /* BrainState_hpp */
