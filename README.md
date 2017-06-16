# finalproject
Implemented a version of Galaga using Qt and C++ for my PIC 10C final project. 

Controls: 
  Space bar: Fire OR start the game.
  Direction keys: Maneuver ship.
  
The structure was adapted from https://github.com/jjw1707/Space-Invaders-Remixed.git (similar display and some class member variables). Nonetheless, there are key differences between the two (similar to the differences between Galaga and Space Invaders), with mine including concepts from PIC 10C. Here are some noteable differences:

Rather than weapon and ship derivative classes (e.g., homing, bomb etc.), this version only uses one class for each object and all its subobjects. 
Rather than have ships be in possession of a weapon, I simply assigned each index array to the same ship and weapon in the cases of enemies. 
Rather than having one shot at a time, my player can shoot up to forty shots. 
All ships have different starting positions, movements and weapons from the original version, and also have health now. 
I also added an accuracy feature on the display.
All of the above required that I write multiple extra functions and modify others.
Although unused, I added RAII features to each class (copy constructor, assignment operator), and made sure RAII was correctly implemented in the big three (copy constructor, assignment operator, destructor). 
I templated a couple of functions in the Game class, and used them effectively in combination with lambda functions and the generic algorithm for_each (which is also templated). 
I used another lambda function to calculate accuracy. 


  
  
  
