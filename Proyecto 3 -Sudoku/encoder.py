#!/usr/bin/python
"""Codificador y decodificador para el juego de Sudoku
   en formato CNF.
   :author: Ruben
   :version:0.6"""
import sys
import tempfile
import subprocess

class Sector:
    """Clase que indica en que sector nos encontramos"""
    sectores =[[ (0,0), (0,1), (0,2), (1,0), (1,1), (1,2), (2,0), (2,1), (2,2)],
	       [ (0,3), (0,4), (0,5), (1,3), (1,4), (1,5), (2,3), (2,4), (2,5)],
	       [ (0,6), (0,7), (0,8), (1,6), (1,7), (1,8), (2,6), (2,7), (2,8)],
	       [ (3,0), (3,1), (3,2), (4,0), (4,1), (4,2), (5,0), (5,1), (5,2)],
	       [ (3,3), (3,4), (3,5), (4,3), (4,4), (4,5), (5,3), (5,4), (5,5)],
	       [ (3,6), (3,7), (3,8), (4,6), (4,7), (4,8), (5,6), (5,7), (5,8)],
	       [ (6,0), (6,1), (6,2), (7,0), (7,1), (7,2), (8,0), (8,1), (8,2)],
	       [ (6,3), (6,4), (6,5), (7,3), (7,4), (7,5), (8,3), (8,4), (8,5)],
	       [ (6,6), (6,7), (6,8), (7,6), (7,7), (7,8), (8,6), (8,7), (8,8)]]
				
    Diccionario = {}

    def __init__(self):
	for i in range(9):
	    for tuplas in self.sectores[i]:
		self.Diccionario[tuplas] = self.sectores[i]

    def buscar_sector(self,fila,columna):
        """Dado una fila y columna rectorna el sector en donde
           se encuentra la casilla
        """
	return self.Diccionario[(fila,columna)]


def mensaje_ayuda():
	"""Imprime un mensaje de ayuda."""
	print "encoder.py: Coder/Decoder in CNF Format for the problem of Sudoku"
	print "Usage: python encoder.py [-s <sat_solver>]  -f <instance_file>"


def imprimir_matriz(linea_resultados,dict_decoder):
    valor_str = ""
    matriz = [[0 for x in range(0,9)] for x in range(0,9)]
    i = 0
    while (i < len(linea_resultados)):

        if (linea_resultados[i] == "-"):
            while (linea_resultados[i] != " "):
                i += 1

        if (linea_resultados[i].isdigit()):
            valor_str += linea_resultados[i]
        elif(linea_resultados[i].isspace() and valor_str.isdigit()):
            if (valor_str == "0"): break
            tupla = dict_decoder[int(valor_str)]
            matriz[tupla[0]][tupla[1]] = tupla[2]
            valor_str = ""
        i += 1

    print matriz

def inicializar_diccionarios():
	"""Inicializa dos diccionarios: uno para codificar la instancia en formato CNF
	y otro para decodificar el resultado dador por el solver
	:return: Dict diccionario de codificacion
	:return: Dict2 diccionario de decodificacion"""
	num = 1 #Empiezo desde 1 ya que el 0 esta reservado para /\ en formato CNF
	Dict = {}
	Dict2 = {}
	for valor in range(1,10):
			for fila in range(0,9):
				for columna in range(0,9):
					tupla_temporal = (fila,columna,valor)
					Dict[tupla_temporal] = num
					Dict2[num] = tupla_temporal
					num += 1
	return Dict,Dict2

def escribir_en_archivo_final(tmp_cerrar,archivo):
	"""Escribe el contenido de tmp_cerrar en archivo y
	   luego cierra a este.
	   :param tmp_cerrar: Archivo temporal a cerrar.
	   :param archivo: Archivo en el que se va a escribir."""
	tmp_cerrar.seek(0) #Me pongo en el principio del archivo.
	for linea in tmp_cerrar:
		archivo.write(linea)
	tmp_cerrar.close()


