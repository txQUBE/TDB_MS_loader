#include <cstdlib>
#include <iostream>

#include <process.h>
#include <cstdio>
#include <errno.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	cout << "Loader is running" << endl;
	int tdb_ms_count = 3;

	for (int i = 1; i <= tdb_ms_count; i++) {

		char ch_i = i + '0';

		cout << "Запуск процесса N" << i << endl;

		if (spawnl(P_NOWAIT, "\home\host\TDB_MS_plug\x86\o\TDB_MS_plug",
				"\home\host\TDB_MS_plug\x86\o\TDB_MS_plug", ch_i, NULL )
				< 0) {
			perror("spawnl error on" + i);
		}
		cout << "Запуск процессов завершен" << endl;
	}

	while (true) {

	}

	return EXIT_SUCCESS;
}
