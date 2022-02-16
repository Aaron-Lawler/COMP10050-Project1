//Project submission for Software Engineering Project 1 - COMP10050
//by Aaron Lawler - Student Number: 20757091

//I am quite new to Clion so I hope this file is in the correct format for you
//I also had to place the artistes+songs.txt file in the cmake-build-debug folder for it to be read successfully

//I was able to complete every specification required for this project apart from:
// - allowing the user to use the command line to input artists and songs (however they could choose a file through the command line)
// - I was unable to break one part of my code into a function
// - The no more than three songs by one artist in the final randomised playlist

//Apart from those mentioned above, I believe this program meets all other specifications


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "functions.c"

int main(int argc, char* argv[]) {


    char temp[50];
    FILE *fp;
    int i = 0;
    int counter = 0;
    int k = -1;
    int count;
    char artSongDur[256][256];
    char artSongDurExtra[256][256];
    int numSongs = 0;
    int c, j;
    char words[256][256];
    char *playList[256][256];

    //if the user has put an argument in command line (name of text file to look for) search for that file
    if(argc > 1)
    {
        //if the file is not found, output error
        if((fp = fopen(argv[1], "r")) == NULL)
        {
          printf("%s does not exist and can not be opened for reading");
          return 1;
        }
        //if file is found, read artistes and songs from it
        else
            {
            i = readFileArgc(words, fp, counter, argv);
            fclose(fp);
            }
    }
    //if not argument is entered into command line, look for default text file (artistes+songs.txt)
    else{
        readFile(words, fp, counter);
        i = readFile(words, fp, counter);

    }


    //this is the part of the program which I was unable to put into a function
    count = 0;

    // i is the number of arguments taken from file, so they all get looped through
    for (j = 0; j < i; j++) {


        //will only pass guard if it is first artist and no songs have been entered
        if ((strchr(words[j], '*') == NULL) && (strlen(words[j]) > 1) && (k == -1)) {

            //it's an artist so they currently have no songs entered so numSongs equals 0
            numSongs = 0;

            //k++ means the next artists reached will be stored in the next column of the array
            k++;
            playList[k][numSongs] = words[j];
            strcpy(temp, playList[k][numSongs]);
            numSongs = 1;
        }

            //will only pass if songs have been entered from the previous artist
            //I also created artSongDurExtra to help with an issue I was having copying strings later on in the program
        else if ((strchr(words[j], '*') == NULL) && (strlen(words[j]) > 1)) {
            for (c = 1; c < numSongs; c++) {
                //edit strings and copy them across
                strcat(playList[k][0], ": ");
                strcat(playList[k][0], playList[k][c]);
                strcpy(artSongDur[count], playList[k][0]);
                strcpy(artSongDurExtra[count], playList[k][0]);
                strcpy(playList[k][0], temp);
                count++;
            }

            numSongs = 0;
            k++;
            playList[k][numSongs] = words[j];
            strcpy(temp, playList[k][0]);
            numSongs = 1;
        } else if (strchr(words[j], '*') != NULL) {
            playList[k][numSongs] = words[j];

            //numSongs holds the number of songs for a particular artist
            //only gets incremented not an artist
            numSongs++;
        }
    }

    for (c = 1; c < numSongs; c++) {
        //edit strings and copy them across
        strcat(playList[k][0], ": ");
        strcat(playList[k][0], playList[k][c]);
        strcpy(artSongDur[count], playList[k][0]);
        strcpy(artSongDurExtra[count], playList[k][0]);
        strcpy(playList[k][0], temp);
        count++;
    }

    //use insertion sort to sort artistes and their songs alphabetically
    insertionSort(artSongDur, count);
    insertionSort(artSongDurExtra, count);

    //print out sorted artistes and their songs
    printSortedSongs(artSongDur, artSongDurExtra, count);

    //randomise the artists and the songs for the playlist
    randomise(artSongDur, count);

    //generate the playlist
    genPlaylist(artSongDur, count);

}