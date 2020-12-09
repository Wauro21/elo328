% Puntos de prueba
P1 = [1 2]';
P2 = [2 1]';
P3 = [3 3]';
subplot(3,1,1)
hold on;
scatter(P1(1),P1(2));
scatter(P2(1),P2(2));
scatter(P3(1),P3(2));
xlim([-4 4])
ylim([-4 4])
hold off;
fixedPoint = P2;
Vdir = P1-P2;
title("Entrada");
% Calculo del angulo del vector direccion
if Vdir(1) < 0
    theta = pi/2 - atan(abs(Vdir)) 
else
    theta = atan(Vdir)
end

theta = -theta(1)

% Calculo matriz rotacion

R = [cos(theta) -sin(theta) ; sin(theta) cos(theta)]

PP1 = R*P1;
PP2 = R*P2;
PP3 = R*P3;

subplot(3,1,2)
hold on;
scatter(PP1(1),PP1(2));
scatter(PP2(1),PP2(2));
scatter(PP3(1),PP3(2));
xlim([-4 4])
ylim([-4 4])
hold off;
title("Rotacion");
% Centrando en el origen

vTraslacion = PP2;

PPP1 = PP1 - vTraslacion;
PPP2 = PP2 - vTraslacion;
PPP3 = PP3 - vTraslacion;

subplot(3,1,3)
hold on;
scatter(PPP1(1),PPP1(2));
scatter(PPP2(1),PPP2(2));
scatter(PPP3(1),PPP3(2));
xlim([-4 4])
ylim([-4 4])
hold off;
title("Ajuste a origen");