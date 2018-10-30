import controller
import time

def main():
    # program loop
    while(True):
        print('=============')

        #Refresh the port list
        controller.run()
        curDevices = controller.get_modules()
        print('Current com devices: {0}'.format(curDevices))

        #read module data
        for comPort in curDevices:
            result = controller.read_module(comPort)
            print(result)


        print('===========')
        print('')
        print('')

        time.sleep(2) #This and import time should be removed (when main program loop is added + timed)

#####################################################

# Start program!
main()
