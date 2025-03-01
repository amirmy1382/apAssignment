#include <iostream>
#include <string>

using namespace std;

struct task{
    int id;
    string name;
    string description;
    string date;
    bool HasBeenDone = false;
};

bool date_check(string date)
{

    const int DATE_STR_SIZE = 10;
    const int FIRST_SLASH_INDEX = 4;
    const int SEC_SLASH_INDEX = 7;
    const int ZERO_ASCII_CODE = 48;

    if(date.size() != DATE_STR_SIZE)
    {
        return false;
    }

    for(int i = 0 ; i < DATE_STR_SIZE; i++)
    {
        if (i == FIRST_SLASH_INDEX || i == SEC_SLASH_INDEX)
        {
            if(date[i] != '/')
            {
                return false;
            }
        }
        else
        {
            if(date[i] < ZERO_ASCII_CODE || date[i] > ZERO_ASCII_CODE+9)
            {
                return false;
            }
        }
    }

    if(date[SEC_SLASH_INDEX+1] > ZERO_ASCII_CODE+3)
    {
        return false;
    }

    if(date[SEC_SLASH_INDEX+1] == ZERO_ASCII_CODE+3 && date[SEC_SLASH_INDEX+2] > ZERO_ASCII_CODE)
    {
        return false;
    }

    if(date[FIRST_SLASH_INDEX+1] > ZERO_ASCII_CODE+1)
    {
        return false;
    }

    if(date[FIRST_SLASH_INDEX+1] == ZERO_ASCII_CODE+1 && date[FIRST_SLASH_INDEX+2] > ZERO_ASCII_CODE+2)
    {
        return false;
    }

    if(date[FIRST_SLASH_INDEX+1] == ZERO_ASCII_CODE && date[FIRST_SLASH_INDEX+2] == ZERO_ASCII_CODE){
        return false;
    }

    if(date[SEC_SLASH_INDEX+1] == ZERO_ASCII_CODE && date[SEC_SLASH_INDEX+2] == ZERO_ASCII_CODE){
        return false;
    }

    return true;
}

void add_task(task tasks[], int &num_of_tasks){
    task temp;
    cin >> temp.id;
    cin.ignore();
    getline(cin, temp.name);
    getline(cin, temp.description);
    getline(cin, temp.date);
    bool flag_id = true;
    bool flag_date = date_check(temp.date);
    for(int i = 0 ; i < num_of_tasks ; i++){
        if(temp.id == tasks[i].id){
            flag_id = false;
            break;
        }
    }
    if(flag_id){
        if(flag_date){
            tasks[num_of_tasks] = temp;
            num_of_tasks++;
            cout << "task added successfully!\n";
        }
        else{
            cout << "Date format is incorrect!\n";
        }
    }
    else{
        cout << "There is a task with similar ID!\n";
    }
}

void deleteByID(task tasks[], int& num_of_tasks){
    int id;
    cin >> id;
    int index_to_delete = -1;
    for(int i = 0; i < num_of_tasks; i++){
        if(tasks[i].id == id){
            index_to_delete = i;
        }
    }

    if(index_to_delete == -1){
        cout << "There is no task with this ID!\n";
    }
    else{
        for(int i = index_to_delete+1 ; i < num_of_tasks; i++){
            tasks[i-1] = tasks[i];
        }
        num_of_tasks--;
        cout << "Task deleted successfully!\n";
    }
}

void edit(task tasks[], int num_of_tasks){
    int id;
    int task_index = -1;
    cin >> id;
    for(int i = 0 ; i < num_of_tasks ; i++){
        if(id == tasks[i].id){
            task_index = i;
        }
    }
    if(task_index == -1){
        cout << "There is no task with this ID!\n";
    }
    else{
        int order;
        cin >> order;
        if(order == 1){
            string name;
            cin.ignore();
            getline(cin, name);
            tasks[task_index].name = name;
            cout << "task edited successfully!\n";
        }
        if(order == 2){
            string description;
            cin.ignore();
            getline(cin, description);
            tasks[task_index].description = description;
            cout << "task edited successfully!\n";
        }
        if(order == 3){
            string date;
            cin.ignore();
            getline(cin, date);
            bool flag_date = date_check(date);
            if(flag_date){
                tasks[task_index].date = date;
                cout << "task edited successfully!\n";
            }
            else{
                cout << "Date format is incorrect!\n";
            }
        }
        if(order == 4){
            int check = -1;
            cin >> check;
            if(check == 0){
                tasks[task_index].HasBeenDone = false;
                cout << "task edited successfully!\n";
            }
            else if(check == 1){
                tasks[task_index].HasBeenDone = true;
                cout << "task edited successfully!\n";
            }
            else{
                cout << "Out of range!\n";
            }
        }
    }
}

