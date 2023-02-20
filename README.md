# CS-330-T3334-Comp-Graphic-and-Visualization
A repository of my work in my Computational Graphics course. Here you'll see the files I created to build a scene of a computer desk using OpenGL


What new design skills has your work on the project helped you to craft?
  While I have worked in creative softwares like unity and blender for many hours this was my first time making shapes and objects from code rather than using a engine. This taught me a lot about abstraction in C++ to make processes more simple. In it I took a main file hundreds of lines of code long and by making classes of each componet of the graphics process I was able to condense the file down. You'll see the header files and classes that hold the methods that are called in the main file. I learned a lot about seperating files and making these files interact in C++ and debugging in the C++ environment.

What design process did you follow for your project work?
  Like i said earlier abstraction was the biggest design lesson I learned from this project. After struggling with so many functions, vertex arrays, and indice arrays in the main file I decided to go through and make the class files to make the main file smaller and easier to handle. The files I am most proud about were the shape files of a Cube, Pyramid, and Plane files. These files allowed me to create and render each shape in a 2 lines of code rather than a hundred. 
  
How could tactics from your design approach be applied in future work?
  Abstraction is important in programming to create readable and scalable code. Through this project I was able to build my skills in abstraction and how to apply it in a graphical environment to create custom visuals in C++. These skills would aid in making a visual engine like blender or unity where the complex inner workings are hidden from the users and the users are given simple tools to create the objects.
  
What new development strategies did you use while working on your 3D scene?
  I faced a lot of problems with this project that I spent many hours debugging. I learned about the debugging techniques in C++ and debugging in Visual Studio. I learned how to hunt for problems and make solutions when the program would fail to load. Sometimes I would do a test run after some code and the window would flash on screen on screen with nothing on it and crash the program. I used visual studio debugger to find where my issues were and fix the issue. I had not used the visual studio debugger outside of Unity before so there were some learning to do.

How did iteration factor into your development?
  To make the objects I created render I would have to call the LinkAttrib, AssignUniforms, and Build functions for each shape I created. Since I had a few cubes and pyramids I created two vector lists, one to hold the pyramids and one to hold the cubes then at key points in the program the lists would go through and perform the LinkAttrib, AssignUniforms, and Build functions when needed. This allowed for me to create a shape and just add it to the list for it be rendered properly. This saved me from having to manually add the functions each time I added a shape.
  
How has your approach to developing code evolved throughout the milestones, which led you to the project’s completion?
  My approch grew more and more to make the program easier to work within. Knowing that I only want to work on this program as long as the class lasts means I just want to power through and get done, at the start. As the class continued I was facing issue with the amount of things to keep track of and it took me hours to do the smallest things. So I found wanting to make the program easier to work in and did research on my own to find solutions to this problem. I had not done this in my other classes but it felt required here even if it wasn't in the requirements. This would lead me to create the system I did.

How can computer science help me in reaching my goals?
I will be pursuing game development in my education which will involve me using the concepts I learned here to create systems to manage 3d visuals that will be useful in my future game development education. 

