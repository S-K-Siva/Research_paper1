//Square Shaped Phantom Concept!.

#include <iostream>
#include <vector>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <string>
#define OFFSET 50
#define v 10
#define total_packet_sending 750
#include <set>
#include <random>
#include <ostream>
using namespace std;

struct package_data{
    int k =  2048;
    long double e_elec = 50 * pow(10,-9);
    long double e_amp = 100 * pow(10,-12);
    string data = NULL;
    
};


class packs{
public:
    
        int k =  2048;
        long double e_elec = 50 * pow(10,-9);
        long double e_amp = 100 * pow(10,-12);
        string data = NULL;
    
    
};
typedef struct package_data pack;
struct node{
    int x;
    int y;
    int ID;
    long double power;
    struct package_data *package;
    packs packages;
    
    vector<int> neighbours;
    vector<node> phantom_sqaure,closure_neighbour,equal_neighbour,forther_neighbour;
    
    bool operator<(const node& t) const
    {
        return (this->ID < t.ID);
    }

};
void set_packdata(struct node *Node){
    Node->package->k = 2048;
    Node->package->data = "\0";
    Node->package->e_elec = 50 * pow(10,-9);
    Node->package->e_amp = 100 * pow(10,-12);
}
void power_reduction(node *current,node *current2){
    if(current->package == NULL){
        current->package = (pack *)malloc(sizeof(pack));
        set_packdata(current);
    }
    if(current2->package == NULL){
        current2->package = (pack *)malloc(sizeof(pack));
        set_packdata(current2);
    }
    cout << "Initially...."<<endl;
    cout << "The power of node "<<current->ID<<" is "<< current->power<<endl;
    cout << "The power of node "<<current2->ID<<" is "<< current->power<<endl;
    cout << "Working" << endl;
    if(current2->package == NULL) cout << "There is no package!" << endl;
    else cout << "The package exist" << endl;
    if(current->package == NULL) cout << "Node1 has 0 package"<<endl;
    else cout << "Node1 package exist" << endl;
    long double consumption = (current->package->e_elec * current->package->k) + (current->package->e_amp * current->package->k * 50);
    
    cout << "Elec is:"<< current->package->e_elec << endl;
    cout << "S1:"<<(current->package->e_elec * current->package->k)<<endl;
    cout << "S2:"<<(current->package->e_amp * current->package->k * 50)<<endl;
    cout << (current->package->e_elec * current->package->k) + (current->package->e_amp * current->package->k * pow(50,2)) << endl;
    if(current2->ID == -1){
        current->power = current->power - consumption;
        cout << "After......."<<endl;
    cout << "The power of node "<<current->ID<<" is "<< current->power<<endl;
    return;
    }
    current->power = current->power - consumption;
    current2->power = current2->power - consumption;
    cout << "After......"<<endl;
    cout << "The power of node "<<current->ID<<" is "<< current->power<<endl;
    cout << "The power of node "<<current2->ID<<" is "<< current->power<<endl;
}


class board{
    public:
        int offset = 50;
        struct node *array[11][11];
        int m = 10;
        int source_x,source_y,source_id;//To get the equal,forther,closer neighbours.
        int Packets_received_counts = 0;
        int Packets_cancelled_counts = 0;
        std::set<node> phantom1,phantom2;
        
