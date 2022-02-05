# Hand Gesture Presentation Controller

This hand gesture controller, measured using ultrasonic, is an alternative input gesture which  helps keep keep the presenter in flow and smoothly transition from slide to slide without having to look down at a keyboard.

- [Hand Gesture Presentation Controller](#hand-gesture-presentation-controller)
  - [Problem](#problem)
    - [Flow State](#flow-state)
  - [Motivation](#motivation)
  - [Design](#design)
    - [Materials used](#materials-used)

## Problem

The problem the `Hand Gesture Presentation Controller` is trying to solve is to help aid in the struggles of public speaking and help keep presentations flowing. Public speaking is well known to be one of the biggest fears for people throughout the world. Many presenters use the keyboard in order to advance through slides and using the keyboard can break the flow of a presenter. Though the clicker solves the problem of breaking the immersive flow state of the presenter, when people present, they often do not have the clicker, especially students in many universities. People end up using their keyboard and fumble on the keys for a split second; thus breaking their concentration.

### Flow State

The flow state is a "mental state in which a person performing some activity is fully immersed in a feeling of energized focus, full involvement, and enjoyment in the process of the activity." [(Wikipedia)](https://en.wikipedia.org/wiki/Flow_(psychology)) The flow state can happen through activities such as work, writing an exam, and presenting. If you would like to learn more about the flow state, I would recommend reading [Flow: The Psychology of Optimal Experience](https://www.amazon.com/Flow-Psychology-Experience-Perennial-Classics/dp/0061339202) on the Psychology of Flow.

## Motivation

The motivation for this project was experiencing the challenges of presenting myself in front of an audience. Personally, I find it scary to present in front of an audience, and having everything "work" as intended is vital to a successful presentation in order to keep my focus.

Throughout, my degree and having to do multiple presentations, I have witnessed many people stumble and break concentration over even the littlest things that can interrupt their presentations. The act of looking down at the keyboard and looking for the arrow keys (instead of using the spacebar) breaks my concentration and makes me lose my train of thought for a couple seconds.

Some people present without the ability to switch slides because they unfortunately do not have fingers. Seeing some people without fingers presenting and struggling to switch slides, broke my heart and being able to make an alternative and helping them overcome one of the most feared obstacles in life is also a motivation behind doing this project.

## Design

The initial design is simple and uses one ultrasonic sensor and senses if an object is `< 10cm` away then it will advance the next slide.

### Materials used

- x1 Arduino Uno board
- x1 Ultrasonic Distance Sensor
