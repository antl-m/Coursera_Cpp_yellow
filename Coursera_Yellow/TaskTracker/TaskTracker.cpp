/*
#include <iostream>
#include <map>

using namespace std;

// ������������ ��� ��� ������� ������
enum class TaskStatus {
	NEW,          // �����
	IN_PROGRESS,  // � ����������
	TESTING,      // �� ������������
	DONE          // ���������
};

// ��������� ���-������� ��� map<TaskStatus, int>,
// ������������ ������� ���������� ����� ������� �������
using TasksInfo = map<TaskStatus, int>;
*/

class TeamTasks {
public:
	//�������� ���������� �� �������� ����� ����������� ������������
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return base.at(person);
	};

	//�������� ����� ������ (� ������� NEW) ��� ����������� �������������
	void AddNewTask(const string& person) {
		base[person][TaskStatus::NEW]++;
	};

	//�������� ������� �� ������� ���������� ����� ����������� ������������,
	//����������� ��. ����
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const string& person, int task_count) {

		if (base.count(person) == 0) {
			return make_tuple(TasksInfo(), TasksInfo());
		}

		TasksInfo changed;
		TasksInfo old = base[person];
		while (old[TaskStatus::NEW] > 0 && task_count > 0) {
			--base[person][TaskStatus::NEW];
			--old[TaskStatus::NEW];
			--task_count;
			++base[person][TaskStatus::IN_PROGRESS];
			++changed[TaskStatus::IN_PROGRESS];
		}
		while (old[TaskStatus::IN_PROGRESS] > 0 && task_count > 0) {
			--base[person][TaskStatus::IN_PROGRESS];
			--old[TaskStatus::IN_PROGRESS];
			--task_count;
			++base[person][TaskStatus::TESTING];
			++changed[TaskStatus::TESTING];
		}
		while (old[TaskStatus::TESTING] > 0 && task_count > 0) {
			--base[person][TaskStatus::TESTING];
			--old[TaskStatus::TESTING];
			--task_count;
			++base[person][TaskStatus::DONE];
			++changed[TaskStatus::DONE];
		}

		if (old[TaskStatus::NEW] == 0) old.erase(TaskStatus::NEW);
		if (old[TaskStatus::IN_PROGRESS] == 0) old.erase(TaskStatus::IN_PROGRESS);
		if (old[TaskStatus::TESTING] == 0) old.erase(TaskStatus::TESTING);
		old.erase(TaskStatus::DONE);
		
		if (base[person][TaskStatus::NEW] == 0) base[person].erase(TaskStatus::NEW);
		if (base[person][TaskStatus::IN_PROGRESS] == 0) base[person].erase(TaskStatus::IN_PROGRESS);
		if (base[person][TaskStatus::TESTING] == 0) base[person].erase(TaskStatus::TESTING);
		if (base[person][TaskStatus::DONE] == 0) base[person].erase(TaskStatus::DONE);

		return tie(changed, old);
	};
private:
	map<string, TasksInfo> base;
};

/*
void PrintTasksInfo(const TasksInfo& tasks_info) {
    if (tasks_info.count(TaskStatus::NEW)) {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING)) {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE)) {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";

    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";

    std::cout << std::endl;
}

int main() {
    TeamTasks tasks;
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;

    // TEST 1 
    std::cout << "Alice" << std::endl;

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
        2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
    PrintTasksInfo(updated_tasks, untouched_tasks);

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    // TEST 2 
    std::cout << "\nJack" << std::endl;

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

    tasks.AddNewTask("Jack");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
    std::cout << std::endl;

    // TEST 3 
    std::cout << "\nLisa" << std::endl;

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;

    tasks.AddNewTask("Lisa");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

    return 0;
}
*/