// Practica 1 protipo 1
//1.03V

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstdlib>//srand semilla
#include <ctime>//hora


using namespace std;

//Se definen algunas constantes y datos basicos
#define length(x) (sizeof(x)/sizeof(x[0]));
const int T = 72; //constante resultante de 360/nº de elementos
const string NICKS_DATA = "registro.txt";
const string CENTINEL = "XXX";
//por abreviacion se la llama T en vez de usar otro id. mas largo
enum tElemento
{
	Tijeras = 0, Papel = T, Piedra = 2 * T, Lagarto = 3 * T, Spock = 4 * T
};


//Se declaran las siguientes funciones: -----------------------------------------------------------------------------------

bool startLauncher();   //secuencia principal de programa
bool isRegistred(string);
bool loadData(string, string[]);
bool registration(string);

bool showRules();
int menu();

bool startGame();   //secuencia principal de juego
int cpuSelects();
int playerSelects();
tElemento eleccionHumano();
int getWinner(tElemento, tElemento);

bool addElementToArray(string[], string);


//Se implementan las funciones: --------------------------------------------------------------------------------------------

int main()
{
	//eleccionHumano();
	while (startLauncher()); //revisar
	return 0;
}

bool startLauncher()
{


	//inicio del lanzador, el dialogo y la gestion del juego
	cout << "Introducir apodo:\n";
	string nick;
	cin >> nick;

	//comprobacion existencia del apodo
	if (isRegistred(nick))
	{

		//el apodo existe, continuar con el menu
		int select;
		system("cls");
		do
		{

			cout << "Welcom player " << nick << "\n";
			select = menu();
			switch (select)
			{
			case 1: //Iniciar juego
				startGame();
				break;
			case 2:	//Mostrar reglas
				showRules();
				break;
			}

		} while (select != 0);
		return false;
	}
	else
	{
		//posibilidad de registrar un nick nuevo
		cout << "Apodo no encontrado, desea registrarlo como nuevo?(y,n) (0 -> Salir del juego)\n";
		char op;
		cin >> op;
		if (op == '0')
		{
			return false;
		}
		if (op == 'y' || op == 'Y')
		{
			//registrar nick
			cout << "Nuevo usuario:\n" << "Apodo: " << nick << "\n";

			//registro
			if (!registration(nick))
			{
				cout << "\nError al procesar!\n";
			}
			else
			{
				cout << "\nRegistro finalizado!\n";
			}
		}
		else
		{
			cout << "Volviendo al menu\n";
			return true;
		}
	}

}

bool isRegistred(string nick)
{
	string nickData[1];

	if (loadData("registro.txt", nickData))
	{
		//archivo cargado correctamente
		for (int i = 0; i < length(nickData) i++)
		{
			//buscando nick en el array
			if (nick == nickData[i])
			{
				return true;	//nick encontrado
			}
		}
		//nick no encontrado
		return false;
	}
	else
	{
		return false;
	}
}

bool loadData(string fileName, string result[])
{
	//string s[50];
	//se borrara los datos de result[] para llenarlo con los del archivo
	string data;
	ifstream loadFich;
	loadFich.open(fileName);
	if (!loadFich.is_open())
	{
		return false;
	}
	else
	{
		do
		{
			getline(loadFich, data);
			addElementToArray(result, data);

		} while (loadFich.peek() != EOF && data != CENTINEL);
		loadFich.close();
		return true;
	}
}

bool registration(string nick)
{
	string nicksData[50];
	if (loadData(NICKS_DATA, nicksData))
	{
		ofstream archivo;
		archivo.open(NICKS_DATA);
		/*
		archivo << nick;
		archivo.close();
		*/
		string c;
		do
		{
			archivo << c << "\n";
		} while (c[0] != EOF);





		/*
		//ampliar array
		addElementToArray(nicksData, nick);
		//escribir datos nuevos en archivo
		//averiguar cuantos datos no vacios tiene el array
		int l = length(nicksData);
		int numeroNicks = 0;
		for (int i = 0; i < l; i++)
		{
			if (nicksData[i] != "")
			{
				numeroNicks++;
			}
		}

		for (int i = 0; i < numeroNicks; i++)
		{
			archivo << nicksData[i] << "\n";	//comprobar instruccion de insercion
		}
		archivo << nick;
		archivo.close();
		//archivo << "XXX";*/
		return true;
	}
	return false;
}

bool showRules() {
	bool open = false;
	string linea;
	ifstream Rules;

	Rules.open("reglas.txt");

	if (!Rules.is_open()) {
		cout << "Error de carga de archivo" << endl;
		system("PAUSE");
		system("cls");

	}
	else {
		cout << "Archivo abierto" << endl;
		do {
			getline(Rules, linea);//saca la linea y la pasa por pantalla hasta XXX, a partir de la V1.01 se eliminan los centinelas
			cout << linea;
		} while (Rules.peek() != EOF && linea != CENTINEL);//el do while es temporal ya que solo pasa la condicion en la 2ª iteracion


		open = true;
	}

	return open;
}

