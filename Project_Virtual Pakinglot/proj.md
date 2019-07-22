# Project FAQs

* Author: Yao Yue, Fu Xiaohan
* This document might be updated in realtime .
* You can see online version [here](https://gist.github.com/Reapor-Yurnero/aade81371b73146ebad74279ad6e367f)

FAQs (Frequently asked questions) are document provided with programs to answer common confusions. We suggest each team pick at least one students in charge of reading this document carefully, and make sure that everything mentioned is well-understood by the team. This will ease your work, provide inspirations and most importantly help you earn more points!

***

## General Guidelines

1. **Read the project specification carefully.** Follow and understand all things mentioned in the specification. **Especially the "Introduction" part.** If you have anything unclear, take the time to ask Manuel and us directly.
2. For those details are not mentioned in the specification. It's up to you to decide. This typically include 1)IO formats 2) Number of random vehicles in ex1 etc. We reserve great freedom to design this project as your wish, so take advantage of your creativity and try surprising us!
3. **Make comments on important aspects of your program in `README`.** These includes "How should your program be compiled". "How should we inteprete your ouput?". "What is your program's hightlights? Why do you think your program is worth more points then others?". Remember that the `README` is the only way that you can communicate with us. It may be hard for you to argue for your final project since it would be graded after the final exam.

## Grading Policy

The project will be graded on the following aspects:

* Running Effects:
  * This focus how is the "end result" of the code. For instance, in ex1, Is the demonstration clear and easy to understand? Is the demo consists most of common cases (e.g. is your demo code is actually "random"). In ex2, is your designed trajectory "smooth" enough? 
* Design of structure:
  * Is your program structured in a clean way? Are you abusing the "switch" statement? Are you writing duplicate code repeatedly (for instance copying drawing code for Rectangle and Square)? Is your program split into sub-functions and classes? 
  * A general rule will be, whenever you write functions longer then 50 lines, it's very likely you can split the code into smaller functions. 
* Grammatical correctness:
  * Can your program compile? Can your program compile with no "Warnings" under ```-Wall```?
  * Do you remember to `delete` after `new`? Do you remember to close files?
  * Do you use correctly assign `public`, `protected` and `private` to member attributes? This may lead to heavy penalties.
  * Is your `Vec` class **imuttable**? Your member function is not allowed to change any attribute!
* README, highlights, and Bonus:
  * Is your README concise yet containing all neccessary info? 
  * Maybe you have write something worth recieving a Bonus for your creative work. Convince us to give you bonus through clearly stating them in the `README`.

## FAQs on Part I:

### Q: Where does the vehicles in the simulation come from? Files or user input?
Neither, you randomly generate them inside the programe. You should generate randomly arrived vehicles, with random type, random parking duration... etc. The program should inform the user of all neccessary attributes of the vehicle whenever a vehicle comes or leaves. 

## FAQs on Part II:

### Q: What is the `Vec` class? What is `operator+`?
The `Vec` class models the mathematical vector, or equivalently the concept of mathematical "Point". It makes sense to add to vectors together. So we provide compiler the definition of "+" when the two operator of "+" are `Vec`s. This is called operator overloading. Search online how to write operator overloads. An example is provided for you. After overloading "+", the following intuitive code works.

```cc
Vec v1(1,0);
Vec v2(1,1);
Vec v3 = v1 + v2; //v3 is now Vec(2,1);
```

Use `Vec` class as much as possible. Avoid directly computing coordinates!

### Q: Do we need to draw the trajectory in the window?
No, you are not require to, but some good implementation may lead to bonus. But you do need to make sure the trajectory of the car is smooth enough (Try avoiding sharp turns as much as possible, no spinning in one place, etc.).

### Q: Do we need to submit the class inheritance relation ship? In what form?
Yes, but you can do this either by providing a picture of the relationship (handwritten one as a taken photo is acceptable also, but we prepare something by LaTeX or else). Or you can simply submit a textual file, one looks like:

```
figure------group ------- UFO
        |           |---- ...
        |
        |---coloredFig------- triangle
        |               |---- ...
        ...
```

### Q: Can we change the given class interface/inheritance relation?
Yes, you can. **In the README file argue logically why the new one is better!** 

For the new inheritance relation, argue why the old inheritance relation is invalid in your design, and why the new one more logical and efficiency.

For the class interface, you are subject to the following rules:

1. 'Private' member attributes cannot be `public`
2. The `Vec` class stays immutable. 

### Q: What is the use of `anchor`?
Think of this concept as the "Frame of reference" in physics. Each figure has its own frame of reference, and the anchor vector(points) specifies where the origin of this frame of reference is. Since the object always rotate/zoom around its anchor point. Think how can you take advantage of this together with `<<` in `Vec` to simplify things.

### Q: Is there an essy way to perform rotation?
Yes, instead of using many `arcsin` and `arctan` etc, an easy way to perform rotation is to use "rotation matrix". See [this wiki page](https://en.wikipedia.org/wiki/Rotation_matrix) for details. You can rotate a vector easily by using simple multiplication/additions.


### Q: Is there a "criteria" for a "good" design ?
Yes, but some of it is related to personal "taste". But, a good design should be able to be regarded to be good for most people looking at it.

There does exists sort of "Minimum Requirement", that is a good design should be "consistent", for example, the implementation for `Group`:

* Possible to contain (has) other `Group`. A `Group` is a `Figure`, thus logically it can be part of a bigger `Group`
* Symmetric: if you do ask a `Group` (and of course any figure)
  
  1.  `Move(Vec(1,0))` 
  2.  `Zoom(3.0)` 
  3.  `Rotate(PI / 6)`
  4.  `Draw()` 
  5.  `Move(Vec(-1,0))`
  6.  `Rotate(-PI / 6)`
  7.  `Zoom(1.0/3.0)` 
  8.  `Draw()`. 
  
  Logically, the figure should be identical to the one before these operations. You should draw 2 identical figure at the same place. `Draw()` shouldn't affect the figure. The order of the operations shouldn't matter (the order of these 8 operation shouldn't affect how the figure is after the 8 operations) as well. Check if your implementation fits these criteria.

## Other questions

### Q: Can I use "windows/MacOS" specific functions?
Pricipally not. But if you have to do so. **Note and explain your reasons clearly in the README!**

### Q: Can We change the setup?
As this may surprise you, yes you can. You are allowed to change the setup, as long as you are "generalizing" the problem, or equivalently, not making the problem "easier". This is especially true for exercise 2. We encourage you to try more directions, and develop new methods.

### Q: What are the other directions that we can pursue to get bonus?
In general, you need to identify part of the code you believe is "too complicated". Such as:

* Duplicated code: code that you are writing over and over again. 
* Long functions: functions that are longer then 50 lines.
* Complex logic/calculation, simplify them using similar techniques as `Vec`.

In particular, some ways to go in Ex.2 to get bonus are:

* Add a small flag on the car, let it move up and down while the car is driving forward.

 The idea behind this is that all object are "rigid bodies" in our setup. In reality it is seldom true. A character will wave his hand when he is moving forward. Can you try and develop a good way of letting a figure has its "internel animation"?

* Very long drawing function / continuously created (destroyed) objects.

In the display function of your code (the function where you instantiate and draw figures), you will implement all the animations there. The code tends to be lengthy, and the logic will be quite complex. Also note that for each frame drawn, these objects will be reateed then destroyed. That's quite a waste of time and resources. It there a good work around? 

One obvious idea would be try to define object outside this function. But since this function does not take arguments, how can we pass our objects into the function? Well, you are not allowed to use global variables. 

* More complicated drawings

Try to make the teleporter more complicated. Can you try to implement a polygon teleporter, with the number of sides changes with time? 

* An interactive user interface

We did introduce the concept of a "function pointer" in the lecture. The technique is used in `glutTimerFunc()`. This type of code is quite common actually. It's called a `callback()` function. One very important use of callback functions are User interface, thins like buttons, text box, scrolls etc. Glut lets you draw these things in your application very easily. Try to add some interactive elements into your code. 

* Anything creative!

We might give big bonus if you show something that we have never thought of and really impressive. Don't restrict your imagination as long as you strictly follow the basic specification!

