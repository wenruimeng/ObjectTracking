// why not #pragma once?
#ifndef COMMON_H
#define COMMON_H

// why are these included here?
#include <stdlib.h>
#include <stdio.h>


class Direction {
public:
  enum direction{up, down, right, left}; //the direction is for x-y plane. up means direction in the y-axis and y-->biggest 
    Direction(const Direction& d);
	// ????
	double getAngularVelocity(direction target); 

    // rotated 1/4 turn to the right
    Direction right();
    // rotated 1/4 turn to the left
    Direction left();
	// odd choice...
    // this direction rotated 1/2 turn
    Direction operator -();
};


class Position {
    int x,y;
public:
    Position operator +(Direction d);
    Position operator -(Direction d);
    Position& operator +=(Direction d);
    Position& operator -=(Direction d);
    Position& operator =(Position p);
};




#endif