    board(){
        cout << "Constructor working..." << m << endl;
    if(m%2 == 0){
        m = m+1;
        }
        int max_val = offset * (m/2);
        int cnt = 1;
        for(int i = 0;i<m;i++){
        int col = offset * (m/2);
        //setting co-ordinates
        for(int j = 0;j<m;j++){
            array[i][j] = (struct node *)malloc(sizeof(struct node));
            array[i][j]->ID = cnt;
            cnt++;
            if(i < (m/2)){
                if(j == (m/2)){
                    array[i][j]->x = 0;
                    array[i][j]->y = max_val;
                    col = offset;
                }else if(j < (m/2)){
                    array[i][j]->x = -1 * col;
                    array[i][j]->y = max_val;
                    col = col - offset;
                }else if(j > (m/2)){
                    array[i][j]->x = col;
                    array[i][j]->y = max_val;
                    col = col + offset;
                }
                
            }else if(i == (m/2)){
                if(j == (m/2)){
                    array[i][j]->x = 0;
                    array[i][j]->y = 0;
                    array[i][j]->ID = -1;
                    col = offset;
                }else if(j < (m/2)){
                    array[i][j]->x = -1 * col;
                    array[i][j]->y = 0;
                    col = col - offset;
                    
                }else if(j > (m/2)){
                    array[i][j]->x = col;
                    array[i][j]->y = 0;
                    col = col + offset;
                    
                }
            }else if(i > (m/2)){
                if(j == (m/2)){
                    array[i][j]->x = 0;
                    array[i][j]->y = -1 * max_val;
                    col = offset;
                }else if(j < (m/2)){
                    array[i][j]->x = -1 * col;
                    array[i][j]->y = -1 * max_val;
                    col = col - offset;
                }else if(j > (m/2)){
                    array[i][j]->x = col;
                    array[i][j]->y = -1 * max_val;
                    col = col + offset;
                }
                
            }
        }
        if(i == (m/2)){
            max_val = offset;
        }else if(i < (m/2)){
            max_val = max_val - offset;
        }
        else if(i > (m/2)){
            max_val = max_val + offset;
        }

    }
    
    }
    