def escribir_header(tmp):
	"""Escribe un comentario inicial para cada archivo.
	   Esta funcion no es necesaria pero se coloca para verificar la escritura.
	   :param tmp: Archivo a escribir."""
	#if (not isinstance(num_var,int)): return
	#if (not isinstance(tmp,file)): return
	tmp.write("c\n")
	tmp.write("c Archivo en formato CNF para las reglas\n")
	tmp.write("c de una instancia determinada de Sudoku.\n")
	tmp.write("c\n")

def escribir_regla_un_numero_casilla(fila,columna, dict_encoder, tmp_numero, valor_str):
	"""Escribe la regla de que toda casilla debe tener un numero.
	   :param fila: Fila en la que se debe colocar la regla. 
	   :param columna: Columna en la que se debe colocar la regla.
	   :param dict_encoder: Diccionario con el nombre de todas las variables a usar.
	   :param tmp_numero: Archivo temporal en el que se va a escribir.
	   :param valor_str: Valor de la casilla que se debe considerar, si este es '.' se deben colocar todos los valores numericos. 
	   :return clausulas: Numero de clausulas escritas.
	"""
	posibles_valores = ['1','2','3','4','5','6','7','8','9']
	if (valor_str == "."):
		for valor_str_tmp in posibles_valores:
			valor_tmp = int(valor_str_tmp)
			casilla = (fila,columna,valor_tmp)
			tmp_numero.write( str(dict_encoder[casilla]) + " ")
		tmp_numero.write("0\n")
		return 1
	elif (valor_str in posibles_valores):
		# Representar que existe un numero en la fila y columna 'fila','columna' de valor 'valor'
		valor = int(valor_str)
		casilla = (fila,columna,valor)
		tmp_numero.write( str(dict_encoder[casilla]) + " 0\n")
		return 1
	return 0

def escribir_regla_sector(fila,columna,dict_encoder, tmp_sector, valor_str,sector):
	"""Escribe la regla de que no puede existir otro valor_str en un mismo sector.
	   :param fila: Fila en la que se debe colocar la regla. 
	   :param columna: Columna en la que se debe colocar la regla.
	   :param dict_encoder: Diccionario con el nombre de todas las variables a usar.
	   :param tmp_sector: Archivo temporal en el que se va a escribir.
	   :param valor_str: Valor de la casilla a considerar, si este es '.' se deben colocar todos los casos de columna. 
           :param sector: Clase que nos indica el sector en donde se encuetra la casilla.
	   :return clausulas: Numero de clausulas escritas.
	"""
	posibles_valores = ['1','2','3','4','5','6','7','8','9']
	if (valor_str == "."):
		clausulas = 0
		for valor_str_tmp in posibles_valores:
			clausulas += escribir_regla_sector(fila,columna,dict_encoder,tmp_sector,valor_str_tmp,sector)
		return clausulas
	elif(valor_str in posibles_valores):
		valor = int(valor_str)
		casilla = (fila,columna,valor)
		tmp_sector.write("-"+str(dict_encoder[casilla]) + " ")
                sectores_arr = sector.buscar_sector(fila,columna)
		for tupla in sectores_arr:
			casilla_tmp = (tupla[0],tupla[1],valor)
			if (casilla_tmp == casilla): continue
			tmp_sector.write("-"+str(dict_encoder[casilla_tmp])+ " ")
		tmp_sector.write("0\n")
		return 1
	return 0

