# Logic Table

This program parses an infix logical expression and displays the interpretation of every valuation of the logical terms in a table a.k.a. tautology table

I created the project because I found it tedious to check every possible variation by hand multiple times just to confirm I did a problem correctly in my Discrete Structures 1 class. I learned a lot about parsing and combinatorial algorithms, but I've learned the most about creating a modern `C++` project.

I hope that anybody reading the code could learn something new.

## Dependencies

The project was developed and tested on Linux. Windows support isn't tested. 

- `cmake` >= 3.16 (lower versions will probably work but it isn't tested)
- `make`

## Building

Clone the repository locally and go into the created directory:
```bash
> git clone https://github.com/smiga287/logic_table.git
> cd logic_table
```

Build by making a build directory (i.e. `build/`), run `cmake` in that directory, and then use `make` to build the project and try it out!
```bash
> mkdir build && cd build
> cmake .. 
> make
> ./logic_table
```

## Usage

After successfully building and running the program you should input a logical formula that consists of `logical variables` presented as letters, `()` and `logical operators` given in the table below (sorted by priority).

| operator | meaning |
|     --- | ---      |
~        | negation
&        | conjunction
\|       | disjunction
^        | exclusive disjunction
\>       | implication
=        | equivalence

Example of running the program and its output:
```bash
> ./logic_table # we are continuing from where we left off
(~q | ~(r = p)) ^ (p & (r > ~p))

p | q | r | *
--------------
T | T | T | F
F | T | T | F
T | F | T | T
F | F | T | F
T | T | F | T
F | T | F | F
T | F | F | T
F | F | F | T
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. 

## Todo

- [ ] Make the program more user friendly
- [ ] Add more descriptive comments
- [ ] Add unit tests
- [ ] Transition to using C++20 ranges and concepts when the compiler support allows it


## License
[MIT](https://choosealicense.com/licenses/mit/)
