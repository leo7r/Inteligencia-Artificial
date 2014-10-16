minimax <- c(9e-06 ,2e-05 ,3.3e-05 ,3.4e-05 ,7.9e-05 ,8.4e-05 ,0.000396 ,0.000737 ,0.004437 ,0.017601 ,0.036707 ,0.165346 ,0.863469 ,7.01575 ,26.226 ,179.944)

negamax <- c(8e-06 ,1.8e-05 ,2.7e-05 ,2.8e-05 ,6.6e-05 ,6.6e-05 ,0.000532 ,0.000884 ,0.004988 ,0.019868 ,0.03948 ,0.165635 ,0.869375 ,7.02546 ,26.6488 ,180.838)

alphabeta <- c(8e-06 ,2.3e-05 ,4e-05 ,4.2e-05 ,9.7e-05 ,0.000105 ,0.000183 ,0.000457 ,0.001319 ,0.005112 ,0.007316 ,0.019392 ,0.03512 ,0.242454 ,0.30035 ,0.627391 ,2.98754 ,4.82922 ,67.3806 ,101.286 ,250.428)

negamaxp <- c(8e-06 ,1.9e-05 ,3.6e-05 ,2.5e-05 ,5.9e-05 ,6.1e-05 ,0.000151 ,0.000455 ,0.001442 ,0.004961 ,0.007183 ,0.018486 ,0.034785 ,0.240063 ,0.306279 ,0.635811 ,3.01995 ,4.92678 ,68.4892 ,102.293 ,254.145)

scout <- c(4e-06 ,1.4e-05 ,2.4e-05 ,2.1e-05 ,7.6e-05 ,7.6e-05 ,0.000138 ,0.000342 ,0.001777 ,0.007162 ,0.00965 ,0.014719 ,0.041124 ,0.132178 ,0.212773 ,0.492021 ,1.56218 ,2.92981 ,19.2388 ,73.9064 ,179.605)

negascout <- c(5e-06 ,1.4e-05 ,3.9e-05 ,3.4e-05 ,8.2e-05 ,7.7e-05 ,0.000139 ,0.000344 ,0.001408 ,0.006256 ,0.008784 ,0.013813 ,0.038254 ,0.120481 ,0.194183 ,0.443091 ,1.48761 ,2.78245 ,17.3766 ,62.3421 ,149.038 ,563.158)

length(minimax);
summary(minimax);

length(negamax);
summary(negamax);

length(negamaxp);
summary(negamaxp);

length(alphabeta);
summary(alphabeta);

length(scout);
summary(scout);

length(negascout);
summary(negascout);