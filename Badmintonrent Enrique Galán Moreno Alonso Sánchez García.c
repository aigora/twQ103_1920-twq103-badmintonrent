#include<iostream>
#include<stdio.h>
#include <string.h>
#include<math.h>

using namespace std;

bool alquilarPista(char horariosP[][100],bool vecinosP[][24],int pista, int vecino){
	cout<<"Introduce el tramo horario indicado por la hora de comienzo"<<endl;
	int hora;
	cin>>hora;
	while(hora<9||hora>20){
		cout<<"La pista está cerrada a esas horas, porfavor, introduzca la hora de nuevo"<<endl;
		cin>>hora;
	}
	//Ahora transformamos la hora en un entero de 0 a 12, para que nos permita inspeccionar el vector mas cómodamente
	hora = hora -9;
	//Para saber si podemos reservar o no, debemos de comprobar el caracter numero 13 (posicion 12 del vector). Si es 'D', significa que está disponible. Si es 'N' Significa que no está disponible
	if(horariosP[hora][12]=='D'){
		//Si entramos aquí, es porque la pista está disponible, por lo tanto cambiamos el texto en la matriz de horarios a NO DISPONIBLE, y reservamos la pista al usuario que lo ha pedido
		horariosP[hora][12] = 'N';horariosP[hora][13] = 'O';horariosP[hora][14] = ' ';horariosP[hora][15] = 'D';horariosP[hora][16] = 'I';horariosP[hora][17] = 'S';horariosP[hora][18] = 'P';horariosP[hora][19] = 'O';horariosP[hora][20] = 'N';horariosP[hora][21] = 'I';horariosP[hora][22] = 'B';horariosP[hora][23] = 'L';horariosP[hora][24] = 'E';
		//Reservamos la pista en el usuario:
		if(pista==1){
			vecinosP[vecino][hora]=true;
		}else{
			vecinosP[vecino][hora+12]=true;
		}
		cout<<"Pista "<<pista<<" reservada a las "<<(hora+9)<<endl;
		return true;
	}else{
		cout<<"La pista no esta disponible a esa hora"<<endl;
		return false;
	}

}

bool eliminarRes(char horariosP[][100],bool vecinosP[][24], int pista,int vec){
	cout<<"Introduce el tramo horario indicado por la hora de comienzo que quieres eliminar"<<endl;
	int hora;
	cin>>hora;
	//Como hemos hecho en la funcion de reservar, restamos 9 a la hora para obtener la posicion en el vector
	hora = hora-9;
	//Y diferenciamos entre ambas pistas
	if(pista==1){
		if(vecinosP[vec][hora]==true){
			//Si tienen reserva a esa hora, les cambiamos su reserva en ambos vectores
			vecinosP[vec][hora]=false;
			horariosP[hora][12] = 'D';horariosP[hora][13] = 'I';horariosP[hora][14] = 'S';horariosP[hora][15] = 'P';horariosP[hora][16] = 'O';horariosP[hora][17] = 'N';horariosP[hora][18] = 'I';horariosP[hora][19] = 'B';horariosP[hora][20] = 'L';horariosP[hora][21] = 'E';
			return true;
		}else{
			//Si no, lo decimos por pantalla
			cout<<"No tienes reserva a esta hora"<<endl;
			return false;
		}
	} else{
		if(vecinosP[vec][hora+12]==true){
			//Si tienen reserva a esa hora, les cambiamos su reserva en ambos vectores
			vecinosP[vec][hora+12]=false;
			horariosP[hora][12] = 'D';horariosP[hora][13] = 'I';horariosP[hora][14] = 'S';horariosP[hora][15] = 'P';horariosP[hora][16] = 'O';horariosP[hora][17] = 'N';horariosP[hora][18] = 'I';horariosP[hora][19] = 'B';horariosP[hora][20] = 'L';horariosP[hora][21] = 'E';
			return true;
		}else{
			//Si no, lo decimos por pantalla
			cout<<"No tienes reserva a esta hora"<<endl;
			return false;
		}
	}
}

