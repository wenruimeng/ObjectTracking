#ifndef PATH_FINDER
#define PATH_FINDER

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

// This is a status matrix for the grid map
int map[40][80] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0},
{0,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0},
{0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
{0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0},
{0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0},
{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0},
{0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0},
{0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0},
{0,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
{0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1},
{0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0},
{0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0}
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

//Assume the movement is only up down right left, no diagonal movement allowed
//No wrap arround allowed, the map doesn't allow exceed the boundary ??
class PathFinder{
public:
  int width, height;
 std::map<Point, int>  *pointStatus; //map from point to its status
 std::map<Point, int>  *open; //all untraversed squares
 std::set<Point> *closed; //previous traversed squares
 std::vector<Point> path; //path from start to end

// Return the neighbors of the point, no more than 4 points.
 std::vector<Point> getNeighbors(Point point);
 //valid point is the point in the map bound
 bool validPoint(Point point); 
 //Use dijkstra shortest path algorithm to get the shortest length
 int shortestLength(int iteration);
 //get the path which from destination to the start point, the length is less than given length
 std::vector<Point> getPath(Point point, int iteration);
 //find the shortest path from start to the end
 std::vector<Point> findPath(Point start, Point end);
 PathFinder(int w, int h);
 ~PathFinder();
};
#endif
