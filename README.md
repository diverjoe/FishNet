# What is this project about?
This project's vision is to enable folks to enjoy their aquariums by creating an easy to use automation platform on which the community can add/update modules.  

The code and documentation are to be 100% open-source.  Submissions are to be done via Pull Requests so we can ensure consistency.  

No decision on license yet, but if you wish to use this as a foundation for a business, go ahead!  As a responsible citizen you would, of course, contribute back in the same manner with which this project was given.  Right? :)


## Features:
* Node-Red base code for Logic and Control
* MQTT Message Bus for interoperability between sensors and controllers
* Pluggable architecture (pick the sensor packages you want to use)
* Communication to the outside world  HTTP
* Dashboard system (Grafana + InfluxDB)
* Water change 
* Automated Top-off (ATO)
* Automated temperature control
* PWM digital control of LED lighting
* Fully automatic CO2 injection
* Automated system shutdown based on sensor input
* Data gathering/analysis
* Alerting/notifying via Twitter


As a consumer of this system, you would be responsible for:
* Building the sensor packages 
* Ensuring your sensor packages follow the standards laid out here (e.g. JSON format)
* Ensuring your sensor packages can communicate with the core system
* Adding any code specific to your sensors


# Some systems on the horizon:
* Alerting/notifying via SMS/email
* ORP

# Latest diagram...

[https://raw.github.com/diverjoe/repository/blob/master/img/AquaEscape Architecture.png|alt=AquaEscape Architecture.png]

#  Some format and content lifted from CrazyMittens