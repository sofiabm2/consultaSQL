#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	
	// Estructura especial para almacenar resultados de consultas
	
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int fecha, duracion;
	char nombre[20];
	char consulta [80];
	
	// Creamos una conexion al servidor MYSQL
	
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	// Inicializar la conexion
	
	conn = mysql_real_connect (conn, "localhost","user", "pass", "Tablas",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	// consulta SQL para obtener una tabla los datos que queremos
	// de la base de datos
	
	err=mysql_query (conn, "SELECT Partida.Ganador, Partida.Fecha, Partida.Duracion FROM (Partida) WHERE Partida.Ganador = 'Pol'");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	resultado = mysql_store_result (conn);
	
	// El resultado es una estructura matricial en memoria
	
	// Ahora obtenemos la primera fila que se almacena en una 
	// variable de tipo MYSQL_ROW
	
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	
	else
		while(row !=NULL){
		    // Convertimos las columnas 1 y 2 las cuales contienen la palabra fecha y duracion
		    // en un entero 
		
		    fecha = atoi (row[1]);
	 	    duracion = atoi (row[2]);
		
			// la columna 1 tiene el nombre y las 2 siguientes los puntos y el numero de veces jugados.
		
		    printf ("Pedro ha ganado: %d, con fecha %d y duracion\n", row[0], fecha, duracion);
		
		    // obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
		}
	
	 // cerrar la conexion con el servidor MYSQL 
		
	mysql_close (conn);
	exit(0);
	
}
