/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    return "";
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {


    int numUp = 0;
    int numDown = 0;
    int angerBeforeExplodeUp = 0;
    int angerBeforeExplodeDown = 0;
    string downList = "";
    string UpList = "";
    int i = 0;

    //direction true = up
    bool direction = true;

    for (i = 0; i < floorToPickup.getNumPeople(); i++) {
    
        if (floorToPickup.getPersonByIndex(i).getTargetFloor() > floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
        
            numUp++;
            angerBeforeExplodeUp += (MAX_ANGER - floorToPickup.getPersonByIndex(i).getAngerLevel());
            UpList += to_string(i);
        
        }
        else {
        
            numDown++;
            angerBeforeExplodeDown += (MAX_ANGER - floorToPickup.getPersonByIndex(i).getAngerLevel());
            downList += to_string(i);

        
        }
    
    }

    if (numUp != 0) {
    
        angerBeforeExplodeUp = (angerBeforeExplodeUp*1.0)/numUp;
    
    }

    if (numDown != 0) {

        angerBeforeExplodeDown = (angerBeforeExplodeDown * 1.0) / numDown;

    }



    if (angerBeforeExplodeDown > angerBeforeExplodeUp) {
    
        return downList;
    
    }






    return UpList;
}
