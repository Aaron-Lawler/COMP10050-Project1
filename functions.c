//
// Created by aaron on 27/03/2021.
//

//all function definitions used in the program

//insertion sort function to sort a 2d array of strings
//num acts as the max number of arguments in the array
//loops through array and continuously swaps elements if one is smaller (lower in alphabet)
void insertionSort(char array[256][256], int num){
    int a, b;
    char temp[50];
    for(int d=0;d<num;d++){
        for (b = 1; b <num; b++) {
            a = b;
            while (a > 0 && strcmp(array[a], array[a - 1]) < 0) {
                strcpy(temp, array[a]);
                strcpy(array[a], array[a - 1]);
                strcpy(array[a - 1], temp);
                a--;
            }
        }
    }

}

//knuth shuffle to swap elements
//this form of randomising the artistes and songs guarantees that no song will be played twice
void randomise(char array[256][256], int num){
    srand(time(NULL));
    int i,j;
    char temp[400];
    for ( i = num - 1; i >= 0; i--)
    {
        // Pick a random index from 0 to i
        j = rand() % (i + 1);

        // Swap arr[i] with the element
        // at random index
        strcpy(temp, array[i]);
        strcpy(array[i], array[j]);
        strcpy(array[j], temp);
    }
}

//function to generate the random playlist
//num acts as the max number of arguments in the array
void genPlaylist(char array[256][256], int num){
    int d = 0;
    int totalTime = 0;
    char temp[300];
    char *token;
    int minutes = 0;
    int seconds = 0;
    int total = 0;

    //while time is less than 59 minutes (shown in seconds) and we have not gone through more than all arguments
    //the first guard guarantees that the playlist will always be close to 60 minutes in duration
    //due to the last song not starting past 59 minutes
    while(totalTime<3540 && d<num){

        //this stops a triple play by skipping over what would be the 3rd song in a row
        if((strncmp(array[d], array[d - 1], 5)== 0) &&
           (strncmp(array[d], array[d - 2], 5)== 0)){
            d++;
        }
        //using strcpy and strtok to split up string
        strcpy(temp, array[d]);
        token = strtok(temp, ":");
        printf("%s: ", token);
        token = strtok(NULL, "***");

        printf( "\"%s\"", token );

        token = strtok(NULL, "**:");

        //multiply minutes of song by 60 to get seconds (I found seconds easier to work with)
        minutes = (atoi(token) * 60);
        printf(" (%s:", token);



        token = strtok(NULL, ":");
        printf("%s)\n", token);

        //record seconds
        seconds = atoi(token);
        //find total amount of seconds for that song
        total = minutes + seconds;

        //add these to the running total of time for whole playlist which acts as guard for loop
        totalTime += total;

        //look at next song
        d++;
    }
    printf("\n" );
    int mins = 0;
    int secs = 0;

    //totalTime divided by 60 will give us total minutes for playlist
    //as it's an int we will get a whole number
    mins = totalTime / 60;

    //totalTime modulus 60 will give us the remainder i.e the seconds
    //as it's an int we will get a whole number
    secs = totalTime % 60;



    //if the amount of seconds is less than 10, print a 0
    //this way you will get e.g (62:05) instead of (62:5)
    if(secs<10){
        printf("Total duration:  %d:0%d\n", mins, secs);

    }
    //else just print it out
    else{
        printf("Total duration:  %d:%d\n", mins, secs);
    }
}

//reads contents of default file into an array
int readFile(char array[256][256], FILE *fp, int counter){
    counter = 0;
    if ((fp = fopen("artistes+songs.txt", "r")) == NULL) {
        printf("File could not be opened\n");
    } else {
        while (fgets(array[counter], 256, fp)) {

            //this eliminates the trailing newline character
            array[counter][strlen(array[counter]) - 1] = '\0';
            counter++;

            // remove trailing newline from string
        }
    }
    return counter;
}

//reads contents of user specified file into an array
int readFileArgc(char array[256][256], FILE *fp, int counter, char* argv[]){
    counter = 0;
    if ((fp = fopen("%s", "r"), argv[1]) == NULL) {
        printf("File could not be opened\n");
    } else {
        while (fgets(array[counter], 256, fp)) {

            //this eliminates the trailing newline character
            array[counter][strlen(array[counter]) - 1] = '\0';
            counter++;

            // remove trailing newline from string
        }
    }
    return counter;
}

//prints the sorted songs in the required format
void printSortedSongs(char array[256][256],char array2[256][256], int num){
    char *token;
    char *temps;
    for (int d = 0; d < num; d++) {
        if (strncmp(array[d], array[d - 1], 5) != 0) {

            //uses str functions to split up and edit string
            token = strtok(array[d], ":");
            printf("\n");
            printf("%s:\n", token);
        }
        //copying over artSongDurExtra fixes issue with strtok and first song not printing
        const char ch = ':';
        strcpy(array[d], array2[d]);

        temps = strchr(array[d], ch);
        printf("%s\n", temps);
    }
    printf("\n");
}



