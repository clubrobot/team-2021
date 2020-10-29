#!/usr/bin/python3
# -*- coding: utf-8 -*-
from time import sleep
from math import pi

from behaviours.action.action import *
from behaviours.robot_behaviour import RobotBehavior
from logs.log_manager import *

class GrabRackCupsAction(Action):
    def __init__(self, geo, color, idx):

        self.logger = LogManager().getlogger(self.__class__.__name__, Logger.SHOW, INFO)

        self.color = color
        self.idx = idx

        if self.color == RobotBehavior.YELLOW_SIDE:
            self.actionpoint = geo.get('GrabYellow'+str(self.idx))
            if self.idx == 1:
                self.orientation = -pi/2
            else:
                self.orientation = -pi
        else:
            self.actionpoint = geo.get('GrabBlue'+str(self.idx))
            if self.idx == 1:
                self.orientation = pi/2
            else:
                self.orientation = -pi

        self.actionpoint_precision = 10

    def procedure(self, robot):
        self.logger(INFO, 'Action is launch on', robot.__class__.__name__)
        self.logger(INFO, 'Go to Grab action '+str(self.idx))

        robot.wheeledbase.turnonthespot(self.orientation)
        robot.wheeledbase.wait()

        x_in, y_in, theta_in = robot.wheeledbase.get_position()

        if self.color == RobotBehavior.YELLOW_SIDE:
            if self.idx == 1:
                x_sp, y_sp, theta_sp = x_in, y_in + 250, theta_in
            else:
                x_sp, y_sp, theta_sp = x_in - 250, y_in, theta_in
        else:
            if self.idx == 1:
                x_sp, y_sp, theta_sp = x_in, y_in - 250, theta_in
            else:
                x_sp, y_sp, theta_sp = x_in - 250, y_in, theta_in

        # /!\ On considère que les ascenseurs sont montés

        #Ouverture de toutes les pinces
        robot.actionneur.set_clamp_position(0,70)
        robot.actionneur.set_clamp_position(1,65)
        robot.actionneur.set_clamp_position(2,110)
        robot.actionneur.set_clamp_position(3,110)
        robot.actionneur.set_clamp_position(4,110)
        sleep(1)  
        #Le robot avance de 250 mm, le dos face au rack
        robot.wheeledbase.goto(x_sp, y_sp, theta_sp)
        robot.wheeledbase.wait()
        #Les ascenseurs descendent
        robot.actionneur.move_elevator(0,0)
        robot.actionneur.move_elevator(1,0)
        robot.actionneur.move_elevator(2,0)
        #Fermeture des pinces
        robot.actionneur.set_clamp_position(2,25)
        robot.actionneur.set_clamp_position(3,30)
        robot.actionneur.set_clamp_position(4,10)
        #Les ascenseurs remontent
        robot.actionneur.move_elevator(0,1)
        robot.actionneur.move_elevator(1,1)
        robot.actionneur.move_elevator(2,1)
        #Le robot recule à sa position de départ
        robot.wheeledbase.goto(x_in, y_in, theta_in)
        robot.wheeledbase.wait()
        #Le robot se déplace de 100 mm sur le côté et se retourne (/!\ robot pas symétrique)
        x_in, y_in, theta_in = robot.wheeledbase.get_position()

        if self.color == RobotBehavior.YELLOW_SIDE:
            if self.idx == 1:
                x_sp, y_sp, theta_sp = x_in + 150, y_in, theta_in
            else:
                x_sp, y_sp, theta_sp = x_in, y_in - 150, theta_in pi
        else:
            if self.idx == 1:
                x_sp, y_sp, theta_sp = x_in + 150, y_in, theta_in -pi/2
            else:
                x_sp, y_sp, theta_sp = x_in, y_in + 150, theta_in pi

        robot.wheeledbase.goto(x_sp, y_sp, theta_sp)
        robot.wheeledbase.wait()

        if self.color == RobotBehavior.YELLOW_SIDE:
            if self.idx == 1:
                robot.wheeledbase.turnonthespot(pi/2)
            else:
                robot.wheeledbase.turnonthespot(pi)
        else:
            if self.idx == 1:
                robot.wheeledbase.turnonthespot(-pi/2)
            else:
                robot.wheeledbase.turnonthespot(pi)

        #Le robot avance de 250 mm, l'avant face au rack
        x_in, y_in, theta_in = robot.wheeledbase.get_position()

        if self.color == RobotBehavior.YELLOW_SIDE:
            if self.idx == 1:
                x_sp, y_sp, theta_sp = x_in, y_in + 250, theta_in
            else:
                x_sp, y_sp, theta_sp = x_in - 250, y_in, theta_in
        else:
            if self.idx == 1:
                x_sp, y_sp, theta_sp = x_in, y_in - 250, theta_in
            else:
                x_sp, y_sp, theta_sp = x_in - 250, y_in, theta_in

        robot.wheeledbase.goto(x_sp, y_sp, theta_sp)
        robot.wheeledbase.wait()
        #Les ascenseurs descendent
        robot.actionneur.move_elevator(0,0)
        robot.actionneur.move_elevator(1,0)
        #Fermeture des pinces
        robot.actionneur.set_clamp_position(0,30)
        robot.actionneur.set_clamp_position(1,15)
        #Les ascenseurs remontent
        robot.actionneur.move_elevator(0,1)
        robot.actionneur.move_elevator(1,1)
        #Le robot recule à sa position de départ
        robot.wheeledbase.goto(x_in, y_in, theta_in)
        robot.wheeledbase.wait()