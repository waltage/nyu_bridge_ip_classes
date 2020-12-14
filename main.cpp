/* Copyright 2020 walt@danielwalt.io
 * Author: Daniel Walt
 * NYU Email: dw2789@nyu.edu
 */

#include <iostream>
#include "ip.h"

#define print(_var) std::cout << _var;
#define println(_var) std::cout << _var << std::endl;
#define line() std::cout << std::endl;



int main() {
    IP test(192, 168, 2, 1);
    IP cidr(192, 168, 2, 1, 26);

    println(test.host);
    println("Class: " << test.host.inet_class());
    println(test.mask);
    line();
    line();
    println(cidr.host);
    println(cidr.mask.bits());


}