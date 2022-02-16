//
// Created by aaron on 27/03/2021.
//

#ifndef SE_FUNCTIONS_H
#define SE_FUNCTIONS_H

//all function prototypes that were used in this program
void insertionSort(char array[256][256], int num);
void randomise(char array[256][256], int num);
void genPlaylist(char array[256][256], int num);
int readFile(char array[256][256], FILE *fp, int counter);
int readFileArgc(char array[256][256], FILE *fp, int counter, char* argv[]);
void printSortedSongs(char words[256][256],char array[256][256], int num);



#endif //SE_FUNCTIONS_H
