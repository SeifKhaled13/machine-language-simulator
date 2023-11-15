// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once //preprocessor used to prevent a header file from being included more than once in a translation unit.

#include <iostream>
#include <cmath>
#include <algorithm>
#define all(v) v.begin(), v.end()
#define each auto &
using namespace std;

// function declarations for converting between decimal and base representations
string dec_to_base(int value, int base);
int base_to_dec(string value, int base);
int base_to_dec(char c);

// base class representing a memory cell
class Memory_Cell
{
protected:
    int value{0};

public:
    // constructor with default value
    Memory_Cell(int val = 0);

    // setter and getter for the cell's value
    void set_value(int val);
    int get_value() const;

    // functions for obtaining binary, hexadecimal, two's complement, and floating-point representations
    string bi_value() const;
    string hex_value() const;
    int twos_comp_value() const;
    double float_value() const;
};

// derived class representing a register, inherits from Memory_Cell
class Register : public Memory_Cell
{
public:
    // comparison operators and assignment operators
    bool operator==(const Memory_Cell &rhs) const;
    bool operator!=(const Memory_Cell &rhs) const;
    Register operator=(const Memory_Cell &rhs);
    Register operator=(const int &rhs);
    Register operator++();
    Register operator+=(const Register &rhs);
    Register operator+=(const int &rhs);
};

// class representing an arithmetic unit
class Arthmetic_Unit
{
public:
    // function for converting a floating-point number to its binary representation
    string float_to_bi(double d);

    // functions for adding integers and floating-point numbers
    int add_int(int val1, int val2);
    double add_float(double val1, double val2);
};

// class representing a machine with registers, memory cells, and an arithmetic unit
class Machine
{
    Arthmetic_Unit AU;
    Memory_Cell *M;
    Register *R, PCtr, InsR;
    int rCount, mSize;
    bool halt;
    string screen;

    // helper function to check if a given string represents a valid hexadecimal value
    bool valid_value(string ins);

    // functions for executing different machine instructions
    void __1(string ins);
    void __2(string ins);
    void __3(string ins);
    void __4(string ins);
    void __5(string ins);
    void __6(string ins);
    void __B(string ins);

public:
    // constructor with default values for memory size and register count
    Machine(int memory_size = 256, int register_count = 16);

    // getter functions for register count and memory size
    int registerCount();
    int memorySize();

    // function to execute one cycle of the machine
    bool run_one_cycle();

    // function to get the screen content
    string sceen_content();

    // functions to access memory cells and registers
    Memory_Cell &atM(int index);
    Register &atR(int index);

    // function to reset the machine's state
    void reset();

    // getter functions for program counter and instruction register
    string PC();
    string IR();

    // function to check if the machine is halted
    bool halted();

    // destructor to release dynamically allocated memory
    ~Machine();
};

