# Logic Transformer 

This program parses an infix logical expression and optionally transforms it to DNF, KNF, or prints it's truth table.

Originally I used it to learn more about combinatorial algorithms, while unknowingly creating a "gateway drug" into the world of parsers, formal languages, and finite/push-down automata. 

It also showed me how different (and exponentially more difficult) it was to (correctly) set up a build system for ```C++``` in comparison to ```node.js```.  

## Dependencies

The project was developed and tested on Linux. Windows support isn't tested. 

- `cmake` >= 3.16 (lower versions will probably work but it isn't tested)
- `make` (I used GNU Make 4.3, other will probably work)
- `clang++` >= 9.0.1 (or any other compiler that supports C++20)

## Building

Clone the repository locally and go into the created directory:
```bash
> git clone https://github.com/smiga287/logic_transformer.git
> cd logic_transformer
```

Build by making a build directory (i.e. `build/`), run `cmake` in that directory, and then use `make` to build the project and try it out!
```bash
> mkdir build && cd build
> cmake .. 
> make
> ./logic_tranformer
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
> ./logic_transformer # continuing from where we left off
(~q | ~(r = p)) ^ (p & (r > ~p))

p │ q │ r │ *
─────────────
T │ T │ T │ F
T │ T │ F │ F
T │ F │ T │ T
T │ F │ F │ F
F │ T │ T │ T
F │ T │ F │ F
F │ F │ T │ T
F │ F │ F │ T
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. 

## Todo

- [ ] [WIP] Explore different parsing methods 
- [ ] [WIP] DNF/KNF
- [ ] Make the program more user and cli friendly

## License
[MIT](https://choosealicense.com/licenses/mit/)
