poly = load('POLY.txt'); 
node = load('NODE.txt'); 
error_nodes = load('ERROR.txt');


figure 
plot(poly(:, 1), poly(:, 2));
hold all
grid on
plot(node(:, 1), node(:, 2), 'o');
%x1 = -5:0.01:5;
%y1 = x1.^3-exp(x1)+1;
%plot(x1', y1')

error = zeros(1, 405);

for i=1:405
    x = poly(i, 1);
    y = x.^3 - exp(x) + 1;
    error(1, i)= poly(i, 2) - y; 
end

figure 
plot(poly(:, 1), error);
hold all
grid on

figure 
semilogy(error_nodes(:, 1), error_nodes(:, 2));

hold all
grid on