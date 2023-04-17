# OSED_Project
An equipment in an industry continuously monitors the temperature to open or close a valve to the air conditioner. We realize the system.

## Block Diagram :
![image](https://user-images.githubusercontent.com/130765279/232584369-c5d667a6-1186-42b3-9175-da3d9a275f8e.png)


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

