//
//  cpathGraph.h
//  cpath
//
//  Created by Raj Patel on 11/25/19.
//  Copyright © 2019 Raj Patel. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <sstream>
#include <fstream>
#ifndef cpathGraph_h
#define cpathGraph_h
using namespace std;

class graph
{
    
    struct edge
    {
      int vertex_id;
      int cost;
      int time;
      edge(int vtx_id = 0,int _cost=0, int _time = 1.0)
        : vertex_id{vtx_id}, cost{_cost}, time{_time}
        {
        }
    };
    struct vertex
     {
       int id;
       vector<edge> outgoing;
       vector<edge> incoming;
       vertex(int _id = 0)
           : id{_id}
         {
         }
     };
    
   // vector<vertex> vertices;
private:
    map<int, vertex> vertices;
    
    
   
   
    bool add_edge(const string &str)
    {
      std::stringstream ss(str);
        string junk;
      int src=0,dest=0,cost=0,time=0;

        if (!(ss >> src))
            return false;
        if (!(ss >> dest))
            return false;
        if (!(ss >> cost))
        {
            cost=0;
        }
        if (!(ss >> time))
        {
            time=0;
        }
      else
      {
       
        if (ss >> junk)
        {
          // extra token?  format error
          return false;
        }
      }
       // cout<<src<<" "<<dest<<" "<<cost<<" "<<time<<endl;
       
      add_edge2(src, dest,cost,time);
      return true;
    }
    
     bool add_edge2(int src, int dest,
                       int cost, int time)
         {
            add_vertex(src);
            add_vertex(dest);
            this->vertices[src].outgoing.push_back(edge(dest,cost,time));
            this->vertices[dest].incoming.push_back(edge(src,cost,time));
           return true;
         }
    void add_vertex(int src)
    {
        vertices[src].id=src;
    }
    void _add_edge(const string &str)
    {

      if (!add_edge(str))
        std::cout << "add_edge failed; str='" << str << "'\n";
    }
    
public:
    bool read_file(const string &fname)
     {
       std::ifstream file;
       string line;

       file.open(fname, std::ios::in);
       if (!file.is_open())
         return false;

       while (getline(file, line))
       {
         // skip blank lines
         if (line.length() > 0)
         {
             //cout<<line<<endl;
           if (!add_edge(line))
           {
             std::cerr << "warning: skipped input line '"
                       << line << "' (ill-formatted)\n";
           }
         }
       }
       file.close();
       return true;
     }
    void display()
    {
        for( auto p: this->vertices)
        {
            cout<<p.second.id<<" has outgoing edges to ";
            for(auto a: p.second.outgoing)
            {
                cout<<a.vertex_id<<" ";
            }
             cout<<endl;
             cout<<p.second.id<<" has incoming edges from ";
            for(auto a: p.second.incoming)
            {
                cout<<a.vertex_id<<" ";
            }
             cout<<endl;
        }
            
        cout<<endl;
    }
};
#endif /* cpathGraph_h */
