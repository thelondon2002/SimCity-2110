# SimCity Milestone Submission
This project simulates the growth of a city per development of residential, industrial, and commercial zones.
A configuration file is read in to initialize the city region and output its initial state. Then, the simulation will
begin. Once complete, the final region state is outputted.

## Members of Group 204-5:
Derek Green  
Loredana Fouonji  
London Haith  
Sidharth Nair  
Muriel Nicholas  
Marcus Weber

## Compilation
Before compilation, be sure that the config txt file and the region csv file are located in the same directory as the program files.
  
The program files include a Makefile, so this program may be compiled by typing "make" into the Linux terminal.
No additional flags are necessary.
This will generate the executable "proj1.exe" so the user may then input the following to run the program:

```bash
./proj1.exe
```

## Usage
The program will prompt the user for the name of the city region's configuration file. It may be entered as follows:

```bash
Enter the simulation configuration file name: config1.txt
```

The program will then read in the configuration information and output the initial city region state. Then, The time step will commence
when the user presses the Enter key. The user can advance the time step further by pressing the Enter key repeatedly. Once the time limit has been reached, the program will then ask whether the user would like to look at the information specific to an area of the region. To accept, the user will input 'y' as follows:

```bash
Would you like to analyze the area between two coordinates? (Enter y or n): y
```

Then the program will prompt for the two coordinate pairs that constitute opposite corners of the area. The user will enter them will a comma separated the two as follows:

```bash
Enter the first coordinate as x,y (0-7,0-7) assuming the top left is 0,0: 5,7
```

The second pair can be anywhere else on the region since the program accounts for maximum and minimum values:

```bash
Now enter the second coordinate as 0-7,0-7: 3,5
```

Then the information of the region will be outputted and the program will prompt whether the user wants to analyze another area:

```bash
Would you like to analyze another area? (Enter y or n): y
```

If anything other than 'y' is inputted, then the program will terminate.
