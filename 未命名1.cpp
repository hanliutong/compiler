#include<iostream>

#include<windows.h>

#include<conio.h>

#include<time.h>

#include<string>

using namespace std;

int matrix[64][48];

void map(){
	//int matrix[64][48];
	for(int i=0;i<48;i++){
		for(int j=0;j<64;j++){
			matrix[j][i]=0;
		//	cout<<matrix[j][i];
		}
		//cout<<endl;
	}
}
//	cout<<matrix<<endl;
void makeAnemy(int matrix[][48]){
//	rand1 = rand()%(63 - 0 + 1) + 0;
//	rand2 = rand()%(47 - 36 + 1) + 36;
	int i=0;
	while(i<20){
		int rand1 = rand()%(63 - 0 + 1) + 0;
		int rand2 = rand()%(11 - 0 + 1) + 0;
		matrix[rand1][rand2]=3;
		i+=1;
	}
} 

void show(){
	for(int i=0;i<48;i++){
		for(int j=0;j<64;j++){
			//matrix[j][i]=0;
			cout<<matrix[j][i];
		}
		cout<<endl;
	}

}

setMyPlane(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			matrix[29+i][47-j]=1;
		}
	}
}

int main(){
	map();
	makeAnemy(matrix);
	setMyPlane();
	show();
}