def escribir_regla_columna(fila,columna,dict_encoder,tmp_col, valor_str):
	"""Escribe la regla de que no puede existir otro valor_str en la misma columna [columna].
	   :param fila: Fila en la que se debe colocar la regla. 
	   :param columna: Columna en la que se debe colocar la regla.
	   :param dict_encoder: Diccionario con el nombre de todas las variables a usar.
	   :param tmp_col: Archivo temporal en el que se va a escribir.
	   :param valor_str: Valor de la casilla a considerar, si este es '.' se deben colocar todos los casos de columna. 
	   :return clausulas: Numero de clausulas escritas.
	"""
	posibles_valores = ['1','2','3','4','5','6','7','8','9']
	if (valor_str == "."):
		clausulas = 0
		for valor_str_tmp in posibles_valores:
			clausulas += escribir_regla_columna(fila,columna,dict_encoder,tmp_col,valor_str_tmp)
		return clausulas
	elif(valor_str in posibles_valores):
		valor = int(valor_str)
		casilla = (fila,columna,valor)
		tmp_col.write("-"+str(dict_encoder[casilla]) + " ")
		for i in range(0,9):
			casilla_tmp = (i,columna,valor) #Cambio el valor de la fila
			if (casilla_tmp == casilla): continue
			tmp_col.write("-"+str(dict_encoder[casilla_tmp])+ " ")
		tmp_col.write("0\n")
		return 1
	return 0


def escribir_regla_fila(fila,columna, dict_encoder, tmp_fila, valor_str):
	"""Escribe la regla de que no puede existir otro valor_str en la misma fila [fila].
	   :param fila: Fila en la que se debe colocar la regla. 
	   :param columna: Columna en la que se debe colocar la regla.
	   :param dict_encoder: Diccionario con el nombre de todas las variables a usar.
	   :param tmp_fila: Archivo temporal en el que se va a escribir.
	   :param valor_str: Valor de la casilla a considerar, si este es '.' se deben colocar todos los casos de fila. 
	   :return clausulas: Numero de clausulas escritas.
	"""
	posibles_valores = ['1','2','3','4','5','6','7','8','9']
	if (valor_str == "."):
		clausulas = 0
		for valor_str_tmp in posibles_valores:
			clausulas += escribir_regla_fila(fila,columna,dict_encoder,tmp_fila,valor_str_tmp)
		return clausulas
	elif(valor_str in posibles_valores):
		valor = int(valor_str)
		casilla = (fila,columna,valor)
		tmp_fila.write("-"+str(dict_encoder[casilla]) + " ")
		for i in range(0,9):
			casilla_tmp = (fila,i,valor) #Cambio el valor de la columna
			if (casilla_tmp == casilla): continue
			tmp_fila.write("-"+str(dict_encoder[casilla_tmp])+ " ")
		tmp_fila.write("0\n")
		return 1
	return 0

def escribir_regla_una_sola_casilla(fila, columna, dict_encoder, tmp_casillas, valor_str):
	"""Escribe la regla de que no puede existir otro valor_str en la misma casilla [fila][columna].
	   :param fila: Fila en la que se debe colocar la regla. 
	   :param columna: Columna en la que se debe colocar la regla.
	   :param dict_encoder: Diccionario con el nombre de todas las variables a usar.
	   :param tmp_casillas: Archivo temporal en el que se va a escribir.
	   :param valor_str: Valor de la casilla que se debe considerar, si este es '.' se deben colocar todos los valores numericos. 
	   :return clausulas: Numero de clausulas escritas.
	"""
	#if (not isinstance(dict_encoder,dict)): return
	#if (not isinstance(tmp_casillas,file)): return
	#if (not isinstance(valor_str,str)): return
	#if (not isinstance(fila,int)): return
	#if (not isinstance(columna,int)): return
	posibles_valores = ['1','2','3','4','5','6','7','8','9']
	if (valor_str == "."):
		clausulas = 0
		for valor_str_tmp in posibles_valores:
			clausulas += escribir_regla_una_sola_casilla(fila,columna,dict_encoder,tmp_casillas,valor_str_tmp)
		return clausulas
	elif(valor_str in posibles_valores):
		valor = int(valor_str)
		casilla = (fila,columna,valor)
		tmp_casillas.write( str(dict_encoder[casilla]) + " ")
		for i in range(1,10):
			casilla_tmp = (fila,columna,i)
			if (casilla_tmp == casilla): continue
			tmp_casillas.write("-"+str(dict_encoder[casilla_tmp])+ " ")
		tmp_casillas.write("0\n")
		return 1
	return 0

