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
    abc.read_file(argv[1]);
    abc.result(0, 5);
    
    //abc.display();
    return 0;
}
