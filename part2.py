import socket
import time
import json
import sys




print("Enter 1 for temperature in celsius")
print("Enter 2 for temperature in fahrenheit")
print("Enter 3 for  humidity")
print("Enter 4 for Led and Button functionality")
print("______________________________________________")
val = input("Enter from the below option:")

print(val)

host = "192.168.223.201"
port = 6668

while(True):
    print("Inside while loop")
    if val=='1':
        print("**********Temperature in Celsius***************")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s1:
            s1.connect((host,port))
            message1=  b"{ \"Tweet Type\" : \"Service call\", \"Thing ID\" : \"MySmartThing01\", \"Space ID\" : \"MySmartSpace\", \"Service Name\" : \"Temp_Celsius_C\", \"Service Inputs\" : \"()\" }"
            s1.sendall(message1)
            data1 = str(s1.recv(2048), 'utf-8')
            #if(data1 != None and data1 != ''):
             #   celsius = json.loads(data1)["Service Result"]
              #  print("Celsius value: " + celsius + "°C")
            s1.close()

    elif val=='2':
        print("**********Temperature in Fahrenheit***************")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s2:
            s2.connect((host,port))
            message2=  b"{ \"Tweet Type\" : \"Service call\", \"Thing ID\" : \"MySmartThing01\", \"Space ID\" : \"MySmartSpace\", \"Service Name\" : \"Analog_temp_F\", \"Service Inputs\" : \"()\" }"
            s2.sendall(message2)
            data2 = str(s2.recv(2048), 'utf-8')
            fahrenheit = json.loads(data2)["Service Result"]
            print(fahrenheit)
            if(data2 != None and data2 != ''):
                fahrenheit = json.loads(data2)["Service Result"]
                print(fahrenheit)
                #print("Fahrenheit value: " + fahrenheit + "°F")
            s2.close()
    elif val=='3':
        print("**********Humidity in Percent***************")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s3:
            s3.connect((host,port))
            message3=  b"{ \"Tweet Type\" : \"Service call\", \"Thing ID\" : \"MySmartThing01\", \"Space ID\" : \"MySmartSpace\", \"Service Name\" : \"Humidity_percentage\", \"Service Inputs\" : \"()\" }"
            s3.sendall(message3)
            data3 = str(s3.recv(2048), 'utf-8')
            #if(data3 != None and data3 != ''):
             #   Humidity = json.loads(data3)["Service Result"]
              #  print("Humidity percent: " + Humidity + "%")
            s3.close()
    elif val=='4':
        print("**********Led and Button***************")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s4:
            s4.connect((host,port))
            message4=  b"{ \"Tweet Type\" : \"Service call\", \"Thing ID\" : \"MySmartThing01\", \"Space ID\" : \"MySmartSpace\", \"Service Name\" : \"ledButton\", \"Service Inputs\" : \"(3000)\" }"
            s4.sendall(message4)
            data4 = str(s4.recv(2048), 'utf-8')
            #if(data4 != None and data4 != ''):
                #ledButton = json.loads(data4)["Service Result"]
                
            s4.close()







