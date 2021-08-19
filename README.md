**Computer Graphics (CSC 4118)**<br>
Course Instructor: Dipta Justin Gomes<br>
Project Report<br>
Summer 20-21, Section- I<br>
Fayeaz Ahmed : 19-39360-1<br>

***Project title:*** Ancient Egypt

### Introduction: 
This is a computer graphics project made using OpenGL library- GLUT. It is basically a view of The River Nile from ancient Egypt. We can see boats travelling along the river. The great pyramids of Giza can also be seen. And there are some houses and trees to fill up blank spaces. The sun starts going down after running the project. After it sets, moon rises and night view appears which is basically a darker version of the scenery, and stars on the sky. We can press ‘f’ to fast forward day-night cycle and click on any position on the sky to add a star there instantly.

### Implementation details:
At first, the sky and river is drawn using glRect. The pyramids are created using two triangles for each one. There are some trees, grass and boats all over which were drawn using glPolygon. The sun/moon is just a circle which changes color.

The boats are moving through the x axis towards both side and repositioned when out of frame. The variable “isDay” tracks if it is day or night and sets the color of the ambience accordingly. So after the sun reaches certain y coordinate while going down, the value of ‘isDay’ is inversed, and then the circle turns white (moon) and the same cycle continues.

Keyboard interaction - After a key press, ‘kbcallback’ function is called. If the pressed key is ‘f’, the variable to fast forward all the translation (ff = 1) is set to 20 and so everything moves faster until the cycle ends.

Mouse interaction - After mouseup event, in ‘mousecallback’ function the x and y position are calculated properly in -1 to 1 range. And if it’s within the range of sky, then a new star is added to the ‘stars’ array. Star is basically a struct with two float values x and y which are initialized at beginning with randomly generated x and y values. *Credit for uniform random number generation-* https://stackoverflow.com/a/7560564/11105382 
