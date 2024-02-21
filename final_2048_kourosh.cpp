#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<fstream>
#include <string>
#include<iomanip>
#include<windows.h>
#include<cmath>
#include<string>

// checkme hanoghte gooshe rast, khal bashe crash mikone???
// too merge ham true beshe a_possible ,...
// leader board
// boll is w possible?? vaghti raste khoone khali hast, d ghaboole
// bool win tooye case 2048 true beshe
// 
// 

using namespace std;
//colours
    #define RESET "\033[0m"
    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN "\033[36m"
    #define WHITE "\033[37m"
    #define Gray  "\033[90m"	
    #define BrightRed "\033[91m"	
    #define BrightGreen "\033[92m"	
    #define BrightYellow "\033[93m"	
    #define BrightBlue "\033[94m"	
    #define BrightMagenta "\033[95m"	
    #define BrightCyan "\033[96m"	

struct Player{
    int score;
    // int averageScore;
    string name;
    int board_size;


};
// functions prototypes
    void zero_initializing(int** , int);
    void print_upper_part_box(int );
    void print_lower_part_box(int );
    void print3(int** , int);
    void cheking_size ();

    void insert_rand_num(int** , int);
    void dispMenue();
    void disp_2048();
    void merge_scoring(int** ,int ,char);
    void shift(int** , int, char);
    void shift2(int ** , int , char);
    void goodbye_message();
// gameover functions
    bool w_s_possible_move(int ** , int  );
    bool d_a_possible_move( int ** , int  );
    bool is_gameOver(int** , int );
    bool is_screen_full(int** , int);
// moving possiblity

//leaderboard fuctions
    void storeData();
    void print_from_arr();
    void resize();
    void append();
    void bubbleSort(int);


bool winner = false;
bool a_possible =false, d_possible =false , w_possible =false , s_possible =false ;
char key , menue_key;
int table_size;
int** mat = new int*[table_size];
Player new_player;
Player * player_arr;
int players_num =0;     //for each new game , players_num ++

// int capacity = 1;   

// Player * player_arr = new Player[capacity];
// ..............
// void storeData(){
//     // player_arr[players_num] = new_player;
//     ofstream writer("KouroshScores.txt", ios::app);
//     writer <<"Player's name : "<< new_player.name <<"    ***    " 
//     <<"Player's Score : "<< new_player.score <<"    ***    " << "Game's Board Size : "<< new_player.board_size << "\n";
    
// }
void storeData(){
    ofstream writer ("KouroshScores.txt", ios::app);
    writer <<new_player.name <<" "<<new_player.score<<" "<< new_player.board_size<< "\n";
}
void from_file_to_arr(){
    ifstream reader("KouroshScores.txt");
    string line ;
    int line_count =0;

    if(!reader){
        cerr<<"sorry ,there is a problem storing scores";
    }

    else{
        while(getline (reader , line)){
            line_count ++;
        }

        reader.close();
        players_num = line_count;
        player_arr = new Player[line_count];         // chon line count az sefr shoroo shode na az 1
        line_count =0;
        ifstream reader2("KouroshScores.txt");
        while(reader2 >> player_arr[line_count].name >> player_arr[line_count].score >> player_arr[line_count].board_size){
            // int beginning_of_score =line.find("Score") + 8;
            // int end_of_score = line.find("Game's Board Size") -11;
            // int length =( end_of_score ) - ( beginning_of_score );

            // string temp = line.substr(beginning_of_score , length);
            // player_arr[ line_count].score = stoi(temp);
            
            line_count ++;
        }
        reader2.close();
    }
}

void bubbleSort(int n) 
{ 
    int i, j; 
    for (i = 0; i < n - 1; i++) 
        for (j = 0; j < n - i - 1; j++) 
            if (player_arr[j].score < player_arr[j + 1].score) 
                swap(player_arr[j], player_arr[j + 1]); 
} 

void print_from_arr(){
    for(int i =0 ; i< players_num;i++){
        cout<<left << setw(5)<<i+1 << left<<setw(30)<<player_arr[i].name<<left<<setw(15)<<player_arr[i]. score <<left<<setw(3)<<player_arr[i].board_size<<endl;
    }
}

