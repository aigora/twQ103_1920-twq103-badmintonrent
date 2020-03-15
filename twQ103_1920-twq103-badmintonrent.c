#include<iostream> 
#include<math.h>

using namespace std;

int main()
int saldo ;
{
	int a;
	cout<<"Entrega de Menu"<<endl;
	cout<<"1.-Reservar pista" <<endl;
	cout<<"2.-Ver planificacion"<<endl;
	cout<<"3.-Cambiar reserva"<<endl;
	cout<<"4.-Ver reservas de un vecino"<<endl;
	cout<<"5.-Informe pistas para vecinos"<<endl;
	cout<<"6.-Saldo cuenta pistas de padel"<<endl;
	cout<<"7.-Info"<<endl;
	cout<<"8.-Salir"<<endl;
	cin>>a;
	switch (a)
	{
			case 1: { //Te pide identificación
		cout <<"Reservar pista"<<endl;
		break;
	}
	case 2: {
		cout<<"Ver Planificacion"<<endl;
		break;
	}
	case 3: {
		cout<<"Cambiar reserva"<<endl;
		break;
	}
	case 4: {
		cout<<"Ver reservas de un vecino"<<endl;
		break;
	}
	case 5:{
		cout<<"Informe pistas para vecinos"<<endl;
		break;
	}
	case 6:{
		cout<<"Saldo cuenta pistas de padel"<<endl;
		break;
	}
	case 7:{
		cout<<"Info"<<endl;
		cout<< "Pistas de Badminton Abiertas de 9:00 - 21:00 Precio= 2€ Hora"<<endl;
		break;
	}
	case 8:{
		cout<<"Salir"<<endl;
		break;
	}


	default: cout<<"El valor ingresado no esta en el menu"<<endl;
	
	
	}
	

	

}
