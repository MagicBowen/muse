# AEB : vehicle should stop when a static car is in front of it

## scenario

- duration: 60 s
- time : daytime
- weature : sunny
- terrian : Tanglu road

## static objects

- traffic light

## dynamic objects

- vehicle 0
	- driver type : adas
	- max speed : 15 km/h

- vehicle 1
	- driver type: user defined
	- max speed : 0 km/h


## expectation

~~~
concurrent:
{
	not exist:{Collision:{vehile 0}}
    sequential:
    {
    	exist:(Distance:{vechile 0, vechile 1, predof:{less than: 5}})
    }
}
~~~

~~~bash
concurrent
    ├── not exist(collsion of vehicle 0)
    └── sequential
           ├── exist(distance of vehicle 0 and vehicle 1, less than 10)
           ├── concurrent
				   ├── not exist(distance of vehicle 0 and vehicle 1, greater than 5)

~~~

~~~json

~~~

