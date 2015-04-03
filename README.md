# PrimeNumbers

PrimeNumbers is program written in C to find prime numbers using parallel programing concepts learned on Parallel Programming classes at [UnB](http://unb.br/).

## Requirements
- OpenMP

## Usage
```sh
$ ./main
```
The program would ask you to enter some parameters in this order:
- `int` limit - Should be the max number you want to find prime numbers;
- `char` type - Should be the type of return you want to. The available return are:
 - `t` - Return the execution time of the program;
 - `l` - Return only the list of prime numbers separated by space;
 - `a` - Return both list and execution time.
