# Created by Alex Pereira

# Imports
import serial
import serial.tools.list_ports

# Creates the SerialComms Class
class SerialComms:
    # Constructor
    def __init__(self, portNum = None, baudRate = 9600, testMode = False):
        """
        Constructor for the SerialComms class.
        :param serialPortNumber
        :param baudRate
        """
        # Sets variables
        connected     = False
        self.testMode = testMode

        # Creates a mode that bypasses serial creation
        if (self.testMode == False):
            # Port number not given
            if portNum is None:
                ports = list(serial.tools.list_ports.comports())
                for port in ports:
                    if "Arduino" in port.description:
                        print(f'{port.description} Connected')
                        self.ser = serial.Serial(port.device, baudRate)
                        connected = True
                if not connected:
                    raise OSError("Arduino not found. Enter COM port.")
            # Port number given
            else:
                try:
                    self.ser = serial.Serial(portNum, baudRate)
                    print("Connected to Serial Device")
                except:
                    raise OSError("Failed to connect to Serial Device")
        elif (self.testMode == True):
            # Creates the serial object as a blank
            self.ser = None

    def sendData(self, data):
        """
        Sends the data over serial.
        :param dataArray
        """
        # Creates the holder string
        myString = ""

        # Adds the data to myString
        for d in data:
            myString += str(int(d)).zfill(3)

        # Adds the terminating character to the end
        myString += "\r"

        # Writes data to serial if testMode is disabled
        if (self.testMode == False):
            self.ser.write(myString.encode())
        else:
            myString = myString.encode()

        # Returns the string for debugging
        return myString

    def getData(self):
        """
        Gets the data from serial.
        :return recievedData
        """
        # Reads data from serial if testMode is disabled
        if (self.testMode == False):
            data = bytes(self.ser.read())
        else:
            data = "No Value".encode()

        # Decodes the recieved data 
        data = data.decode("utf-8")
        
        # Return the data
        return data