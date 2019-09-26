#include <functional>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <std_msgs/msg/string.hpp>
#include <uaspire_msgs/msg/command.hpp>
#include <uaspire_msgs/msg/sensors.hpp>

namespace arg = std::placeholders;
namespace ros = ::rclcpp;
using UaspireCommand = ::uaspire_msgs::msg::Command;
using UaspireSensors = ::uaspire_msgs::msg::Sensors;

class ControlsNode : public ros::Node
{
private:
    ros::Subscription<UaspireCommand>::SharedPtr _command_subscription;
    ros::Publisher<UaspireSensors>::SharedPtr _sensors_publisher;
    ros::TimerBase::SharedPtr _timer;

public:
    RCLCPP_SHARED_PTR_DEFINITIONS(ControlsNode)

    ControlsNode()
        : Node("uaspire_controls")
    {
        _command_subscription = create_subscription<UaspireCommand>(
            "uaspire/commands",
            ros::QoS(10),
            std::bind(&ControlsNode::on_message, this, arg::_1)
        );
        _sensors_publisher = create_publisher<UaspireSensors>(
            "uaspire/sensors",
            ros::QoS(10)
        );
        _timer = create_wall_timer(std::chrono::milliseconds(1000),
            std::bind(&ControlsNode::on_loop, this));
    }

    void on_message(const UaspireCommand::SharedPtr cmd)
    {
        RCLCPP_INFO(get_logger(), "Command received: %s", cmd->data.c_str());
    }

    void on_loop() {
		UaspireSensors sensors;
		sensors.position = ros::Clock(RCL_STEADY_TIME).now().seconds();
		_sensors_publisher->publish(sensors);
		RCLCPP_INFO(get_logger(), "loop");
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv);
    {
        auto node = ControlsNode::make_shared();
		ros::spin(node);
    }
    ros::shutdown();
    return 0;
}
