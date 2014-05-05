ObjectTracking
==============

CIS542 Project

There are two direcotries mini-shark  and  cis542-project

In the mini-shark there are some files which is already available for the the mini-shark control system. It include the detector file which is repsonsible to provide position of the object.



In the cis542-project direcotry, there are several files for the object tracking with obstacle avoidance.
It includes:
pathFinder.h and pathFinder.cpp  are responsible to provide the path from current mini-shark position to the current object position. It will publish this path message to the pathTransfer. It subscribe the mini-shark position message and object position message.

pathTransfer.h and pathTransfer.cpp are responsible for converting the path to the command of linear and angular velocity of mini-shark. It publish velocity message several times according to the path information. It subscribe path message and mini-shark direction message. 



