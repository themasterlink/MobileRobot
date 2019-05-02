#include <iostream>

#include "Robot.h"
#include "Map.h"
#include "Visualizer.h"

int main(){
	Robot::SensorPositions sensorPositions;
	sensorPositions.emplace_back(25, 0.52359877558);
	sensorPositions.emplace_back(25, -0.52359877558);
	Map map("/Users/Max/work/workspace/mobile-robotic/RoboterMap.png");

	Robot robot(sensorPositions, map, 4, map.size() * 0.4, 0., 100000);

	Visualizer vis(map, robot);
	vis.run();

	return 0;
}