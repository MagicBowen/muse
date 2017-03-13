# TestId : simply describe your test case

![](pics/logo.png "logo" "width:100px")

## category

- functional : composite
- priority : high
- running environment : simulation

## scenario

- sce : xxxxx_xxxx.sce

## static objects

- terrain : xxxxx_xxxx.rnd

## dynamic objects

1. adas vehicle
    - id : 0
    - max speed : 30 km/h
2. vechile
    - id : 1
    - driver : Traffic
3. pedestrain
    - driver : Random
        
## expectation

~~~
f1 : duration predicate that greater than 10 s.
f2 : lane gap predicate that variance less than 0.2.
f3 : distance to vehicle 1 predicate that average between 10 m and 20 m.
promise : !collision -< (f1 && f2 && (stop -> f3).
~~~

## comment

This test case is a template.