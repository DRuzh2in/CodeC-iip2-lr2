#include <time.h>
#include <stdio.h>
#include <cstring>

struct users
{
    bool isEmpty;
    int id;
    char surname [15];
    char name [15];
    char middle_name [15];
    char date [20];
    int durat;
};

int duration(int timeColl) // вместо ввода длительности разговора, ввожу длительность заполнения формы
{
    if (timeColl == 0)
        timeColl = time(0);
    else
        timeColl = time(0) - timeColl;
    return timeColl;
}


void init (users *DB, int n) //  инициализация пустыми значниями
{
    for (int i = 0; i < n; i++)
    {
        DB[i] = { true, 0, "empty", "empty", "empty", "empty", 0 };
    }
}

void dialogUser(int key)
{
    switch (key) {
        case 1: {
            printf (" --------------------------------------------------------------------------------------\n");
            break;
        }
        case 2: {
            printf("\n********* Note not found *********\n");
            break;
        }
        case 3: {
            printf (" --------------------------------------------------------------------------------------\n");
            printf ("|%3s| %15s| %15s| %15s| %8s| %20s|\n", "id", "Surname", "Name", "Middle name", "Duration", "Date");
            printf ("|---+----------------+----------------+----------------+---------+---------------------|\n");
            break;
        }
        case 4: {
            printf("\n\n********** Add function **********\n\n");
            break;
        }
        case 5: {
            printf("\n*********** Note added ***********\n");
            break;
        }
        case 6: {
            printf("\n\n********** Show function *********\n\n");
            break;
        }
        case 7: {
            printf("\n\n********* Remove function ********\n\n");
            break;
        }
        case 8: {
            printf("\n\n********** Note deleted **********\n\n");
            break;
        }
        case 9: {
            printf("\n\n********** Edit function *********\n\n");
            break;
        }
        case 10: {
            printf("\n\n********** Note changed **********\n\n");
            break;
        }
        case 11: {
            printf("\n\n********** Sort function *********\n\n");
            break;
        }
        case 12: {
            printf("\n******** Sorting complete ********\n");
            break;
        }
        case 13: {
            printf("\n\n********* Searh function *********\n\n");
            break;
        }
        case 14: {
            printf("\n\n************ GAME OVER ************\n\n");
            break;
        }
        default:
            break;
    }
}

void notificationFun(int key, int result)
{
    switch (key) {
        case 1: {
            printf("\nADD Note ID: %d\n", result);
            break;
        }
        case 2: {
            printf("\nTotal Note: %d\n",result);
            break;
        }
        case 3: {
            printf("\nRemove Note ID: %d\n",result);
            break;
        }
    }
}

users getusers() // заполнение структуры
{
    int timeColl = 0; // длительность звока заполняю длительностью заполнения формы ниже
    timeColl = duration(timeColl);

    users temp;
    temp.isEmpty = false;

    printf("Enter ");
    gets(temp.surname);
    fflush(stdin);

    printf("Surname:\n\r");
    gets(temp.surname);
    fflush(stdin);

    printf("Enter Name:\n\r");
    gets(temp.name);
    fflush(stdin);

    printf("Enter Middle Name:\n\r");
    gets(temp.middle_name);
    fflush(stdin);

    temp.durat = duration(timeColl);

    time_t seconds = time(NULL);
    tm  *timeinfo = localtime(&seconds);
    char format[] = "%Y.%m.%d %I:%M:%S";
    strftime(temp.date, 20, format, timeinfo); // дата звонка - дата заполнения формы

    return temp;
}

int add(users *DB, int n, users p) // добавление записи в пустую строку
{
    int key = -1;
    for (int i=0; i<n;i++)
    {
        if(DB[i].isEmpty)
        {
            DB[i]=p;
            key = i;
            DB[i].id = key;
            break;
        }
    }
    return key;
}

int edit(users *DB, int i, users p) // редактирование записи
{
    int key = -1;
    //DB[i]=p;
    key = i;
    DB[i].id = key;
    return key;
}

int remove (users *DB, int max_size, int index) // удаление записи
{
    for (int i=0; i < max_size; i++)
    {
        if (DB[i].id == index)
        {
            DB[i].isEmpty = true;
        }
    }
    return index;
}

