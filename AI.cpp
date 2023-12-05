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
    
    int i = 0;
    int elevatorsOccupied = 0;

    for (i = 0; i < NUM_ELEVATORS; i++) {
    
        if (!buildingState.elevators[i].isServicing) {
        
            break;
        
        }

        elevatorsOccupied++;

        if (elevatorsOccupied == NUM_ELEVATORS) {
        
            return "";
        
        }
    
    }


    int sumPeople = 0;

    for (i = 0; i < NUM_FLOORS; i++) {
        sumPeople += buildingState.floors[i].numPeople;
    }

    if (sumPeople == 0) {
        return "";
    }

    int currentFloor = 0;
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        currentFloor = buildingState.elevators[i].currentFloor;

        if (buildingState.elevators[i].targetFloor == currentFloor && buildingState.floors[currentFloor].numPeople > 0) {
            return "e" + to_string(i) + "p";
        }
    }


    int ElevatorsfloorDis[10] = { 0 };
    int distance = NUM_FLOORS+1;
    int j = 0;


    for (int i = 0; i < NUM_FLOORS; i++) {


        int minDistance = NUM_FLOORS + 1;

        for (j = 0; j < NUM_ELEVATORS; j++) {

            if (!buildingState.elevators[j].isServicing) {


                distance = abs(buildingState.elevators[j].currentFloor - i);
                if (distance < minDistance) {
                    
                    minDistance = distance;
                    ElevatorsfloorDis[i] = j;
                
                }
            }
        }
    }

    distance = 0;
    int angerForDis = 0;
    int ScoresofFloors[10] = { 0 };
    int sum = 0;

    for (i = 0; i < NUM_FLOORS; i++) {
        
        sum = 0;

        for (j = 0; j < buildingState.floors[i].numPeople; j++) {

            distance = abs(buildingState.elevators[ElevatorsfloorDis[i]].currentFloor - i);
            angerForDis = distance / TICKS_PER_ANGER_INCREASE;

            if (buildingState.floors[i].people[j].angerLevel + angerForDis >= MAX_ANGER) {
            
                continue;
            
            }
            else {
            
                sum += (10 - buildingState.floors[i].people[j].angerLevel- angerForDis);

            
            }


        }

        ScoresofFloors[i] = sum - 0.6*buildingState.floors[i].numPeople * distance;

    }


    int chosenFloor = FIRST_FLOOR;
    for (int i = 0; i < NUM_FLOORS; i++) {
        if (ScoresofFloors[i] > ScoresofFloors[chosenFloor]) {
            chosenFloor = i;
        }
    }

    int chosenElevator = ElevatorsfloorDis[chosenFloor];

    return "e" + to_string(chosenElevator) + "f" + to_string(chosenFloor);



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
