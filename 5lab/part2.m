otdeli = zeros(1, 10);
norm =  zeros(1, 10);
for i=1:10
    otdeli(i) = 10.^(-i+1);
end

poly = load('poly.txt'); %все коэф полинома
nevyazka = load('nevyazka.txt'); %все невязки
eigenvalues = load('eigenvalues.txt'); %все сч полученные
x=-10:0.0001:10;
pol = polyval(poly(i, :),x); %вычисления значения полиномa
r = roots(poly(i, :));
norm(1) = sqrt(abs(eigenvalues(i, 2)^2 - r(4, 1)^2));
for i=2:9
    pol = polyval(poly(i, :),x); %вычисления значения полиномa
    r = roots(poly(i, :));
    norm(i)= sqrt(abs(eigenvalues(i, 2)^2 - r(2, 1)^2));
end


figure
loglog(otdeli, nevyazka, 'red');
xlabel('отделимость') ;
ylabel('невязка');
hold all
grid onotdeli = zeros(1, 10);
norm =  zeros(1, 10);
for i=1:9
    otdeli(i) = 10.^(-i+1);
end

poly = load('poly.txt'); %все коэф полинома
nevyazka = load('nevyazka.txt'); %все невязки
eigenvalues = load('eigenvalues.txt'); %все сч полученные
x=-10:0.0001:10;
pol = polyval(poly(i, :),x); %вычисления значения полиномa
r = roots(poly(i, :));
norm(1) = sqrt(abs(eigenvalues(i, 2)^2 - r(4, 1)^2));
for i=1:10
    pol = polyval(poly(i, :),x); %вычисления значения полиномa
    r = roots(poly(i, :));
    norm(i)= sqrt((eigenvalues(i, 10) - r(10, 1))^2);
end


figure
loglog(otdeli, nevyazka, 'red');
xlabel('отделимость') ;
ylabel('невязка');
hold all
grid on
figure
loglog(otdeli, norm, 'blue');
xlabel('отделимость') ;
ylabel('фактическая ошибка сч');
hold all
grid on

figure
loglog(otdeli, norm, 'blue');
xlabel('отделимость') ;
ylabel('фактическая ошибка сч');
hold all
grid on
