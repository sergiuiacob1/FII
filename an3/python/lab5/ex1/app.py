import utils

if __name__=='__main__':  
    s = input('Enter x: ')
    while (s != 'q'):
        print (utils.process_item(int(s)))
        s = input('Enter x: ')