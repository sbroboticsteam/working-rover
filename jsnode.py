import sdl2
import sdl2.ext
from Node import Node
import json
import time

jsnode = Node("controls_node.json")

sdl2.SDL_Init(sdl2.SDL_INIT_JOYSTICK)

""" For when we want to use multiple joysticks
self.joysticks = []
for i in range(0, sdl2.SDL_NumJoySticks()):
    joy = sdl2.SDL_JoystickOpen(i)
    self.joysticks.append(joy)
print("joystick initialized")
"""

joy = sdl2.SDL_JoystickOpen(0)

while True:
    sdl2.SDL_PumpEvents()
    data = []
    for i in range(0, 6):
        data.append(int(sdl2.SDL_JoystickGetAxis(joy, i)))
    for i in range(0, 11):
        data.append(int(sdl2.SDL_JoystickGetButton(joy, i)))
    data.append(int(sdl2.SDL_JoystickGetHat(joy, 0)))
    msg = json.dumps(data)
    jsnode.send("inputs-out",msg)
    time.sleep(0.05)
    print(data)

    # Data array format:
    ## 16 bit signed ints:
    # 0  | right joystick x
    # 1  | right joystick y
    # 2  | right trigger
    # 3  | left joystick x
    # 4  | left joystick y
    # 5  | left trigger
    ## 1 bit (0 = unpressed, 1 = pressed)
    # 6  | A
    # 7  | B
    # 8  | X
    # 9  | Y
    # 10 | left bumper
    # 11 | right bumper
    # 12 | view (left center button)
    # 13 | menu (right center button)
    # 14 | xbox (center button)
    # 13 | left joystick button
    # 14 | right joystick button
    ## 4 bit
    # 17 | hat switch / dpad
    #    | (1 = N, 3 = NE, 2 = E, 6 = SE, 4 = S, 12 = SW, 8 = W, 9 = NW)

def shutdown(self):
    print("joystick shutting down")
