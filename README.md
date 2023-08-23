# What is it?
Calculates the weight of an object using a custom-built scale.

# Why was this created?
This is created for soft robotics research work at Seattle University. A custom, 3D printed clamp (which can move vertically and horizontally) can hold multiple different types of extensors over a scale which extend to push down on the scale vertically. The object of this is to see how much force the extensors expel. 

The extensors that are being used with this scale are finger-extenders. Their purpose is to help extend the fingers of clenched fists and re-establish muscle to brain connection in stroke patients. However, clenched fists require a certain amount of force to open and too much force can strain patient's muscles. As a result, making accurate force calculations is integral to this research and furthering advancement for stroke recovery.

# How does it work?
The code works in steps:
1. Finds the scale's zero value by finding the average of 20 values outputted by the load cell when there is nothing on the scale.
3. Then it asks the user to put a known weight on the scale and input that weight
4. The outputted value when nothing is on the scale (zero value), the outputted value when the weight is put on the scale (weight value), and the known weight are used to create the slope of the equation to determine any weight on the scale by subtracting the weight value by the zero value and dividing that by the known weight.
6. An equation is created to find the max weight of any new object by multiplying the slope by x (max value outputted by setting a new on the scale) and subtracting the zero value to get y (the max weight of the new object)
7. A second equation is created to find the average weight of any new object by multiplying the slope by x (max value outputted by setting a new on the scale) and subtracting the zero value to get y (the max weight of the new object)
8. Both of these values are outputted to represent the weight of something pushing on a load cell. A quick calculation would give the force in N outputted by the object.

A custom, 3D printed clamp holds the extensor in place and when air is pushed into the extensor, it pushes against a laser cut acrylic connected to the load cell. 

# Scale
This code is meant to be used with a load cell powered scale. Anyone can build a weight scale with the following materials:
1. Load cell
2. Drill
3. Wood
4. Screws and corresponding nuts
Extra:
6. Acrylic
7. Laser cutter (to cut the acrylic)



