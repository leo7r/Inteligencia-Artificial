

entrenamientos=(datos_P1_2_SD2014_n500.txt datos_P1_2_SD2014_n1000.txt  datos_P1_2_SD2014_n2000.txt)

pruebas=(instancia_correcta500 instancia_correcta1000 instancia_correcta2000)

entrenamientos_iris=(entrenamiento_iris50 entrenamiento_iris60 entrenamiento_iris70 entrenamiento_iris80 entrenamiento_iris90)

pruebas_iris=(bezdekIris.data)

make 

echo "" > resultados_puntos

echo "Pruebas para punto"

for i in {2..10} #Estoy probando todos las neuronas posibles
do
  for prueba in ${pruebas[*]}
  do
    for entrenamiento in ${entrenamientos[*]}
    do
    echo $i
    echo $prueba
    echo  $entrenamiento
    ./punto $entrenamiento $pruebas $i >> resultados_puntos
    done
  done
done

echo "Pruebas para iris"

echo "" > resultados_iris


for i in {4..10} #Estoy probando todos las neuronas posibles
do
  for prueba in ${pruebas_iris[*]}
  do
    for entrenamiento in ${entrenamientos_iris[*]}
    do
    echo $i
    echo $prueba
    echo  $entrenamiento
    for pregunta in {1..2}
    do
      echo $pregunta
      ./iris -p $pregunta -n $i -f $entrenamiento -c $pruebas >> resultados_iris
    done
    done
  done
done
