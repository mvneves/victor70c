
# Victor70C software for Linux

Victor 70C is a Digital Multimeter (DMM) made by Shenzhen Victor Hi-Tech 
Co., Ltd. It is also distributed as OEM by different companies. For example, 
in Brazil, it is sold as EZA EZ-735 (see the following picture).  

![EZA EZ-735](https://github.com/mvneves/victor70c/raw/master/photo.jpg)

Unfortunately, there is no open source software available to access this DMM in Linux.
Thus, this program is the first step in order to have an open source tool to 
decode the USB packets and displays the output as shown in the DMM's LCD.


# Installing 


This program uses HIDAPI to access the USB interface on Linux. Since HIDAPI 
is a multi-platform library, this program may also work with Windows and OS X 
(Although it has not been tested yet).

First of all, download and build HIDAPI:

	git clone git://github.com/signal11/hidapi.git
	cd hidapi/linux
	make

Download, build and install the victor70C app:

	git clone git://github.com/mvneves/victor70c
	cd victor70c
	# edit the right HIDAPI path in the Makefile
	make
	make install


# Setting up permissions for USB ports

By default, only root has full access to the usb devices. To change that, 
copy the udev rules files to /etc/udev/rules.d/ and restart the udev service:

	cp 45-victorusbhidrule.rules /etc/udev/rules.d/
	/etc/init.d/udev restart



# Usage examples

	Usage: victor70c [options] duration
	Options:
	-i --interval          interval in seconds between each read
	-v --verbose           turn on verbose output
	-h --help              print this help message


Example of how to read AC Amps for 5 seconds:

	$ victor70c 5
	1334452992.788321 0.986 A AC
	1334452993.372336 0.988 A AC
	1334452994.508409 1.155 A AC
	1334452995.044356 1.155 A AC
	1334452995.636368 1.216 A AC
	1334452996.156378 1.237 A AC
	1334452996.700382 1.221 A AC
	1334452997.308444 1.243 A AC
	1334452997.900399 1.219 A AC



# References

- A USB interface for Victor 86B Digital Multimeter using HIDAPI: 
[http://code.google.com/p/victor86b-usb-interface](http://code.google.com/p/victor86b-usb-interface)
- A closed-source DDM app for Victor 86B and 86C: 
[http://homepage.ntlworld.com/green_bean/coffee/roastlogger/dmmdetails.html](http://homepage.ntlworld.com/green_bean/coffee/roastlogger/dmmdetails.html)
- Victor 86C multimeter USB encoding for linux:
[http://www.daveansell.co.uk/?q=node/44](http://www.daveansell.co.uk/?q=node/44)


