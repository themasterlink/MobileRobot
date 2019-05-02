#include <iostream>

#include "src/Robot.h"
#include "src/Map.h"
#include "src/Visualizer.h"

int main(){
	Robot::SensorPositions sensorPositions;
	sensorPositions.emplace_back(25, 0.52359877558);
	sensorPositions.emplace_back(25, -0.52359877558);
	Map map("../RoboterMap.png");

	Robot robot(sensorPositions, map, 4, map.size() * 0.4, 0., 100000);

	Visualizer vis(map, robot);
	vis.run();

	return 0;
}