// void resize(){
//     Player * newArr = new Player [2*capacity];
//     for (int i = 0; i < capacity; i++)
//         newArr[i] = player_arr [i];
//     delete[] player_arr ;
//     player_arr  = newArr;
// }
// void append(){
//     if (players_num < capacity)
//        player_arr[players_num] = new_player;
//     else{
//         resize();
//         capacity *= 2;
//          player_arr[players_num] = new_player;
//     }
// }





void disp_2048(){
     //line1_two
    cout<<" "<<" "<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<< "\u25C6";
    //line1_zero
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<"\u25C6";
    //line1_four
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line1_eight
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<"\u25C6"<<endl;



    //line2_two
    cout<<" "<<" "<< "\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line2_zero
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line2_four
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line2_eight
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<endl;



    // line3_two
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    // line3_zero
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line3_four
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line3_eight
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<endl;



    // line4_two
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    // line4_zero
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line4_four
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<"\u25C6";
    //line4_eight
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<endl;


    //line5_two
    cout<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line5_zero
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line5_four
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line5_eight
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<endl;



    //line6_two
    cout<<" "<<" "<<" "<<" "<<"\u25C6";
    // line6_zero
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line6_four
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line6_eight
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<endl;



    // line7_two
    cout<<" "<<" "<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<"\u25C6";
    // line7_zero
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<"\u25C6";
    //line7_four
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6";
    //line7_eight
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<"\u25C6"<<" "<<"\u25C6"<<" "<<"\u25C6"<<endl;

}
void cheking_size (){
    while ( new_player.board_size <= 1){
        cerr<<"\n Square Table's size Must Be Bigger Than 1\nPlease Enter a Valid Size : ";
        cin>>new_player.board_size;
    }
}
void dispMenue(){
    system("cls");
    cout<<"~~Enter The Desired Operation~~"<<endl;
    cout<<"1) NEW GAME"<<endl;
    cout<<"2) LEADER BOARD"<<endl;
    cout<<"3) EXIT"<<endl;

   
    // while(true){
            menue_key= getch();
            switch(menue_key){

            //NEW GAME
                case '1':
                    new_player.score =0;
                    cout<<"PLAYER'S NAME : ";
                    cin>> new_player.name;
                    cout<<"\n~~Your square table will be nXn\nplease enter n : " ;
                    cin>>new_player.board_size;
                    cheking_size ();
                    
                    table_size = new_player.board_size;
                
                    system("cls");
                    zero_initializing(mat ,table_size);

                // inputalaki(mat , n);
                    insert_rand_num(mat , table_size);
                    table_size = new_player . board_size ;
                    /*serfan baraye inke dobar random poshte ham, natije yeksani 
                    darad, beine do random yek dastoor badihi midaham*/
                    insert_rand_num(mat , table_size);

                    print3(mat , table_size);

                    while(key =getch()){
                        d_possible=false;
                        a_possible=false;
                        w_possible=false;
                        s_possible=false;
                    if(!winner){ //checkme
                        if(key!= 'w' && key!= 'a' && key!= 's' && key!= 'd'&& key!= 'r'){
                            cerr << "You Must Only Use \"W , A , S , D\" Keys. Please Just Press Valid Keys\n";
                            continue;

                        }
                            if(key == 'r'){
                                // mikhad bazi tamoom she. pas bayad data ha ro save kone

                                storeData();
                                dispMenue();
                            }
                            else{
                                // if( !is_gameOver(mat , table_size) ){
                                shift(mat , table_size , key);
                                merge_scoring(mat , table_size , key);
                                shift2(mat , table_size , key);
                                
                                if(!is_screen_full(mat , table_size)) {           //age safhe por nabood
                                    // if(key=='a' &&  !a_possible){
                                    //     cerr<<RED<<"\nyou can't move this way, please make another move"<<RESET<<endl;
                                    //     continue;
                                        
                                    // }
                                    // else if( key == 'd' && !d_possible ){
                                    //     cerr<<RED<<"\nyou can't move this way, please make another move"<<RESET<<endl;
                                    //     continue;
                                    // }
                                    // else if(key == 'w' && !w_possible){
                                    //     cerr<<RED<<"\nyou can't move this way, please make another move"<<RESET<<endl;
                                    //     continue;
                                    // }
                                    // else if( key == 's' && !s_possible){
                                    //     cerr<<RED<<"\nyou can't move this way, please make another move"<<RESET<<endl;
                                    //     continue;

                                    // }
                                    // else
                                    insert_rand_num(mat , table_size);
                                    print3(mat , table_size);   
                                    // }


                                }
                                
                                else{                           // age por bood
                                    if( is_gameOver(mat , table_size) ){
                                        storeData();
                                        cout<< RED<<endl<<endl<<endl<<"                                       YOU LOSE"<<endl<<endl<<endl;
                                        cout<<RESET;
                                        cout<<"press any key to return to menue";
                                        getch();
                                        system("cls");
                                        dispMenue();

                                    }
                                    else{           //age por bood vali gameover nabood
                                        print3(mat , table_size);
                                    }
                                    // checkme
                                }
                            }
                        }
                    else{  //yani winner shode
                        winner =false;
                        cout<<GREEN<<endl<<endl<<"                                       you won"<<endl<<endl;
                        storeData();
                        cout<<"press any key to return to menue\n"<<RESET;
                        getch();
                        dispMenue();
                    }                    

            }

                    break;
            
            // LeaderBoard
                case '2':
                    // storeData();
                    from_file_to_arr();
                    bubbleSort(players_num);
                    print_from_arr();
                    cout<<"press any key to return to menue\n"<<RESET;
                    getch();
                    dispMenue();
                    break;
                    
                
                case '3':
                //EXIT
                            
                    // system("cls");
                    goodbye_message();
                    // storeData();
                    for(int i=0 ;i<table_size ; i++)
                        delete [] mat[i];
                    cout<<RESET;
                    delete [] player_arr;
                    exit(0);
                    break;
        
        
        }
        
    }
    
