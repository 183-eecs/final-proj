/*
 * Copyright 2023 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

void person_tests();
void elevator_tests();
void floor_tests();


void start_tests() {
    //person_tests();
    //elevator_tests();
    floor_tests();
    return;
}

void person_tests() {
    //initialize a person with targetFloor 5, anger 5
    Person p("0f0t5a5");

    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl;

    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE);

    cout << exploded << " Expected 0" << endl;

    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;

    //simulate time not being a multiple
    p.tick(TICKS_PER_ANGER_INCREASE - 1);

    //no change
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;

    p.tick(TICKS_PER_ANGER_INCREASE); //7 after

    p.tick(TICKS_PER_ANGER_INCREASE); //8 after

    p.tick(TICKS_PER_ANGER_INCREASE); //9 after

    exploded = p.tick(TICKS_PER_ANGER_INCREASE);

    cout << exploded << " Expected 1" << endl;
}


void elevator_tests() {
    Elevator ele;
    ele.setCurrentFloor(2);
    ele.serviceRequest(8);
    ele.tick(10);
    cout << ele.getCurrentFloor() << endl;
    
    ele.serviceRequest(1);
    ele.tick(100);
    cout << ele.getCurrentFloor() << endl;
    
    ele.setCurrentFloor(2);
    ele.serviceRequest(2);
    ele.tick(10);
    cout << ele.isServicing() << endl;
}

void floor_tests(){
    Person p1("0f8t5a5");
    Person p2("0f2t5a10");
    Person p3("0f6t5a5");
    Person p4("0f3t7a11");
    Person p5("0f7t8a5");
    Floor flr;
    
    flr.addPerson(p1, p1.getTargetFloor()-p1.getCurrentFloor());
    flr.addPerson(p2, p2.getTargetFloor()-p2.getCurrentFloor());
    flr.addPerson(p3, p3.getTargetFloor()-p3.getCurrentFloor());
    flr.addPerson(p4, p4.getTargetFloor()-p4.getCurrentFloor());
    flr.addPerson(p5, p5.getTargetFloor()-p5.getCurrentFloor());
    
    
    cout << flr.tick(0) << endl;
    cout << flr.getNumPeople() << endl;
    cout << flr.getHasUpRequest() << endl;
    cout << flr.getHasDownRequest() << endl;
    
    
}
