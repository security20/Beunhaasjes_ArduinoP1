import serial_controller as ser_con
import time
import module

def main():

    # program loop
    while(True):

        print('=============')

        #Refresh the port list, could be threaded?
        ser_con.run()

        #Returns an list of all connected devices
        current_devices = ser_con.get_devices()

        print('Current identified devices: {0}'.format(current_devices))
        print('ALL DEVICE INFO:')
        for port, device in current_devices.items():
            print('---------')
            print(device)
            data_max = ser_con.get_distance_max(device, 5)
            print('Our max distance', data_max, 'cm')
            print('---------')

        # handle data of devices:
        # print('data not handled')

        print('===========')
        print('')
        print('')

        time.sleep(5) #This and import time should be removed (when main program loop is added + timed)

#####################################################


# Start program!
main()
