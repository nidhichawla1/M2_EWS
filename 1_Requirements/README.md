
# Requirements/Solution Design
This section details the requirements and solutions created for our system.

High-Level Requirements:

•	Allow the user to depend on our product and reduce its dependency on others.

•	Introducing the stick at ground level such as NGO’s and blind schools can help them adopt the mechanism  which would them in a longer run.

•	Allow the user to be successfully  guided  with the help of ultrasonic sensor,led and buzzer.

•	As the obstacle changes its position , the user in turn gets updated by the change in frequency of the beeping sound of the buzzer.

•	Led in turn makes the surrounding people aware of the presence of the presence of the visually impaired person in a dark room etc. 


Low-Level Requirements

•	We’ll be having a circuit box in our hardware prototype which will be carrying all the circuitry.


•	Obstacle detection works on the principle of an ultrasonic sensor

•	Mechanism begins with the trigger pin of the sensor sending the signal and getting reflected back to the echo pin of the sensor followed by the calculation of the distance between the user and the obstacle.








![Screenshot (83)](https://user-images.githubusercontent.com/67824009/164532746-d042918b-e2dd-46bf-b87c-aad346d4b43f.png)

•	The Lcd shown display the status of the obstacle near the user and it gets updated whenever the obstacle changes position near the user.

•	If the obstacle is 100 m away from the user the lcd display will show up 100m  and the turn the led will blink and the buzzer will beep.

•	If the distance betwwn the tworeduce to say 80 or 70m , the lcd will show that particular distance and in turn the frequency of the blinking of the led will increase and this in turn will increase the frequency with which thw buzzer beeps.

•	Here, in the simulide we can’t show the lcd display changing the value of the distance since there is no provision of the placing an obstacle in front of the sensor. That’s why the working is conveyed through an led and a buzzer.

•	A screen with below-mentioned rules should be displayed to the user.
