#!/usr/bin/python3
# -*- coding: utf-8 -*-
from time import sleep
from math import pi

from behaviours.action.action import *
from behaviours.robot_behaviour import RobotBehavior
from logs.log_manager import *


class WindAction(Action):
    def __init__(self, geo, color):

        self.logger = LogManager().getlogger(self.__class__.__name__, Logger.SHOW, INFO)

        self.color = color

        if self.color == RobotBehavior.YELLOW_SIDE:
            self.actionpoint = geo.get('WindYellow')
            self.orientation = -pi/2
        else:
            self.actionpoint = geo.get('WindBlue')
            self.orientation = pi/2

        self.actionpoint_precision = 10

    def procedure(self, robot):
        self.logger(INFO, 'Action is launch on', robot.__class__.__name__)
        self.logger(INFO, 'Go to Wind action ')

        robot.wheeledbase.turnonthespot(self.orientation)
        robot.wheeledbase.wait()

        x_in, y_in, theta_in = robot.wheeledbase.get_position()

        if self.color == RobotBehavior.YELLOW_SIDE:
            x_sp, y_sp, theta_sp = x_in, y_in - 500, theta_in
        else:
            x_sp, y_sp, theta_sp = x_in, y_in + 500, theta_in

        # Deploy arm
        sleep(1)

        robot.wheeledbase.goto(x_sp, y_sp, theta_sp)

        # UnDeploy arm
        sleep(1)
