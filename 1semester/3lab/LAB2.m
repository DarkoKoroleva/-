A = zeros(10);
condA=10;
mini = rand(1);

% writematrix(A,'M_tab.txt','Delimiter','tab');
% type 'M_tab.txt';
condReal = [0 0 0 0 0 0 0 0 0 0];
for q=1:10
    condA = condA*10;
    maxi = condA*mini;
    A(1,1) = maxi; A(2,2) = mini;

    for i=3:10
        A(i,i) = mini + (maxi-mini)*rand(1);
    end

    for i=1:10
        for j = (i+1):10
            A(i,j) = rand(1);
        end
    end

    [Q, R]=qr(rand(10));

    A =Q.'* A*Q;
    condReal(q) = cond(A);
%     writematrix(A,'M_tab.txt','WriteMode','append','Delimiter','tab');
end

figure
data = load('NORM.txt');
loglog(condReal, data(:,1), 'red');
grid on;
hold on; 
loglog(condReal, data(:,2), 'blue');
hold on;

data2 = load('NORM2.txt');

figure

X = zeros(1, 100);
A = zeros(1, 100);
for i=1:100
    X(i) = data2(i, 1) / data2(i, 2);
    k = data2(i, 3) / data2(i, 4);
    s = floor((i-1)/10) + 1;
    A(i) = condReal(s)*k / (1 - condReal(s)*k);
    loglog(A(i), X(i), 'o');
    hold on; 
end
loglog(A, A);
grid on;
hold on; 

