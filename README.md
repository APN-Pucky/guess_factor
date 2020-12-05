# guess_factor

Guesses a factor by looping over possible exponents and bases.

## Install/Compile
```
cmake . && make
```
Will create a bin/guess_factor executable.


## Usage
```
./guess_factor goal [divisor [config]]
```
goal is the number to reproduce. 
If divisor is supplied goal gets divided by it. Then the guess_factor tries to find the factor inbetween goal and divisor.
config contains the bases and exponents to be used (see config.txt).

## Example
```
./bin/guess_factor 5 1 config.txt
```
![IMG](/img/img.png)

## const vs flex 

### const 

bases and exponents from src/config.h will be used. Needs a recompile with make, but is generally faster.

###  flex

bases and exponents from passed config.txt will be used. No recompile needed, but is a bit slower. 


