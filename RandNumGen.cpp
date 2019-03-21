#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define FILE_NAME "data"
#define HOW_MANY 1000
#define MAX_RANGE 10000

// Will generate UNIQUE numbers
int main(){
	fstream fout;
	fout.open(FILE_NAME);

	srand(time(NULL)); // Seed random number with current time

	int tmpArray[HOW_MANY], tmp, i, j;
	for(i = 0; i < HOW_MANY; i++){
		tmp = rand() % MAX_RANGE + 1; // From 1 to MAX_RANGE, instead of 0 to MAX_RANGE - 1
		tmpArray[i] = tmp;
		for(j = 0; j < i; j++){
			if(tmp == tmpArray[j]){
				i--;
			} // Check for duplicates
		}
	}
	for(i = 0; i < HOW_MANY; i++){
		fout << tmpArray[i];
		if(i != (HOW_MANY - 1)){
			fout << endl;
		} // Don't add new line after last number
	}
	fout.close();
}