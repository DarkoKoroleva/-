figure
solution5 = load("solution5.txt");
solution10 = load("solution10.txt");

plot(solution5(:, 1), solution5(:,2), 'o', solution5(:, 1), solution5(:,3), solution10(:, 1), solution10(:,2), '*');
hold on;
grid on;
legend('вычисленное решение 5 узлов','точное решение', 'вычисленное решение 10 узлов')

figure
plot(solution5(:, 1), solution5(:,4), solution10(:, 1), solution10(:,4))
hold on;
grid on;
legend('фактическая ошибка при 5 узлах','фактическая ошибка при 10 узлах')
ylabel('фактическая ошибка') 

figure
data = load("ERROR.txt");

f =@ (x) (x.^4);
func = f(data(:, 1));
loglog(data(:, 1), data(:,2), data(:, 1), func);
hold on;
grid on;
legend('фатическая ошибка','h^p, p=4')
xlabel('длина отрезка разбиения') 
ylabel('фактическая ошибка') 


figure
accuracy = load("accuracy.txt");
loglog(accuracy(:, 1), accuracy(:,2), accuracy(:, 1), accuracy(:, 1))
hold on;
grid on;
xlabel('заданная точность') 
ylabel('фактическая ошибка') 

figure
iter = load("iter.txt");
semilogx(iter(:, 1), iter(:,2))
hold on;
grid on;
xlabel('заданная точность') 
ylabel('число итераций') 


