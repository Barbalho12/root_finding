#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include <cmath>
#include "../model/function.cpp"
#include <vector>

using namespace std;

double tempoPrint;


void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}

void lerArgs(int argc, const char * argv[], float &x_init, float &passo){
	if(argc > 1){
		x_init = atof(argv[1]);
	}if(argc > 2){
		passo = atof(argv[2]);
	}
}

int troca_sinal(Function f, float x_init, float passo, float &baixo, float &alto){

	int qtd_passos = 0;

	float x = x_init;
	
	while(f.solve(x) * f.solve(x + passo) > 0){
		qtd_passos++;

		cout << x <<  " = " << f.solve(x) << " ------ " << passo + x << " = " << f.solve(passo+ x) << endl;
		x += passo;
	}
	cout << x <<  " = " << f.solve(x) << " ------ " << passo + x << " = " << f.solve(passo+ x) << endl;

	baixo = x;
	alto = x + passo;

	return qtd_passos;
}


int main(int argc, const char * argv[]){

	Function f;
	f.readFromUser();

	float x_init = 0; 
	float passo = 0.1; 
	float baixo;
	float alto;

	lerArgs(argc, argv, x_init, passo);


	auto t1 = std::chrono::high_resolution_clock::now();

	int qtd_passos = troca_sinal(f, x_init, passo, baixo, alto);
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	showTime(tempoTotal);



	cout << "Intervalo das raízes: [" << baixo << ";" << alto << "]" << endl; 
	cout << "Numero de passos: " << qtd_passos << endl; 



	return 0;
}