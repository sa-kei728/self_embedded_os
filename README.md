# self_embedded_os
Instruction of self made embedded OS

# Environment
| Category | Detail |
|:---:|:---:|
|OS|Ubuntu 18.04.4 LTS|
|CPU|x86-64(Core i7-8550U)|

# Prepare
1. get submodule kozos-build-server and build docker.
```
$ docker_setup.sh
```

2. USB-Serial cable.  
```
$ ls /dev | grep ttyUSB0
ttyUSB0
```

3. install gtkterm
```
$ sudo apt install gtkterm
```

# H8/3069F Manual
https://akizukidenshi.com/download/ds/renesas/hd64f3069r.pdf
