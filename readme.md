# Hardware components for home automation



## Setup
To fetch submodules, run the command:
```
$ git submodule update --init
```


## Contribute
You are very welcome to do pull requests. Before doing so, please read the repository guidelines.


### Repository structure
KiCad can not handle libaries outside its project folders. Therefore common libraries must be places in ```include/libs/kicad``` and any project then symlinks this directory.

E.g. this will create a symbolic link ```libs```inside the kicad project.
```
$ cd mains-light-controller/circuits
$ ln -s ./../../include/libs/kicad ./libs
```