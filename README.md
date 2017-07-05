# SDL Factory Example

This is a remake of an old school project using SDL 2. The project requirements were to simulate a
factory with consumer and producer machines and a robot. The consumer and producer machines are
stationary and work for a set time duration. The robot goes around the factory looking for a payload
from a producer machine to be dropped off at a consumer machine. The robot can only carry one
payload at a time, a producer machine can only produce one payload at a time, and a consumer machine
can only consume one payload at a time. There were other minor requirements for the assignment, but
this is the main idea behind the factory.

# Remarks

This project is an exploration in a number of ideas. Namely that I want to avoid using loops
wherever possible inside the game loop. I also want to avoid using conditional branching as much as
possible; the exception to this is using the ternary operator when choosing between two static
values (as in a literal). It is also an exercise in practicing the use of SDL.

To get around using loops inside the game loop, I created an API that takes advantage of the game
loop itself. I call it an "iterative algorithm"; the idea being that instead of nesting loops, we
define steps of an iterative computation. This way, at each call to `update`, the next step of the
algorithm is executed. This happens until the algorithm completes. It is particularly useful for the
robot when it needs to pick a machine to move towards. The robot is given a collection of candidate
machines, iteratively computes a path for each one, then selects the machine with the shortest path.

As for avoiding conditional branching, in many cases, it is simply unavoidable, so I do the best I
can.

Another interesting topic I think deserves mention is the events system--or, the change notification
system. It uses callbacks, templates, and some standard c++ library collections.

Unfortunately, this project does not make use of any multithreading.

---
Created June 28, 2017 by CJ Dimaano