// }

   



void zero_initializing(int **mat ,int n){
    for(int i=0 ; i<n ; i++){
        mat[i]=new int[n];
        for (int j=0 ; j<n ; j++){
            mat[i][j]=0 ;
        }
    }
}
// d_a_possible=false hast
bool a_possible_move(int **mat , int n){        //left to right
     for (int i=0 ;i < n ; i++){
        for (int j=0 ;j < n-1 ; j++){
            if( mat[i][j] ==0 || mat[i][j+1] ==0 || mat[i][j]==mat[i][j+1]){
                return true;
            }
        }
    }
    return false;
}
bool d_a_possible_move( int **mat , int n ){
    for (int i=0 ;i < n ; i++){
        for (int j=0 ;j < n-1 ; j++){
            if( mat[i][j] ==0 || mat[i][j+1] ==0 || mat[i][j]==mat[i][j+1]){
                return true;
            }
        }
    }
    return false;
}
// w_s_possible = false hast
bool w_s_possible_move(int **mat , int n ){
     for (int i=0 ;i < n-1 ; i++){
        for (int j=0 ;j < n ; j++){
            if( mat[i][j] ==0 || mat[i+1][j] ==0 ||mat[i+1][j]==mat[i][j] ){
                return true;
            }
        }
    }
    return false;
}


bool is_gameOver(int** mat , int n){
    
    // age hich sefri nadashte basham o rooie noghte goshe paini_rast nabasham
    // vaghti safhe por ast vali hanooz harekat darim, nabayad be ezaye harkate gheire momken insert random ro anjam bede.
        for(int i=0 ; i<n-1 ; i++){
            for(int j=0 ; j<n-1 ;j++){
                
                if(  mat[i][j] == mat[i][j+1] || mat[i][j] == mat[i+1][j]){
                    return false;
                }
            }
        }
        
        for(int j=0 ; j<n-1  ; j++){
            if( mat[n-1][j] == 0 || mat[n-1][j] == mat[n-1][j+1])
            return false;
        }

    
        for(int i =0 ; i<n-1 ; i++){
            if( mat[i][n-1] == 0 || mat[i][n-1] == mat[i+1][n-1])
            return false;
        }
        return true;
}

    

