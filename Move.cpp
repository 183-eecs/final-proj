/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if(commandString.length() == 0){
        isPass = true;
        return;
    }
    
    if(commandString == "Q"){
        isQuit = true;
    }
    else if(commandString == "S"){
        isSave = true;
    }
    else if(commandString[0] == 'e'){
        elevatorId = commandString[1] - '0';
        
        if(commandString.length() > 2){
            if(commandString.length() == 4 && commandString[2] == 'f'){
                targetFloor = commandString[3] - '0';
            }
            else if(commandString.length() == 3 && commandString[2] == 'p'){
                isPickup = true;
            }
        }
       
    }
    
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if(isPass || isSave || isQuit){
        return true;
    }
    
    //check if elevator id is valid
    if(elevatorId < 0 || elevatorId >= NUM_ELEVATORS
       || elevators[elevatorId].isServicing()){
        return false;
    }
    
    
    //check additional criterion for servicing moves
    if(!isPickup){
        if(targetFloor < 0 || targetFloor >= NUM_FLOORS || targetFloor ==
           elevators[elevatorId].getCurrentFloor()){
            return false;
        }
    }
    
    return true;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    
    int maxFloorDistance = 0;
    
    for(int i = 0;i < pickupList.length();i++){
        int index = pickupList[i] - '0';
        if(index >= 0 && index < MAX_PEOPLE_PER_FLOOR){
            peopleToPickup[numPeopleToPickup++] = index;
            
           int angerLevel = pickupFloor.getPersonByIndex(index).getAngerLevel();
            totalSatisfaction += (MAX_ANGER - angerLevel);
            
            int personTargetFloor = 
            pickupFloor.getPersonByIndex(index).getTargetFloor();
            int floorDistance = abs(currentFloor - personTargetFloor);
            if(floorDistance > maxFloorDistance){
                maxFloorDistance = floorDistance;
                targetFloor = personTargetFloor;
            }
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
