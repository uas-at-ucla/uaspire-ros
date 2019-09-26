#!/usr/bin/env node

const rcl = require("rclnodejs");

async function start() {
    await rcl.init();
    console.log("Initialized ROS client");

    const MsgCommand = rcl.require('uaspire_msgs/msg/Command');
    const MsgSensors = rcl.require('uaspire_msgs/msg/Sensors');

    const node = rcl.createNode("uaspire_ground");
    node.createSubscription(MsgSensors, "uaspire/sensors", (sensors) => {
        console.log("Received sensors: ", sensors);
    });
    rcl.spin(node);
}

start().catch((err) => console.error("Unhandled error:", err));
