# What is this project about?
This project's vision is to enable folks to enjoy their aquariums by creating an easy to use automation platform on which the community can add/update modules.  

The code and documentation are to be 100% open-source.  Submissions are to be done via Pull Requests so we can ensure consistency.  

No decision on license yet, but if you wish to use this as a foundation for a business, go ahead!  As a responsible citizen you would, of course, contribute back in the same manner with which this project was given.  Right? :)


## Features:
* Node-Red base code for Logic and Control
* MQTT Message Bus for interoperability between sensors and controllers
* Communication to the outside world  HTTP
* Dashboard system (Grafana + InfluxDB)
* Sensors
	* pH (I2C) 
	* Electrical Conductivity (EC/TDS) (I2C)
	* Water Level  (I2C and WiFi)
	* Temperature
* Automated Water Change 
	* Drain 5 gal of water from tank
	* Stop Filter
	* Start ATO
	* Re-start Filter
	* Dose Macros, Micros, GH and KH
* Automated dosing  (WiFi)	
* Controlled 8 socket power strip for controlling AC based devices (WiFi)
* Automated Top-off (ATO)
* Automated temperature control
* PWM digital control of LED lighting 
* Fully automatic CO2 injection / pH controller (use pH to control CO2 rather than other way around)
	* Starts 1 hr before lights ramp update
	* Quick load of CO2 until pH drop from 6.8 to 6
	* Maintain pH of 6 until lights ramp down
* Alerting/notifying via Twitter


##As a consumer of this system, you would be responsible for:
* Building the sensor packages 
* Ensuring your sensor packages follow the standards laid out here (e.g. JSON format)
* Ensuring your sensor packages can communicate with the core system
* Adding any code specific to your sensors


## Some systems on the horizon:
* Alerting/notifying via SMS/email
* ORP
* Colorimetric sensing for KH, CO2 and others, automated titration based on CY-31 board.
* Sensor to watch CO2 cylinder level

## Latest diagram...

<img src="https://raw.githubusercontent.com/diverjoe/FishNet/master/Documentation/AquaEscape%20Architecture.png" alt="AquaEscape Architecture.png">

*  Some format and content lifted from CrazyMittens