def regla_columna(linea,tmp_col,dict_encoder):
	"""Escribe la regla de que un numero no puede repetirse en una misma fila.
	   :param linea: Instancia del sudoku.
	   :param tmp_numero: Archivo temporal en donde se van a escribir las reglas.
	   :param dict_encoder: Diccionario para codificar las reglas.
	"""
	i = 0
	fila = 0
	clausulas = 0
        tmp_col.write("c Reglas Columna\n")
	while (i < len(linea)):
		columna = i % 9
		if (columna == 0 and i != 0): fila += 1
		clausulas += escribir_regla_columna(fila,columna, dict_encoder, tmp_col, linea[i])
		i += 1
	return clausulas

def regla_fila(linea,tmp_fila,dict_encoder):
	"""Escribe la regla de que un numero no puede repetirse en una misma fila.
	   :param linea: Instancia del sudoku.
	   :param tmp_numero: Archivo temporal en donde se van a escribir las reglas.
	   :param dict_encoder: Diccionario para codificar las reglas.
	   :return clausulas: Retorna el numero de clausulas realizadas.
	"""
	i = 0
	fila = 0
	clausulas = 0
        tmp_fila.write("c Reglas Fila\n")
	while (i < len(linea)):
		columna = i % 9
		if (columna == 0 and i != 0): fila += 1
		clausulas += escribir_regla_fila(fila,columna, dict_encoder, tmp_fila, linea[i])
		i += 1
	return clausulas

def regla_un_numero_casilla(linea,tmp_numero, dict_encoder):
	"""Escribe la regla de que cada casilla debe tener un numero.
	   :param linea: Instancia del sudoku.
	   :param tmp_numero: Archivo temporal en donde se van a escribir las reglas.
	   :param dict_encoder: Diccionario para codificar las reglas.
	   :return clausulas: Retorna el numero de clausulas realizadas.
	"""
	i = 0
	fila = 0
	clausulas = 0
        tmp_numero.write("c Reglas Cada Casilla Debe Tener un Numero\n")
	while (i < len(linea)):
		columna = i % 9
		if (columna == 0 and i != 0): fila += 1
		clausulas += escribir_regla_un_numero_casilla(fila,columna, dict_encoder, tmp_numero, linea[i])
		i += 1
	return clausulas

def regla_un_solo_numero_casilla(linea, tmp_casillas, dict_encoder):
	"""Funcion que llama a escribir_regla_una_sola_casilla en cada caso
	   de la instancia del sudoku que se encuentra en linea.
	   :param linea: Instancia del sudoku.
	   :param tmp_casillas: Archivo temporal en donde se van a escribir las reglas.
	   :param dict_encoder: Diccionario para codificar las reglas.
	"""
	#if (not isinstance(dict_encoder,dict)): return
	#if (not isinstance(tmp_casillas,file)): return
	#if (not isinstance(linea,str)): return
	i = 0
	fila = 0
	clausulas = 0
        tmp_casillas.write("c Reglas Un Solo Numero Por Casilla\n")
	while (i < len(linea)):
		columna = i % 9
		if (columna == 0 and i != 0): fila += 1
		clausulas += escribir_regla_una_sola_casilla(fila,columna, dict_encoder, tmp_casillas, linea[i])
		i += 1
	return clausulas

def regla_sector(linea,tmp_sector,dict_encoder, sector):
	"""Funcion que llama a escribir_regla_una_sola_casilla en cada caso
	   de la instancia del sudoku que se encuentra en linea.
	   :param linea: Instancia del sudoku.
	   :param tmp_casillas: Archivo temporal en donde se van a escribir las reglas.
	   :param dict_encoder: Diccionario para codificar las reglas.
           :param sector: Clase sector que nos indicara en que sector nos encontramos.
           :return clausulas: Numero de clausulas escritas.
	"""
	#if (not isinstance(dict_encoder,dict)): return
	#if (not isinstance(tmp_casillas,file)): return
	#if (not isinstance(linea,str)): return
	i = 0
	fila = 0
	clausulas = 0
        tmp_sector.write("c Reglas Sector\n")
	while (i < len(linea)):
		columna = i % 9
		if (columna == 0 and i != 0): fila += 1
		clausulas += escribir_regla_sector(fila,columna, dict_encoder, tmp_sector, linea[i], sector)
		i += 1
	return clausulas

