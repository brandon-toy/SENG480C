# Hand Gesture Presentation Controller

This hand gesture controller, measured using ultrasonic, is an alternative input gesture that helps keep the presenter inflow and smoothly pause a video without having to look down at a keyboard.

- [Hand Gesture Presentation Controller](#hand-gesture-presentation-controller)
  - [Problem](#problem)
    - [Alternatives](#alternatives)
  - [Motivation](#motivation)
  - [Design](#design)
    - [Materials used](#materials-used)
    - [How the Ultrasonic Sensor works](#how-the-ultrasonic-sensor-works)
      - [Formula for distance in cm](#formula-for-distance-in-cm)
    - [Simplifying Calculating the Distance](#simplifying-calculating-the-distance)
  - [Systems Design](#systems-design)
  - [Steps to Recreate](#steps-to-recreate)
    - [Installing Software Programs](#installing-software-programs)
    - [Connecting the Arduino to the Ultrasonic Sensor](#connecting-the-arduino-to-the-ultrasonic-sensor)
    - [Adding Functionality and Code to the UltraSonic Sensor](#adding-functionality-and-code-to-the-ultrasonic-sensor)
      - [Creating a New file in Arduino IDE](#creating-a-new-file-in-arduino-ide)
      - [Adding an External Library to the Arduino IDE](#adding-an-external-library-to-the-arduino-ide)
      - [Interpreting `Serial.print()` to the machine](#interpreting-serialprint-to-the-machine)
      - [Creating the Python Code](#creating-the-python-code)
    - [Running Everything Together](#running-everything-together)
  - [To The Future And Beyond](#to-the-future-and-beyond)

## Problem

I'm lazy and when I am relaxing trying to watch a video, I hate fumbling around with the keyboard/remote to adjust the volume and try to control/stop playing a video. Some technology has been created to control the TV through hand gestures. Some alternatives do exist however are cumbersome to use and are not adopted by mainstream media yet. For example, Samsung's implementation lacks quick functionality with using the hand gestures only to control a cursor in order to change the volume and channel. A quick swiping motion or pausing motion would be quick and easy for the user to control.

### Alternatives

Some alternatives I have found to TV hand gestures are

- [Samsung TV](https://www.youtube.com/watch?v=xHFXE6R60VE)
- [One Cue](https://www.onecue.de/) (Seems to have discountined)
- [Paper published in 1994 about tv controlling hand gestures](https://www.merl.com/publications/docs/TR94-24.pdf)

The Samsung TV seems to have been able to implement it though it has been rarely used and somewhat cumbersome. Users have to control a cursor and really only supports changing channels and volumes.

## Motivation

The motivation for this project was experiencing losing the TV remote when watching TV and when sitting back in my chair watching a video, having to sit up and press pause on my laptop can be annoying. Netflix has an auto-play the next episode so trying to find the remote before the next episode plays is a frantic endeavor and encourages binging episodes when people don't want to.

This project also will help people without fingers to be able to control their laptop video player without being able to awkwardly trying to hit the keyboard.

## Design

The initial design is simple and uses one ultrasonic sensor and senses if an object is `< 10cm` away then it will pause a video. The prototype has the only simple function of pausing a video.

### Materials used

- x1 Arduino Uno board
- x1 Ultrasonic Distance Sensor
- x4 wires to connect the Arduino to the Ultrasonic Sensor
- Tape

![Simple Design Ultrasonic Sensor](https://user-images.githubusercontent.com/46540226/152660008-accd5499-56c4-4038-83a4-453b04083e85.png)

### How the Ultrasonic Sensor works

According to the [HR-SR04 Ultrasonic Sensor Manual](https://web.eece.maine.edu/~zhu/book/lab/HC-SR04%20User%20Manual.pdf), the Ultrasonic Sensor measures distance by the `TRIG` of the sensor receiving a pulse of a high (5V) for at least 10us. The sensor will then transmit an 8 cycle ultrasonic burst at 40kHz and wait for a reflected ultrasonic burst. After detecting ultrasonic, it will then set the `ECHO` pin to high (5V) and delay for a period (width) with proportion to distance.

![Ultrasonic Diagram](https://user-images.githubusercontent.com/46540226/152660257-e8864a40-2a83-4e34-92e3-0375a3bc354b.png)

The Ultrasonic sensor receives an ECHO and to interpret the time as the distance we need to calculate the distance by dividing the width of the `ECHO` pulse (in uS microseconds) by `/58` to get the distance in CM

#### Formula for distance in cm

```
Distance = Width of Echo Pulse/58 = Time/58 
```

### Simplifying Calculating the Distance

Through research, the problem of calculating the distance through the input of the ultrasound sensor has already been solved. I used a [library](https://github.com/ErickSimoes/Ultrasonic) to calculate the distance. Thank you to `Erick Simoes` for making his library open source and free to use.

The library lets you pass in the TRIG and ECHO pins into a type `Ultrasonic` as parameters and lets you easily have access to the distance in a few lines of code.

```C++
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
ultrasonic.read(); // get distance
```

## Systems Design

The Ultrasonic sensor interprets data towards the arduino which is then picked up by a python script and then the python script pauses the video

![Video](https://user-images.githubusercontent.com/46540226/152705219-4f18fba5-f758-4098-ae7a-d255bf9a423b.png)

## Steps to Recreate

### Installing Software Programs

A number of various software programs are needed to run this project assignment

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Python](https://www.python.org/downloads/)
  - Install `PIP` packages
    - `pip install pyautogui serial`

### Connecting the Arduino to the Ultrasonic Sensor

The HR-SR04 Ultrasonic Sensor has 4 pin inputs

- VCC
- TRIG
- ECHO
- GND

To connect the Ultrasonic Sensor to the Arduino board connect the Ultrasonic Sensor pins to the following (on the Arduino board)

- VCC -> 5V
- TRIG -> D1/PIN1
- ECHO -> D2/PIN2
- GND -> GND

### Adding Functionality and Code to the UltraSonic Sensor

Inputting code to the Arduino is how we let manipulate and calculate the distance in order to pause a video in our program.

#### Creating a New file in Arduino IDE

1. Open [Arduino IDE](https://www.arduino.cc/en/software)
2. Navigate to `File` -> `New`
3. Save the new file and rename to `hand-gesture-presentation-controller.ino`
4. Copy and paste the following code into the newly created file

   ```c++
    #include <Ultrasonic.h>
    const int trigger = 1;
    const int echo = 2; 

    Ultrasonic ultrasonic(trigger, echo);

    void setup() {
      Serial.begin(9600); 
      pinMode(trigger, OUTPUT); 
      pinMode(echo, INPUT); 

    }

    void loop() { 
      int distance = ultrasonic.read();
      Serial.print(distance);
      if(distance < 10) {
        Serial.println('Pause');
      }
    }
   ```

Since the arduino code uses an external library to calculate the distance we must first import the a library into the arduino.

#### Adding an External Library to the Arduino IDE

1. In the Arduino IDE navigate to `Tools` -> `Manage Libraries`
2. Search field type `ultrasonic`
3. Look for the library named `Ultrasonic by Erick Simões`
4. Install!
   > Alternatively, you can download the library [here](https://github.com/ErickSimoes/Ultrasonic/archive/master.zip) and import the ```.zip``` file into the IDE (see how to import a library [here](https://www.arduino.cc/en/Guide/Libraries#toc4)).

#### Interpreting `Serial.print()` to the machine

Using the code and trying to manipulate our laptop is difficult, so an easier way is to make a Python script to listen to `Serial.print()` and act accordingly.

#### Creating the Python Code

1. Create a new python file `python-interpreter.py` (preferabbly in same directory as previous Arduino)
2. Copy and paste the following code

   ```python
    import serial
    import pyautogui
    arduino = serial.Serial('PORT', 9600)
    def write_read(x):
        data = arduino.readline()
        return data
    while True:
        value = str(write_read(1))
        print(value)
        if 'Pause' in value:
            pyautogui.hotkey('spacebar')
   ```

> NOTE: On line 3 `arduino = serial.Serial(PORT, 9600)` replace `PORT` with a your Arduino PORT. To find your Arduino PORT open the Arudino IDE and plug your board in and your PORT should be located at the bottom right.
> ![PORT](https://user-images.githubusercontent.com/46540226/152662266-0b039b32-97b2-45b9-9967-fb5555544ab4.png)

### Running Everything Together

We setup everything, now it is the time to run everything together!

1. Plug in the Arduino to your laptop and tape the Ultrasonic Sensor to the top of your laptop
2. Upload the Arduino Script to your board using the Arduino IDE
   - Click the little right arrow at the top of the Arudino IDE and make sure you have selected your correct Arduino board and PORT
3. Run the python script by using `python python-interpreter.py`
4. Navigate to your video!
5. Watch the video and move your hand close to the sensor to pause the video

Everytime you put your hand up or get close to the ultrasensor, the sensor should pause the video.
  
## To The Future And Beyond

A simple way to add more functionality and build upon my design would be to add a second Ultrasonic Sensor.

![Ultrasonic Spec Diagram](https://user-images.githubusercontent.com/46540226/152660010-59a5cff7-a5ac-47be-8f8b-1388808571ad.png)

The use of two Ultrasonic sensors would enable back and forth mechanisms using a `Sliding motion`
By moving your hand left to right it would be able to control multiple functions like controlling volume through the Ultrasonic sensor detecting close motion from the left sensor and then also picking it up through the right sensor.

![Ultrasonic Diagram](https://user-images.githubusercontent.com/46540226/152660475-2fe39984-bbfa-463b-bbf6-87094a7e41b0.png)

Aesthetically, multiple Ultrasonic Sensor would be built into the top of a laptops screen to detect motion which can be used for more than just detecting hand gestures.

![Laptop Design](https://user-images.githubusercontent.com/46540226/152663122-ac4aa18a-5a2f-4755-883f-9572e6d27473.png)
