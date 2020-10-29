# -*- coding: utf-8 -*-
from time import sleep
from math import pi

from behaviours.action.action import *
from behaviours.robot_behaviour import RobotBehavior
from logs.log_manager import *


class ActivateLighthouseAction(Action):
    def __init__(self, geo, color):

        self.logger = LogManager().getlogger(self.__class__.__name__, Logger.SHOW, INFO)

        self.color = color

        if self.color == RobotBehavior.YELLOW_SIDE:
            self.actionpoint = geo.get('ActivateLighthouseYellow')
            self.orientation = 0
        else:
            self.actionpoint = geo.get('ActivateLighthouseBlue')
            self.orientation = 0

        self.actionpoint_precision = 10

    def procedure(self, robot):
        self.logger(INFO, 'Action is launch on', robot.__class__.__name__)
        self.logger(INFO, 'Go to Lighthouse action ')

        robot.wheeledbase.max_linvel.set(300)

        #robot.actionneur.move_elevator(2,0)
        #robot.actionneur.set_clamp_position(4,70)
        #robot.actionneur.set_clamp_position(3,100)
        robot.actionneur.set_clamp_position(2,40)
        sleep(2)

        robot.wheeledbase.turnonthespot(self.orientation)
        robot.wheeledbase.wait()
        sleep(1)

        x_in, y_in, theta_in = robot.wheeledbase.get_position()

        if self.color == RobotBehavior.YELLOW_SIDE:
            x_sp, y_sp, theta_sp = x_in - 170, y_in, theta_in
        else:
            x_sp, y_sp, theta_sp = x_in - 170, y_in, theta_in

        robot.wheeledbase.goto(x_sp, y_sp, theta_sp)
        robot.wheeledbase.wait()

        robot.wheeledbase.goto(x_in, y_in, theta_in)
        robot.wheeledbase.wait()

        robot.actionneur.set_clamp_position(2,40)

        #robot.actionneur.move_elevator(2,1)

        robot.wheeledbase.max_linvel.set(600)

        robot.display.addPoints(15)