void printNote (users *DB, int j) // вывод на экран записей
{
    printf("|%3d| %15s| %15s| %15s| %8d| %20s|\n",
           DB[j].id,
           DB[j].surname,
           DB[j].name,
           DB[j].middle_name,
           DB[j].durat,
           DB[j].date);
}
void show (users *DB, int max_size) // вывод на экран всех записей
{
    dialogUser(3);
    for (int i = 0; i<max_size; i++)
    {
        if(!DB[i].isEmpty)
        {
            printNote(DB, i);
        }
    }
}

int dialogValInt()
{
    int Srh;
    printf ("\nEnter value: ");
    scanf("%d",&Srh);
    return Srh;
}

void SearchInt (users *DB, int max_size, int Srh, int srhKey) // вывод на экран найденных записей int
{
    dialogUser(3);
    int i=0;
    for (int j = 0; j<max_size; j++)
    {
        if(!DB[j].isEmpty) {
            switch (srhKey) {
                case 1:
                {
                    if (DB[j].id == Srh)
                    {
                        printNote(DB, j);
                        i++;
                    }
                    break;
                }
                case 2:
                {
                    if (DB[j].durat == Srh) {
                        printNote(DB, j);
                        i++;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    dialogUser(1);
    if(i == 0)
        dialogUser(2);
    else
        printf("Total: %d\n",i);
}

void SearchChar (users *DB, int max_size, int srhKey) // вывод на экран найденных записей char
{
    char serhfild[15];
    printf("\nEnter value: ");
    scanf("%s",serhfild);

    dialogUser(3);

    int i=0;
    for (int j = 0; j<max_size; j++)
    {
        if(!DB[j].isEmpty) {
            switch (srhKey) {
                case 3: {
                    if (strcmp(DB[j].surname, serhfild) == 0) {
                        printNote(DB, j);
                        i++;
                    }
                    break;
                }
                case 4: {
                    if (strcmp(DB[j].name, serhfild) == 0) {
                        printNote(DB, j);
                        i++;
                    }
                    break;
                }
                case 5: {
                    if (strcmp(DB[j].middle_name, serhfild) == 0) {
                        printNote(DB, j);
                        i++;
                    }
                    break;
                }
                case 6: {
                    if (strcmp(DB[j].date, serhfild) == 0) {
                        printNote(DB, j);
                        i++;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    dialogUser(1);
    if(i == 0)
        dialogUser(2);
    else
        printf("Total: %d\n",i);
}

void threeRul (users *DB, int i, int j) // три стакана
{
    users sortx[20];
    sortx[i] = DB[j];
    DB[j] = DB[j+1];
    DB[j+1] = sortx[i];
}

bool mo (int a, int b) // сортировка по возрастанию интов
{
    return a>b;
}
bool mc (int a, int b) // сортировка по убыванию интов
{
    return a<b;
}
bool mo2 (char *a, char *b) // сортировка по возрастанию строк
{
    return strcmp(a, b)>0;
}
bool mc2 (char *a, char *b) // сортировка по убыванию строк
{
    return strcmp(a, b)<0;
}

void sort(users *DB, int n, bool(*comp)(char *a, char *b), int key) // сортировка строк
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            switch (key)
            {
                case 3:
                {
                    if (comp(DB[j].surname, DB[j + 1].surname))
                        threeRul(DB, i, j);
                    break;
                }
                case 4:
                {
                    if (comp(DB[j].name, DB[j + 1].name))
                        threeRul(DB, i, j);
                    break;
                }
                case 5:
                {
                    if (comp(DB[j].middle_name, DB[j + 1].middle_name))
                        threeRul(DB, i, j);
                    break;
                }
                case 6:
                {
                    if (comp(DB[j].date, DB[j + 1].date))
                        threeRul(DB, i, j);
                    break;
                }
                default: break;
            }
        }
    }
}

void sort2(users *DB, int n, bool(*comp2)(int a, int b), int key) // сортировка интов
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++)
        {
            switch (key)
            {
                case 1:
                {
                    if (comp2(DB[j].id, DB[j + 1].id))
                        threeRul(DB, i, j);
                    break;
                }
                case 2:
                {
                    if (comp2(DB[j].durat, DB[j + 1].durat))
                        threeRul(DB, i, j);
                    break;
                }
                default: break;
            }
        }
    }
}

int printMenu() // вывод на экран меню программы
{
    int key;
    printf ("\n\n************** Menu **************\n");
    printf("%10s %s\n", "Add:","1");
    printf("%10s %s\n", "Show:", "2");
    printf("%10s %s\n", "Remove:", "3");
    printf("%10s %s\n", "Edit:", "4");
    printf("%10s %s\n", "Sort:", "5");
    printf("%10s %s\n", "Search:", "6");
    printf ("%10s %s\n", "Exit:", "7");
    printf ("**********************************\n");
    printf ("Press key: ");
    scanf("%d",&key);
    return key;
}

void printNoteMenu() // вывод на экран полей
{
    printf("%12s %s\n", "id:","1");
    printf("%12s %s\n", "Duration:", "2");
    printf("%12s %s\n", "Surname:", "3");
    printf("%12s %s\n", "Name:", "4");
    printf("%12s %s\n", "Middle name:", "5");
    printf("%12s %s\n", "Date:", "6");
}

int printSortMenu() // вывод на экран меню сортировки
{
    int sortKey;
    printf ("\n\n************* Sort by ************\n");
    printNoteMenu();
    printf ("**********************************\n");
    printf ("Press key: ");
    scanf("%d",&sortKey);
    return sortKey;
}

int printAz() // вывод на экран порядка сортировки
{
    printf ("\n\n************* Form by ************\n");
    int aZkey;
    printf("%12s %s\n", "Sort A->Z:", "1");
    printf("%12s %s\n", "Sort Z->A:", "2");
    printf ("**********************************\n");
    printf ("Press key: ");
    scanf("%d",&aZkey);
    return aZkey;
}

int printSearhMenu() // вывод на экран меню сортировки
{
    int sortKey;
    printf ("\n\n************ Search by ***********\n");
    printNoteMenu();
    printf ("**********************************\n");
    printf ("Press key: ");
    scanf("%d",&sortKey);
    return sortKey;
}

int dialogNo()
{
    int no;
    printf("Enter note number: ");
    scanf("%d", &no);
    return no;
}

void selectFunction(users *db, int max_size,int key) // вызов функции из меню программы
{
    switch (key) {
        case 1:
        {
            dialogUser(4);
            users t = getusers();
            int result = add(db, max_size, t);
            notificationFun(1, result);
            dialogUser(5);
            key = printMenu();
            selectFunction(db, max_size, key);

            break;
        }
        case 2:
        {
            dialogUser(6);
            show(db, max_size);
            dialogUser(1);
            key = printMenu();
            selectFunction(db, max_size, key);
            break;
        }
        case 3:
        {
            dialogUser(7);
            int no = dialogNo();
            int result = remove(db, max_size, no);
            notificationFun(3, result);
            dialogUser(8);
            key = printMenu();
            selectFunction(db, max_size, key);
            break;
        }
        case 4:
        {
            dialogUser(9);
            int no = dialogNo();
            users t = getusers();
            edit(db, no, t);
            dialogUser(10);
            key = printMenu();
            selectFunction(db, max_size, key);
            break;
        }
        case 5:
        {
            dialogUser(11);
            int sortKey = printSortMenu();
            int aZkey = printAz();
            if (sortKey > 2 && aZkey == 1) // уф
                sort(db, max_size, mo2, sortKey);
            else if (sortKey > 2 && aZkey == 2)
                sort(db, max_size, mc2, sortKey);
            else if (sortKey <= 2 && aZkey == 1)
                sort2(db, max_size, mo, sortKey);
            else if (sortKey <= 2 && aZkey == 2)
                sort2(db, max_size, mc, sortKey);
            dialogUser(12);
            key = printMenu();
            selectFunction(db, max_size, key);
            break;
        }
        case 6:
        {
            dialogUser(13);
            int srhKey = printSearhMenu();
            if (srhKey <= 2){
                int Srh = dialogValInt();
                SearchInt (db, max_size, Srh, srhKey);
            }
            else
            {
                SearchChar (db, max_size, srhKey);
            }


            key = printMenu();
            selectFunction(db, max_size, key);
            break;
        }
        case 7:
        {
            dialogUser(14);
            break;
        }
        default: break;
    }
}

int main()
{
    const int max_size = 20;
    users db [max_size];
    init (db, max_size);
    int key = printMenu();
    selectFunction(db, max_size, key);
}

