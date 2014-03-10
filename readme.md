###BallSorter###

This is the code that ran a robot a partner and I designed and built.  The
goal was to sort 3 different types of balls onto a pre-designed turn table.

The code consists of four main parts:

1. **Releasing**: A solenoid plunger is used to hold the balls in position
   until a button press is detected.
2. **Detecting**: The balls are detected using a reflectance sensor
   ([Fairchild QRB1113][refSensor]) that distinguishes the three types of
   balls and their order.
3. **Sorting**: The balls are assigned set points that correspond to slots
   on the turntable.
4. **Placing**: A proportional-integral-derivative controller moves the
   turntable to each set point in sequence, and the balls are placed in
   their slots.

The program was run by an [Arduino Uno][arduinoUno] with a [DFRobot screw
shield][screwShield] and a [Rugged Circuits motor driver][motorDriver]. The
final design had three outputs: a solenoid plunger that holds the balls in
their starting position, one motor that controls the turntable, one motor
that controls the chute; and three inputs: a button releases the solenoid
plunger and starts the sorting, a reflectance sensor that detects the balls,
and a potentiometer that gives the position of the turntable.

###Why?###

The original work was done for a course that culminated in a competition
among 35 teams of 2 people.

I'm releasing this code because I don't hate it, and I don't want it to get
lost on my computer forever. There's definitely a lot that could be improved
that will likely never be because the robot had to be stripped down (all
electrical components had to be returned after the competition), and it is
extremely improbable that it will ever be restored to working order. Which,
I suppose, means that this and the two videos we have of it working are the
only proof that it did, in fact, work. How oddly sentimental.

The code itself is pretty much C in .cpp files because the Arduino IDE
builds and links all .cpp and .h files in the same folder as the main
project .ino. I am not very experienced with OOP, so it was easier for me to
write it C-style than C++-style.

####Everyone Loves Copyright####

If you desperately need to use this code for reasons I cannot possibly
foresee, it is licensed under the [WTFPL][wtfpl].

[refSensor]: http://www.micro-machine-shop.com/QRB1114.pdf
[arduinoUno]: http://arduino.cc/en/Main/arduinoBoardUno
[screwShield]: http://www.dfrobot.com/index.php?route=product/product&product_id=468
[motorDriver]: http://www.ruggedcircuits.com/motor-control/rugged-motor-driver
[wtfpl]: http://www.wtfpl.net/about/
