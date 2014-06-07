#!/usr/bin/python
import sys

def mensaje_ayuda():
    print "encoder.py: Coder/Decoder in SAT Format for the problem of Sudoku"
    print "Usage: python encoder.py [-s <sat_solver>]  -f <instance_file>"

def inicializar_diccionarios():
    num = 0
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

def main():
    D1,D2 = inicializar_diccionarios()

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
        elif (sys.argv[i] == "-a"):
            if ( i + 1 < len(sys.argv)):
                sat_solver = sys.argv[i + 1] 
        i += 1
    if (nombre_archivo == "" and sat_solver == ""):
        mensaje_ayuda()


if __name__ == "__main__":
    main()
