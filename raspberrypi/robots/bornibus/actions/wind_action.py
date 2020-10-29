#!/usr/bin/python3
# -*- coding: utf-8 -*-
from time import sleep
from math import pi

from behaviours.action.action import *
from behaviours.robot_behaviour import RobotBehavior
#from behaviours.robot_behaviour import AviodanceBehaviour
from logs.log_manager import *


class WindAction(Action):
    def __init__(self, geo, color):

        self.logger = LogManager().getlogger(self.__class__.__name__, Logger.SHOW, INFO)

        self.color = color

        if self.color == RobotBehavior.YELLOW_SIDE:
            self.actionpoint = geo.get('WindYellow')
            self.orientation = -pi
        else:
            self.actionpoint = geo.get('WindBlue')
            self.orientation = -pi

        self.actionpoint_precision = 10

    def procedure(self, robot):
        self.logger(INFO, 'Action is launch on', robot.__class__.__name__)
        self.logger(INFO, 'Go to Wind action ')

        robot.wheeledbase.max_linvel.set(300)

        if self.color == RobotBehavior.YELLOW_SIDE:
            robot.actionneur.set_windsock_arm_position(100)
            sleep(1)

        if self.color == RobotBehavior.YELLOW_SIDE:
            robot.wheeledbase.turnonthespot(-pi/2)
        else:
            robot.wheeledbase.turnonthespot(-pi/2)

        robot.wheeledbase.wait()

        if self.color == RobotBehavior.BLUE_SIDE:
            robot.actionneur.set_windsock_arm_position(100)
            sleep(1)

        x_in, y_in, theta_in = robot.wheeledbase.get_position()

        if self.color == RobotBehavior.YELLOW_SIDE:
            x_sp, y_sp, theta_sp = x_in, y_in - 520, theta_in
        else:
            x_sp, y_sp, theta_sp = x_in, y_in + 520, theta_in

        robot.wheeledbase.goto(x_sp, y_sp, theta_sp)

        if self.color == RobotBehavior.BLUE_SIDE:
            robot.wheeledbase.turnonthespot(0)
            robot.wheeledbase.wait()

        robot.actionneur.set_windsock_arm_position(180)
        sleep(1)

        robot.wheeledbase.max_linvel.set(600)

        robot.display.addPoints(15)
