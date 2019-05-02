//
// Created by Maximilian Denninger on 2019-05-01.
//

#ifndef MOBILE_ROBOTIC_ROBOTCONTROLLER_H
#define MOBILE_ROBOTIC_ROBOTCONTROLLER_H

#include "Robot.h"


class RobotController {
public:

	enum class MoveType {
		TurnLeft = 0,
		TurnRight = 1,
		Move = 2
	};

	RobotController(Robot& robot): m_robot(robot){
		m_lastMove = MoveType::Move;
	};

	void update(){
		const auto sensor = m_robot.getSensorMeasurements();
		const double turnAngle = M_PI / 45.;
		if(sensor[1] < 15.0 || sensor[0] < 15.0){
			if(m_lastMove != MoveType::Move){
				if(m_lastMove == MoveType::TurnLeft){
					m_robot.turn(turnAngle);
				}else{
					m_robot.turn(-turnAngle);
				}
				return;
			}
		}
		if(sensor[1] < 15.0){
			m_robot.turn(turnAngle);
			m_lastMove = MoveType::TurnLeft;
		}else if(sensor[0] < 15.0){
			m_robot.turn(-turnAngle);
			m_lastMove = MoveType::TurnRight;
		}else{
			m_robot.move(1);
			m_lastMove = MoveType::Move;
		}
	}

private:
	Robot& m_robot;
	MoveType m_lastMove;

};


#endif //MOBILE_ROBOTIC_ROBOTCONTROLLER_H
