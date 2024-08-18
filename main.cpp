/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"

DigitalOut myled(LED1);
UnbufferedSerial pc(USBRX, USBTX); // Serial outdated < OS 6 for Mbed 
UnbufferedSerial dev(PA_6, PA_7); // Serial outdated < OS 6 for mbed

void dev_recv(){
    char buff; // include char 
    while(dev.readable()){
        dev.read(&buff,1); //using read and write 
        pc.write(&buff,1);      
    }    
}

void pc_recv(){
    char buff;
    while(pc.readable()){
        pc.read(&buff,1); // using read and write 
        dev.write(&buff,1);    
    }    
}

int main() {
    pc.baud(9600);
    dev.baud(115200);
    pc.attach(&pc_recv);
    dev.attach(&dev_recv); // wrong spelling of the word "attach" & put in _recv for dev
    printf("Hello!! \r\n"); // removed pc.
    while(1) {
        myled = 1;
        ThisThread::sleep_for(1s); // changed this from wait 
        myled = 0;
        ThisThread::sleep_for(1s); // changed this from wait 
    }
}