#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from common.serialutils import Deserializer
from daughter_cards.arduino import SecureArduino, TopicHandler, SHORT, BYTE
import time

# Instructions
GET_SENSOR1_OPCODE = 0x10
GET_SENSOR2_OPCODE = 0x11
GET_SENSOR3_OPCODE = 0x12
GET_SENSOR4_OPCODE = 0x13
GET_SENSOR5_OPCODE = 0x14
GET_SENSOR6_OPCODE = 0x15
GET_SENSOR7_OPCODE = 0x16
GET_SENSOR8_OPCODE = 0x17

CHECK_ERROR_OPCODE = 0X18

GET_ALL_TOPIC_OPCODE = 0x01


class Sensors(SecureArduino):
    TIMESTEP = 200
    MAX_DIST = 1000
    DEFAULT = {GET_SENSOR1_OPCODE: Deserializer(SHORT(MAX_DIST)),
               GET_SENSOR2_OPCODE: Deserializer(SHORT(MAX_DIST)),
               GET_SENSOR3_OPCODE: Deserializer(SHORT(MAX_DIST)),
               GET_SENSOR4_OPCODE: Deserializer(SHORT(MAX_DIST)),
               GET_SENSOR5_OPCODE: Deserializer(SHORT(MAX_DIST)),
               GET_SENSOR6_OPCODE: Deserializer(SHORT(MAX_DIST)),
               GET_SENSOR7_OPCODE: Deserializer(SHORT(MAX_DIST)),
               GET_SENSOR8_OPCODE: Deserializer(SHORT(MAX_DIST)), }

    def __init__(self, parent, uuid='SensorBoard'):
        SecureArduino.__init__(self, parent, uuid, default_result=self.DEFAULT)
        self.last_time = None

        self.addTopic(GET_ALL_TOPIC_OPCODE,
                      self.get_all_sensors_handler, "sensors", self.TIMESTEP)

        self.sensor1 = self.MAX_DIST
        self.sensor2 = self.MAX_DIST
        self.sensor3 = self.MAX_DIST
        self.sensor4 = self.MAX_DIST
        self.sensor5 = self.MAX_DIST
        self.sensor6 = self.MAX_DIST
        self.sensor7 = self.MAX_DIST
        self.sensor8 = self.MAX_DIST

    @TopicHandler(SHORT, SHORT, SHORT, SHORT, SHORT, SHORT, SHORT, SHORT)
    def get_all_sensors_handler(self, sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7, sensor8):
        self.sensor1 = sensor1
        self.sensor2 = sensor2
        self.sensor3 = sensor3
        self.sensor4 = sensor4
        self.sensor5 = sensor5
        self.sensor6 = sensor6
        self.sensor7 = sensor7
        self.sensor8 = sensor8

    def get_all(self):
        return [self.sensor1, self.sensor2, self.sensor3, self.sensor4, self.sensor5, self.sensor6, self.sensor7, self.sensor8]

    def get_range1(self):
        return self.sensor1, 65535

    def get_range2(self):
        return self.sensor2, 65535

    def get_range3(self):
        return self.sensor3, 65535

    def get_range4(self):
        return self.sensor4, 65535

    def get_range5(self):
        return self.sensor5, 65535

    def get_range6(self):
        return self.sensor6, 65535

    def get_range7(self):
        return self.sensor7, 65535

    def get_range8(self):
        return self.sensor8, 65535

    def is_ready(self):
        try:
            return self.is_connected
        except:
            return False

    def check_errors(self):
        deser = self.execute(CHECK_ERROR_OPCODE)
        error = deser.read(BYTE)
        return error


if __name__ == "__main__":
    from setups.setup_serialtalks import *

    s = Sensors(manager, '/dev/tty.SLAB_USBtoUART')
    s.subscribeSensors()
