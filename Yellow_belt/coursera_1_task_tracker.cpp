#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;
/*
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;
*/
class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person){
    if (personTasks.count(person) == 1){
        return personTasks.at(person);
    } else
    return map<TaskStatus,int>();
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person){
    personTasks[person][TaskStatus::NEW] += 1;
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){
    vector<TaskStatus> statuses = {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE};

    TasksInfo temp;
    TasksInfo unchanged = personTasks[person];

    for (size_t i = 0; i + 1 < statuses.size(); ++i){
        if (unchanged.count(statuses[i]) == 1){
            int num_of_tasks = personTasks[person].at(statuses[i]);
            if (task_count > num_of_tasks){
                temp[statuses[i+1]] = num_of_tasks;
                task_count -= num_of_tasks;
            } else {
                temp[statuses[i+1]] = task_count;
                break;
            }
        }
    }

    for (size_t i = 1; i < statuses.size(); ++i){
        if (temp.count(statuses[i]) == 1){
            unchanged[statuses[i - 1]] -= temp[statuses[i]];
            personTasks[person][statuses[i - 1]] -= temp[statuses[i]];
            personTasks[person][statuses[i]] += temp[statuses[i]];
        }
        unchanged[TaskStatus::DONE] = 0;
    }
    return make_tuple(temp, unchanged);
  }
private:
  map<string, TasksInfo> personTasks;
};

void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << endl;
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  return 0;
}
