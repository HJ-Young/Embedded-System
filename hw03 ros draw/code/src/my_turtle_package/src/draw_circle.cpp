#include "ros/ros.h"
#include<geometry_msgs/Twist.h> //运动速度结构体类型  geometry_msgs::Twist的定义文件

#define PI 3.14159265358979323846
 
int main(int argc, char *argv[])
{
    int iterator = 0; //Set an iterator to turn turtle around
    ros::init(argc, argv, "vel_ctrl");  //对该节点进行初始化操作
    ros::NodeHandle n;         //申明一个NodeHandle对象n，并用n生成一个广播对象vel_pub
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    //vel_pub会在主题"/cmd_vel"(机器人速度控制主题)里广播geometry_msgs::Twist类型的数据
    ROS_INFO("draw_circle start...");//输出显示信息
    
    srand(time(0));
    ros::Rate rate(1);
    
    while(ros::ok())
    {
        geometry_msgs::Twist vel_cmd; //声明一个geometry_msgs::Twist 类型的对象vel_cmd，并将速度的值赋值到这个对象里面
 
        vel_cmd.linear.x = 1.0;//前后（+-） m/s
        vel_cmd.linear.y = 0.0;  //左右（+-） m/s
        vel_cmd.linear.z = 0.0;
        iterator++;
 
        if(iterator==7){
            iterator = 0;
            vel_cmd.linear.x = 0;
            vel_cmd.angular.z = PI * 2 / 3;
    	}
        vel_pub.publish(vel_cmd); //赋值完毕后，发送到主题"/cmd_vel"。机器人的核心节点会从这个主题接受发送过去的速度值，并转发到硬件体上去执行
 
        ros::spinOnce();//调用此函数给其他回调函数得以执行(比例程未使用回调函数)
        rate.sleep();
    }
    return 0;
}
