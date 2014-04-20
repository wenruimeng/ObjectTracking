#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include "sensor_msgs/Image.h"
#include <leader_follower/object_position.h>

class Detector {
public:
	ros::NodeHandle nh;
	ros::Subscriber sub, back_dist_sub;
	ros::Publisher	pub;
	static const int BLOCKSIZE = 16;
	int BACKGROUND_DISTANCE;
	
	//Detected object data
	uint32_t avg_dist;
	int32_t bl_frm_center;
	
	
	Detector():
	nh("~")
	{
		nh.getParam("background_distance", BACKGROUND_DISTANCE);
		ROS_INFO("Background distance is set to %d", BACKGROUND_DISTANCE);
		sub = nh.subscribe<sensor_msgs::Image>("/camera/depth/image_raw", 1000, &Detector::depthCallBack, this);
		back_dist_sub = nh.subscribe("/landshark_demo/leader_bkdist", 1, &Detector::backDistCallBack, this);
		pub = nh.advertise<leader_follower::object_position>("/detected_position",1);
	}

private:
	void backDistCallBack(const std_msgs::UInt32::ConstPtr& val) {
		if(val->data != BACKGROUND_DISTANCE) 
			BACKGROUND_DISTANCE = val->data;
	}
	
	
	void depthCallBack(const sensor_msgs::Image::ConstPtr& image) {
		uint32_t depth[36] = {0};
		char buffer[200], temp_buf[10];
		
		int row = 232, col = 32;
		int counter = 0;
	
		buffer[0] = '\0';
	
		while(counter < 36) {
			depth[counter] = getBlockAvg(image, row, col, BLOCKSIZE);
			col = col + BLOCKSIZE;		
			sprintf(temp_buf, "%d  ", depth[counter]);
			counter++;
			strcat(buffer, temp_buf);
		}
	
		//ROS_INFO("%s", buffer);
		uint32_t min = 10000;
		for(int i = 0; i < 36; i++) {
			if(depth[i] < min)
				min = depth[i];
		}
		
		//ROS_INFO("Min: %d", min);	
		detectObject(depth);
		publishObjectPosition();
	}

	uint16_t getData(const sensor_msgs::Image::ConstPtr& image, int row, int col) {
		uint16_t temp;
		int index;
		index = row * image->step + col * 2;
		memcpy(&temp, &(image->data[index]), 2);
		return temp;
	}


	uint16_t getBlockAvg(const sensor_msgs::Image::ConstPtr& image, int row_start, int col_start, int blockSize) {
		int i, j;
		uint32_t sum = 0, val;
		int counter = 0;
		for(i = row_start; i < (row_start + blockSize); i++) {
			for( j = col_start; j < (col_start + blockSize); j++) {
				val = getData(image, i, j);
				if(val > 50) {
					sum += val;
					counter++;
				}
			}
		}
		
		if(counter < 100) {
			//ROS_WARN("High number of dark pixels being detected. Move Kinect");
			return (uint16_t)(-1);
		}
	
		else {
			sum = sum / counter;
			return (uint16_t)sum;
		}
	}
	
	
	void detectObject(uint32_t *depth) {
		int i;
		int counter;
		bool present[35] = {false};
		
		for(i = 0; i < 17; i++) {
			if(depth[17 - i] < BACKGROUND_DISTANCE) {
				findRestOfObject(depth, present, 17 - i);
				break;
			}
			
			else if(depth[17 + i] < BACKGROUND_DISTANCE) {
				findRestOfObject(depth, present, 17 + i);
				break;
			}
		}
		
		
		avg_dist = 0;
		bl_frm_center = 0;
		counter = 0;
		for(i = 0; i < 35; i++) {
			if(present[i]) {
				avg_dist += depth[i];
				bl_frm_center += i;
				counter++;
			}
		}
		
		if(counter == 0) {
			avg_dist = 	BACKGROUND_DISTANCE;
			bl_frm_center = 0;
		}
		
		else {
			avg_dist = avg_dist / counter;
			bl_frm_center = bl_frm_center / counter;
			bl_frm_center = bl_frm_center - 17;
		}
		
		//ROS_INFO("Distance: %d\t\t\tOffset: %d", avg_dist, bl_frm_center);
				
	}
	
	void findRestOfObject(uint32_t *depth, bool *array, int position) {
		int i;
		i = position;
		while( (i != 0) && (depth[i] < BACKGROUND_DISTANCE) ) {
			array[i] = true;
			i--;
		}
		
		i = position;
		while( (i != 35) && (depth[i] < BACKGROUND_DISTANCE) ) {
			array[i] = true;
			i++;
		}
	}
	
	void publishObjectPosition() {
		leader_follower::object_position curPos;
		curPos.avg_distance = avg_dist;
		curPos.blocks_from_center = bl_frm_center;
		curPos.stamp = ros::Time::now();
		pub.publish(curPos);
	}
};	
	




int main(int argc, char **argv) {
	ros::init(argc, argv, "detector");
	Detector d;
	ros::spin();	
	
	return 0;
}