def escribir_instancia_sudoku(linea, tmp,dict_encoder, sector):
	"""Escribe todas las reglas de la instancia del sudoku que se encuentra en linea.
	   :param linea: Instancia del sudoku.
	   :param tmp: Archivo temporal en donde se escribiran todas las reglas.
	   :param dict_encoder: Diccionario de codificacion.
           :param sector: Clase que indica todos los sectores del tablero.
           :return clausulas_casilla: Retorna el numero de clausulas escritas.
        """
	#if (not isinstance(dict_encoder,dict)): return
	#if (not isinstance(tmp,file)): return
	#if (not isinstance(linea,str)): return 
	escribir_header(tmp)
	num_var = len(dict_encoder)
	tmp_casillas = tempfile.NamedTemporaryFile()
	tmp_numero	 = tempfile.NamedTemporaryFile()
	tmp_fila	 = tempfile.NamedTemporaryFile()
	tmp_col		 = tempfile.NamedTemporaryFile()
	tmp_sector	 = tempfile.NamedTemporaryFile() 
	tmp.write("p cnf "+str(num_var)+ " ")
	clausulas_un_numero_casilla           = regla_un_numero_casilla(linea,tmp_numero,dict_encoder)
	clausulas_casilla                     = regla_un_solo_numero_casilla(linea,tmp_casillas, dict_encoder)
	clausulas_fila                        = regla_fila(linea,tmp_fila,dict_encoder)
	clausulas_col                         = regla_columna(linea,tmp_col,dict_encoder)
	clausulas_sector                      = regla_sector(linea,tmp_sector,dict_encoder, sector)
	clausulas                             = clausulas_casilla + clausulas_un_numero_casilla + clausulas_fila #+ clausulas_col +clausulas_sector
	tmp.write(str(clausulas)+'\n')
	escribir_en_archivo_final(tmp_numero,tmp)
	escribir_en_archivo_final(tmp_casillas,tmp)
	escribir_en_archivo_final(tmp_fila,tmp)
	#escribir_en_archivo_final(tmp_col,tmp)
	#escribir_en_archivo_final(tmp_sector,tmp)
	return clausulas_casilla


def main():
		
	if (len(sys.argv) <= 1):
	   mensaje_ayuda() 
	   return 

	i = 0
	nombre_archivo = ""
	sat_solver = ""
	while (i < len(sys.argv)):
	    if (sys.argv[i] == "-f"):
		if ( i + 1 < len(sys.argv)):
		    nombre_archivo = sys.argv[i + 1] 
	    elif (sys.argv[i] == "-s"):
		if ( i + 1 < len(sys.argv)):
		    sat_solver = sys.argv[i + 1] 
	    i += 1

	if (nombre_archivo == "" and sat_solver == ""):
		mensaje_ayuda()
		return 

	dict_encoder,dict_decoder = inicializar_diccionarios()
        sector = Sector()

	archivo = open(nombre_archivo,"r")
	for linea in archivo:
            print linea
            resultados = ""
	    if (len(linea)	< 80): continue
	    tmp = open("prueba","w+r") #tempfile.NamedTemporaryFile()
            tmp_resultado = tempfile.NamedTemporaryFile()
	    escribir_instancia_sudoku(linea, tmp,dict_encoder, sector)
	    tmp.seek(0)
            subprocess.call([sat_solver,"-model",tmp.name], stdout=tmp_resultado)
            tmp_resultado.seek(0)
            for linea_resultados in tmp_resultado:
                if (linea_resultados[0] == "c"): continue # No me importan los comentarios
                if (linea_resultados[0] == "v"): 
                    imprimir_matriz(linea_resultados,dict_decoder)
            tmp_resultado.close()
	    tmp.close()


if __name__ == "__main__":
	main()
