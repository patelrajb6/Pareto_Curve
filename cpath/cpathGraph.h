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

#include <map>
#include <sstream>
#include <fstream>
#ifndef cpathGraph_h
#define cpathGraph_h
using namespace std;

 
class graph
{
    struct totalTradeOff
    {
        int vertexID;
        int totalCost;
        int totalTime;
        totalTradeOff(int totcost=-1, int totTime=INT_MAX, int vID=0):totalCost{totcost},totalTime{totTime},vertexID{vID}
        {
            
        }
    };
    struct edge
    {
      int vertex_id;
      int cost;
      int time;
      totalTradeOff total;
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
       vector<totalTradeOff> paretoCurve;
         int predecessor;
       totalTradeOff total;
         vertex(int _id = 0)
         : id{_id},predecessor{_id}
         {
         }
     };
   
    
    
   
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
          return false;
        }
      }
       
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
        vertices[src].predecessor=src;
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
            cout<<p.second.id<<" has outgoing edges to "<<endl;
            for(auto a: p.second.outgoing)
            {
                cout<<a.vertex_id<<" "<<a.cost<<" "<<a.time<<endl;
            }
             cout<<endl;
//             cout<<" has incoming edges from "<<endl;
//            for(auto a: p.second.incoming)
//            {
//                cout<<a.vertex_id<<" "<<a.cost<<" "<<a.time<<endl;
//            }
//             cout<<endl;
        }
            
        cout<<endl;
    }
    

   

    //void path();

    vector<totalTradeOff> nonDominant(int src, int dest)
    {
       auto compare=[](const totalTradeOff& a, const totalTradeOff& b)
          {
              if(a.totalCost==b.totalCost)
                  return a.totalTime<b.totalTime;
                  
              return a.totalCost> b.totalCost;
          };
        
        totalTradeOff vrtx;
        int currentCost= -1;
        int currentTime=-1;
        unsigned long VecSize=0;
        priority_queue <totalTradeOff, vector<totalTradeOff>,decltype(compare)> Que(compare);
        this->vertices[src].total.totalCost=0;
        this->vertices[src].total.totalTime=0;
        this->vertices[src].total.vertexID=src;
        
        Que.push(this->vertices[src].total);

        while(!Que.empty())
        {
            VecSize=this->vertices[src].paretoCurve.size();
            vrtx=Que.top();
            //cout<<"vertex: "<<vrtx.vertexID<<endl;
          //  cout<<"vertex: "<<vrtx.vertexID<<"  cost: "<<vrtx.totalCost<<" time: "<<vrtx.totalTime<<endl;
            Que.pop();

            for (auto &edg: this->vertices[vrtx.vertexID].outgoing)
            {
               
                currentCost=vrtx.totalCost+edg.cost;
                currentTime=vrtx.totalTime+edg.time;
                
               if(this->vertices[edg.vertex_id].total.totalCost<currentCost &&
               this->vertices[edg.vertex_id].total.totalTime>currentTime)
               {
                   this->vertices[edg.vertex_id].predecessor=vrtx.vertexID;
                   this->vertices[edg.vertex_id].total.totalCost=currentCost;
                   this->vertices[edg.vertex_id].total.totalTime=currentTime;
                   Que.push(totalTradeOff(currentCost,currentTime,edg.vertex_id));
               }

                if(dest==edg.vertex_id)
                {
                    this->vertices[src].paretoCurve.push_back(totalTradeOff(currentCost,currentTime,edg.vertex_id));
                }
 
            }
        }
        
        return this->vertices[src].paretoCurve;
    }
    
    bool extract_path(int src,int dest, vector<int> &path)
      {
        path.clear();
      
        if (this->vertices[dest].predecessor == dest)
        {
          path.push_back(dest);
          return true;
        }

        _extract_path(src, dest, path);

        // your code here!
        return true; // placeholder
      }

      void _extract_path(int src,int dest, vector<int> &path)
      {
        if (this->vertices[dest].predecessor == dest)
        {
          path.push_back(dest);
          return;
        }
        _extract_path(src, this->vertices[dest].predecessor, path);
        path.push_back(dest);
      }
        
    void result(int src, int dest)
    {
        vector<totalTradeOff> p= nonDominant(src, dest);
        vector<int> path;
        
        for(auto& curvePoints: p)
        {
            path.clear();
            cout<<"vertex to: "<<curvePoints.vertexID<<"  cost: "<<curvePoints.totalCost<<" time: "<<curvePoints.totalTime<<endl;
            extract_path(src,dest,path);
            for(auto& pathss: path)
                cout<<pathss<<" ";
            cout<<endl;
        }
    }
};
#endif /* cpathGraph_h */
