function getLine(Y, x1)
    
    % Ancho y largo de los rectangulos
    w = 150; h = 100;
    
    w0 = x1 + w/2;
    
    data = [];  % arreglo para guardar los puntos
    
    n_win = floor(size(Y,1)/h);    % numero de ventanas
    
    for k = 1:n_win
        rectangle('Position',[x1-w/2 (k-1)*h w h],'EdgeColor','r')  % esto solo dibuja el rectangulo en la imagen
        
        % Recorre la ventana
        for m = 1+(k-1)*h:k*h    % filas
            for n = x1-w/2:x1+w/2    % columnas
                if Y(m,n) > 0
                    data = [data; m n]; % concatena los puntos (y,x)
                end
            end
        end
        
        if k == 1
            curr_prev = 1;
        else
            curr_prev = curr;
        end
        
        % Se obtiene el promedio de los 'x' en la ventana, el valor
        % se utiliza para mover el centro de la ventana nuevamente
        % (Probablemente se puede mejorar este criterio)
        
        curr = size(data,1);
        x1 = floor(mean(data(curr_prev:curr,2)));

    end
    
    % Polyfit es (x,y), aqui di vuelta los datos por la idea que dijo
    % el Diego de rotar la imagen en 90°
    p = polyfit(data(:,1),data(:,2),2);
    
    x = 1:size(Y,1);    
    q = polyval(p,x);
    plot(q, x,'LineWidth',2)
    set(gca, 'YDir','reverse')  % Da vuelta el eje Y
end