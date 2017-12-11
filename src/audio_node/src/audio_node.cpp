/* Copyright (C) 2017 Emil Albin Ryberg, Albert Sonne Olesen,
 * Nikolaj Binder Amtoft, Thomas Deuffic, 
 * Benedek Gergály, Jonas Brødholt, Mads Riis Thomsen - All Rights Reserved
 * 
 * You may use, distribute and modify this code under the
 * terms of the MIT license. */

#include <unistd.h>
#include <std_msgs/String.h>
#include <ros/ros.h>
#include <sound_play/sound_play.h>

ros::NodeHandle *nh_ptr;
sound_play::SoundClient *sound_client_ptr;

//Function declaration
void playSound(const std_msgs::StringConstPtr &msg);

//start of main
int main(int argc, char **argv)
{
  ros::init(argc, argv, "audio_node");

  //giving handles to specific ros nodes to minize writing time
  ros::NodeHandle nh;
  nh_ptr = &nh;
  sound_play::SoundClient sc;
  sound_client_ptr = &sc;

  //subscribes to a node (audio_play_sound)
  ros::Subscriber sub = nh.subscribe("qr_reader/qr_code/data", 10, playSound);
  ros::spin();

  return 0;
}

//Function to play sounds according to the message recieved
void playSound(const std_msgs::StringConstPtr &msg)
{
  std::string qr_code_data = msg->data;

  //Check that it has actually read some data
  if(qr_code_data!= "")
  {
    sound_client_ptr->say(qr_code_data);
  }
}
