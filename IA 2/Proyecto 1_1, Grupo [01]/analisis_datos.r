cat("Pregunta 1.a. Grafica E como función del numero de iteraciones de entrenamiento para cada una de las funciones")

error_and1 <- c(2,0);

error_or1 <- c(4,4,2,0);

error_xor1 <-c(6,4,6,6,6,8,8,8,8,8)

# Grafica del and
plot(c(1:2),error_and1,type="l", main="Gráfica de Error para AND", ylab ="Error", xlab = "Iteraciones")

#Grafica del OR
plot(c(1:4),error_or1,type="l", main="Gráfica de Error para OR", ylab ="Error", xlab = "Iteraciones")

#Grafica del XOR
plot(c(1:10),error_xor1, type="l", main="Gráfica de Error para XOR", ylab ="Error", xlab = "Iteraciones")

error_and2 <- c(6,2,0)

error_or2 <- c(2,0)

error_xor2 <- c(4,4,4,4,4,4,4,4,4,4)


# Grafica del and
plot(c(1:3),error_and2,type="l", main="Gráfica de Error para AND Delta", ylab ="Error", xlab = "Iteraciones")

#Grafica del OR
plot(c(1:2),error_or2,type="l", main="Gráfica de Error para OR Delta", ylab ="Error", xlab = "Iteraciones")

#Grafica del XOR
plot(c(1:10),error_xor2, type="l", main="Gráfica de Error para XOR Delta", ylab ="Error", xlab = "Iteraciones")

