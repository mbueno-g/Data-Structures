
#include "pilas_estatica.cpp"

int main(){
	Pila p=pila_vacia();
	elemento numero;
	int num,i=1;
	while(i<10){
		apilar(i,p);
		i++;
	}
	cout<<"La pila es: "<<endl;
	mostrar(p);
	desapilar(p);
	desapilar(p);
	desapilar(p);
	cout<<"La pila tras desapilar 3 elementos es: "<<endl;
	mostrar(p);
	num=profundidad(p);
	cout<<"La profundidad es: "<<num<<endl;
	numero= cima(p);
	cout<<"La cima es: "<<numero<<endl;
	return 0;
}
