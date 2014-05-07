#pragma once
// these are needed by pathFinder.cpp, but not for clients of these types, right?
// so why are they here?
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"





// What kind of thing is this supposed to represent? Maybe we should discuss this.
//Assume the movement is only up down right left, no diagonal movement allowed
//No wrap arround allowed, the map doesn't allow exceed the boundary ??
class PathFinder{
public:
  int width, height;
  // why is status an int instead of some enumerated type?
  //this could be a emumerate type, but it might be easy to extend. Like the status matrix might become cost matrix with integer number
 std::map<Point, int>  *pointStatus; //map from point to its status
 // why is this a map instead of a set?
 //this map provide the interation information from point to its iteration
 std::map<Point, int>  *open; //all the reached squares with its iteration 
 std::set<Point> *closed; //previous traversed squares
 std::vector<Point> path; //path from start to end

 // should be const (as should various other methods)
// Return the neighbors of the point, no more than 4 points.
  std::vector<Point> getNeighbors(Point point) const;
 // ??
 //valid point is the point in the map bound
  bool validPoint(Point point) const; 
 // what is iteration?
 //iteration is shortest path length to reach this point
 //Use dijkstra shortest path algorithm to get the shortest length
 int shortestLength(int iteration);

 //get the path which from destination to the start point, the length is less than given length
  std::vector<Point> getPath(Point point, int iteration) ;
 //find the shortest path from start to the end
 std::vector<Point> findPath(Point start, Point end);
 PathFinder(int w, int h);
 ~PathFinder();
};

