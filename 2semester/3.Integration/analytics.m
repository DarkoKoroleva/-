data = load("error.txt");

loglog(data(:, 1), data(:, 2));
hold on;
grid on;
xlabel('заданная точность') ;
ylabel('фактическая точность') ;

figure
semilogx(data(:, 1), data(:, 3));       % графика полинома
grid on;
hold on;
xlabel('заданная точность') 
ylabel('число разбиений отрезка') 

f =@ (x) (x.^2);
x = 0:0.001:0.25;
func = f(data(:, 1));
figure
loglog(data(:, 1), data(:,4));
hold on;
loglog(data(:, 1), func);
grid on;
legend('фатическая ошибка','h^p, p=2')
xlabel('длина отрезка разбиения') 
ylabel('фактическая точность') 

