#!/usr/bin/python3
# -*- coding: utf-8 -*-

from robots.bornibus.setup_bornibus import *
from behaviours.robot_behaviour import RobotBehavior
from behaviours.avoidance_behaviour import AviodanceBehaviour
from robots.bornibus.actions.take_cup_action import TakeCup
from robots.bornibus.actions.harbour_action import Harbour
from math import pi
COLOR = RobotBehavior.YELLO_SIDE
PREPARATION = False


class Bornibus(RobotBehavior):
    """This class is the main objet of bornibus robot, it contain all the action list and initial configuration to run a match

    Args:
        RobotBehavior (class): The main bornibus class inherit from the global robot behaviour in order to have a common behaviour for each robot you want
    """
    def __init__(self, manager, *args, timelimit=None, **kwargs):
        """The initialisation function create all functional module of the robot. This function also instanciate all the match actions

        Args:
            manager (class): One instance of the manager client. It is the client part of th proxy to have access of all the arduino daughter cards
            timelimit (int, optional): The match time limit, usualy set to 100 seconds. Defaults to None.
        """
        RobotBehavior.__init__(self, manager, *args,
                               timelimit=timelimit, **kwargs)

        self.avoidance_behaviour = AviodanceBehaviour(
            wheeledbase, roadmap, robot_beacon, sensors)

        self.wheeledbase = wheeledbase

        take1 = TakeCup(geogebra, 1)
        take2 = TakeCup(geogebra, 2)
        take3 = TakeCup(geogebra, 3)
        take4 = TakeCup(geogebra, 4)
        take5 = TakeCup(geogebra, 5)

        self.harbour = Harbour(geogebra, "Yellow")

        self.automate = [
            take5,
            take1,
            take2,
            take3,
            take4,
            self.harbour
        ]

        self.automatestep = 0

    def make_decision(self):
        """This function make a decision to choose the next action to play. Today it basically return th next action on list
           /!\ You can describe here you own decision behaviour but the return parameter needs to be the same.

        Returns:
            [function pointer, class pointer, tuple, float, float]: This function return the next action procedure pointer,
            a pointer of itself in order the have full robot acess inside procedure method. The destnation tuple and the precision to reach.
        """
        if(self.automatestep < len(self.automate)):
            action = self.automate[self.automatestep]
        else:
            return None, (self,), {}, (None, None)
            self.stop_event.set()

        return action.procedure, (self,), {}, (action.actionpoint + (action.orientation,), (action.actionpoint_precision, None))

    def goto_procedure(self, destination, thresholds=(None, None)):
        """The method describe the behaviour to reach an action point, it use the avoidance beahviour class that describe how to avoid an obstacle.

        Args:
            destination (tuple): the x, y, theta action point
            thresholds (tuple, optional): The optional precision to reach a point. Defaults to (None, None).

        Returns:
            bool: Return True when the robot successfuly reach the desired position false other.
        """
        if self.avoidance_behaviour.move(destination, thresholds):
            self.automatestep += 1
            return True
        else:
            return False

    def set_side(self, side):
        """This function is called during the preparation phase in order to choose the starting side

        Args:
            side (int): Yellow or blue
        """
        pass

    def set_position(self):
        """This function apply the starting position of the robot reagading to the choosed side
        """
        wheeledbase.set_position(*geogebra.get('StartYellow'), -pi/2)

    def positioning(self):
        """This optionnal function can be useful to do a small move after setting up the postion during the preparation phase
        """
        pass


if __name__ == '__main__':
    if PREPARATION:
        Bornibus().start_preparation()
    else:
        robot = Bornibus(manager)
        robot.set_side(COLOR)
        init_robot()
        robot.set_position()
        input()
        robot.start()
