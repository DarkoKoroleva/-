f =@ (x) (x.^3 - exp(x) + 1);

p = load("poly.txt");
node = load("nodes.txt");
for i= 1 : 6
    x = node(i, 1):0.001:node(i+1, 1);
    pol = polyval(p(i, :),x);
    plot(x, pol);       % графика полинома
    grid on;
    hold on; 
end

figure
for i= 1 : 6
    x = node(i, 1):0.001:node(i+1, 1);
    pol = polyval(p(i, :),x);
    func = f(x);
    plot(x, pol - func);      
    grid on;
    hold on; 
end

figure
error = load("ERROR.txt");
semilogy(error(:, 1), error(:, 2));
grid on;
hold on; 


