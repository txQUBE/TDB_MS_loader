/*
 * Модуль автоматического запуска нескольких имитаций СУБТД
 */
#include <cstdlib>
#include <iostream>
#include <process.h>
#include <cstdio>
#include <errno.h>
#include <string>
#include <sstream>
#include <map>

using namespace std;

// Количество запускаемых имитаций (заглушек)
int tdb_ms_count = 3;
map<string, int> pids;

//Функция завершения дочерних процессов имитирующих СУБТД
void killAllTdbMs();
//функция преобразования int в string
string int_to_string(int value);


/*
 * Основная нить main
 * 		Запускает модуль-заглушку с аргументом в виде итератора для формирования имени
 * 		Имеет меню для управления
 */
int main() {
	cout << "Loader is running" << endl;

	// TDB_MS_plug/x86/o
	const char* path = "/home/host/loaders/TDB_MS_plug";

	for (int i = 1; i <= tdb_ms_count; ++i) {
		// Преобразуем число в строку
		string count_str = int_to_string(i);
		const char* count_cstr = count_str.c_str(); // Преобразуем int в string

		// Запускаем процесс, передавая порядковый номер
		int pid = spawnl(P_NOWAIT, path, path, count_cstr, NULL);

		if (pid < 0) {
			perror("Loader: spawnl error");
			cerr << "Loader: error code " << errno << endl;
			return EXIT_FAILURE;
		}

		// записываем в буфер pid запущенной СУБТД
		pids[count_str] = pid;

		cout << "Loader: TDB_MS_" << count_str << " spawned"<<endl;
	}

	while (true) {
		int input;
		cin >> input;
		switch(input){
		// Завершить дочерние процессы
		case 9:
			killAllTdbMs();
			break;
		}
	}

	return EXIT_SUCCESS;
}

void killAllTdbMs(){
	for (map<string, int>::iterator it = pids.begin(); it
					!= pids.end(); ++it) {
		cout << "Sending terminate signal to TDB N " << it->first << endl;
		kill(it->second, SIGUSR2);
		pids.erase(it->first);
	}
}

string int_to_string(int value) {
	std::ostringstream oss;
	oss << value; // Записываем число в поток
	return oss.str(); // Получаем строку из потока
}


