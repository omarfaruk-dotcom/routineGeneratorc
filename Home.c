#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1000

int max = 1000;
char TeacherSubjects[30] = "TeacherSubjects.txt";
char BatchWiseSub[30] = "BatchWiseSub.txt";
char SubjectDestribution[30] = "SubjectDestribution.txt";
char SubjectDestribution2[30] = "SubjectDestribution2.txt";
char Temp[30] = "Temp.txt";
char PreSchedule[30] = "PreSchedule.txt";
char Shedule[30] = "Shedule.txt";

int fileCheck(FILE *file);
int rewrite(const char *subject, char *teacher);
int fileRegenaret();
int distribute(int loop);
int afterdestributeTeachers();
int BatchWiseSubRe();
int destributeTeachers();
int makeClasses();
int makeRoutine();
void appendFile(char *filename);
int find();
int FullRoutine();

struct xClassInfo
{
    char batch[10];
    char section[10];
    char subject[10];
    char teacher[30];
    int nclass;
};
struct ClassInfo
{
    char batch[10];
    char section[10];
    char subject[10];
    char teacher[30];
    int nclass;
};
struct presch
{
    char dayname[10];
    char classname[10];
    int classnum;
};

struct subject
{
    char subject[10];
};
struct teacher
{
    char teacher[20];
    int maxClass;
};
struct batch
{
    int batch;
};
struct section
{
    char section[10];
};
struct teacherFile
{
    char subject[10];
    char teacher[30];
    int maxClass;
};
struct batchSub
{
    char batch[10];
    char section[10];
    char subject[10];
    int ff;
};
struct cbatchSub
{
    char batch[10];
    char section[10];
    char subject[10];
    int ff;
};
int fileCheck(FILE *file)
{
    if (file == NULL)
    {
        printf("Not Opened The File : %s \n", file);
    }
}

