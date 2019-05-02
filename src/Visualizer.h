//
// Created by Maximilian Denninger on 2019-04-27.
//

#ifndef MOBILE_ROBOTIC_VISUALIZER_H
#define MOBILE_ROBOTIC_VISUALIZER_H


#include "Map.h"
#include "Robot.h"
#include "RobotController.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Visualizer {

public:
	Visualizer(Map& map, Robot& robot): m_map(map), m_robot(robot){};

	void run(){
		RobotController robotController(m_robot);
		while(true){
			m_map.getImage().copyTo(m_currentFrame);
			drawRobot();
			drawSensors();


			cv::imshow("Robot Simuation", m_currentFrame);
			char input = (char) cv::waitKey(10);
			if(input == 27){
				break;
			}
			robotController.update();
		}
	}

	void drawRobot(){
		const auto pos = m_robot.getPosition();
		const auto opencvPos = cv::Point2d(pos[0], pos[1]);
		const auto dir = m_robot.getDir();
		int robotSize = 20;
		cv::circle(m_currentFrame, opencvPos, robotSize, CV_RGB(255, 0, 0), 2);
		cv::line(m_currentFrame, opencvPos, opencvPos + cv::Point2d(dir[0] * robotSize, dir[1] * robotSize), CV_RGB(0, 255, 0), 2);
	}

	void drawSensors(){
		const auto sensorMeasurements = m_robot.getSensorMeasurements();
		const auto sensorPositions = m_robot.getSensorPositions();
		const auto pos = m_robot.getPosition();
		const auto opencvPos = cv::Point2d(pos[0], pos[1]);
		for(unsigned int i = 0; i < sensorMeasurements.size(); ++i){
			const double sensorAngle = sensorPositions[i].second + m_robot.getAngle();
			const auto sensorPos= dPoint2(cos(sensorAngle) * sensorPositions[i].first, sin(sensorAngle) * sensorPositions[i].first) + pos;
			const auto endBeamPoint = dPoint2(cos(sensorAngle) * sensorMeasurements[i], sin(sensorAngle) * sensorMeasurements[i]) + sensorPos;

			cv::line(m_currentFrame, sensorPos.cv(), endBeamPoint.cv(), CV_RGB(128, 128, 0), 1);

		}
	}


private:

	Map& m_map;
	Robot& m_robot;

	cv::Mat m_currentFrame;

};


#endif //MOBILE_ROBOTIC_VISUALIZER_H
