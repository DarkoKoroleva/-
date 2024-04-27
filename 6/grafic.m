det_all = zeros(1, 9);
for i = 1:10
    det_all(i) = 10.^(-i+1);
end
figure
data = load('data.txt');
loglog(data(:,1), data(:,6), 'red');
xlabel('точность') ;
ylabel('ошибка');
grid on; 
hold on;
loglog(data(:,1), data(:,7), 'blue');

loglog(data(:, 1), data(:,8), 'green');
legend({'невязка','фактическая ошибка без нормировки', 'фактическая ошибка с нормировкой'},'Location','southwest')

figure
semilogx(data(:, 1), data(:,3), 'red');
xlabel('точность') ;
ylabel('итерации');
grid on;
hold on; 