void insert_rand_num( int**mat , int n){


    int newPosition;
    int i =0 ,j =0 ;
    //ta zamani ke be fazaye khali(0) narese, random vared mikone
    do{
        newPosition=  rand() % (n*n-1) +0;
         i = newPosition/n ;
         j = newPosition - n*i;
    }
    while( mat[i][j] != 0  );

    int newNumber;
    int randomNum;
    randomNum =rand() %   3 + 0 ;
    if(randomNum==1 || randomNum ==2 || randomNum ==3){
       newNumber=2;
    }
    else  newNumber=4;
    mat[i][j] = newNumber;

    }

void merge_scoring (int ** mat , int n , char key){
    switch (key){
       
        // check equality of adjecent cells from right to left 
        case 'd':
            //  d_a_possible=false;
            for(int i=0 ; i<n ;i++){
                 for(int j=n-1 ; j>0 ; j-- ){
                    if( mat[i][j] != 0 && mat[i][j] == mat[i][j-1]){
                        // d_a_possible=true;
                        mat[i][j] *=2 ;// checkme
                        mat[i][j-1]= 0;
                        new_player.score+=  mat[i][j];
                        // else checkme
                        
                    }
                }
            } 
            break;
        
        
        // check equality of adjecent cells from left to right
        case 'a' :
            // d_a_possible = false;
            for(int i=0 ; i<n ;i++){
                 for(int j=0 ; j< n-1 ; j++ ){
                    if(  mat[i][j] !=0 && mat[i][j] == mat[i][j+1]){
                        // d_a_possible= true;
                        mat[i][j] *=2 ;
                        mat[i][j+1]= 0;
                        new_player.score+=  mat[i][j];

                        j++;
                    }
                }
            } 
           
            break;

        
        // check equality of adjecent cells from up to down
        case 'w':
            for(int j=0 ; j<n ;j++){
                for(int i=0 ; i<n-1 ; i++){
                    if( mat[i][j] != 0 && mat[i][j] == mat[i+1][j]){
                        mat[i][j] *=2 ;
                        mat[i+1][j] =0 ;
                        new_player.score+=  mat[i][j];

                    }
                }
            }
            break;


        // check equality of adjecent cells from down to up
        case 's':
            for(int j=0 ; j<n ; j++){
                for(int i = n-1 ; i>0 ; i--){
                    // vaghti ta indexe i=1 ra chak konad.  indexe 0 ham chek shode ast
                    if(mat[i][j] != 0 && mat[i][j] == mat[i-1][j]){
                        mat[i][j]*=2;
                        mat[i-1][j] =0;
                        new_player.score+=  mat[i][j];

                        i--;
                    }
                }

            }
            break;

        }
}
bool is_screen_full(int **mat , int n){
    for(int i=0; i<n ;i++){
        for(int j=0 ; j<n ;j++){
            if(mat [i][j] ==0){
                return false;
            }
        }
    }
    return true;
}
void zero_initilizing_arr( int arr[] , int arr_size){
    for(int i=0 ; i<arr_size ; i++)
        arr[i] = 0 ;
} 
void shift2(int ** mat , int n , char key ){
    int *temp =new int[n];
    switch (key){

        // iterating from right to left
        // putting non_zero numbers together in a temp arr
        case 'd':
            for(int i=0 ; i<n ;i++){
                zero_initilizing_arr(temp , n);
                int k=n-1;
                for(int j=n-1 ; j>=0 ; j-- ){
                    if( mat[i][j] != 0 ){
                       temp[k] = mat[i][j];
                       k--;
                    }
                }           
                    for(int j = 0 ; j < n ; j++){
                        mat[i][j] = temp[j];
                    }
            }
            
            break;



        // iterating from left to right
        // putting non_zero numbers together in a temp arr
        case 'a' :
            for(int i=0 ; i<n ;i++){
                zero_initilizing_arr(temp , n);
                int k=0;
                for(int j=0 ; j< n ; j++ ){
                    if(  mat[i][j] !=0 ){
                        temp[k] = mat[i][j];
                        k++;
                    }
                }
                for(int j=0 ; j<n ; j++){
                    mat[i][j] = temp[j];
                }
            } 
            break;

        
        // iterating from  top to bottom
        // putting non_zero numbers together in a temp arr
        case 'w':
            for(int j=0 ; j<n ;j++){
                zero_initilizing_arr(temp , n);
                int k=0;
                for(int i=0 ; i<n ; i++){
                    if(  mat[i][j] !=0 ){
                        temp[k] = mat[i][j];
                        mat[i][j]=0;
                        k++;
                    }
                }
                for(int i=0 ; i<n ; i++){
                    mat[i][j] = temp[i];
                }
            } 
            break;


        // iterating from botoom  to top
        // putting non_zero numbers together in a temp arr
        case 's':
            for(int j=0 ; j<n ; j++){
                zero_initilizing_arr(temp , n);
                int k=n-1;
                for(int i=n-1 ; i>=0 ; i--){
                    if(  mat[i][j] !=0 ){
                        temp[k] = mat[i][j];
                        k--;
                    }
                }
                for(int i=n-1 ; i>=0 ; i--){
                    mat[i][j] = temp[i];
                }
            } 
            break;

        }
}

