% out = zeros(1000000,3);
% out(:,1) = randi([0, 1000000], 1000000, 1);
% out(:,2) = randi([0, 1000000], 1000000, 1);
% 
% % sample points
% writematrix(out(:,1:2),"build\Release\data_2\1000000\triangulation_prog1_matlab_1000000.csv")
% 
% 
% % scatter points
% out(:,3) = randi([0, 1000000], 1000000, 1);
% writematrix(out(:, 3),"build\Release\data_2\1000000\triangulation_prog1_vals_matlab_1000000.csv")

% query points
query = zeros(5000, 2);
query(:,1) = randi([0, 20000], 5000, 1);
query(:,2) = randi([0, 20000], 5000, 1);

writematrix(query, "..\build\Release\data_2\20000\poster_5000.csv")