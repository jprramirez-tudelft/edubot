#include "robot_sim.hpp"

RobotSim::RobotSim(): 
    Robot(4),
    //HOME({DEG2RAD * 45, DEG2RAD * 110, DEG2RAD * 180, DEG2RAD * 30})
    HOME({DEG2RAD * 0, DEG2RAD * 0, DEG2RAD * 0, DEG2RAD * 0})         
{
    /* Bring to initial state */
    this->homing();
    this->set_des_gripper(GripperState::Open);
}

void RobotSim::set_des_q_single_rad(uint servo, float q)
{
    this->q.at(servo) = q;
}
void RobotSim::set_des_q_single_deg(uint servo, float q)
{
    this->set_des_q_single_rad(servo, q * RAD2DEG);
}

void RobotSim::set_des_q_rad(const std::vector<float> & q)
{
    assert(q.size() == this->n);
    for(uint i = 0; i < this->n; i++)
    {
        this->q.at(i) = q.at(i);
    }

}
void RobotSim::set_des_q_deg(const std::vector<float> & q)
{
    assert(q.size() == this->n);
    for(uint i = 0; i < this->n; i++)
    {
        this->q.at(i) = q.at(i)*DEG2RAD;
    }
}

void RobotSim::set_des_gripper(GripperState state)
{
    if(state == GripperState::Open)
    {
        this->gripper = GripperState::Open;
    }
    else if(state == GripperState::Closed)
    {
        this->gripper = GripperState::Closed;
    }
}

void RobotSim::homing()
{
    for(uint i = 0; i < this->n; i++)
    { 
        this->q.at(i) = this->HOME.at(i);
    }
}


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
    
  rclcpp::spin(std::make_shared<RobotSim>());
  rclcpp::shutdown();
  return 0;
}