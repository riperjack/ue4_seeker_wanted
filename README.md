# ue4_seeker_wanted

## General information
Implementation of seeker / wanted UE4 programming excercise.

![Alt Text](https://github.com/riperjack/ue4_seeker_wanted/raw/master/Docs/demo.gif)

Full demo available at:
https://www.youtube.com/watch?v=Apabx0xFHFY

## Solution description

* At each tick SeekerComponent iterates over all Actors that have WantedComponent attached using Object Iterator:
```
for (TObjectIterator<UWantedComponent> Itr; Itr; ++Itr) {
	...
}
```
Alternatively, I could have maintain a dynamic array of all actors that have wanted component attached, but then I would need to remember to add / remove actors whenever they are created / destroyed. While potentialy more performant, I decided for Object Iterator instead, seeing it as less complex solution and still meeting specified performance requirements ( runs smoothly with 250 actors ). 

* During the iteration, distance between Wanted and Seeker is checked ( distance can be customized in SeekerComponent properties ). Then there a raycast is projected between Seeker and Wanted Actor. If raycast is not blocked by any obstacle, then Wanted Actor is marked as detected. Their color is changed to red, for better visualization. Additionaly closest and most distant Wanted Actors are marked with yellow color ( please note that in case of only 1 wanted actor, he will be closest and most distant at the same time ).

* Currently raycasts sent from Seeker are blocked only by walls - Wanted Actors do not block each other. This could be easily changed if needed. 

* Seeker has 360 field of view. This could be easily changed if needed, by measuring angle between Seeker's forward vector and projected raycast and checking if it's less then desired angle.

* Main solution is contained in SeekerComponent and WantedComponent C++ files. There are also small portions of BVS for simple tasks ( level blueprint, UI, random moving pawn ).

* In a given specification there was no mention about movement of actors. I allowed myself to add movement to make things more interesting. I also skipped using logs to monitor all the changes since they can be observed with colors. Normally I discuss any specification changes in person. 

* UE4 built-in Pawn Sensing Component could be also used for this type of task.

## How to run / build
* Download / clone the project and open with UE 4.22
* There are 2 example maps provided: Maps/MapBig and Maps/MapSmall
* There are 2 sample actors provided: Actors/BP_SeekerExample and Actors/BP_WantedExample . They already have Seeker / Wanted component attached. Seeker component has MaxDistance parameter which can be customized. You can also change movement speed in MovementComponent properties. 
* After hitting play you can move camera with mouse and WSAD
* UI on the left side displays list of Wanted Actors with their distance to Seeker ( ordered )
* Alternatively download and run Windows 64 Binary from the link below. Maps can be changed using console command:
```
open MapBig
open MapSmall
```

## Links
* Windows 64 Executable
https://github.com/riperjack/ue4_seeker_wanted/releases/tag/1.0

* Video presentation
https://www.youtube.com/watch?v=Apabx0xFHFY