int menu() {

	int opcionmenu = 0;

	cout << "////////////MENU DE SELECCION/////////////" << endl;
	cout << "------------------------------------------" << endl;
	cout << "0.-Salir del juego." << endl;
	cout << "1.-Jugar una partida." << endl;
	cout << "2.-Leer las reglas." << endl;
	cout << "------------------------------------------" << endl;
	cout << "//////////////////////////////////////////" << endl << endl;

	cout << "Seleccion una opcion del 0 al 2: " << endl;

	cin >> opcionmenu;

	while (opcionmenu < 0 || opcionmenu > 2) {
		cout << "Opcion no valida, repita la opcion: " << endl;
		cin >> opcionmenu;
	}

	return opcionmenu;
}

bool startGame()
{
	int rounds = 0, selectHuman, victoriesJ1 = 0, victoriesJ2 = 0;
	system("cls");
	cout << "\nIniciando partida....\n";
	do
	{
		//jugar un juego
		cout << "Ronda: " << rounds << "\n";
		cout << "Victorias Jugador 1 (J1): " << victoriesJ1 << "        &       ";
		cout << "Victorias Jugador 2 (J2): " << victoriesJ2 << "\n";

		selectHuman = playerSelects();
		int sJ1 = selectHuman;
		system("cls");
		if (sJ1 == -1)
		{
			return false;
		}
		tElemento J1 = (tElemento)(sJ1*T),  J2 = (tElemento)(cpuSelects());


		string SJ1;
		switch (J1)
		{
		case 0: SJ1 = "Tijeras";
			break;
		case T: SJ1 = "Papel";
			break;
		case 2 * T: SJ1 = "Piedra";
			break;
		case 3 * T: SJ1 = "Lagarto";
			break;
		case 4 * T: SJ1 = "Spock";
			break;
		}
		selectHuman = J1;
		cout << "\nJugador 1 elige " << SJ1 << "\n";
		switch (getWinner(J1, J2))
		{
		case 0: //empate
			cout << "\nEmpate!\n--------\n";
			break;
		case 1:	//J1 gana
			cout << "\nJ1 GANA!\n--------\n";
			victoriesJ1++;
			break;
		case 2:
			cout << "\nJ2 GANA!\n--------\n";
			victoriesJ2++;
			break;
		}
		rounds++;
	} while (selectHuman != -1);
	return false;
}

int cpuSelects()
{
	int eleccionmaq = 0;
	int limitesup = 5;


	srand(time(NULL));
	eleccionmaq = rand() % (limitesup);
	eleccionmaq = eleccionmaq * 72;//Devolveria uno de los numeros
	string sJ2;
	switch (eleccionmaq)
	{
	case 0 * T: sJ2 = "Tijeras";
		break;
	case T: sJ2 = "Papel";
		break;
	case 2 * T: sJ2 = "Piedra";
		break;
	case 3 * T: sJ2 = "Lagarto";
		break;
	case 4 * T: sJ2 = "Spock";
		break;
	}
	cout << "\nJugador CPU elige " << sJ2 << "\n";
	return eleccionmaq;
}

int playerSelects() {
	int selection;

	cout << "Elija una de las opciones: " << endl;
	cout << "-------------" << endl;
	cout << "1.-Piedra" << endl;
	cout << "2.-Papel" << endl;
	cout << "3.-Tijera" << endl;
	cout << "4.-Lagarto" << endl;
	cout << "5.-Spock" << endl << endl;
	cout << "0.-Salir" << endl;
	cout << "-------------" << endl;
	cin >> selection;

	while (selection > 5 || selection < 0) {
		cout << "No computa dentro de las opciones, por favor, repita el input" << endl;
		cin >> selection;
	}
	return selection - 1;
}

tElemento eleccionHumano()
{
	tElemento result;
	int n = 0;
	cin >> n;
	while (n > 4 || n < 0) {
		cout << "No computa dentro de las opciones, por favor, repita el input" << endl;
		cin >> n;
	}
	for (int i = 0; i < 5; i++)
	{
		if (n == i)
		{
			result = (tElemento)(T*i);
		}
	}

	return result;
}

int getWinner(tElemento J1, tElemento J2)
{
	//Quien gana: 0: empate, 1: J1, 2: J2

	//realiza las conversiones si un elemento supera(o iguale) los 360º y los almacena en JC
	int x;
	int C1 = J1 / 72;
	int C2 = J2 / 72;

	if (C1 < 2)
	{
		x = -3;
	}
	if (C1 == 2)
	{
		x = 2;
	}
	if (C1 > 2)
	{
		x = 2;
	}
	if (C1 - x == C2 || C1 + 1 == C2)
	{
		//J1 gana
		return 1;
	}
	if (C2 == C1)
	{
		//nadie gana
		return 0;
	}
	else
	{
		//J2 gana
		return 2;
	}

	return 0;
}


//funciones auxiliares: ----------------------------------------------------------------------------------------------------

bool addElementToArray(string s[], string e)
{
	if (s[0] == CENTINEL || s[0] == "")
	{
		s[0] = e;
	}
	else
	{
		const int x = sizeof(s)/sizeof*(s);
		string newS[x + 1];
		int lNewS = sizeof(newS) / sizeof*(newS);
		for (int i = 0; i < lNewS; i++)
		{
			newS[i] = s[i];
		}
		newS[sizeof s / sizeof *s] = e;
		s = newS;
	}
	return true;
}

