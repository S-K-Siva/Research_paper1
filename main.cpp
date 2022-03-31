#include<iostream>
using namespace std;
struct node{
    int x;
    int y;
    int ID;
    int neighbours[];
};

int main(){
    int m,offset;
    
    cin>>m;
    if(m%2 == 0) m = m+1;
    cout<<"Enter the value for offset:";
    cin>>offset;
    int max_val = offset * (m/2);
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
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
            printf("%d ",array[i][j]->ID);
        }cout<<endl;
    }
    return 0;
}