# Kids-GPS-Tracking-Mobile-App

## Project Idea: 
This project act as a tracking device for kids, where you can moniter the kid's location and view it in real-time using an Android app, you can also turn on the notification where it can notify you when the kid is moving fast by using a car or motorcycle in case he went with a stranger or was kidnapped.   

## Parts
* ESP32
* GPS neo 6m Module (any module will work) 

## Websites
* MIT app inventor to program the mobile app  ( https://appinventor.mit.edu/ )
* Google firebase real-time database  ( https://firebase.google.com/ )

## Working principle 

ESP32 first is connected to the internet then read the GPS coordinates from the module and uploads it to the database in real-time. The mobile app take the coordinates from the database and display it as point in a map using simple UI element in the MIT app inventor. the app wait for an update in the database and then take the latest data and show it in the map.

the notification feature is to detect if the location changed alot in short amount of time meaning the kid is moving using a vehicle, then it will give you a notification.

## Circuit Diagram
<p align="center">
  <img width="250" height="300" src="https://user-images.githubusercontent.com/5675794/221840258-6c7b31e1-83ae-40ca-b92e-a467b89b9257.png">
</p>  
  
  
  
    
      
      
