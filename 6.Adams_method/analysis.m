figure
nodes10 = load("nodes10.txt");
nodes20 = load("nodes20.txt");

plot(nodes10(:, 1), nodes10(:,2), 'o', nodes10(:, 1), nodes10(:,3), nodes20(:, 1), nodes20(:,2), '*');
hold on;
grid on;
legend('вычисленное решение 10 узлов','точное решение', 'вычисленное решение 20 узлов')

figure
plot(nodes10(:, 1), nodes10(:,4), nodes20(:, 1), nodes20(:,4))
hold on;
grid on;
legend('фактическая ошибка при 10 узлах','фактическая ошибка при 20 узлах')
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
