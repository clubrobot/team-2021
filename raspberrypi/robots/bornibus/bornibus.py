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
    def __init__(self, manager, *args, timelimit=None, **kwargs):
        RobotBehavior.__init__(self, manager, *args,
                               timelimit=timelimit, **kwargs)

        self.avoidance_behaviour = AviodanceBehaviour(
            wheeledbase, roadmap, robot_beacon, sensors)

        self.wheeledbase = wheeledbase
        self.display = display

        # Default side
        self.side = self.YELLO_SIDE

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
        if(self.automatestep < len(self.automate)):
            action = self.automate[self.automatestep]
        else:
            self.display.love()
            self.stop_event.set()
            return None, (self,), {}, (None, None)

        return action.procedure, (self,), {}, (action.actionpoint + (action.orientation,), (action.actionpoint_precision, None))

    def goto_procedure(self, destination, thresholds=(None, None)):
        if self.avoidance_behaviour.move(destination, thresholds):
            self.display.happy()
            self.automatestep += 1
            return True
        else:
            self.display.surprised()
            return False

    def set_side(self, side):
        self.side = side

    def set_position(self):
        if self.side == self.YELLO_SIDE:
            wheeledbase.set_position(*geogebra.get('StartYellow'), -pi/2)
        else :
            wheeledbase.set_position(*geogebra.get('StartBlue'), pi/2)

    def positioning(self):
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
