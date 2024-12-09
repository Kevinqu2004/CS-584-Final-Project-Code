Code is in Final_Project, written for Arduino. Essentially, this program takes the current draw of the two servos and if they are above a certain threshold, it assumes that they are being pulled.
Then, depending on which servo is drawing more power, it determines which direction they are being pulled in.
This can then be used to determine whether to allow the servos to spin in that direction or if they should stop.
There is also a potentiometer as a backup/override but it is only active when it is changed.

There is a processing demonstration (a very slightly modified version of the Processing Reach 3 example program) that helps display how the finger is supposed to be actuated.
