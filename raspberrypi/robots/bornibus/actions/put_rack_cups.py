#!/usr/bin/python3
# -*- coding: utf-8 -*-
from time import sleep
from math import pi

from behaviours.action.action import *
from behaviours.robot_behaviour import RobotBehavior
from logs.log_manager import *

class PutRackCupsAction(Action):
    def __init__(self, geo, color, idx):

        self.logger = LogManager().getlogger(self.__class__.__name__, Logger.SHOW, INFO)

        self.color = color
        self.idx = idx

        if self.color == RobotBehavior.YELLOW_SIDE:
            self.actionpoint = geo.get('PutYellow'+str(self.idx))
            self.orientation = 0
        else:
            self.actionpoint = geo.get('PutBlue'+str(self.idx))
            self.orientation = 0

        self.actionpoint_precision = 10

    def procedure(self, robot):
        self.logger(INFO, 'Action is launch on', robot.__class__.__name__)
        self.logger(INFO, 'Go to Put action '+str(self.idx))

        robot.wheeledbase.turnonthespot(self.orientation)
        robot.wheeledbase.wait()

        x_in, y_in, theta_in = robot.wheeledbase.get_position()

        if self.color == RobotBehavior.YELLOW_SIDE:
            if self.idx == 1:
                x_sp, y_sp, theta_sp = x_in - 250, y_in, theta_in
            else:
                x_sp, y_sp, theta_sp = x_in + 250, y_in, theta_in
        else:
            if self.idx == 1:
                x_sp, y_sp, theta_sp = x_in - 250, y_in, theta_in
            else:
                x_sp, y_sp, theta_sp = x_in + 250, y_in, theta_in

        if self.idx == 1:
            robot.actionneur.move_elevator(0,0)
            robot.actionneur.move_elevator(1,0)
            robot.actionneur.move_elevator(2,0)

        robot.wheeledbase.goto(x_sp, y_sp, theta_sp)
        robot.wheeledbase.wait()
        sleep(3)

        #Ouverture des pinces
        if self.idx == 1:
            robot.actionneur.set_clamp_position(2,110)
            robot.actionneur.set_clamp_position(3,110)
            robot.actionneur.set_clamp_position(4,110)
        else:     
            robot.actionneur.set_clamp_position(0,70)
            robot.actionneur.set_clamp_position(1,65)

        sleep(1)  

        #Les ascenseurs remontent
        if self.idx == 2:
            robot.actionneur.move_elevator(0,1)
            robot.actionneur.move_elevator(1,1)
            robot.actionneur.move_elevator(2,1)

        #Le robot recule à sa position de départ
        robot.wheeledbase.goto(x_in, y_in, theta_in)
        robot.wheeledbase.wait()
        
        if self.idx == 1:
            robot.display.add_points(5)
        else:
            robot.display.add_points(7)