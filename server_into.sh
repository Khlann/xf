#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

docker build Dockerfile -t=cnshe_robot_central_server:v1
docker run -itd -P --name cnshe_robot_central_server -v $DIR:/root/CNSHE_RobotCentralServer cnshe_robot_central_server:v1 /bin/bash
