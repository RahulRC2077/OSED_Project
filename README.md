# OSED_Project
An equipment in an industry continuously monitors the temperature to open or close a valve to the air conditioner. We realize the system.

## Block Diagram :
![image](https://user-images.githubusercontent.com/130765279/232583030-3b8ecd2a-a7a0-48f7-8407-118e12ede9c9.png)


## ALGORITHM :

1. START.
2. MAILBOX IS CREATED
3. UART0 IS INITIALIZED
4. MAILBOX IS DEFINED AND INITIALIZED
5. ADC_VALUE IS READ UNDER TASK 1
6. SEND THE ADC_VALUE TO MAILBOX
7. RECEIVE ADC_VALUE FROM MAILBOX IN TASK 2
8. DISPLAY VALUE ON UART0
9. BASED ON CONDITION,RUN DC MOTOR

