#include "pathFinder.h"

std::vector<Point> PathFinder::getNeighbors(Point point){
  std::vector<Point> result;
  if (point.x + 1 < width)
		     result.push_back(Point( point.x+1,point.y));
  if(point.x - 1 >= 0)
       result.push_back(Point( point.x-1,point.y));
  if (point.y + 1 < height)
		     result.push_back(Point( point.x,point.y + 1));
  if(point.y - 1 >= 0)
		       result.push_back(Point( point.x,point.y - 1));
  return result;
}


bool PathFinder::validPoint(Point point){
  return (
	  point.x >=0 && point.x < width &&
	  point.y >=0 && point.y < height
	  );
}


int PathFinder::shortestLength(int iteration=1){
  std::vector<Point> neighbors;
  std::set<Point>::iterator it;
  std::set<Point> * newClosed = new std::set<Point>;

  for(it=closed->begin(); it != closed->end(); it++){
    neighbors=getNeighbors(*it);
    for(int i=0; i< neighbors.size(); i++){
      Point neighbor = neighbors[i];

      if(validPoint(neighbor) && (*open)[neighbor] == -1) return iteration;

      if(validPoint(neighbor) && (*open)[neighbor] == 0 && (*pointStatus)[neighbor] !=1){
	(*open)[neighbor]=iteration +1;
	newClosed->insert(neighbor);
      }
    }
  }


  delete closed;
  closed = newClosed;

  iteration=shortestLength(iteration+1);
  return iteration;
}


std::vector<Point> PathFinder::getPath(Point point, int iteration){
  //reverst the direction to the start --> end
  if(iteration==0){
    std::reverse(path.begin(), path.end());
    return path;
  }


  std::vector<Point> neighbors = getNeighbors(point);
  for(int i=0; i<neighbors.size(); i++){

    Point neighbor=neighbors[i];

    if(validPoint(neighbor) && (*open)[neighbor]==iteration){
      path.push_back(neighbor);
      return getPath(neighbor, iteration-1);
    }
  }
  //If there is no available path, return the empty 
  std::vector<Point> result;
  return result;
}


std::vector<Point> PathFinder::findPath(Point start, Point end){


  std::vector<Point> result;

  if(pointStatus==nullptr) return result;

//End point blocked
  if((*pointStatus)[end]==1) return result;

//End is same as start
  if (start.x == end.x && start.y == end.y){
    result.push_back(start);
    return result;
  }

//Store start & end coordinates with lowest & highest passability, respectively
  open->clear();
  (*open)[start]=1;
  (*open)[end]=-1;

//Create a set of closed pointStatus and add start to it
  closed->clear();
  closed->insert(start);

  result=getPath(end, shortestLength());
  if (result.size() > 0) result.push_back(end);
  return result;
}

PathFinder::PathFinder(int w, int h){
  width=w;
  height=h;
  pointStatus = new std::map<Point, int>;
  open = new std::map<Point, int>;
  closed = new std::set<Point>;
}

PathFinder::~PathFinder(void){
  delete pointStatus;
  delete open;
  delete closed;
}


//global variable to store the vehicle position and object position
Point vehicle_position, object_position;

int main(int argc, char **argv) {
  //set up the map space 
  PathFinder * pathfinder = new PathFinder(40,80);

  //set up the map from point to status
  for(int i=0; i < pathfinder->width; i++){
    for(int j=0; j < pathfinder->height; j++){
      pathfinder->pointStatus->insert(std::pair<Point, int> (Point(i,j), map[i][j]));
    }
  }
  ros::init(argc, argv, "pathFinder");
  
  ros::Subscriber objectPositionSub = nh.subscribe("/detected_position", 1, UpdateObjectPosition);
  ros::Subscriber vehiclePositionSub = nh.subscribe("/vehicle_position", 1, UpdateVehiclePosition);
  
  ros::Publisher pathPub = nh.advertise<path>("/vehicle_path",1);	 
  
  ros::Rate r(50);
  while(ros::ok()) {
    ros::spinOnce();
    
    path cmd = pathfinder->findPath(vehicle_position, object_position);
    pathPub.publish(cmd);
        
    r.sleep();
  }
  
  return 0;
}