void shift(int ** mat , int n , char key ){
    int *temp =new int[n];
    switch (key){

        // iterating from right to left
        // putting non_zero numbers together in a temp arr
        case 'd':
            for(int i=0 ; i<n ;i++){
                zero_initilizing_arr(temp , n);
                int k=n-1;
                for(int j=n-1 ; j>=0 ; j-- ){
                    if( mat[i][j] != 0 ){
                        if ( j!= n-1 && mat[i][j+1] ==0){  // ellate j!=n-1 ineke tooye for , be ezaye j=n-1 --> mat[i][j+1] az jadval biroon mizane
                            d_possible= true;            // vaghti khode deraye !=0 va rastish =0 --> possible hast
                        }
                        
                       temp[k] = mat[i][j];
                       k--;
                    }
                }           
                    for(int j = 0 ; j < n ; j++){
                        mat[i][j] = temp[j];
                    }
            }
            
            break;

// checkme too while falseshoon kon

        // iterating from left to right
        // putting non_zero numbers together in a temp arr
        case 'a' :
            for(int i=0 ; i<n ;i++){
                zero_initilizing_arr(temp , n);
                int k=0;
                for(int j=0 ; j< n ; j++ ){
                    if(  mat[i][j] !=0 ){
                        if(j!= 0 && mat [i][j-1] ==0){  // ellate j!= 0 ineke tooye for , be ezaye j=0 --> mat[i][j-1] az jadval biroon mizane
                            a_possible=true;                // vaghti khode deraye !=0 va chapish =0 --> possible hast
                            
                        }
                        
                        temp[k] = mat[i][j];
                        k++;
                    }
                }
                
                for(int j=0 ; j<n ; j++){
                    mat[i][j] = temp[j];
                }
            } 
            break;

        
        // iterating from  top to bottom
        // putting non_zero numbers together in a temp arr
        case 'w':
            for(int j=0 ; j<n ;j++){
                zero_initilizing_arr(temp , n);
                int k=0;
                for(int i=0 ; i<n ; i++){
                    if(  mat[i][j] !=0 ){
                        if( i!=0 && mat[i-1][j] ==0){        // ellate i!= 0 ineke tooye for , bee ezaye i=0 --> mat[i-1][j] az jadval biroon mizane
                            w_possible= true;               // vaghti khode deraye !=0 hast va balaiish ==0 --> possible hast
                        }
                        
                        temp[k] = mat[i][j];    
                        mat[i][j]=0;
                        k++;
                    }
                }
                for(int i=0 ; i<n ; i++){
                    mat[i][j] = temp[i];
                }
            } 
            break;


        // iterating from botoom  to top
        // putting non_zero numbers together in a temp arr
        case 's':
            for(int j=0 ; j<n ; j++){
                zero_initilizing_arr(temp , n);
                int k=n-1;
                for(int i=n-1 ; i>=0 ; i--){
                    if(  mat[i][j] !=0 ){
                        if( i!= n-1 && mat[i+1][j] ==0){         // ellate i!= n1 ineke tooye for , bee ezaye i=n-1 --> mat[i+1][j] az jadval biroon mizane
                            s_possible = true; 
                        }
                       
                        temp[k] = mat[i][j];
                        k--;
                    }
                }
                for(int i=n-1 ; i>=0 ; i--){
                    mat[i][j] = temp[i];
                }
            } 
            break;

        }

}
// }
void print_upper_part_box(int n){
    for(int i=0 ; i<n ;i++)
        cout<< RESET<<Gray<<" "<<"\u25AC"<<"\u25AC"<<"\u25AC"<<"\u25AC"<<"\u25AC"<<"    ";
        cout<<endl;
    for(int i=0 ; i<n ;i++)
        cout<< RESET<<Gray<<"\u259E"<<"     "<<"\u259A"<<"   ";
        cout<<endl;
}
void print_lower_part_box(int n){
    for(int i=0 ; i<n ;i++)
        cout<<Gray<<"\u259A"<<"     "<<"\u259E"<<"   ";
        cout<<endl;
    for(int i=0 ; i<n ;i++)
        cout<< Gray<<" "<<"\u25AC"<<"\u25AC"<<"\u25AC"<<"\u25AC"<<"\u25AC"<<"    ";
        cout<<endl;

}


