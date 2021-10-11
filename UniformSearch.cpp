#include<iostream>
#include<queue>
#include<set>
#include<string>
using namespace std;
// 8-PUZZLE GAME SOLVER
struct Node{
    string state;
    int cost = 0;
    Node *parent = nullptr;
    vector<Node*> Children;
    
};

class Compare
{
public:
    bool operator() (Node*n1, Node*n2){
        
        if(n1->cost > n2->cost){
            return true;
        }

        else{
            return false;
        }
    }
};
    
void addChildren(Node* N , vector<Node*>&vec){
    string x = N->state;
    for(int i = 0 ; i < x.length() ; i++){

        if(x[i] == '#'){

            //up
            if(i != 0 && i != 1 && i != 2){
                    
                    
                string res = x;
                char temp = x[i-3];
                res[i] = temp;
                res[i-3] = '#';
                Node * n = new Node();
                n->state = res;
                n->cost = N->cost+5;
                vec.push_back(n);
                    
                    
            }
            //down
            if(i != 6 && i != 7 && i != 8){
                string res = x;
                char temp = x[i+3];
                res[i] = temp;
                res[i+3] = '#';
                Node * n = new Node();
                n->state = res;
                n->cost = N->cost+1;
                vec.push_back(n);
            }

            //left 
            if(i != 0 && i != 3 && i != 6 ){
                string res = x;
                char temp = x[i-1];
                res[i] = temp;
                res[i-1] = '#';
                Node * n = new Node();
                n->state = res;
                n->cost = N->cost+1;
                vec.push_back(n);
            }

            //right
            if(i != 2 && i != 5 && i != 8){
                string res = x;
                char temp = x[i+1];
                res[i] = temp;
                res[i+1] = '#';
                Node * n = new Node();
                n->state = res;
                n->cost = N->cost+1;
                vec.push_back(n);
            }

                
        }
            
            
    }


}

void printBoard(char B[3][3]){

    for(int i=0; i<3 ; i++){
        cout << B[i][0];
        for(int j = 1 ; j < 3 ; j++){

            cout << " " << B[i][j];
        }
        cout<<endl;
    }

}

void SetupBoard(string x , char B[3][3] , int &hr , int &hc){

    int row , col = 0;

    for(int i = 0 ; i < x.length() ; i++){

        if(col == 3){
            col = 0;
            row++;
        }

        if(x[i] == '#'){
            hr = row;
            hc = col;
        }

        B[row][col]=x[i];
        col++;
    }

}

int DoMove(int &hr , int &hc , string move , char Board[3][3]){

    if(move == "LEFT"){

        if(hc != 0 ){

            char temp = Board[hr][hc-1];
            Board[hr][hc] = temp;
            Board[hr][hc-1] = '#';
            //update index of hash
            hc = hc - 1;
            return 1;
        }

        else{
            return 0;
        }

    }

    else if(move == "RIGHT"){

        if(hc != 2){

            char temp = Board[hr][hc+1];
            Board[hr][hc] = temp;
            Board[hr][hc+1] = '#';
            hc = hc + 1;
            return 1;
        }

        else{
            return 0;
        }

    }

    else if(move == "UP"){

        if(hr != 0){

            char temp = Board[hr-1][hc];
            Board[hr][hc] = temp;
            Board[hr-1][hc] = '#';
            hr = hr - 1;
            return 1;
        }

        else{
            return 0;
        }

    }
    //move if DOWN
    else{

        if(hr != 2){

            char temp = Board[hr+1][hc];
            Board[hr][hc] = temp;
            Board[hr+1][hc] = '#';
            hr = hr + 1;
            return 1;
        }

        else{
            return 0;
        }
    }

}


Node* Bfs(Node*start , string goal){

    if(start->state == goal){
        return start;
    }

    queue<Node*> q;
    set<string> visited;
    bool inQ , inVis;
    q.push(start);

    while(!q.empty()){

        Node *n = q.front();
        q.pop();
        visited.insert(n->state);
        addChildren(n , n->Children);

        for(int i = 0 ; i < n->Children.size() ; i++){

            Node *child = n->Children[i];
            child->parent = n;
            inVis = visited.find(child->state) != visited.end();

            if(inVis==false){
                if(child->state == goal){
                    return child;
                }

                q.push(child);
            }


        }

    }
    return nullptr;
}

Node* UCS(Node*start,string goal){

    priority_queue<Node* , vector<Node*> ,Compare > pq;
    pq.push(start);
    set<string> visited;
    bool inVis, inPQ;

    while(!pq.empty()){

        Node *node = pq.top();
        pq.pop();

        if(node->state == goal){
            return node;
        }

        visited.insert(node->state);
        addChildren(node , node->Children);

        for(int i = 0 ; i < node->Children.size() ; i++){

            Node *child = node->Children[i];
            child->parent = node;

            inVis = visited.find(child->state) != visited.end();
    
    
            if(inVis == false){
                pq.push(child);
            }
           
            
        }


    }
    return nullptr;
}

bool PQ(priority_queue<Node* , vector<Node*> ,Compare > pq, int c){

    bool isIn = false;
    
    while(!pq.empty()){

        Node *node = pq.top();
        pq.pop();

        if((node->cost == c) ){
            isIn = true;
            
        }

    }
    return isIn;

}

int main(){
    
    char Board[3][3];
 
    string start ;
    string goal;

    cin >> start ;
    cin >> goal;
    
    Node *root = new Node();
    root->state = start;
    
    Node *result = UCS(root,goal);

    cout << result->cost << endl;


    return 0;
}
