const rosidl_gen = require("rclnodejs/rosidl_gen");
const path = require("path");

const workspacePath = path.resolve(__dirname, "..", "..");

console.log(`Generating ROS NodeJS messages in workspace (${workspacePath})`)
rosidl_gen.generateInPath(workspacePath)
    .then(() => {
        console.log("Generated ROS NodeJS messages")
    }, (err) => {
        console.error("Error generating ROS NodeJS messages: ", err);
        process.exit(1);
    });
