# Hydroponic tower
Create a 3D-printed hydroponic tower with Arduino/ESP32!  

<img src="https://github.com/BadCactus634/hydroponic-tower/assets/68558172/b1987811-1263-4c2e-ad06-7a666f1c531b" width="600">

## Overview
This hydroponic tower has been entirely 3D printed using [PolyTerra PLA](https://amzn.eu/d/4JCfyR1). In order to print the brown modules I used almost 1kg of filament, whereas for the green ones I used 400g.  
It has to be sayd tho, that I **haven't got any failed print** and **all models were reduced by 10%** because they won't fit in my printing plate (I have an Flsun Q5).  
You can see a video of me building it (WIP). Note: it's in italian.

These are some of the printed components:  

<img src="https://github.com/BadCactus634/hydroponic-tower/assets/68558172/6685b945-aa3b-4e42-a553-f0862979546f" width="600"> <br>

Shopping list:
- brown filament 1kg
- green filament 1kg
- 3D printer (obiuvsly)
- 12V water pump
- ESP32/Arduino (any)
- water level sensor
- vase cover (if yours isn't in the premade models, you need to create one custom-made)
- water nutriments for hydroponic based coltivations
- plants
- step-up 5V-12V
- potentiometer, cables, LEDs
 
Optional:
- prepboard, solder, soldering iron
- pH, CE and water temperature sensors (I haven't used them)

## 3D models
You can find all the models I used in the **File STL utilizzati** directory, including the box on which I putted the components.  
I haven't included the custom-made file for my vase cover because I builded it using wood.

If you need the original models, you can find them [here](https://t.me/makersITA/907372) (they aren't on Thingiverse anymore).

## Circuit
The heart of this project is a simple **ESP32** used as a timer, that turns on the water pump for 5 minutes and then waits a variable time that we can specify using the potentiometer (from 10 to 60 minutes).    
There are 2 LEDs that indicate the status of the system (green on = pump active; red blinking = no water).  
The ESP32 is connected to a relè via a transistor, the relè triggers a step-up that converts the 5V from the USB cable up to 12V for the water pump, thus turning it on.  
The step-up is connected after the relè, so it's only activated when the pump needs to be on, thus earning some mA for battery life, if you decide to power the system that way.  

<img src="https://github.com/BadCactus634/hydroponic-tower/assets/68558172/ad248261-0450-4d58-aa0b-4c03accaca73" width="300">

You can see the circuit diagram in the picture below.  

ATTENTION!! It's important to connect the potentiometer to pin 33 (which corresponds to ADC1) because if we were to connect it to any ADC2 pin, the integration with Arduino Cloud won't work, as the ADC2 doesn't work if the board is using WiFi.

![Circuito_schema](https://github.com/BadCactus634/hydroponic-tower/assets/68558172/04654709-114e-4044-ba4f-5cec02618bce)

## Code
The code is in the file **Codice_SerraIdroponica.ino** and this is it's base working scheme:  
- Is there any water in the vase?  
  Then if the wait time has expired, activates the pump for 5min.  
  During pump activation time (it works by using millis) verify every second if water is still present in the vase, if not, stop the pump and turn on the red LED.
  
**ATTENTION**  
The pins in the code and in the circuit diagram refers to the ESP32 board. If you want to use an Arduino you need to edit them in the code and thus in the circuit.