void sort_date(task tasks[], int num_of_tasks) {
    const int FIRST_SLASH_INDEX = 4;
    const int SEC_SLASH_INDEX = 7;
    int dates[num_of_tasks];
    for(int i = 0; i < num_of_tasks ; i++){
        string date = tasks[i].date;
        date.erase(date.begin() + FIRST_SLASH_INDEX);
        date.erase(date.begin() + SEC_SLASH_INDEX-1);
        dates[i] = stoi(date);
    }
    for (int i = 0; i < num_of_tasks - 1; i++) {
        for (int j = 0; j < num_of_tasks - i - 1; j++) {
            if (dates[j] > dates[j + 1]) {
                task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
                swap(dates[j], dates[j + 1]);
            }
        }
    }
}

void showAll(task tasks[], int num_of_tasks){
    task done[num_of_tasks];
    task not_done[num_of_tasks];
    int index_done = 0;
    int index_not_done = 0;
    for(int i = 0 ; i < num_of_tasks ; i++){
        if(tasks[i].HasBeenDone){
            done[index_done] = tasks[i];
            index_done++;
        }
        else{
            not_done[index_not_done] = tasks[i];
            index_not_done++;
        }
    }
    sort_date(done, index_done);
    sort_date(not_done, index_not_done);
    for(int i = 0 ; i < index_not_done ; i++){
        cout << not_done[i].id<<"     "<< not_done[i].name<<"     "<<not_done[i].description<<"     "<<not_done[i].date<<"     not Done\n";
    }
    for(int i = 0 ; i < index_done ; i++){
        cout << done[i].id<<"     "<< done[i].name<<"     "<<done[i].description<<"     "<<done[i].date<<"     Done\n";
    }
}

void show(task tasks[], int num_of_tasks){
    int id;
    bool not_found = true;
    cin >> id;
    for(int i = 0 ; i < num_of_tasks ; i++){
        if(tasks[i].id == id){
            cout << tasks[i].id<<"     "<< tasks[i].name<<"     "<<tasks[i].description<<"     "<<tasks[i].date<<"     ";
            if(tasks[i].HasBeenDone){
                cout<<"Done\n";
            }
            else{
                cout<<"not Done\n";
            }
            not_found = false;
            break;
        }
    }
    if(not_found){
        cout << "There is no task with this ID!\n";
    }
}

void MainMenu(int capacity){
    task tasks[capacity];
    int num_of_tasks = 0;
    while (true)
    {
        int order;
        cin >> order;
        if(order == 1){
            if(num_of_tasks >= capacity){
                cout << "The capacity is full!\n";
            }
            else{
                add_task(tasks, num_of_tasks);
            }
            
        }else
        if(order == 2){
            if(num_of_tasks <= 0){
                cout <<"There is no task to delete!\n";
            }
            else{
                deleteByID(tasks, num_of_tasks);
            }
        }else
        if(order == 3){
            if(num_of_tasks <= 0){
                cout <<"There is no task to edit!\n";
            }
            else{
                edit(tasks, num_of_tasks);
            }
        }else
        if(order == 4){
            if(num_of_tasks <= 0){
                cout <<"There is no task to show!\n";
            }
            else{
                showAll(tasks, num_of_tasks);
            }
        }else
        if(order == 5){
            if(num_of_tasks <= 0){
                cout <<"There is no task to show!\n";
            }
            else{
                show(tasks, num_of_tasks);            
            }
        }else
        if(order == 6){
            cout<<"To do list has been stopped!\n";
            break;
        }else{
            cout << "Out of range!";
        }
    }
    
}

int main(){
    int capacity = 0;
    cin >> capacity;
    MainMenu(capacity);
    return 0;
}