#include<iostream>
#include<vector>
using namespace std;

struct node{
    int x;
    int y;
    int ID;
    string package = "\0";
    vector<int> neighbours;
};
int main(){
    int offset,m;
    
    cout<<"Enter the matrix format:";
    cin>>m;
    if(m%2 == 0){
        m = m+1;
    }
    cout<<"Enter the value for offset:";
    cin>>offset;
    int max_val = offset * (m/2);
    //cout<<(m/2)<<endl;
    //cout<<max_val<<endl<<endl;
    int cnt = 1;
    struct node *array[m][m];
    for(int i = 0;i<m;i++){
        int col = offset * (m/2);
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
    max_val = offset * (m/2);
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
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
    //Sending packages to the base station.
    /*
            Base Station : (0,0)
    */

   int id;
   cout<<"Enter the id name, where you need to send the package!:";
   cin>>id;
   for(int i = 0;i<m;i++){
       for(int j = 0;j<m;j++){
                    
           if(array[i][j]->ID == id){
               string data;
               cout<<"Enter the data, that the package should sent to the base station:";
               cin>>data;
               array[i][j]->package = data;
               cout<<"The data present in the source node is:"<<array[i][j]->package<<endl;
               struct node *source;
                   source = array[i][j];
                   int ind_i = i,ind_j = j;
               cout<<"The Package is at the source id, ID = "<<array[i][j]->ID<<" "<<endl;
               if(array[i][j]->x == 0 && array[i][j]->y == 0){
                   cout<<"The Package already sent to the base station! ID = "<< -1 <<endl;
               }
               else if(array[i][j]->x == 0 && array[i][j]->y > 0){
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->y != 0){
                           source = array[ind_i+1][ind_j];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_i = ind_i + 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                       
                   }
               }
               else if(array[i][j]->x < 0 && array[i][j]->y > 0){
                   
                   while(source->x != 0 || source->y != 0){
                       if(source->x == 0 || source->y == 0){
                           break;
                       }
                       int temp = source->ID;
                       source = array[ind_i+1][ind_j+1];
                       source->package = array[ind_i][ind_j]->package;
                        array[ind_i][ind_j]->package = "\0";
                       ind_i = ind_i+1;ind_j = ind_j+1;
                       cout<<"The package send from "<<temp<<" to "<<source->ID<<endl;
                   }
                   
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->y != 0){
                           source = array[ind_i+1][ind_j];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_i = ind_i + 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                       else if(source->x != 0){
                           source = array[ind_i][ind_j+1];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_j = ind_j + 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                   }
                   
               }
               else if(array[i][j]->x > 0 && array[i][j]->y > 0){
                   
                   while(source->x != 0 || source->y != 0){
                       if(source->x == 0 || source->y == 0){
                           break;
                       }
                       int temp = source->ID;
                       source = array[ind_i+1][ind_j-1];
                       source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                       ind_i = ind_i+1;ind_j = ind_j-1;
                       cout<<"The package send from "<<temp<<" to "<<source->ID<<endl;
                   }
                   
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->y != 0){
                           source = array[ind_i+1][ind_j];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_i = ind_i + 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                       else if(source->x != 0){
                           source = array[ind_i][ind_j-1];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_j = ind_j - 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                   }
               }
               else if(array[i][j]->x >= 0 && array[i][j]->y == 0){
                   
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->x != 0){
                           source = array[ind_i][ind_j-1];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_j = ind_j-1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                   }
               }
               else if(array[i][j]->x == 0 && array[i][j]->y > 0){
                   
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->x != 0){
                           source = array[ind_i+1][ind_j];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_i = ind_i+1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                   }
               }
               else if(array[i][j]->x <= 0 && array[i][j]->y == 0){
                   
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->x != 0){
                           source = array[ind_i][ind_j+1];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_j = ind_j+1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                   }
               }
               else if(array[i][j]->x < 0 and array[i][j]->y < 0){
                  while(source->x != 0 || source->y != 0){
                       if(source->x == 0 || source->y == 0){
                           break;
                       }
                       int temp = source->ID;
                       source = array[ind_i-1][ind_j+1];
                       source->package = array[ind_i][ind_j]->package;
                        array[ind_i][ind_j]->package = "\0";
                       ind_i = ind_i-1;ind_j = ind_j+1;
                       cout<<"The package send from "<<temp<<" to "<<source->ID<<endl;
                   }
                   
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->y != 0){
                           source = array[ind_i-1][ind_j];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_i = ind_i - 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                       else if(source->x != 0){
                           source = array[ind_i][ind_j+1];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_j = ind_j + 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                   }
               }
               else if(array[i][j]->x > 0 && array[i][j]->y < 0){
                   while(source->x != 0 || source->y != 0){
                       if(source->x == 0 || source->y == 0){
                           break;
                       }
                       int temp = source->ID;
                       source = array[ind_i-1][ind_j-1];
                       source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                       ind_i = ind_i-1;ind_j = ind_j-1;
                       cout<<"The package send from "<<temp<<" to "<<source->ID<<endl;
                   }
                   
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->y != 0){
                           source = array[ind_i-1][ind_j];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_i = ind_i - 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                       else if(source->x != 0){
                           source = array[ind_i][ind_j-1];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_j = ind_j - 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                   }
               }
               else if(array[i][j]->x == 0 && array[i][j]->y < 0){
                   while(source->ID != -1){
                       int temp = source->ID;
                       if(source->y != 0){
                           source = array[ind_i-1][ind_j];
                           source->package = array[ind_i][ind_j]->package;
                           array[ind_i][ind_j]->package = "\0";
                           ind_i = ind_i - 1;
                           cout<<"The package send this "<<temp<<" to "<<source->ID<<endl;
                       }
                       
                   }
               }
               
               if(source->ID == -1){
                   cout<<"The package sent to the base station successfully!"<<endl;
                   cout<<"The Package received from the source node is "<<source->package<<endl;
                   cout<<"The data present source node  is: ";
                   if(array[i][j]->package == "\0") cout<<"NULL"<<endl;
                   else cout<<array[i][j]->package<<endl;
               }
               break;
           }
           else{
               continue;
           }
       }
   }

    
        
    
    
    return 0;

}