int main() {
	bool salir=false;
//Vectores para las pistas
char  horariosPista1[12][100]; 
char  horariosPista2[12][100];
//Vector para los vecinos. Para ello, vamos a contar el número de filas del fichero Vecinos.txt
char ignore[1024];
FILE *vecinos = fopen("Vecinos.txt","r");
int numVecinos = 0;
while (fgets(ignore,100,vecinos)!=NULL){
	numVecinos++;
}
//Ahora cerramos el fp:
fclose(vecinos);


//Creamos la matriz de vecinos con 24 posiciones cada vecino, para poder guardar sus reservas, true=reservado, false = no reservado. 
bool pistasVecinos[numVecinos][24];

for(int i=0;i<numVecinos;i++){
	for(int j=0;j<24;j++){
		pistasVecinos[i][j]=false;
	}
}

FILE *horarios = fopen("horarios.txt", "r");
if (horarios==NULL){
	perror("El fichero no existe");
	return(0);
}

//Aqui rellenamos las dos matrices con los horarios de las pistas 1 y 2
int i=0;
while(i<13){
	if(i==0){
		fgets(ignore, 100, horarios);
		
	}else{
		fgets(horariosPista1[i-1], 100, horarios);
	}
	i++;	
}

i=0;
while(i<13){
	if(i==0){
		fgets(ignore, 100, horarios);
		
	}else{
		fgets(horariosPista2[i-1], 100, horarios);
	}
	i++;	
}

	int saldo =0;
while (!salir){
	


{

	int a;
	cout<<"1.-Reservar pista" <<endl;
	cout<<"2.-Ver planificacion"<<endl;
	cout<<"3.-Cambiar reserva"<<endl;
	cout<<"4.-Ver reservas de un vecino"<<endl;
	cout<<"5.-Saldo cuenta pistas de badminton"<<endl;
	cout<<"6.-Info"<<endl;
	cout<<"7.-Salir"<<endl;
	cin>>a;
	switch (a)
	{
			case 1: { //Te pide identificación
		cout <<"Reservar pista"<<endl;
		//Para poder reservar pista, hay que identificarse, por lo tanto un vecino que pertenezca a la comunidad tiene que ser quien la reserve
		int numVec;
		char pisoVec[2];
		bool vecinoEncontrado= false;
		//Para esto, creamos una variable boolean para ejecutar el while hasta obtener una identificacion valida
		while(!vecinoEncontrado){
			//Ademas, con la variable numVec, podremos saber que posicion ocupa ese vecino en nuestro array de reserva
			numVec=0;
			cout<<"-----------------"<<endl;
			cout<<"Introduce tu piso"<<endl;
			cout<<"-----------------"<<endl;
			cin>>pisoVec[0];
			cout<<"-----------------"<<endl;
			cout<<" Introduce tu letra (Mayus) "<<endl;
			cout<<"-----------------"<<endl;
			cin>>pisoVec[1];
			FILE *vecinos2 = fopen("Vecinos.txt","r");
			char vectorComparar[4];
			//Inspeccionamos el fichero de nuevo
			while(fgets(vectorComparar,4,vecinos2)!=NULL){
				if(vectorComparar[0]==pisoVec[0] && vectorComparar[1]==pisoVec[1]){
					//Si el vecino leido es el mismo que el introducido, cambiamos a true la variable de encontrado
					vecinoEncontrado=true;
				}
				if(!vecinoEncontrado){
					numVec++;
				}
			}
			fclose(vecinos2);
			if(!vecinoEncontrado){
				cout<<"-----------------"<<endl;
				cout<<"El vecino introducido no existe en la comunidad"<<endl;
				cout<<"-----------------"<<endl;
			}
		}
		//Una vez encontrado el vecino, procedemos a reservar pista
		if(vecinoEncontrado){
			//Pedimos el numero de pista
			cout<<"-----------------"<<endl;
			cout<<"Introduzca el numero de pista (1 o 2)"<<endl;
			cout<<"-----------------"<<endl;
			int numPista;
			cin>>numPista;
			//Aqui vamos a hacer un bucle que no parara hasta que tengamos un numero de pista válido (1 o 2)
			while(numPista!=1 && numPista!=2){
				cout<<"-----------------"<<endl;
				cout<<"Numero de pista incorrecto, introduzca uno valido"<<endl;
				cout<<"-----------------"<<endl;
				cin>>numPista;
			}
			//Ahora sabemos que tenemos el numero de pista correcto, invocamos a la funcion con el vector correspondiente como parámetro
			if(numPista==1){
				if(alquilarPista(horariosPista1,pistasVecinos,numPista,numVec)){
					saldo=saldo+2;	
				}	
			}else{
				if(alquilarPista(horariosPista2,pistasVecinos,numPista,numVec)){
					saldo=saldo+2;	
				}
			}
		}
		break;
	}
	case 2: {
		cout<<"-----------------"<<endl;
		cout<<"Ver Planificacion"<<endl;
		cout<<"-----------------"<<endl;
		//Enseñamos los horarios de la pista 1
		
		cout<<"Pista 1:"<<endl;
	
		for(int a=0;a<12;a++){
			cout<<horariosPista1[a]<<endl;
		}
		//Enseñamos los horarios de la pista 2
		
		cout<<"Pista 2:"<<endl;
		
		for(int a=0;a<12;a++){
			cout<<horariosPista2[a]<<endl;
		}
		break;
	}
	case 3: {
		cout<<"-----------------"<<endl;
		cout<<"Cambiar reserva"<<endl;
		cout<<"-----------------"<<endl;
		int numVec;
		char pisoVec[2];
		bool vecinoEncontrado= false;
		//Para esto, creamos una variable boolean para ejecutar el while hasta obtener una identificacion valida
		while(!vecinoEncontrado){
			//Ademas, con la variable numVec, podremos saber que posicion ocupa ese vecino en nuestro array de reserva
			numVec=0;
			cout<<"-----------------"<<endl;
			cout<<"Introduce tu piso"<<endl;
			cin>>pisoVec[0];
			cout<<"Introduce tu letra (Mayus)"<<endl;
			cout<<"-----------------"<<endl;
			cin>>pisoVec[1];
			FILE *vecinos2 = fopen("Vecinos.txt","r");
			char vectorComparar[4];
			//Inspeccionamos el fichero de nuevo
			while(fgets(vectorComparar,4,vecinos2)!=NULL){
				if(vectorComparar[0]==pisoVec[0] && vectorComparar[1]==pisoVec[1]){
					//Si el vecino leido es el mismo que el introducido, cambiamos a true la variable de encontrado
					vecinoEncontrado=true;
				}
				if(!vecinoEncontrado){
					numVec++;
				}
			}
			fclose(vecinos2);
			if(!vecinoEncontrado){
				cout<<"-----------------"<<endl;
				cout<<"El vecino introducido no existe en la comunidad"<<endl;
				cout<<"-----------------"<<endl;
			}
		}
		//Una vez encontrado el vecino, procedemos a reservar pista
		if(vecinoEncontrado){
			//Pedimos el numero de pista
			cout<<"-----------------"<<endl;
			cout<<"Introduzca la reserva que quieras quitar (1 o 2)"<<endl;
			cout<<"-----------------"<<endl;
			int numPista;
			cin>>numPista;
			//Aqui vamos a hacer un bucle que no parara hasta que tengamos un numero de pista válido (1 o 2)
			while(numPista!=1 && numPista!=2){
				cout<<"-----------------"<<endl;
				cout<<"Numero de pista incorrecto, introduzca uno valido"<<endl;
				cout<<"-----------------"<<endl;
				cin>>numPista;
			}
			//Ahora sabemos que tenemos el numero de pista correcto, invocamos a la funcion con el vector correspondiente como parámetro
			if(numPista==1){
				if(eliminarRes(horariosPista1,pistasVecinos,numPista,numVec)){
					saldo=saldo-2;	
				}
			}else{
				if(eliminarRes(horariosPista1,pistasVecinos,numPista,numVec)){
					saldo=saldo-2;	
				}
			}
			//Ahora, simplemente pedimos el nuevo numero de reserva:
			cout<<"-----------------"<<endl;
			cout<<"Introduce el nuevo numero de pista para la reserva"<<endl;
			cout<<"-----------------"<<endl;
			cin>>numPista;
			//Aqui vamos a hacer un bucle que no parara hasta que tengamos un numero de pista válido (1 o 2)
			while(numPista!=1 && numPista!=2){
				cout<<"-----------------"<<endl;
				cout<<"Numero de pista incorrecto, introduzca uno valido"<<endl;
				cout<<"-----------------"<<endl;
				cin>>numPista;
			}
			//Ahora sabemos que tenemos el numero de pista correcto,reservamos pista de nuevo
			if(numPista==1){
				if(alquilarPista(horariosPista1,pistasVecinos,numPista,numVec)){
					saldo=saldo+2;	
				}
			}else{
				if(alquilarPista(horariosPista2,pistasVecinos,numPista,numVec)){
					saldo=saldo+2;	
				}
			}
		};
		break;
	}
	case 4: {
		cout<<"-----------------"<<endl;
		cout<<"Ver reservas de un vecino"<<endl;
		cout<<"-----------------"<<endl;
		//Aqui simplemente hacemos un bucle y printeamos todas las reservas de los vecinos
		int i;
		FILE *vecinos3 = fopen("Vecinos.txt","r");
		char v[4];
		for(i = 0;i<numVecinos;i++){
			fgets(v,4,vecinos3);
			int j;
			cout<<"Vecino "<<v[0]<<v[1]<<": Pista 1: ";
			for(j = 0;j<24;j++){
				if(j==12){
					cout<<"Pista 2: ";
				}
				if(pistasVecinos[i][j]==true){
					if(j<12){
						cout<<	(j+9)<<":00 ";	
					}else{
						cout<<	(j+9-12)<<":00 ";
					}
					
				}
			}
			cout<<endl;
		}
		fclose(vecinos3);
		break;
	}
	case 5:{
		cout<<"-----------------"<<endl;
		cout<<"Saldo cuenta pistas de padel"<<endl;
		cout<<"-----------------"<<endl;
		cout<<saldo<<" EUROS"<<endl;
		break;
	}
	case 6:{
		cout<<"Info"<<endl;
		cout<<"--------------------"<<endl;
		cout<< "Pistas de Badmiton Abiertas de 9:00 - 21:00 Precio= 2€ Hora"<<endl;
		cout<< "Debido a la pandemia del Covid-19, se deberan adoptar las medidas estipuladas por las autoridades sanitarias"<<endl;
		cout<< "El uso de mascarilla y guantes es obligatorio en los alrededores de las instalaciones, respetando una distancia de seguridad entre vecinos"<<endl;
		cout<<"--------------------"<<endl;
		break;
	}
	case 7:{
		cout<<"Salir"<<endl;
		salir=true;
		break;
	}


	default: cout<<"El valor ingresado no esta en el menu"<<endl;
	
	
	}
	

	
	
} 
}
return 0 ;						
}


