//
//  main.cpp
//  cpath
//
//  Created by Raj Patel on 11/25/19.
//  Copyright © 2019 Raj Patel. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include "cpathGraph.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    graph abc;
    std::cout<<argv[1];
    abc.read_file(argv[1]);
    abc.display();
    return 0;
}
