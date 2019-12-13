#include <iostream>
#include <fstream>
#include <math.h>
#include "ros/ros.h"
#include "unistd.h"
#include "ardrone_autonomy/Navdata.h"
#include "string.h"
#include <iostream>
#include <fstream>
#include <std_msgs/Float32.h>

using namespace std;
ardrone_autonomy::Navdata::ConstPtr navdata;
static bool isNavdataReady = false;

void ardroneNavdataCallback(const ardrone_autonomy::Navdata::ConstPtr& msg){
  navdata = msg;
  isNavdataReady = true;
}

int main(int argc, char* argv[])
{
  cout<<"Ros Ardrone Initialize"<<endl;
  ros::init(argc, argv, "ardrone_example");
  ros::NodeHandle nh;

    
  ros::Rate loop_rate(10);
  ros::spinOnce();

  ros::Subscriber subscriberNavdata = nh.subscribe("/ardrone/navdata", 1, ardroneNavdataCallback);
  ros::Publisher publisher = nh.advertise<std_msgs::Float32>("/fi", 1000);
  
  ros::spinOnce();

  std::ofstream File ("/home/ardrone_cat/test.txt",std::ofstream::out);

  while (ros::ok()){
    if(!isNavdataReady){
      
      
  
      ros::spinOnce();
      loop_rate.sleep();

      continue;
    }

    /*if(!navdata->tags_xc.empty() && !navdata->tags_yc.empty()) {
      cout << "X: " << navdata->tags_xc.front() << " Y: " << navdata->tags_yc.front() << endl;
      File << "X: " << navdata->tags_xc.front() << " Y: " << navdata->tags_yc.front() << endl;
    }*/
	
	float fi = 10*navdata->ay;
   

    //cout << "X: " << navdata->ax << " Y: " << navdata->ay << endl;
    
    cout << "fi: "<< fi  << endl;
    File << "X: " << navdata->ax << " Y: " << navdata->ay << endl;
    
    
    std_msgs::Float32 msg;
    msg.data = fi;
    publisher.publish(msg);
    

    ros::spinOnce();
    loop_rate.sleep();
  }

  File.close();
  return 0;
}
