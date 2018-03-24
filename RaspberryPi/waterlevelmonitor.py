# Python script to monitor serial connection between RPi and Arduino Uno where the Ardunio Uno is sending water level stats to the serial console. 

import serial
import time
import MySQLdb as mdb

arduino = serial.Serial("/dev/ttyACM0")

arduino.baudrate=9600

while True:
	data = arduino.readline()
	con = mdb.connect('localhost','dbuser','dbuserpassword','dbdatabase');
	with con:
		cursor =con.cursor()
		cursor.execute('insert into level_reading (level) values("%s")' 
% (data))
	
	con.commit()
	cursor.close()
	time.sleep(60)

