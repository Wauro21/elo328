%% Read Image
X = imread('proj3.tif'); X = double(X);

% Lo de abajo es solo para imagenes no binarias
%X = X(:,:,1);
%X = imresize(X,[647 969],'nearest');
%X(X < 255) = 0;
%% Correr por secciones
cols = size(X,2); rows = size(X,1);
histo = zeros(cols,1);

Y = imdilate(X, 255*ones(4,4));
%Y = imerode(Y, 255*ones(4,4));
%Y = X;

% Calculo de Histograma para la mitad superior de la imagen
for m = 1:floor(rows/2)
    for n = 1:cols
        if Y(m,n) > 0
            histo(n) = histo(n) + 1;
        end
    end
end

[~,I] = maxk(histo,2);  %
figure, stem(histo,'.'), title('Histograma')
%% Plot Lines

% x1 y x2 son los puntos iniciales, no supe como obtener los valores
% automaticamente del histograma, asi que los ingreso manualmente :/

x1 = 377; x2 = 559; % x1 linea izquierda, x2 linea derecha

imshow(Y,gray)
hold on

getLine(Y, x1);
getLine(Y, x2);