//
//  main.cpp
//  cpath
//
//  Created by Raj Patel on 11/25/19.
//  Copyright © 2019 Raj Patel. All rights reserved.
//

#include <iostream>
#include <vector>
#include "cpathGraph.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    graph abc;
    std::cout<<argv[1];
//    std::cout<<argv[2];
//    std::cout<<argv[3];
//    std::cout<<argv[4];abc.read_file("g2.txt");
    abc.read_file(argv[1]);
    
    
   // abc.display();
    abc.result(0,6,12);
    return 0;
}
