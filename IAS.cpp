#include<bits/stdc++.h>
#include<stdlib.h>
typedef long long int ul;
#define endl "\n"
using namespace std;
void execute(ul arr[], int next, int max){
    ul AC=0, MQ=0,MBR=0;
    ul IBR=0,PC=0,MAR=0,IR=0;   
    PC=next;
    while(PC<1000 && PC<max){
        //initial fetch where OPCODE of left instruction goes to IR
        //ADDRESS goes to MAR
        //take care of left and right case
        bool left=true;
        MAR=PC;
        MBR=arr[MAR];
        IBR=(MBR)%((ul)1<<20);
        IR=MBR>>32;
        MAR=(MBR>>20)%((ul)1<<12);
        //IR now contains opcode which is now being decoded by using switch cases
        right:;
        switch(IR){
            case(1)://(0X01) LOAD M(X)
            {  
                cout<<"LOAD M("<<MAR<<")"<<endl;  
                MBR=arr[MAR];
                AC=MBR;//storing arr[MAR] in AC
                break;
            }
            case(2): //(0X02) LOAD -M(X)
            {
                cout<<"LOAD -M("<<MAR<<")"<<endl;  
                MBR=arr[MAR];
                AC=(-MBR);//storing -arr[MAR] in AC
                break;
            }
            case(3): //(0X03) LOAD |M(X)|
            {   
                cout<<"LOAD |M("<<MAR<<")|"<<endl;  
                MBR=arr[MAR];
                AC=abs(MBR);//storing |arr[MAR]| in AC
                break;
            }
            case(4): //(0X04) LOAD -|M(X)|
            {
                cout<<"LOAD -|M("<<MAR<<")|"<<endl;  
                MBR=arr[MAR];
                AC=(-abs(MBR));//storing -|arr[MAR]| in AC
                break;
            }
            case(5): //(0X05) ADD M(X)
            {
                cout<<"ADD M("<<MAR<<")"<<endl;  
                MBR=arr[MAR];
                AC=AC+MBR;//Adding MBR with the value present in AC
                break;
            }
            case(6): //(0X06) SUB M(X)
            {
                cout<<"SUB M("<<MAR<<")"<<endl;  
                MBR=arr[MAR];
                AC=AC-MBR;//Subtracting MBR with the value present in AC
                break;
            }
            case(7): //(0X07) ADD |M(X)|
            {
                cout<<"ADD |M("<<MAR<<")|"<<endl;  
                MBR=arr[MAR];
                AC=AC+abs(MBR);//Adding |MBR| with the value present in AC
                break;
            }
            case(8): //(0X08) SUB |M(X)|
            {
                cout<<"SUB |M("<<MAR<<")|"<<endl; 
                MBR=arr[MAR];
                AC=AC-abs(MBR);//Subtracting |MBR| with the value present in AC
                break;
            }
            case(9): //(0X09) LOAD MQ,M(X)
            {
                cout<<"LOAD MQ, M("<<MAR<<")"<<endl; 
                MBR=arr[MAR];
                MQ=MBR;//storing MBR in MQ
                break;
            }
            case(10): //(0X0A) LOAD MQ
            {
                cout<<"LOAD MQ"<<endl; 
                AC=MQ;//storing MQ in AC
                break;
            }
            case(11): //(0X0B) MUL M(X)
            {
                cout<<"MUL M("<<MAR<<")"<<endl; 
                MBR=arr[MAR];
                MQ=MQ*MBR;//Multiply MQ with MBR and then store the 40 left bits in MQ  and the 40 right bits in AC
                    AC=AC*MBR;
                    AC=AC+(MQ>>40);
                // else AC=(MQ>>40);
                MQ=(MQ)%((ul)1<<40);
                break;
            }
            case(12): //(0X0C) DIV M(X)
            {
                cout<<"DIV M("<<MAR<<")"<<endl; 
                MBR=arr[MAR];
                MQ=(AC-AC%MBR)/MBR;//quotient in MQ and remainder in AC
                AC=AC%MBR;
                break;
            }
            case(13): //(0X0D) JUMP M(X, 0:19)
            {
                cout<<"JUMP M("<<MAR<<", 0:19)"<<endl; 
                PC=MAR;
                MBR=arr[MAR];
                ul temp=(MBR>>20);
                IR=temp>>12;
                MAR=(temp)%((ul)1<<12);
                IBR=(MBR)%((ul)1<<20);//Put MAR in PC, take the left instruction of MBR and take IR, MAR and the right instruction in IBR
                left=true;
                goto right;
                break;
            }
            case(14): //(0X0E) JUMP M(X, 20:39)
            {
                cout<<"JUMP M("<<MAR<<", 20:39)"<<endl; 
                PC=MAR;
                MBR=arr[MAR];
                ul temp=(MBR)%((ul)1<<20);
                IR=(temp>>12);
                MAR=(temp)%((ul)1<<12);
                left=false;
                goto right;
                break;
            }
            case(15): //(0X0F) JUMP+ M(X, 0:19)
            {
                cout<<"JUMP+ M("<<MAR<<", 0:19)"<<endl; 
                if(AC>0){
                    PC=MAR;
                    MBR=arr[MAR];
                    ul temp=(MBR>>20);
                    IR=temp>>12;
                    MAR=(temp)%((ul)1<<12);
                    IBR=(MBR)%((ul)1<<20);
                    left=true;
                   //if AC>0, Put MAR in PC, take the left instruction of MBR and take IR, MAR and the right instruction in IBR
                    goto right;
                }
                break;
            }
            case(16)://(0X10) JUMP + M(X, 20:39)
            {
                cout<<"JUMP M("<<MAR<<", 20:39)"<<endl; 
                if(AC>0){
                    PC=MAR;
                    MBR=arr[MAR];
                    ul temp=(MBR)%((ul)1<<20);
                    IR=(temp>>12);
                    MAR=(temp)%((ul)1<<12);
                    left=false;
                    goto right;
                }
                break;
            }
            case(18): //(0X12) STOR M(X, 8:19)
            {
                cout<<"STOR M("<<MAR<<", 8:19)"<<endl; 
                ul AC1=(AC)%((ul)1<<12);
                ul r1=(arr[MAR])%((ul)1<<20);
                ul l1=(arr[MAR])>>32;
                l1=(l1)<<32;
                l1+=(AC1<<20);
                l1+=r1;
                arr[MAR]=l1;
                break;
            }
            case(19): //(0X13) STOR M(X, 28:39)
            {
                cout<<"STOR M("<<MAR<<", 28:39)"<<endl; 
                ul AC1=(AC)%((ul)1<<12);
                ul l1=(arr[MAR]>>20);
                l1=(l1<<20);
                ul r1=(arr[MAR])%((ul)1<<20);
                r1=r1>>12;
                r1=r1<<12;
                r1+=AC1;
                l1+=r1;
                arr[MAR]=l1;
                break;
            }
            case(20): //(0X14) LSH
            {
                cout<<"LSH"<<endl;
                AC=AC<<1;//left shift by one bit
                break;
            }
            case(21): //(0X15) RSH
            {
                cout<<"RSH"<<endl;
                AC=AC>>1;//right shift by one bit
                break;
            }
            case(33): //(0x21) STOR M(X)
            {
                cout<<"STOR M("<<MAR<<")"<<endl;
                arr[MAR]=AC;//store AC value in M(MAR)
                break;
            }
            default:
            { 
                cout<<"Invalid opcode"<<endl;
                exit(1);
            }
        }
        PC=PC+1;
        if(left==true){
            IR=(IBR>>12);
            MAR=(IBR)%((ul)1<<12);//take instruction in IBR, store IR, MAR, and then execute
            left=false;
            goto right;
        }
        cout<<"PC value is: "<<PC<<endl;
        cout<<"Value in memory value is: "<<arr[MAR]<<endl;
        cout<<"MBR value is: "<<MBR<<endl;
        cout<<"IBR value is: "<<IBR<<endl;
        cout<<"IR value is: "<<IR<<endl;
        cout<<"MAR value is: "<<MAR<<endl;
    }
    return;
}
int main()
{
    ul arr[1000];
    ul choice=0;
    while(choice!=7){
        cout<<"Enter 1--> for addition"<<endl;
        cout<<"Enter 2--> for subtraction"<<endl;
        cout<<"Enter 3--> for multiply"<<endl;
        cout<<"Enter 4--> for division"<<endl;
        cout<<"Enter 5--> for product of 10 numbers"<<endl;
        cout<<"Enter 6--> for factorial of n"<<endl;
        cout<<"Enter 7--> to exit"<<endl;
        cin>>choice;
        if(choice==1){
            int a, b; 
            cout<<"Enter first number: ";
            cin>>a;
            cout<<"Enter second number: ";
            cin>>b;
            arr[0]=a;
            arr[1]=b;
            arr[2]=0X0100005001;//LOAD M(X) ADD M(X) 
            arr[3]=0X0E00321002;//JUMP M(X, 20:39) STOR M(X)
            execute(arr,2, 4);
            cout<<"Answer is: "<<arr[2]<<endl;
        }
        else if(choice==2){
            int a, b; 
            cout<<"Enter first number: ";
            cin>>a;
            cout<<"Enter second number: ";
            cin>>b;
            arr[0]=a;
            arr[1]=b;
            arr[2]=0X0100006001;//LOAD M(X) SUB M(X) 
            arr[3]=0X0E00321002;//JUMP M(X, 20:39) STOR M(X)
            execute(arr,2, 4);
            cout<<"Answer is: "<<arr[2]<<endl;
        }
        else if(choice==3){
            int a, b; 
            cout<<"Enter first number: ";
            cin>>a;
            cout<<"Enter second number: ";
            cin>>b;
            arr[0]=a;
            arr[1]=b;
            arr[2]=0X090000B001;//LOAD MQ , M(X) MUL M(X)
            arr[3]=0X0E00321001;//JUMP M(X, 20:39) STOR M(X)
            arr[4]=0X0A00621002;//LOAD MQ STOR M(X)
            execute(arr, 2, 5);
            cout<<"Answer is: "<<arr[2]<<endl;
        }
        else if(choice==4){
            int a, b; 
            cout<<"Enter first number: ";
            cin>>a;
            cout<<"Enter second number: ";
            cin>>b;
            arr[0]=a;
            arr[1]=b;
            arr[2]=0X010000C001;//LOAD M(X) DIV M(X)
            arr[3]=0X0E00321001;//JUMP M(X, 20:39) STOR M(X)
            arr[4]=0X0A00621002;//LOAD MQ STOR M(X)
            execute(arr, 2, 5);
            cout<<"Quotient is: "<<arr[2]<<endl;
            cout<<"Remainder is: "<<arr[1]<<endl;
        }
        else if(choice==5){
            cout<<"Enter first number: ";
            cin>>arr[0];
            cout<<"Enter second number: ";
            cin>>arr[1];
            cout<<"Enter third number: ";
            cin>>arr[2];
            cout<<"Enter fourth number: ";
            cin>>arr[3];
            cout<<"Enter fifth number: ";
            cin>>arr[4];
            cout<<"Enter sixth number: ";
            cin>>arr[5];
            cout<<"Enter seventh number: ";
            cin>>arr[6];
            cout<<"Enter eighth number: ";
            cin>>arr[7];
            cout<<"Enter ninth number: ";
            cin>>arr[8];
            cout<<"Enter tenth number: ";
            cin>>arr[9];
            arr[10]=0X090000B001;//LOAD MQ, M(X) MUL M(X)
            arr[11]=0X0B0020B003;//MUL M(X) MUL M(X)
            arr[12]=0X0B0040B005;//MUL M(X) MUL M(X)
            arr[13]=0X0B0060B007;//MUL M(X) MUL M(X)
            arr[14]=0X0B0080B009;//MUL M(X) MUL M(X)
            arr[15]=0X210010F010;//STOR M(X) JUMP + M(X , 0:19)
            arr[16]=0X0A00621002;//LOAD MQ STOR M(X)
            execute(arr, 10,17);
            cout<<"Answer is : "<<arr[2]<<endl;           
        }
        else if(choice==6){
            arr[0]=1;
            arr[6]=1;
            cout<<"Enter number to find factorial: ";
            cin>> arr[1];
            arr[2]=0X090000B001;//LOAD MQ, M(X) MUL M(X)
            arr[3]=0X0A00021000;//LOAD MQ STOR M(X)
            arr[4]=0X0100106006;//LOAD M(X) SUB M(X)
            arr[5]=0X210010F002;//STOR M(X) JUMP + M(X, 0:19)
            execute(arr, 2, 6);
            cout<<"Answer is: "<<arr[0]<<endl;
        }
    }
    return 0;
}
