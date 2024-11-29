# my_sample

## Document description:

./test _ sample: Project workspace for preliminary debugging 

buzzer _ test: After adding the buzzer file, the burned file of the passive buzzer (ky-006) generated after partial compilation in the Jiulian Union Tiger development environment. 

./buzzer: Stores * *./include * * and * *./src * * and the inner layer BUILD.gn internally, including the reference path of header file, compiled file directory, external component and module names, etc. 

./include: Store necessary header files internally 

./src: Store necessary. c files internally 

Outer layer BUILD.gn: internally stores the name of the inner layer module to be compiled 

bundle.json: Add modifications to subsystem components 

 

## Team internal document submission instructions:

include：Add、Modification、Remove 

Each submission should specify the number of submissions, the files modified at the time of submission, and the corresponding directory 

Good routine: 

``` 
Add: 
First modification: Add XXX file with path./XXX/XXX 
 
Modification: 
Second modification: Modify the XXX file to XXX file, and the path is./XXX/XXX 
 
Remove： 
Third modification: Delete./XXX/XXX file because test did not meet expectations 
```

 

## Division of labor within the group:

Wu: compilation environment construction, code framework writing, sensor operation and debugging 

Zhang: Responsible for code modification and optimization of PWM control buzzer 

Du: Responsible for writing and optimizing key switch drives
