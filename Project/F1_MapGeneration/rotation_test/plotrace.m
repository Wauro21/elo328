clc;
clear;
close all;
pause on;
load('plotrace_data.mat','xin','zin','xou','zou')

sample = 5000; % Numero de puntos de la pista a leer

xin_ini = xin(1);       % Punto iniciales
zin_ini = zin(1);
xin_end = xin(sample);  % Puntos finales
zin_end = zin(sample);


figure(1)               % Grafico de pista estatica con puntos de partida y termino 
plot(xin_ini,zin_ini, 'b.', 'LineWidth', 2, 'MarkerSize', 25);
hold on;
plot(xin_end,zin_end, 'r.', 'LineWidth', 2, 'MarkerSize', 25);
hold on;
plot(xin,zin);
hold on;
plot(xou,zou);
view(0,90)

figure(2)           % Grafico donde realiza un ploteo de avance
plot(xin_ini,zin_ini, 'b.', 'LineWidth', 2, 'MarkerSize', 25);
hold on;
plot(xin_end,zin_end, 'r.', 'LineWidth', 2, 'MarkerSize', 25);
hold on;
plot(xin,zin);
hold on;
plot(xou,zou);
hold on;

 for i=1:15:sample      % i = inicio:paso:fin
   xt0 = xin(i);
   zt0 = zin(i);
   xt1 = xin(i+15);
   zt1 = zin(i+15);
   dx = xt0 - xt1;              % Toma de distancias
   dz = zt0 - zt1;
   hip = sqrt((dx)^2+(dz)^2);   % Calculo de hipotenusa
   if(dz > 5)                   % Ajuste de angulos segun caso (falta pulir)
       theta = asin(dx/hip);
   elseif(dz < 5)
       theta = -(pi/2 + asin(dx/hip)); % pi/2 + asin(dx/hip);
   else
       theta = theta;
   end
   
   angle = -90 + (theta*180)/pi                             % Conversion radian a angulo
   plot(xt0,zt0, 'g.', 'LineWidth', 2, 'MarkerSize', 25);   % Ploteo posicion actual
   pause(0.1)                                               % Retardo
   
   view(angle,90)                                           % Rotacion de perspectiva
 end