//
// Created by Maximilian Denninger on 2019-04-27.
//

#ifndef MOBILE_ROBOTIC_MAP_H
#define MOBILE_ROBOTIC_MAP_H

#include "BaseTypes.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


class Map {
public:

	Map(const std::string& filePath){
		m_savedImage = cv::imread(filePath, CV_LOAD_IMAGE_COLOR);
		cv::resize(m_savedImage, m_savedImage, cv::Size(), 0.5, 0.5);
		m_xSize = m_savedImage.size().width;
		m_ySize = m_savedImage.size().height;
		m_values.resize(m_xSize);
		for(unsigned int i = 0; i < m_xSize; ++i){
			m_values[i].resize(m_ySize);
		}
		for(unsigned int i = 0; i < m_xSize; ++i){
			for(unsigned int j = 0; j < m_ySize; ++j){
				const auto colorValue = m_savedImage.at<cv::Vec3b>(j, i);
				const double sum = colorValue[0] + colorValue[1] + colorValue[2];
				m_values[i][j] = sum != 0;
			}
		}
	}

	bool isInMap(const iPoint2& pose){
		return 0 <= pose[0] and pose[0] < m_xSize and 0 <= pose[1] and pose[1] < m_ySize;
	}

	cv::Mat& getImage(){
		return m_savedImage;
	}

	iPoint2 size(){
		return iPoint2(m_xSize, m_ySize);
	}


	bool isInFreeSpace(const iPoint2& pose){
		if(isInMap(pose)){
			return m_values[pose[0]][pose[1]];
		}
		return false;
	}

	using OccupanyMap = std::vector<std::vector< bool> >;

private:
	OccupanyMap m_values;
	cv::Mat m_savedImage;
	int m_xSize, m_ySize;
};


#endif //MOBILE_ROBOTIC_MAP_H