    void get_neighbours(){
        //Getting neighbours
    int max_val = offset *(m/2);
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
            array[i][j]->power = 0.5;
            cout << array[i][j]->ID << "'s power is:"<<array[i][j]->power<<endl;
            if((array[i][j]->y == max_val) && (array[i][j]->x == -1 * max_val)){
                
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j+1]->ID);
            }
            else if((array[i][j]->y == max_val) && (array[i][j]->x == max_val)){
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j-1]->ID);
            }else if((array[i][j]->y == max_val) && (array[i][j]->x != max_val)){
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j+1]->ID);
            }
            else if((array[i][j]->y == -1 * max_val) && (array[i][j]->x == -1 * max_val)){
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j+1]->ID);
            }
            else if((array[i][j]->y == -1 * max_val) && (array[i][j]->x == max_val)){
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j-1]->ID);
            }
            else if((array[i][j]->y == -1 * max_val) && (array[i][j]->x != max_val)){
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j-1]->ID);
            }
            else if((array[i][j]->x == -1 * max_val) && (array[i][j]->y != max_val)){
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j+1]->ID);
            }
            else if((array[i][j]->x == max_val) && (array[i][j]->y != max_val)){
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j-1]->ID);
            }
            else{
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j+1]->ID);
            }
        }
    }
    }
    void print_node_with_neighbours(){
        //printing the neighbours
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
            printf("%d : {",array[i][j]->ID);
            for(int k = 0;k< array[i][j]->neighbours.size();k++){
                if(k == array[i][j]->neighbours.size()-1){
                    cout<<array[i][j]->neighbours[k]<<"";
                    
                }
                else{
                    cout<<array[i][j]->neighbours[k]<<",";
                }
            }cout<<"} ";
        }cout<<endl;
    }
    }

    void get_3N(int id){
        cout << "The id:"<<id<<endl;
        long double cal = (v/2)/4;
        int h_max = ceil(cal);
        int max_val = offset *(m/2);
        int found = 0;
        for(int i = 0;i<11;i++){
            for(int j = 0;j<11;j++){
                if(array[i][j]->ID == id){
                    found = 1;
                    source_x = i;
                    source_y = j;
                    
                    //north
                    if(array[i][j]->x == 0 && array[i][j]->y > 0 && array[i][j]->y != max_val){
                        cout << "A1" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->equal_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j-1]);
                    }
                    else if(array[i][j]->x == 0 && array[i][j]->y == max_val){
                        cout << "A2" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->equal_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                    }
                    //south
                    else if(array[i][j]->x == 0 && array[i][j]->y < 0 && array[i][j]->y != -1 * max_val){
                        cout << "A3" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->equal_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                    }
                    else if(array[i][j]->x == 0 && array[i][j]->y == -1 * max_val){
                        cout << "A4" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->equal_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                    }
                    //west
                    else if(array[i][j]->x > 0 && array[i][j]->y == 0 && array[i][j]->x != max_val){
                        cout << "A5" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j+1]);
                    }
                    else if(array[i][j]->x == max_val && array[i][j]->y == 0){
                        cout << "A6" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                       array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                    }
                    //east
                    else if(array[i][j]->x < 0 && array[i][j]->y == 0 && array[i][j]->x != -1 * max_val){
                        cout << "A7" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j-1]);
                       array[i][j]->forther_neighbour.push_back(*array[i-1][j-1]);
                    }
                    else if(array[i][j]->x == -1 * max_val && array[i][j]->y == 0){
                        cout << "A8" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                    }
                    //top
                    else if(array[i][j]->y == max_val && array[i][j]->x == -1 * max_val){
                        cout << "A9" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        
                       array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                         }
                    else if(array[i][j]->y == max_val && array[i][j]->x == max_val){
                        cout << "A10" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        
                    }
                    else if(array[i][j]->y == max_val && array[i][j]->x != -1*max_val && array[i][j]->x != max_val){
                        if(array[i][j]->x < 0){
                        cout << "A11" << endl;

                            array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j-1]);
                        }
                        else if(array[i][j]->x > 0){
                            cout << "A12" << endl;
                           array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                      array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j+1]);
                        }
                        
                    }
                    //bottom
                    else if(array[i][j]->x == -1 * max_val && array[i][j]->y == -1 * max_val){
                        cout << "A13" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                       array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                    }
                    else if(array[i][j]->x == max_val && array[i][j]->y == -1 * max_val){
                        cout << "A14" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                       array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                    }
                    else if(array[i][j]->y == -1 * max_val && array[i][j]->x != max_val && array[i][j]->x != -1 * max_val){
                        cout << "A15" << endl;
                        if(array[i][j]->x < 0){
                            array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j-1]);
                        }
                        else if(array[i][j]->x > 0){
                            cout << "A16" << endl;
                            array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j+1]);
                        }
                    }
                    //left
                    else if(array[i][j]->x == -1 * max_val && array[i][j]->y != -1 * max_val && array[i][j]->y != max_val){
                        cout << "A17" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                       array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                    }
                    //right
                    else if(array[i][j]->x == max_val && array[i][j]->y != -1 * max_val && array[i][j]->y != max_val){
                        cout << "A18" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                    }
                    //side-1
                    else if(array[i][j]->x > 0 && array[i][j]->y != max_val && array[i][j]->y != -1*max_val && array[i][j]->x != max_val){
                        cout << "A19" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j+1]);
                    }
                    //side2
                    else if(array[i][j]->x < 0 && array[i][j]->x != -1*max_val && array[i][j]->y != max_val && array[i][j]->y != -1 * max_val){
                        cout << "A20" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                    }
                   cout << "Done" << endl;
                   cout << array[i][j]->equal_neighbour.size() << " "<<array[i][j]->closure_neighbour.size()<<endl;
                   
                }
            }
        }
        if(found == 0){
            cout << "The id not found!"<<endl;
        }
        cout << "Exited"<<endl;
    }
    
    void set_package(node *source,string data){
        cout<<"in-process"<<endl;
        cout << "The given data :" << data << endl;
        source->package = (struct package_data *)malloc(sizeof(struct package_data));
        set_packdata(source);
        source->package->data = data;
        cout << "Test:"<<source->package->data<<endl;
        cout << "Package fixed!"<<endl;
    }
    void get_square2(int source_x,int source_y){
        int h_max = ceil((v/2)/4);
        int start1 = source_x - (h_max+2);
        int end1 = source_y +(h_max+2);
        int start2 = source_x + (h_max+2);
        int end2 = source_y + (h_max + 2);
        int start3 = source_x + (h_max+2);
        int end3 = source_y - (h_max+2);
        int start4 = source_x - (h_max+2);
        int end4 = source_y -(h_max+2);
        cout << "Start1:"<<start1 << "end1:"<<end1<<endl<<" start2:"<< start2<<" end2:"<< end2<<endl;
        cout << "start3:"<<start3 << " end3:"<<end3<<endl<<" start4:" << start4<<" end4:"<<end4<<endl;
        cout << "Size:" << phantom1.size() << endl;
        if(start1 > -1 && start1 < 11&& end1 > -1 && end1 < 11){
            phantom2.insert(*array[start1][end1]);
        }
        if(start2 < 11 && end2 > -1 && end2 < 11){
            phantom2.insert(*array[start2][end2]);
        }
        if(start3 < 11 && start3 > -1 && end3 > -1 && end3 < 11){
            phantom2.insert(*array[start3][end3]);
        }
        if(start4 < 11 && start4 > -1 && end4 > -1 && end4 < 11){
            phantom2.insert(*array[start4][end4]);
        }
       
        cout << "The size of the phantom set is:"<<phantom1.size()<<endl;
        cout << "The nodes are...."<<endl;
        for(set<node>::iterator iter = phantom2.begin();iter!=phantom2.end();iter++){
            cout << iter->ID << endl;
        }
        
    }

    void get_square(int source_x,int source_y){
        int h_max = ceil((v/2)/4);
        int start1 = source_x - (h_max+2);
        int end1 = source_y +(h_max+2);
        int start2 = source_x + (h_max+2);
        int end2 = source_y + (h_max + 2);
        int start3 = source_x + (h_max+2);
        int end3 = source_y - (h_max+2);
        int start4 = source_x - (h_max+2);
        int end4 = source_y -(h_max+2);
        cout << "Start1:"<<start1 << "end1:"<<end1<<endl<<" start2:"<< start2<<" end2:"<< end2<<endl;
        cout << "start3:"<<start3 << " end3:"<<end3<<endl<<" start4:" << start4<<" end4:"<<end4<<endl;
        cout << "Size:" << phantom1.size() << endl;
        if(start1 < 0 && end1 > 0 && end1 < 11){
            start1 = 0;
        }
        
        if(start4 < 0 && end4 > 0 && end4 < 11){
            start4 = 0;
        }
        if(start3 > 10 && end3 > 0 && end3 < 11){
            start3 = 10;
        }
        if(start2 > 10 && end2 > 0 && end2 < 11){ 
            start2 = 10;
        }
        
        if(start1 > 0 && start1 < 11 && end1 < 0){
            end1 = 0;
        }
        if(start2 > 0 && start2 < 11 && end2 < 0){
            end2 = 0;
        }
        if(start3 > 0 && start3 < 11 && end3 < 0){
            end3 = 0;
        }
        if(start4 > 0 && start4 < 11 && end4 < 0){
            end4 = 0;
        }
        cout << "Start1:"<<start1 << "end1:"<<end1<<endl<<" start2:"<< start2<<" end2:"<< end2<<endl;
        cout << "start3:"<<start3 << " end3:"<<end3<<endl<<" start4:" << start4<<" end4:"<<end4<<endl;
        cout << "Size:" << phantom1.size() << endl;
        if(start4 > -1 && start1 > -1 && start4 < 11 && start1 < 11){
            for(int i = end4;i<=end1;i++){
            phantom1.insert(*array[start1][i]);
            }
        }
        if(start3 > -1 && start2 > -1 && start3 < 11 && start2 < 11){
            for(int i = end3;i<=end2;i++){  
                phantom1.insert(*array[start3][i]);
            }
        }
            
        if(start1 > -1 && start2 > -1 && start1 < 11 && start2 < 11){
            for(int i = start1;i<=start2;i++){
            phantom1.insert(*array[i][end1]);
        }
        }
        
        if(start4 > -1 && start3 > -1 && start4 < 11 && start3 < 11){
            for(int i = start4;i<=start3;i++){
            phantom1.insert(*array[i][end4]);
        }
        }
       
        cout << "The size of the phantom set is:"<<phantom1.size()<<endl;
        cout << "The nodes are...."<<endl;
        for(set<node>::iterator iter = phantom1.begin();iter!=phantom1.end();iter++){
            cout << iter->ID << endl;
        }
        
    }

    
   
    void print_all_nodes(){
        cout << "Working..." << endl;
        printf("\nPrinting all nodes\n");
        cout << m << endl;
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
            cout << array[i][j]->ID << "\t";
        }cout << endl;
    }
    cout << "Done" << endl;
    } 
    
    void packing(node *source,string new_data){
        source->package = (pack *)malloc(sizeof(pack));
        set_packdata(source);
        source->package->data = new_data;
        cout << source->package->data<<endl;
        cout << "Packet packed successfully!" << endl;
    }
    
    void SP(int src_ii,int src_jj,int des_ii,int des_jj){
        int src_i = src_ii;
        int src_j = src_jj;
        int des_i = des_ii;
        int des_j = des_jj;
        cout << "The source node details:"<<endl;
        cout<<"ID:"<<array[src_i][src_i]->ID<<endl;
        cout << "The destination node details:"<<endl;
        cout << "ID:"<<array[des_i][des_j]->ID<<endl;
    
        struct node *iter = array[src_i][src_j],*dest = array[des_i][des_j];
       
        
        while(src_i != des_i && src_j != des_j){
            
            if(src_i > des_i && src_j == des_j){
                cout << "A1"<<endl;
                iter = array[src_i-1][src_j];
                iter->package = (pack *)malloc(sizeof(pack));
                set_packdata(iter);
                iter->package->data = array[src_i][src_j]->package->data;
                power_reduction(iter,array[src_i][src_j]);
               array[src_i][src_j]->package = NULL;
                cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                
                src_i = src_i - 1;
                
            }
            else if(src_i < des_i && src_j == des_j){
                cout << "A2"<<endl;
                iter = array[src_i+1][src_j];
                iter->package = (pack *)malloc(sizeof(pack));
                set_packdata(iter);
                power_reduction(iter,array[src_i][src_j]);
                iter->package->data = array[src_i][src_j]->package->data;
                array[src_i][src_j]->package = NULL;
                cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                
                src_i = src_i + 1;
                
            }
            
            if(src_j > des_j && src_i == des_i){
                cout << "A3"<<endl;
                iter = array[src_i][src_j+1];
                iter->package = (pack *)malloc(sizeof(pack));
                set_packdata(iter);
                iter->package->data = array[src_i][src_j]->package->data;
                power_reduction(iter,array[src_i][src_j]);
                array[src_i][src_j]->package = NULL;
                cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                
                src_j = src_j + 1;
            }else if(src_j < des_j && src_i == des_i){
                cout << "A4"<<endl;
                iter = array[src_i][src_j - 1];
                iter->package = (pack *)malloc(sizeof(pack));
                set_packdata(iter);
                iter->package->data = array[src_i][src_j]->package->data;
                power_reduction(iter,array[src_i][src_j]);
                array[src_i][src_j]->package = NULL;
                cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                
                src_j = src_j - 1;
            }
            
            if(src_j != des_j && src_i != des_i){
                if(des_j > src_j && des_i > src_i){
                    cout << "A5"<<endl;
                    iter = array[src_i+1][src_j+1];
                    iter->package = (pack *)malloc(sizeof(pack));
                    set_packdata(iter);
                    iter->package->data = array[src_i][src_j]->package->data;
                    power_reduction(iter,array[src_i][src_j]);
                    array[src_i][src_j]->package = NULL;
                    cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                    
                    src_i = src_i + 1;
                    src_j = src_j + 1;
                }else if(des_j < src_j && des_i < src_i){
                    cout << "A6"<<endl;
                    iter = array[src_i-1][src_j-1];
                    iter->package = (pack *)malloc(sizeof(pack));
                    set_packdata(iter);
                    iter->package->data = array[src_i][src_j]->package->data;
                    power_reduction(iter,array[src_i][src_j]);
                    array[src_i][src_j]->package = NULL;
                    cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                    
                    src_i = src_i - 1;
                    src_j = src_j - 1;
                }
                else if(des_j < src_j && des_i > src_i){
                    cout << "A7"<<endl;
                    iter = array[src_i + 1][src_j - 1];
                    iter->package = (pack *)malloc(sizeof(pack));
                    set_packdata(iter);
                    iter->package->data = array[src_i][src_j]->package->data;
                    power_reduction(iter,array[src_i][src_j]);
                    array[src_i][src_j]->package = NULL;
                    
                    cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                    src_i = src_i + 1;
                    src_j = src_j - 1;
                }
                else if(des_j > src_j && des_i < src_i){
                    cout << "A8"<<endl;
                    iter = array[src_i - 1][src_j + 1];
                    iter->package = (pack *)malloc(sizeof(pack));
                    set_packdata(iter);
                    iter->package->data = array[src_i][src_j]->package->data;
                    power_reduction(iter,array[src_i][src_j]);
                    array[src_i][src_j]->package = NULL;
                    
                    cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                    src_i = src_i - 1;
                    src_j = src_j + 1;
                }
            }
        }
        
        while(src_i < des_i && src_j == des_j){
            cout << "A9"<<endl;
            iter = array[src_i+1][src_j];
            iter->package = (pack *)malloc(sizeof(pack));
            set_packdata(iter);
            iter->package->data = array[src_i][src_j]->package->data;
            power_reduction(iter,array[src_i][src_j]);
            array[src_i][src_j]->package = NULL;
            
            cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
            src_i = src_i + 1;
        }
        while(src_i > des_i && src_j == des_j){
            cout << "A10"<<endl;
            iter = array[src_i-1][src_j];
            iter->package = (pack *)malloc(sizeof(pack));
            set_packdata(iter);
            iter->package->data = array[src_i][src_j]->package->data;
            power_reduction(iter,array[src_i][src_j]);
            array[src_i][src_j]->package = NULL;
            cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
            src_i = src_i - 1;
        }
        while(src_j > des_j && src_i == des_i){
            cout << "A11"<<endl;
            iter = array[src_i][src_j - 1];
            iter->package = (pack *)malloc(sizeof(pack));
            set_packdata(iter);
            iter->package->data = array[src_i][src_j]->package->data;
            power_reduction(iter,array[src_i][src_j]);
            array[src_i][src_j]->package = NULL;
            cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
            src_j = src_j - 1;
        }
        while(src_j < des_j && src_i == des_i){
            cout << "A12"<<endl;
            iter = array[src_i][src_j + 1];
            iter->package = (pack *)malloc(sizeof(pack));
            set_packdata(iter);
            iter->package->data = array[src_i][src_j]->package->data;
            power_reduction(iter,array[src_i][src_j]);
           array[src_i][src_j]->package = NULL;
            cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
            src_j = src_j + 1;
        }
        if(src_i == des_i && src_j == des_j){
            cout << "transfer done" << endl;
            cout << "Mission Success" << endl;
            cout << array[des_i][des_j]->package->data<<endl;
        }
    }
    void check_pack(node *source){
        cout << source->package->data<<endl;
        cout << "Passed" << endl;
    }
    void forward_random_walk(node &source){
        
        cout << "Source id:"<<source.ID<<endl;
        cout << "Source's package:"<<source.package->data<<endl;
        
            for(int i = 0;i<array[source_x][source_y]->closure_neighbour.size();i++){
            if(array[source_x][source_y]->closure_neighbour[i].ID == -1){
                cout << "working" << endl;
                array[5][5]->package = (pack *)malloc(sizeof(pack));
                set_packdata(array[5][5]);
                cout << "alloted"<<endl;
                array[5][5]->package->data = source.package->data;
                power_reduction(array[source_x][source_y],array[5][5]);
                cout << "alloted and shifted"<<endl;
                array[source_x][source_y]->package = NULL;
                this->get_3N(array[source_x][source_y]->closure_neighbour[i].ID); 
                this->Packets_received_counts++;
                cout << "Package shifted to base station"<<endl;
                return;
            }
        }
        
        
        this->get_3N(source.ID);
        int new_ind = rand()%array[source_x][source_y]->closure_neighbour.size();
        cout << "New_ind:"<<new_ind<<endl;
        cout << "New_source:"<<array[source_x][source_y]->closure_neighbour[new_ind].ID<<endl;
        
        array[source_x][source_y]->closure_neighbour[new_ind].package = (pack *)malloc(sizeof(pack));
        cout << "Memeory alloted"<<endl;
        cout << "The package data:"<<source.package->data<<endl;
        struct node *iter;
        iter = &array[source_x][source_y]->closure_neighbour[new_ind];
        set_packdata(iter);
        array[source_x][source_y]->closure_neighbour[new_ind].package->data = source.package->data;
        cout << "Package shifted" << endl;
        power_reduction(iter,array[source_x][source_y]);
        
        array[source_x][source_y]->package = NULL;
        forward_random_walk(array[source_x][source_y]->closure_neighbour[new_ind]);
    }
    
           
    void mission1(){
        
        int id;
        cout << "Enter the source id:"<<endl;
        cin>>id;
        if(id == -1){
            this->get_3N(id);
            cout << "The SOURCE impersonating as BASE STATION"<<endl;
            return;
        }
        int src_i,src_j;
        int found = 0;
        for(int i = 0;i<11;i++){
            for(int j = 0;j<11;j++){
                
                if(array[i][j]->ID == id){
                    src_i = i;
                    src_j = j;
                    found = 1;
                    //total packets sending...
                    for(int i = 0;i<total_packet_sending;i++){
                        cout << "Initial power of the source......"<<endl;
                        cout << "The power of the source node is:"<<array[src_i][src_j]->power<<endl;
                        long double initial_power = array[src_i][src_j]->power;
                    this->get_3N(id);
                    this->get_square(source_x,source_y);
                    srand(time(0));
        int ind = rand()%phantom1.size();
        cout << "The random picked node is:";
        set<node>::iterator iter = phantom1.begin();
        advance(iter,ind);
        cout << iter->ID << endl;
        string new_data = "Secret Mission 001";
        this->packing(array[source_x][source_y],new_data);
        int des_x = 0,des_y = 0;
        int found = 0;
        for(int i = 0;i<11;i++){
            if(found == 1) break;
            for(int j = 0;j< 11 ;j++){
                if(array[i][j]->ID == iter->ID){
                    des_x = i;
                    des_y = j;
                    found = 1;
                    break;
                }
            }
        }
        
        //cout << "Des i:"<<des_x<<" j:"<<des_y<<endl;
        this->SP(source_x,source_y,des_x,des_y);
        //cout << "Package sent successfully!" << endl;
        get_square2(des_x,des_y);
        int ind2 = rand()%phantom2.size();
        set<node>::iterator inter_iter = phantom2.begin();
        advance(inter_iter,ind2);
        cout << inter_iter->ID << endl;
        int inter_des_x = 0,inter_des_y = 0;
        int inter_found = 0;
        for(int i = 0;i<11;i++){
            if(inter_found == 1) break;
            for(int j = 0;j< 11 ;j++){
                if(array[i][j]->ID == inter_iter->ID){
                    inter_des_x = i;
                    inter_des_y = j;
                    inter_found = 1;
                    break;
                }
            }
        }
        this->SP(des_x,des_y,inter_des_x,inter_des_y);
        cout << "Inter_Pack_data:"<<array[inter_des_x][inter_des_y]->package->data<<endl;
        cout<<"Inter id:"<<array[inter_des_x][inter_des_y]->ID<<endl;
        this->get_3N(array[inter_des_x][inter_des_y]->ID); 
        cout << "The source id :"<<array[source_x][source_y]->ID<<endl;
        cout<<"Inter id:"<<array[inter_des_x][inter_des_y]->ID<<endl;
        //this->FRW_mission(array[inter_des_x][inter_des_y]); 

        cout << "Forward Random walk starting......."<< endl<<endl<<endl<<endl;
        this->forward_random_walk(*array[inter_des_x][inter_des_y]);
        cout << "The Source id atlast is:"<<array[source_x][source_y]->ID<<endl;
        cout << "The source id pack is:"<<array[source_x][source_y]->package->data<<endl;
        array[source_x][source_y]->power = 0.5;
        cout << "The power of the source is:"<<array[source_x][source_y]->power<<endl;
        if(array[src_i][src_j]->package == NULL) cout << "Yes, source doesn't have a package." << endl;
    cout << "Power reduction status:"<< initial_power << "-->" << array[src_i][src_j]->power<<endl;
    cout << "Power reduced:";
    if(initial_power > array[src_i][src_j]->power) cout << "True" << endl;
    else cout << "False" << endl;
    cout << "The power of the source node is:"<<array[src_i][src_j]->power<<endl;
    }

                }
            }
            if(found == 0){
                cout << "ID not found"<<endl;
            }

    

        }
        }
    
        
    
};


int main(){
    board circuit;
    circuit.print_all_nodes();
    circuit.get_neighbours();
    circuit.print_node_with_neighbours();
    
    circuit.mission1();
    cout<<circuit.Packets_received_counts<<endl;
    return 0;
}
