

entrenamientos=(datos_P1_2_SD2014_n500.txt datos_P1_2_SD2014_n1000.txt  datos_P1_2_SD2014_n2000.txt)

pruebas=(my_data500 my_data1000 my_data2000)

entrenamientos_iris=(entrenamiento_iris50 entrenamiento_iris60 entrenamiento_iris70 entrenamiento_iris80 entrenamiento_iris90)

pruebas_iris=(bezdekIris.data)

make 

echo "" > resultados_puntos

echo "Pruebas para punto"

#for i in {2..10} #Estoy probando todos las neuronas posibles
#do
#  for prueba in ${pruebas[*]}
#  do
#    for entrenamiento in ${entrenamientos[*]}
#    do
#    echo $i
#    echo $prueba >> resultados_puntos
#    echo  $entrenamiento >> resultados_puntos
#    ./punto $entrenamiento $prueba $i >> resultados_puntos
#    done
#  done
#done

echo "Pruebas para iris"

echo "" > resultados_iris

for pregunta_i in {1..2}
do
for i in {4..10} #Estoy probando todos las neuronas posibles
do
  for prueba_i in ${pruebas_iris[*]}
  do
    for entrenamiento_i in ${entrenamientos_iris[*]}
    do
    echo $i
    echo $prueba_i
    echo  $entrenamiento_i
    echo $pregunta_i 
    ./iris -p $pregunta_i -n $i -f $entrenamiento_i -c $prueba_i 
    done
    done
  done
done
