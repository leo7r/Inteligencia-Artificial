#!/usr/bin/python
"""Codificador y decodificador para el juego de Sudoku
   en formato CNF.
   :author: Ruben
   :version:0.1"""
import sys
import tempfile
import subprocess

def mensaje_ayuda():
    """Imprime un mensaje de ayuda."""
    print "encoder.py: Coder/Decoder in CNF Format for the problem of Sudoku"
    print "Usage: python encoder.py [-s <sat_solver>]  -f <instance_file>"

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



def regla_un_numero_casilla(linea,tmp_numero, dict_encoder):
    """Escribe la regla de que cada casilla debe tener un numero.
       :param linea: Instancia del sudoku.
       :param tmp_numero: Archivo temporal en donde se van a escribir las reglas.
       :param dict_encoder: Diccionario para codificar las reglas.
    """
    i = 0
    fila = 0
    clausulas = 0
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
    while (i < len(linea)):
        columna = i % 9
        if (columna == 0 and i != 0): fila += 1
        clausulas += escribir_regla_una_sola_casilla(fila,columna, dict_encoder, tmp_casillas, linea[i])
        i += 1
    return clausulas



def escribir_instancia_sudoku(linea, tmp,dict_encoder):
    """Escribe todas las reglas de la instancia del sudoku que se encuentra en linea.
       :param linea: Instancia del sudoku.
       :param tmp: Archivo temporal en donde se escribiran todas las reglas.
       :param dict_encoder: Diccionario de codificacion."""
    #if (not isinstance(dict_encoder,dict)): return
    #if (not isinstance(tmp,file)): return
    #if (not isinstance(linea,str)): return 
    escribir_header(tmp)
    num_var = len(dict_encoder)
    tmp_casillas = tempfile.NamedTemporaryFile() 
    tmp_numero = tempfile.NamedTemporaryFile()
    tmp.write("p cnf "+str(num_var)+ " ")
    clausulas_un_numero_casilla = regla_un_numero_casilla(linea,tmp_numero,dict_encoder)
    clausulas_casilla = regla_un_solo_numero_casilla(linea,tmp_casillas, dict_encoder) 
    clausulas = clausulas_casilla + clausulas_un_numero_casilla
    tmp.write(str(clausulas)+'\n')
    escribir_en_archivo_final(tmp_numero,tmp)
    escribir_en_archivo_final(tmp_casillas,tmp)
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

    archivo = open(nombre_archivo,"r")
    nombre = "prueba"
    for linea in archivo:
        if (len(linea)  < 80): continue
        tmp = open(nombre,"w") # NamedTemporaryFile()
        escribir_instancia_sudoku(linea, tmp,dict_encoder)
        tmp.seek(0)
        subprocess.call([sat_solver,nombre])
        tmp.close()


if __name__ == "__main__":
    main()
