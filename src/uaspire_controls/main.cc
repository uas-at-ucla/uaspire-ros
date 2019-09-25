#include <functional>

#include <rclcpp/rclcpp.hpp>
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
    ros::WallRate _rate;

public:
    RCLCPP_SHARED_PTR_DEFINITIONS(ControlsNode)

    ControlsNode()
        : Node("uaspire_controls"),
        _rate(1.0)
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
    }

    void on_message(const UaspireCommand::SharedPtr cmd)
    {
        RCLCPP_INFO(get_logger(), "Command received: %s", cmd->data.c_str());
    }

    void loop() {
        while (ros::ok()) {
            UaspireSensors sensors;
            sensors.position = ros::Clock(RCL_STEADY_TIME).now().seconds();
            _sensors_publisher->publish(sensors);
            RCLCPP_INFO(get_logger(), "loop");
            ros::spin_some(shared_from_this());
            _rate.sleep();
        }
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv);
    {
        auto node = ControlsNode::make_shared();
        node->loop();
    }
    ros::shutdown();
    return 0;
}
