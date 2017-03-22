# Hyper-Fighters
A text base console game, players select moves and then play that move againsed one-another.


Tecnical Design Description

I wanted the moves to be there own objets to make personalising there behaviour an easier proces, these should be contained within the charicter.
I also wanted the moves to be able to take in an object containing the charicters values such as health and focus.

It would be bad design to create a circular dependancy between the charicter and the mooves.
To avoid this I split the charicter into two objects, one containig the charicters data and one containing the charicters moves.



This is a project I started working on while I worked at Payground squad when I was at home.
It was to implemet all the design patterns I learned about from Game Programming Patterns.

I also wanted to write a framework for a game that would be easy to add new charicters to with new trates (like power up states,
Inflicting statuses on the enemy, or having extra requirements for using there hyper move.

