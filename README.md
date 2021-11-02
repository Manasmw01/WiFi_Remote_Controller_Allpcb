# ESP-12F Based WiFi Remote Controller


> Nowadays, home automation is trending everywhere. Right from controlling lights from anywhere in the world to monitoring our homes, we use home automation everywhere.
There are lots of IoT platforms available where we can completely set up a Home automation system all by ourselves. 
But, instead of making an app or a dashboard, I thought of adding a dedicated remote for this task. So, I’ve designed a PCB that can be used as a remote to control appliances and also display any data if needed.
The controller used in this project is the ESP-12F from Espressif which can be used to connect to the internet and also perform some dedicated tasks. 
The PCB design is made such that we can either wear it on our wrists or keep it on a desk or somewhere and use it whenever needed. 

<p align="center">
<img align="center" src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/working.gif">
</p>

  
# PCB Description
> The PCB consists of a TP4056 Charging circuit, USB C type Charging, MT3608 based Boost Converter, and some pushbuttons.
The pushbuttons are placed in the shape of a remote controller, i.e. Up, Down, Left and Right.
The OLED display is used to display any data if needed.

# Designed using EasyEDA, Ordered from Allpcb
> [EasyEDA Project Link Here](https://oshwlab.com/manasmw333/esp-12f-oled-watch)
>
> [Ordered from Allpcb](https://allpcb.com/activity/free-pcb-prototype-2021.html)

This PCB is designed using EasyEDA which is an easy-to-use PCB design tool. 
The PCBs are ordered from ALLPCB since they have a free PCB prototype offer going on. Even though I’m from India, I received the free PCBs within 10 days after I placed the order.

# Schematic

> The EasyEDA Schematic is attached below. 

<p align="center">
<img align="center" src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/Schematic_ESP-12F%20OLED%20Watch_2021-11-02.png">
</p>

# Design
The PCB design and 3D Model images are attached below

<p align="center">
<img align="center" src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/PCB.png">
</p>

# 3D Model
<p align="center">
<img align="center"src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/top.png">
</p>

<p align="center">
<img align="center"src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/bottom.png">
</p>

# Working
For demonstration, I have used a 4 wheel robot having an ESP8266 NodeMCU as a microcontroller.
The PCB designed, acts as a transmitter, and the ESP8266 NodeMCU on the robot acts as the receiver. 
<p align="center">
<img align="center"src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/4.jpg">
</p>

<p align="center">
<img align="center"src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/5.jpg">
</p>

Both transmitter and receiver work on the MQTT Protocol. I’ve used the free MQTT broker provided by HiveMQ for connecting to the internet. The link for the same is given below: https://www.hivemq.com/

The code for both transmitter and receiver is provided in the GitHub repository.
The transmitter code is written such that it prints a message on the OLED Display when started and also reads if any button is pressed. If any button press is found, a message is published on a defined MQTT Topic. The receiver then decides what to do if a certain data is published on a certain topic.

<p align="center">
<img align="center" src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/display.gif">
</p>

<p align="center">
<img align="center" src="https://github.com/Manasmw01/WiFi_Remote_Controller_Allpcb/blob/master/working.gif">
</p>

	
# About ALLPCB

>Just as they claim, ALLPCB is the fastest PCB Manufacturer out there. The Free prototype offer of ALLPCB helped me in getting this PCB manufactured for free and also delivered to me as soon as possible!
