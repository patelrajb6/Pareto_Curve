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
    if(argc<4)
    {
        cout<<"Sorry Invalid Syntax"<<endl;
        cout<<"Usage: ./cpath <file> <src> <dest> <budget>"<<endl;
        return 0;
    }
    abc.read_file(argv[1]);
    int source= atoi(argv[2]);
    int target= atoi(argv[3]);
    int budget=atoi(argv[4]);
    
    abc.result(source,target,budget);
    return 0;
}
