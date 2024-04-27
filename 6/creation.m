B = zeros(10);
V=zeros(1, 10);
for i=1:10
    for j=i:10
        B(i, j) = rand(1);
        B(i, i) =i+1;
        V(1,i)=B(i, i);
    end
end

[Q, r]=qr(rand(10));
A =Q.'*B*Q;
eigenvalue =  max(diag(B));

writematrix(A,'M_tab.txt','WriteMode','append','Delimiter','tab');
writematrix(eigenvalue,'M_tab.txt','WriteMode','append','Delimiter','tab');
writematrix(V(1, :),'M_tab.txt','WriteMode','append','Delimiter','tab');