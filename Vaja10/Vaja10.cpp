#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

struct vozlisce {
	int indeks, predhodnik, cena;
};

struct Graf {
	int stevilo_vozlisc = 0;
	vector <vozlisce> vozlisca;
	int** E = new int* [stevilo_vozlisc];
};

void menu() {
	cout << "Bellman-Fordov algoritem - izbira:" << endl;
	cout << "1) Preberi graf iz datoteke" << endl;
	cout << "2) Generiraj nakljucen graf" << endl;
	cout << "3) Pozeni algoritem" << endl;
	cout << "4) Izpis najkrajse poti" << endl;
	cout << "5) Konec" << endl;
	cout << endl;
	cout << "Izbira: ";
}

void branje(Graf& G) {
	int stevilo_vozlisc;

	ifstream f("grafBig.txt");
	f >> stevilo_vozlisc;

	G.stevilo_vozlisc = stevilo_vozlisc;
	G.E = new int* [stevilo_vozlisc];
	for (int i = 0; i < stevilo_vozlisc; i++) {			
		G.E[i] = new int[stevilo_vozlisc];
	}

	int cena_povezave;
	for (int i = 0; i < stevilo_vozlisc; i++) {
		for (int j = 0; j < stevilo_vozlisc; j++) {
			f >> cena_povezave;
			if (cena_povezave == 9999)
				G.E[i][j] = NULL;
			else
				G.E[i][j] = cena_povezave;
		}
	}

	cout << endl;
}

void generate(Graf& G, int st_voz) {
	G.stevilo_vozlisc = st_voz;

	G.E = new int* [st_voz];

	for (int i = 0; i < st_voz; i++) {
		G.E[i] = new int[st_voz];
	}

	for (int i = 0; i < st_voz; i++) {
		for (int j = 0; j < st_voz; j++) {
			G.E[i][j] = rand() % st_voz + 1;
		}
	}
}

void bellman_ford(Graf &G, int S) {
	if (S > G.stevilo_vozlisc) {
		cout << "Vozlisce " << S << "ne obstaja!" << endl;
		return;
	}


	for (int i = 0; i < G.stevilo_vozlisc; i++) {		//ustvarimo vector vozlišč
		vozlisce v;
		v.indeks = i;
		G.vozlisca.push_back(v);
	}

	auto start = std::chrono::steady_clock::now();

	G.vozlisca[S].cena = 0;
	G.vozlisca[S].predhodnik = -1;


	for (int i = 0; i < G.stevilo_vozlisc; i++) {		//vsem vozliščem razen začetnemu določimo ceno poti na neskončno in predhodnika na -1
		if (G.vozlisca[i].indeks == S)
			continue;
		G.vozlisca[i].cena = INT16_MAX;
		G.vozlisca[i].predhodnik = -1;
	}


	for (int k = 0; k < G.stevilo_vozlisc - 1; k++) {		
		for (int u = 0; u < G.vozlisca.size(); u++) {
			for (int v = 0; v < G.vozlisca.size(); v++) {
				if (G.vozlisca[v].indeks == u)
					continue;

				if ((G.vozlisca[u].cena + G.E[u][v]) < G.vozlisca[v].cena) {
					G.vozlisca[v].cena = G.vozlisca[u].cena + G.E[u][v];
					G.vozlisca[v].predhodnik = G.vozlisca[u].indeks;
				}

			}
		}
	}

	for (int u = 0; u < G.vozlisca.size(); u++) {
		for (int v = 0; v < G.vozlisca.size(); v++) {
			if (G.vozlisca[v].indeks == u)
				continue;

			if (G.vozlisca[u].cena + G.E[u][v] < G.vozlisca[v].cena) {
				cout << "Napaka!" << endl;
				return;
			}

		}
	}

	auto end = std::chrono::steady_clock::now();
	cout << "Cas trajanja bellman-fordovega algoritma: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << endl;
	
}

void izpis_poti(Graf G, vozlisce s, vozlisce d) {
	if (s.indeks == d.indeks) {
		cout << "Pot je: " << d.indeks << " ";
	}
	else {
		if (d.predhodnik == -1)
			cout << "Med " << s.indeks << " in " << d.indeks << " ni poti!" << endl;
		else {
			izpis_poti(G, s, G.vozlisca[d.predhodnik]);
			cout << d.indeks << " ";
		}
	}
}

void print(Graf G) {
	for (int i = 0; i < G.stevilo_vozlisc; i++) {
		for (int j = 0; j < G.stevilo_vozlisc; j++) {
			cout << G.E[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	int selection;
	bool running = true;

	Graf G;
	int st_voz;

	int index1;
	int index2;

	do {
		menu();
		cin >> selection;
		switch (selection) {
		case 1:
			branje(G);
			print(G);
			break;
		case 2:
			cout << "Vpisi stevilo vozlisc: ";
			cin >> st_voz;
			generate(G, st_voz);
			print(G);
			break;
		case 3:
			cout << "Vpisi zacetno vozlisce: ";
			cin >> index1;
			bellman_ford(G, index1);
			cout << endl;
			break;
		case 4:
			cout << "Vnesi koncno vozlisce: ";
			cin >> index2;
			izpis_poti(G, G.vozlisca[index1], G.vozlisca[index2]);
			cout << endl;
			cout << "Cena poti: " << G.vozlisca[index2].cena << endl;
			cout << endl;
			G.vozlisca.clear();
			break;
		case 5:
			running = false;
			break;
		default:
			cout << "ERROR";
			break;
		}
	} while (running);

    return 0;
}