void print3(int **mat , int n){
    system("cls");
    for(int i=0 ; i<n ; i++){
        // checkme
        // cout<<"its we";
        // Sleep(1000);
        print_upper_part_box( n );
        //to cout the upper part of the box
        for (int j=0 ; j<n ; j++){
            switch(mat[i][j]){
                case 0:
                    cout<<"          ";
                    break;
        
                case 2: 
                // light yellow
                    cout<< BrightCyan<<"   " << mat[i][j] << "   "<<"   " ;
                    break;

                case 4:
                // yellow
                    cout<< CYAN<<"   " << mat[i][j] << "   "<<"   " ;
                    break;

                case 8:
                    cout<< BrightBlue<<"   " << mat[i][j] << "   "<<"   " ;
                    break;

                 case 16:
                    cout<< BLUE<<"  " << mat[i][j] << "   "<<"   " ;
                    break;

                 case 32:
                    cout<< BrightMagenta<<"  " << mat[i][j] << "   "<<"   " ;
                    break;

                 case 64:
                    cout<< MAGENTA<<"  " << mat[i][j] << "   "<<"   " ;
                    break;

                 case 128:
                    cout<< RESET<<"  " << mat[i][j] << "  " <<"   " ;
                    break;

                 case 256:
                    cout<<"  " << mat[i][j] << "  " <<"   " ;
                    break;

                 case 512:
                    cout<<"  " << mat[i][j] << "  " <<"   " ;
                    break;

                 case 1024:
                    cout<<" " << mat[i][j] << "  "<<"   " ;
                    break;

                 case 2048:
                 winner = true;
                    cout<<" " << mat[i][j] << "  "<<"   " ;
                    break;
                 
            }
        }
        cout<<endl;
        print_lower_part_box( n );
        cout<<endl<<endl;
    }
    cout<<endl<<endl;
    cout<<YELLOW<<"\nYou can press 'r' to end game at any time and return to menue\n";
    cout<<RESET;

}

void inputalaki(int **mat , int n){
    for(int i=0 ; i<n;i++){
        for (int j=0 ; j<n ;j++){
           cin>> mat[i][j] ;
        }
    }
}
void goodbye_message(){
    cout<<endl<<setw(15)<<"Can't Wait\n";
    Sleep(500);
    cout<<setw(33)<<"Seeing You Again\n";
    Sleep(500);
    cout<<setw(48)<<"In a New Game\n";
    Sleep(500);
    cout<<setw(51)<< "[="<<endl<<endl ;  
    Sleep(500);
 }
  
int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    
    //!!!!!!!!
    dispMenue();
    
    
        
    return 0;
}