# Chapter1
Execute Hello world by H8/3069F Tutorial Code

# Board Setting
Depending on the purpose, change H8/3069F DIP-SW and connect power adapter.  
- Write Mode for Flash ROM  

|SW|ON/OFF|
|:---:|:---:| 
|1|ON|
|2|ON|
|3|OFF|
|4|ON|

- Boot Mode from Flash ROM  

|SW|ON/OFF|
|:---:|:---:|
|1|ON|
|2|OFF|
|3|ON|
|4|OFF|

# Execute
```
$ docker_make.sh
```

- Build Only
```
$ docker_make.sh build
```

- Write Only
```
$ docker_make.sh write
```

- DEBUG (Enter in Docker interactive mode)
```
$ docker_make.sh debug
```
$ docker_make.sh clean
```

- Clean Only


# Operation Check
1. Setting R/W Permission for USB-Serial.
```
$ sudo chmod 666 /dev/ttyUSB0
```

2. Open gtkterm.
```
$ sudo gtkterm -p /dev/ttyUSB0
```

3. Connect power adapter.

4. Print "Hello World." for Terminal.

# Serial Setting

|Setting|Value|
|:---:|:---:|
|baudrate|9600bps|
|Bits|8bit|
|Stopbits|1bit|
|Parity|none|
|Flow control|none|

