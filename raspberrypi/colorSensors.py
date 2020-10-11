from common.serialtalks import FLOAT
from common.components import Manager
from daughter_cards.arduino import Arduino

if __name__ == "__main__":
    serv = Manager("tin-devices-gecu")
    serv.connect()
    a = Arduino(serv, "ColorSensors")
