#pragma once

#include <vector>

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


class Point{
public:
int x,y;
Point(int xValue=0, int yValue=0){
x=xValue;
y=yValue;
}

bool operator < ( const Point &other) const {

if(x<other.x) return true;
if(x>other.x) return false;

if(y<other.y) return true;
if(y>other.y) return false;
return false;
}
};

typedef std::vector<Point> Path;



