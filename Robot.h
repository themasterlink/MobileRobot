//
// Created by Maximilian Denninger on 2019-04-27.
//

#ifndef MOBILE_ROBOTIC_ROBOT_H
#define MOBILE_ROBOTIC_ROBOT_H

#include <vector>
#include "Map.h"
#include "BaseTypes.h"

class Robot {
public:
	using SensorPositions = std::vector<std::pair<double, double> >;

	Robot(const SensorPositions& sensorPositions, Map& map, double speed, const iPoint2& startPose, double startAngle, double maxSensorDist): m_map(map){
		m_sensorPositions = sensorPositions;
		m_currentPose = startPose;
		m_currentAngle = startAngle;
		m_currentSpeed = speed;
		m_maxSensorDist = maxSensorDist;
	}


	// all angles have to be in rad
	void turn(double addedAngle){
		auto newAngle = m_currentAngle + addedAngle;
		while(newAngle > M_PI){
			newAngle -= 2 * M_PI;
		}
		while(newAngle <= -M_PI){
			newAngle += 2 * M_PI;
		}
		m_currentAngle = newAngle;
	}

	bool move(double timeStep = 1){
		const auto newPose = m_currentPose + iPoint2(cos(m_currentAngle) * m_currentSpeed, sin(m_currentAngle) * m_currentSpeed);
		if(m_map.isInFreeSpace(newPose)){
			m_currentPose = newPose;
			return true;
		}
		return false;
	}

	iPoint2 getPosition(){
		return m_currentPose;
	}

	double getAngle(){
		return m_currentAngle;
	}

	dPoint2 getDir(){
		return dPoint2(cos(m_currentAngle), sin(m_currentAngle));
	}

	SensorPositions& getSensorPositions(){
		return m_sensorPositions;
	}

	std::vector<double> getSensorMeasurements(){
		std::vector<double> sensorMeasurements;
		double res = 0.1;
		for(const auto& sensorPose : m_sensorPositions){
			const double sensorAngle = sensorPose.second + m_currentAngle;
			auto currentBeamPose = dPoint2(cos(sensorAngle) * sensorPose.first, sin(sensorAngle) * sensorPose.first) + m_currentPose;
			auto updateStep = dPoint2(cos(sensorAngle) * res, sin(sensorAngle) * res);
			double dist = 0.;
			bool found = false;
			while(dist < m_maxSensorDist){
				currentBeamPose += updateStep;
				if(!m_map.isInFreeSpace(iPoint2(currentBeamPose))){
					found = true;
					sensorMeasurements.emplace_back(dist);
					break;
				}
				dist += res;
			}
			if(!found){
				sensorMeasurements.emplace_back(m_maxSensorDist);
			}
		}
		return sensorMeasurements;
	}

private:
	SensorPositions m_sensorPositions;
	Map& m_map;
	iPoint2 m_currentPose;
	double m_currentAngle;
	double m_currentSpeed;
	double m_maxSensorDist;


};


#endif //MOBILE_ROBOTIC_ROBOT_H
