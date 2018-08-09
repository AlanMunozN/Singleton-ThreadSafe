#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#define MAX 6          ///es una manera de cambiar mas facilmente el maximo de hilos y definir una constantes , ademas es mas rapido en ejecucion
using namespace std;

class Singleton
{
public:
	static Singleton *getsingle();/// declaro un metodo estatico llamado get instance con el cual puedo instanciar

private:
	Singleton(){}///constructor
	static Singleton* single;///objeto o instancia
};

Singleton* Singleton::single = 0;///inicializo
Singleton* Singleton::getsingle()/// mandar a llamar el metodo de la clase
{
    static pthread_mutex_t mutex;/// mutex nos ayuda a las secciones criticas en este caso lo como semaforo
    pthread_mutex_lock(&mutex);///al entrar el hilo lo bloqueo para evitar la entrada de otro
	if(!single) {///pregunto si el objeto tiene algo recordemos que se puede usar como true>1 false<1
		single = new Singleton();///se crea el objeto
		cout << "First\n";
		return single;///retorno el objeto
	}
	else {
		cout << "Previous\n";
		return single;///retorno el objeto
	}
	pthread_mutex_unlock(&mutex);///desbloqueo el paso al siguiente hilo , de esta manera usamos los hilos seguramente
}
 void *getsin (void *){/// esta parte me la sugiere el compilador para enviar s1 ,para comprobarlo se puede comentar la subrutina
     ///comentar la linea 34 y 36 para comprobar lo que digo
 Singleton *s1 = Singleton::getsingle();///mandamos a getsingle
 }

int main()
{
  for (int i=0; i<MAX; ++i)///mando varios hilos con el uso de ciclos
    {
      pthread_t thread;///Crea el hilo
      int rc = pthread_create(&thread,NULL, getsin, NULL);/// puntero al hilo/tam stack/funcion/ parametros
      cout <<i+1<<"\n"<<endl;///rastrear mis hilos
    }
    pthread_exit(NULL);///terminar hilos
	return 0;
}
