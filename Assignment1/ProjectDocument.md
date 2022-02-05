# Hand Gesture Presentation Controller

This hand gesture controller, measured using ultrasonic, is an alternative input gesture that helps keep the presenter inflow and smoothly transition from slide to slide without having to look down at a keyboard.

- [Hand Gesture Presentation Controller](#hand-gesture-presentation-controller)
  - [Problem](#problem)
    - [Flow State](#flow-state)
  - [Motivation](#motivation)
  - [Design](#design)
    - [Materials used](#materials-used)
    - [How the Ultrasonic Sensor works](#how-the-ultrasonic-sensor-works)
      - [Formula for distance in cm](#formula-for-distance-in-cm)
    - [Simplifying Calculating the Distance](#simplifying-calculating-the-distance)
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

The problem the `Hand Gesture Presentation Controller` is trying to solve is to help aid in the struggles of public speaking and help keep presentations flowing. Public speaking is well known to be one of the biggest fears for people throughout the world. Many presenters use the keyboard to advance through slides and using the keyboard can break the flow of a presenter. Though the clicker solves the problem of breaking the immersive flow state of the presenter, when people present, they often do not have the clicker, especially students in many universities. People end up using their keyboard and fumble on the keys for a split second; thus breaking their concentration.

### Flow State

The flow state is a "mental state in which a person performing some activity is fully immersed in a feeling of energized focus, full involvement, and enjoyment in the process of the activity." [(Wikipedia)](https://en.wikipedia.org/wiki/Flow_(psychology)) The flow state can happen through activities such as work, writing an exam, and presenting. If you would like to learn more about the flow state, I would recommend reading [Flow: The Psychology of Optimal Experience](https://www.amazon.com/Flow-Psychology-Experience-Perennial-Classics/dp/0061339202) on the Psychology of Flow.

## Motivation

The motivation for this project was experiencing the challenges of presenting myself in front of an audience. I find it scary to present in front of an audience, and having everything "work" as intended is vital to a successful presentation to keep my focus.

Throughout, my degree and having to do multiple presentations, I have witnessed many people stumble and break concentration over even the littlest things that can interrupt their presentations. The act of looking down at the keyboard and looking for the arrow keys (instead of using the spacebar) breaks my concentration and makes me lose my train of thought for a couple of seconds.

Some people present without the ability to switch slides because they, unfortunately, do not have fingers. Seeing some people without fingers presenting and struggling to switch slides, broke my heart and being able to make an alternative and helping them overcome one of the most feared obstacles in life is also a motivation behind doing this project.

## Design

The initial design is simple and uses one ultrasonic sensor and senses if an object is `< 10cm` away then it will advance the next slide. The prototype has the only simple function of advancing the next slide.

### Materials used

- x1 Arduino Uno board
- x1 Ultrasonic Distance Sensor
- x4 wires to connect the Arduino to the Ultrasonic Sensor

![Simple Design Ultrasonic Sensor](https://user-images.githubusercontent.com/46540226/152660008-accd5499-56c4-4038-83a4-453b04083e85.png)

### How the Ultrasonic Sensor works

According to the [HR-SR04 Ultrasonic Sensor Manual](https://web.eece.maine.edu/~zhu/book/lab/HC-SR04%20User%20Manual.pdf), the Ultrasonic Sensor measures distance by the `TRIG` of the sensor receiving a pulse of a high (5V) for at least 10us. The sensor will then transmit an 8 cycle ultrasonic burst at 40kHz and wait for a reflected ultrasonic burst. After detecting ultrasonic, it will then set the `ECHO` pin to high (5V) and delay for a period (width) with proportion to distance.

![Ultrasonic Diagram](https://user-images.githubusercontent.com/46540226/152660257-e8864a40-2a83-4e34-92e3-0375a3bc354b.png)

The Ultrasonic sensor receives an ECHO and to interpret the time as the distance we need to calculate the distance by dividing the width of the `ECHO` pulse (in uS microseconds) by `/58` to get the distance in CM

#### Formula for distance in cm

$Distance = Width of Echo Pulse/58 = Time/58$

### Simplifying Calculating the Distance

Through research, the problem of calculating the distance through the input of the ultrasound sensor has already been solved. I used a [library](https://github.com/ErickSimoes/Ultrasonic) to calculate the distance. Thank you to `Erick Simoes` for making his library open source and free to use.

The library lets you pass in the TRIG and ECHO pins into a type `Ultrasonic` as parameters and lets you easily have access to the distance in a few lines of code.

```C++
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
ultrasonic.read(); // get distance
```

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

Inputting code to the Arduino is how we let manipulate and calculate the distance in order to advance the slides in our program.

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
        // advance next slide
        Serial.println('Next');
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
        if 'Next' in value:
            pyautogui.hotkey('right')
   ```

> NOTE: On line 3 `arduino = serial.Serial(PORT, 9600)` replace `PORT` with a your Arduino PORT. To find your Arduino PORT open the Arudino IDE and plug your board in and your PORT should be located at the bottom right.
> ![PORT](https://user-images.githubusercontent.com/46540226/152662266-0b039b32-97b2-45b9-9967-fb5555544ab4.png)

### Running Everything Together

We setup everything, now it is the time to run everything together!

1. Plug in the Arduino to your laptop and tape the Ultrasonic Sensor to the top of your laptop
2. Upload the Arduino Script to your board using the Arduino IDE
   - Click the little right arrow at the top of the Arudino IDE and make sure you have selected your correct Arduino board and PORT
3. Run the python script by using `python python-interpreter.py`
4. Navigate to your slides!
5. Start presenting

Everytime you put your hand up or get close to the ultrasensor, the sensor should move the the next slide!
  
## To The Future And Beyond

A simple way to add more functionality and build upon my design would be to add a second Ultrasonic Sensor.

![Ultrasonic Spec Diagram](https://user-images.githubusercontent.com/46540226/152660010-59a5cff7-a5ac-47be-8f8b-1388808571ad.png)

The use of two Ultrasonic sensors would enable back and forth mechanisms using a `Sliding motion`
By moving your hand left to right it would advance to the next slide by the Ultrasonic sensor detecting close motion from the left sensor and then also picking it up through the right sensor. This would enable also swiping from right to left to progress to the previous slide.

![Ultrasonic Diagram](https://user-images.githubusercontent.com/46540226/152660475-2fe39984-bbfa-463b-bbf6-87094a7e41b0.png)

Aesthetically, multiple Ultrasonic Sensor would be built into the top of a laptops screen to detect motion which can be used for more than just detecting hand gestures to advance a slide.
