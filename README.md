# Vayu

A customizable smart air coolers/conditioners controller with IoT integration lets the manufacturers to get a room for their production of the coolers from building the control unit. In the upcoming days it is expected that most of our electronic devices will be connected thus leading to the sustainability of this unit.

# How it works
The controller is an advanced PI type controller with anti windup for self controlling and adapting. The PID calculations are made at 0.1Hz, this slow rate is okay since temperature is a sluggish changing variable. The motor control is a phase angle control for smooth dimming and variable AC drive of the motor. Firstly, it looks for a input command from the WiFi, if something new is in the buffer, it reads it and changes it's setpoint. Else it goes with the previously set setpoint. 
Then it calculates the PI value needed for the delay time of the phase angle control, then it drives the motor with triac, three triac are parallelly placed for high current drive of the motor. This phase angle control is also done by the same microcontroller by detecting the zero cross, so there is a interrupt occuring when the microcontroller is not in deep sleep mode, when it wakes up(every 10s) it calculates the PI value and with that the interrupt mask is set and loops with the drive power of the motor, thus driving the motor with the desired speed. After setting the speed, the microcontroller again goes to sleep mode and this cycle repeats.
The above agenda is written in the firmwire which is attached above.

# Tech used
PI control for setting the power of the compressor fan.
The drive of the fan is obtained by phase angle control by zero cross detection.
We made the PCB in EasyEda