int rewrite(const char *subject, char *teacher)
{
    struct teacherFile t[max];
    int i = 0;
    FILE *file4 = fopen(TeacherSubjects, "r");
    FILE *temp = fopen(Temp, "w");
    if (!fileCheck(file4) || !fileCheck(temp))
    {
        return 0;
    }
    while (fscanf(file4, "%s %s %d", t[i].subject, t[i].teacher, &t[i].maxClass) != EOF)
    {
        if (strcmp(t[i].subject, subject) == 0 && strcmp(t[i].teacher, teacher) == 0)
        {
            t[i].maxClass = t[i].maxClass - 2;
            fprintf(temp, "%s %s %d\n", t[i].subject, t[i].teacher, t[i].maxClass);
        }
        fprintf(temp, "%s %s %d\n", t[i].subject, t[i].teacher, t[i].maxClass);
        i++;
    }
    fclose(file4);
    fclose(temp);

    return 1;
}
struct Line
{
    char text[MAX_LINE_LENGTH];
};
int fileRegenaret()
{
    struct Line lines[MAX_LINES];
    int lineCount = 0;
    FILE *file = fopen("TeacherSubjects.txt", "r+");
    if (file == NULL)
    {
        perror("Unable to open file");
        return 1;
    }
    while (lineCount < MAX_LINES)
    {
        char input[MAX_LINE_LENGTH];
        if (fgets(input, sizeof(input), file) == NULL)
        {
            break;
        }
        int found = 0;
        for (int i = 0; i < lineCount; i++)
        {
            if (strcmp(lines[i].text, input) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            strcpy(lines[lineCount].text, input);
            lineCount++;
        }
    }
    fclose(file);
    file = fopen("TeacherSubjects.txt", "w");
    if (file == NULL)
    {
        perror("Unable to open file");
        return 1;
    }
    for (int i = 0; i < lineCount; i++)
    {
        fputs(lines[i].text, file);
    }
    fclose(file);
    return 0;
}

int distribute(int loop)
{
    struct ClassInfo b[max];
    struct presch p[max];
    int j = 0;
    int i = 0;
    int n = 0;
    FILE *file3 = fopen(SubjectDestribution, "r");
    fileCheck(file3);
    FILE *temp = fopen(Temp, "w");
    fileCheck(temp);
    while (fscanf(file3, "%s %s %s %s %d", b[i].batch, b[i].section, b[i].subject, b[i].teacher, &b[i].nclass) != EOF)
    {
        for (int j = 0; j < b[i].nclass; j++)
        {
            fprintf(temp, "%s %s %s %s %d\n", b[i].batch, b[i].section, b[i].subject, b[i].teacher, 1);
        }
        i++;
    }
    fclose(temp);
    fclose(file3);
    remove(SubjectDestribution2);
    rename(Temp, SubjectDestribution2);
    i = 0;
    FILE *file = fopen(SubjectDestribution2, "r");
    fileCheck(file);
    while (fscanf(file, "%s %s %s %s %d", b[i].batch, b[i].section, b[i].subject, b[i].teacher, &b[i].nclass) != EOF)
    {
        i++;
        n = i;
    }
    fclose(file);
    struct times
    {
        char time[30];
    } t[max];
    int ii = 0;
    printf("Enter Times : ");
    for (ii = 0; ii <= loop; ii++)
    {
        scanf("%s", t[ii].time);
    }
    FILE *file1 = fopen(PreSchedule, "r");
    fileCheck(file1);
    FILE *file2 = fopen(Shedule, "w");
    fileCheck(file2);
    FILE *file4 = fopen(SubjectDestribution2, "r");
    fileCheck(file4);
    i = 0;
    ii = 0;
    int ttt = ii;
    while (fscanf(file1, "%s %s %d", p[j].dayname, p[j].classname, &p[j].classnum) != EOF)
    {
        if (strcmp(p[j].classname, "Break") == 0)
        {
            ii++;
            continue;
        }
        fprintf(file2, "%s %s %s %s %s %s %d %s\n", b[i].batch, b[i].section,
                b[i].subject, b[i].teacher, p[j].dayname, p[j].classname, p[j].classnum, t[ii].time);
        i++;
        j++;
        ii++;
        if (ii > loop)
        {
            ii = 0;
        }
        if (i > n)
        {
            break;
        }
    }
    fclose(file1);
    fclose(file2);
    fclose(file4);
}
int afterdestributeTeachers()
{
    system("cls");
    struct ClassInfo c[max];
    int i = 0;
    int j = 0;
    FILE *file2 = fopen(BatchWiseSub, "r");
    fileCheck(file2);
    struct batchSub bb[max];
    while (fscanf(file2, "%s %s %s %d", bb[i].batch, bb[i].section, bb[i].subject, &bb[i].ff) != EOF)
    {
        if (bb[i].ff != 0)
        {
            printf("Need %s Subject Teacher\n", bb[i].subject);
        }
    }
    fclose(file2);
    i = 0;
    int totalClass = 0;
    FILE *file6 = fopen("SubjectDestribution.txt", "r");
    fileCheck(file6);
    while (fscanf(file6, "%s %s %s %s %d", c[i].batch, c[i].section, c[i].subject, c[i].teacher, &c[i].nclass) != EOF)
    {
        totalClass += c[i].nclass;
        i++;
    }
    fclose(file6);
    printf("Total Class : %d\n", totalClass);
    printf("\n\n");
    int classesPerDay, daysInWeek, breakTime, nclassNumber;
    printf("Enter The Number Of Classes Per Day: ");
    scanf("%d", &classesPerDay);
    printf("Enter The Number Of Days In A Week: ");
    scanf("%d", &daysInWeek);
    printf("Enter The Break Time (After How Many Classes): ");
    scanf("%d", &breakTime);
    printf("Enter How Much Class Rooms You Have : ");
    scanf("%d", &nclassNumber);
    int Loop = classesPerDay + daysInWeek;
    int totalClasses = classesPerDay * daysInWeek;
    FILE *file = fopen(PreSchedule, "w");
    fileCheck(file);
    char *dayNames[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    int classNumber = 1;
    for (int day = 0; day < daysInWeek; day++)
    {
        for (int classCount = 1; classCount <= classesPerDay; classCount++)
        {
            fprintf(file, "%s Class %d\n", dayNames[day], classNumber);

            if (classCount % breakTime == 0 && classCount < classesPerDay)
            {
                fprintf(file, "%s Break %d\n", dayNames[day], classNumber);
            }
            classNumber++;
            if (classNumber > nclassNumber)
            {
                classNumber = 1;
            }
        }
    }
    fclose(file);
    distribute(Loop);
}
int BatchWiseSubRe()
{
    struct cbatchSub b[max];
    struct batchSub bb[max];
    int j = 0;
    int i = 0;
    FILE *file1 = fopen("Temp1.txt", "r");
    fileCheck(file1);
    FILE *file2 = fopen(BatchWiseSub, "r");
    fileCheck(file2);
    FILE *temp = fopen(Temp, "w");
    fileCheck(temp);
    while (fscanf(file1, "%s %s %s %d", b[j].batch, b[j].section, b[j].subject, &b[j].ff) != EOF)
    {
        j++;
    }
    j = 0;
    while (fscanf(file2, "%s %s %s %d", bb[i].batch, bb[i].section, bb[i].subject, &bb[i].ff) != EOF)
    {
        if (strcmp(b[j].subject, bb[i].subject) == 0 && strcmp(bb[i].section, b[j].section) == 0 && strcmp(b[j].batch, bb[i].batch) == 0)
        {
            printf("Here\n");
            b[j].ff = 0;
            fprintf(temp, "%s %s %s %d\n", b[j].batch, b[j].section, b[j].subject, b[j].ff);
            i++;
        }
        else
        {
            fprintf(temp, "%s %s %s %d\n", b[j].batch, b[j].section, b[j].subject, b[j].ff);
        }
        j++;
    }
    fclose(file1);
    fclose(file2);
    fclose(temp);
    remove("Temp1.txt");
    remove(BatchWiseSub);
    rename(Temp, BatchWiseSub);
}
int destributeTeachers()
{
    struct teacherFile t[max];
    struct batchSub b[max];
    int i = 0;
    int j = 0;
    FILE *file1 = fopen(TeacherSubjects, "r");
    FILE *file2 = fopen(BatchWiseSub, "r");
    FILE *file3 = fopen(SubjectDestribution, "w");
    FILE *temp = fopen("Temp1.txt", "w");
    fileCheck(temp);
    fileCheck(file1);
    fileCheck(file2);
    fileCheck(file3);


    while (fscanf(file1, "%s %s %d", t[i].subject, t[i].teacher, &t[i].maxClass) != EOF)
    {
        i++;
    }
    int Nclass = 2;
    while (fscanf(file2, "%s %s %s %d", b[j].batch, b[j].section, b[j].subject, &b[j].ff) != EOF)
    {
        for (int k = 0; k < i; k++)
        {
            if (strcmp(t[k].subject, b[j].subject) == 0 && t[k].maxClass >= 2)
            {
                fprintf(file3, "%s %s %s %s %d\n", b[j].batch, b[j].section, b[j].subject, t[k].teacher, Nclass);
                rewrite(t[k].subject, t[k].teacher);
                remove(TeacherSubjects);
                rename(Temp, TeacherSubjects);
                fprintf(temp, "%s %s %s %d\n", b[j].batch, b[j].section, b[j].subject, 0);
                break;
            }
        }
        j++;
    }
    fclose(temp);
    fclose(file1);
    fclose(file2);
    fclose(file3);
    fileRegenaret();
    BatchWiseSubRe();
    afterdestributeTeachers();
    return 1;
}
int makeClasses()
{
    system("cls");
    struct batch bat[max];
    struct section sec[max];
    struct subject sub[max];
    int i = 0, ii = 0, iii = 0;
    FILE *file2 = fopen(BatchWiseSub, "a");
    fileCheck(file2);
    while (1)
    {
        i = 0;
        ii = 0;
        iii = 0;
        printf("\n\n");
        printf("Enter 00 For Exit Batch\n");
        printf("Enter Batch Number : ");
        scanf("%d", &bat[i].batch);
        if (bat[i].batch == 0)
        {
            break;
        }
        while (1)
        {
            printf("Enter Section : ");
            scanf("%s", sec[ii].section);
            if (strcmp(sec[ii].section, "00") == 0)
            {
                break;
            }
            ii++;
        }
        while (1)
        {
            printf("Enter Subject : ");
            scanf("%s", sub[iii].subject);
            if (strcmp(sub[iii].subject, "00") == 0)
            {
                break;
            }
            int n = i, nn = ii, nnn = iii;
            for (ii = 0; ii < nn; ii++)
            {
                fprintf(file2, "%d %s %s %d\n", bat[i].batch, sec[ii].section, sub[iii].subject, 1);
            }
            iii++;
        }
        i++;
    }
    fclose(file2);
    destributeTeachers();
    return 1;
}
int makeRoutine()
{
    struct subject s[max];
    struct teacher t[max];
    int ii = 0, i = 0;
    FILE *file1 = fopen(TeacherSubjects, "a");
    fileCheck(file1);
    printf("Enter Max Class For The Teachers : ");
    int maxClass;
    scanf("%d", &maxClass);
    while (1)
    {
        printf("\n\n");
        printf("Enter 00 For Exit Subjects\n");
        printf("Enter Subject : ");
        scanf("%s", s[i].subject);
        if (strcmp(s[i].subject, "00") == 0)
        {
            break;
        }
        printf("\n\n");
        printf("Enter 00 For Exit Subjects\n");
        while (1)
        {
            printf("\n");
            printf("Enter Teacher For The Subject : ");
            scanf("%s", t[ii].teacher);
            if (strcmp(t[ii].teacher, "00") == 0)
            {
                break;
            }
            fprintf(file1, "%s %s %d\n", s[i].subject, t[ii].teacher, maxClass);
            ii++;
        }
        i++;
    }
    fclose(file1);
    makeClasses();
    return 1;
}
void appendFile(char *filename)
{
    FILE *file = fopen(filename, "w");
    fileCheck(file);
    fclose(file);
}
int find()
{
    int i = 0;
    FILE *file = fopen(Shedule, "r");
    fileCheck(file);
    printf("Enter Batch : ");
    char batch[30];
    scanf("%s", batch);
    printf("Enter Section :");
    char section[10];
    scanf("%s", section);
    struct check
    {
        char batch[10];
        char section[10];
        char subject[10];
        char teacher[30];
        int nclass;
        char dayname[10];
        char classname[10];
        int classnum;
        char time[30];
    } b[max];
    system("cls");
    printf("Batch: %s, Section: %s\n", batch, section);
    printf(" _______________________________________________________\n");
    printf("| Subject  | Teacher  | Day      | Class | Num  | Time  |\n");
    printf("|----------|----------|----------|-------|------|-------|\n");
    i = 0;
    while (fscanf(file, "%s %s %s %s %s %s %d %s\n", b[i].batch, b[i].section, b[i].subject, b[i].teacher, b[i].dayname, b[i].classname, &b[i].classnum, b[i].time) != EOF)
    {
        if (strcmp(batch, b[i].batch) == 0 && strcmp(section, b[i].section) == 0)
        {
            printf("| %-8s | %-8s | %-8s | %-5s | %-4d | %-5s |\n",
                   b[i].subject, b[i].teacher, b[i].dayname, b[i].classname, b[i].classnum, b[i].time);
            printf(" _______________________________________________________\n");
        }

        i++;
    }
    printf(" _______________________________________________________\n");
}
int FullRoutine()
{
    int i = 0;
    FILE *file = fopen(Shedule, "r");
    if (file == NULL)
    {
        printf("Error opening Shedule file.\n");
        return 1;
    }
    struct check
    {
        char batch[10];
        char section[10];
        char subject[10];
        char teacher[30];
        int nclass;
        char dayname[10];
        char classname[10];
        int classnum;
        char time[30];
    } b[max];
    system("cls");
    printf(" _____________________________________________________________________________\n");
    printf("| Batch    | Section  | Subject  | Teacher  | Day      | Class | Num  | Time  |\n");
    printf("|----------|----------|----------|----------|----------|-------|------|-------|\n");
    i = 0;
    while (fscanf(file, "%s %s %s %s %s %s %d %s\n", b[i].batch, b[i].section, b[i].subject, b[i].teacher, b[i].dayname, b[i].classname, &b[i].classnum, b[i].time) != EOF)
    {
        printf("| %-8s | %-8s ", b[i].batch, b[i].section);
        printf("| %-8s | %-8s | %-8s | %-5s | %-4d | %-5s |\n",
               b[i].subject, b[i].teacher, b[i].dayname, b[i].classname, b[i].classnum, b[i].time);
        printf(" _____________________________________________________________________________\n");
        i++;
    }
    printf(" _____________________________________________________________________________\n");
    fclose(file);
    return 0;
}
int main()
{
    system("cls");
    while (1)
    {
        printf("1. Make Routine \n2. Find Routine\nSelect One : ");
        int option;
        scanf("%d", &option);
        system("cls");
        switch (option)
        {
        default:
        {
            printf("Ooops!!! Wrong Options...\n\nSelect Again : ");
        }
        case 0:
        {
            appendFile(TeacherSubjects);
            appendFile(BatchWiseSub);
            appendFile(SubjectDestribution);
            appendFile(SubjectDestribution2);
            appendFile(Temp);
            appendFile(PreSchedule);
            appendFile(Shedule);
            system("cls");
            printf("Files Are Appended\n");
            break;
        }
        case 1:
        {
            makeRoutine();
            break;
        }
        case 2:
        {
            find();
            break;
        }
        case 3:
        {
            FullRoutine();
            break;
        }
        }
    }
    return 0;
}
