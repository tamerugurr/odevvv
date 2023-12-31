#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_ELEMENTS 12
#define MAX_GENRES 10
#define MAX_DIRECTORS 10
#define MAX_ENTRIES 3600

typedef struct {
    int budget;
    int year;
    char *title;
    char *titletype;
    char *top250;
} Budget;

typedef struct {
    char **genre;
    char *title;
    char **directors;
    char *mustsee;
    double votes;
    char *url;
} Name;

void printBudgetList(Budget *budgetArray, int count) {
    printf("=== List of Budget ===\n");
    for (int i = 1; i < count; i++) {
        printf("Budget: %d\n", budgetArray[i].budget);
        if(budgetArray[i].year != 0) printf("Year: %d\n", budgetArray[i].year);
        else printf("Year: No Data\n");
        printf("Title: %s\n", budgetArray[i].title);
        printf("Title Type: %s\n", budgetArray[i].titletype);
        printf("Top 250: %s\n", budgetArray[i].top250);
        printf("-------------------\n");
    }
    printf("\n");
}

void printNameList(Name *nameArray, int count, int genreSizes[], int directorSizes[]) {
    printf("=== List of Name ===\n");
    for (int i = 0; i < count; i++) {
        printf("Genre: ");
        int size_genre = genreSizes[i];
        for (int j = 0; j < size_genre; j++) {
            printf("%s ", nameArray[i].genre[j]);
        }
        printf("\n");
        printf("Title: %s\n", nameArray[i].title);
        printf("Directors: ");
        int size_director = directorSizes[i];
        for (int j = 0; j < size_director; j++) {
            printf("%s ", nameArray[i].directors[j]);
        }
        printf("\n");
        printf("Must See: %s\n", nameArray[i].mustsee);
        printf("Votes: %.1lf\n", nameArray[i].votes);
        printf("URL: %s\n", nameArray[i].url);
        printf("-------------------\n");
    }
    printf("\n");
}

void printMovieInformation(Name *nameArray, int count) {
    printf("=== Movie Information ===\n");
    int choice;
    printf("Enter the index of the movie (1-%d): ", count);
    scanf("%d", &choice);
    choice--;

    if (choice >= 0 && choice < count) {
        printf("Title: %s\n", nameArray[choice].title);
        printf("Must See: %s\n", nameArray[choice].mustsee);
        printf("Votes: %.1lf\n", nameArray[choice].votes);
        printf("URL: %s\n", nameArray[choice].url);
        printf("-------------------\n");
    } else {
        printf("Invalid choice.\n");
    }
    printf("\n");
}

void printGenreFrequency(Name *nameArray, int lineNum) {
    printf("=== Frequency of Genres ===\n");
    int frequency[MAX_GENRES];
    for(int i=1;i<MAX_GENRES;i++) frequency[i] = 0;
    for (int i = 0; i < lineNum; i++) {
        for (int j = 0; j < MAX_GENRES; j++) {
            if (nameArray[i].genre[j] != NULL) {
                frequency[j]++;
            }
        }
    }
    for(int i = 0; i<lineNum; i++){
        for (int j = 0; j < MAX_GENRES; j++) {
            if(nameArray[i].genre[j] != NULL) printf("%s: %d\n", nameArray[i].genre[j], frequency[j]);
        }
    }
    
    printf("\n");
}

int countLines(char *filename) {
    FILE* file = fopen(filename, "r");
    int count = 0;
    char c;
    
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    
    fclose(file);
    
    return count;
}

void selectionSortBudget(Budget budgetArr[], int arrLen) {
    int index;
    for (int i = 0; i < arrLen - 1; i++) {
        index = i;
        for (int j = i + 1; j < arrLen; j++) {
            if (budgetArr[j].year > budgetArr[index].year) index = j;
            
        }
        if (index != i) {
            Budget temp = budgetArr[i];
            budgetArr[i] = budgetArr[index];
            budgetArr[index] = temp;
        }
    }
}

void selectionSortName(Name nameArr[], int arrLen) {
    int index;
    for(int i = 0; i<arrLen-1; i++){
        index = i;
        for(int j = i+1; j < arrLen; j++){
            if(strcmp(nameArr[j].title, nameArr[index].title)) index = j;
        }
        if(index != i){
            Name temp = nameArr[i];
            nameArr[i] = nameArr[index];
            nameArr[index] = temp;
        }
    }
}

void writeToBudgetFile(Budget *budgetArray, int count){
    FILE *file = fopen("budget.txt","w");
    for (int i = 1; i < count; i++) {
        fprintf(file,"Budget: %d\n", budgetArray[i].budget);
        if(budgetArray[i].year != 0) fprintf(file,"Year: %d\n", budgetArray[i].year);
        else fprintf(file,"Year: No Data\n");
        fprintf(file,"Title: %s\n", budgetArray[i].title);
        fprintf(file,"Title Type: %s\n", budgetArray[i].titletype);
        fprintf(file,"Top 250: %s\n", budgetArray[i].top250);
        fprintf(file,"-------------------\n");
    }
}
void writeToListFile(Name *nameArray, int count, int genreSizes[], int directorSizes[]){
    FILE *file = fopen("list.txt","w");
    for (int i = 1; i < count; i++) {
        fprintf(file, "Genre: ");
        int size_genre = genreSizes[i];
        for (int j = 0; j < size_genre; j++) {
            fprintf(file, "%s ", nameArray[i].genre[j]);
        }
        fprintf(file,"\n");
        fprintf(file,"Title: %s\n", nameArray[i].title);
        fprintf(file,"Directors: ");
        int size_director = directorSizes[i];
        for (int j = 0; j < size_director; j++) {
            fprintf(file,"%s ", nameArray[i].directors[j]);
        }
        fprintf(file,"\n");
        fprintf(file,"Must See: %s\n", nameArray[i].mustsee);
        fprintf(file, "Votes: %.1lf\n", nameArray[i].votes);
        fprintf(file,"URL: %s\n", nameArray[i].url);
        fprintf(file,"-------------------\n");
    }
    printf("\n");
    }

int main(int argc, char *argv[]) {

    if(argc != 2){
        printf("Dogru Kullanim: ./odev.exe <dosya_adi>");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    int lineNum = countLines(argv[1]);
    char line[MAX_LINE_LENGTH];
    Budget budgetArray[MAX_ENTRIES];
    Name nameArray[MAX_ENTRIES];
    int count = 0;
    int genre_max[lineNum];
    int director_max[lineNum];
    while (fgets(line, sizeof(line), file) != NULL && count < MAX_ENTRIES) {
        char *elements[MAX_ELEMENTS];
        int elementCount = 0;

        // split the line by ;
        char *token = strtok(line, ";");
        while (token != NULL && elementCount < MAX_ELEMENTS) {
            elements[elementCount++] = token;
            token = strtok(NULL, ";");
        }

        // creating a Budget struct and assigning the values
        Budget budget;
        budget.budget = atoi(elements[0]); //atoi for str->int 
        budget.year = atoi(elements[6]);
        budget.title = strdup(elements[1]); 
        budget.titletype = strdup(elements[2]);
        budget.top250 = strdup(elements[9]);

        // creating a Name struct and assigning the values
        Name name;
        name.title = strdup(elements[1]);
        name.mustsee = strdup(elements[10]);
        name.votes = atof(elements[4]); //atof for str->double
        name.url = strdup(elements[11]);

        // split the genres by , and store them in the genre array
        name.genre = (char **)malloc(MAX_GENRES * sizeof(char *));
        char *genreToken = strtok(elements[7], ",");
        int genreCount = 0;
        while (genreToken != NULL && genreCount < MAX_GENRES) {
            name.genre[genreCount++] = strdup(genreToken);
            genreToken = strtok(NULL, ",");
            genre_max[count] = genreCount;
        }

        // split the directors by , and store them in the directors array
        name.directors = (char **)malloc(MAX_DIRECTORS * sizeof(char *));
        char *directorToken = strtok(elements[3], ",");
        int directorCount = 0;
        while (directorToken != NULL && directorCount < MAX_DIRECTORS) {
            name.directors[directorCount++] = strdup(directorToken);
            directorToken = strtok(NULL, ",");
            director_max[count] = directorCount;
        }

        budgetArray[count] = budget;
        nameArray[count] = name;
        count++;
    }
    selectionSortBudget(budgetArray,count);
    selectionSortName(nameArray,count);
    fclose(file);
    printf("%d\n",budgetArray[2].year);
    int choice;
    do {
        printf("=== MENU ===\n");
        printf("1. List of Budget Array\n");
        printf("2. List of Name Array\n");
        printf("3. Write sorted budget array elements to budget.txt file\n");
        printf("4. Write sorted list array elements to list.txt file\n");
        printf("5. All Information of a Single Movie\n");
        printf("6. Frequency of the Genres\n");
        printf("7. Exit");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printBudgetList(budgetArray, count);
                break;
            case 2:
                printNameList(nameArray, count, genre_max, director_max);
                break;
            case 3:
                writeToBudgetFile(budgetArray,count);
                break;
            case 4:
                writeToListFile(nameArray, count, genre_max, director_max);
                break;
            case 5:
                printMovieInformation(nameArray, count);
                break;
            case 6:
                printGenreFrequency(nameArray, count);
                break;
            case 7:
                printf("Bye!\n");
                break;
            default:
                printf("Invalid choice. Please choose between 1-8!.\n");
                break;
        }
    } while (choice != 8);
    
    return 0;
}
