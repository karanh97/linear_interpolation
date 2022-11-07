% % reading files
% cgal_result = readmatrix("..\build\Release\data_graph\interpolation_60000_5000_scatter.csv");
% mtlb_result = readmatrix("..\build\Release\data_graph\interpolation_60000_5000_scatter_matlab.csv");
% query_points = readmatrix("..\build\Release\data_graph\triangulation_prog1_func_matlab_5000.csv");
% 
% % computing function values
% % linear function
% % func_result = (0.2 .* query_points(:, 1)) + (0.03 .* query_points(:, 2));
% 
% % quadratic function
% % func_result = ((0.001 .* query_points(:, 1) .* query_points(:, 1)) + (0.002 .* query_points(:, 2) .* query_points(:, 2)) + (0.003 .* query_points(:, 1) .* query_points(:, 2)));
% % processing the data
% zeros_matrix = zeros(5000, 1);
% 
% % extracting elements with NaN values
% for i = 1 : length(mtlb_result)
%     if isnan(mtlb_result(i))
%         zeros_matrix(i) = i;
%     end
% end
% zeros_matrix = nonzeros(zeros_matrix);
% 
% mtlb_result(isnan(mtlb_result)) = 0;
% 
% % eliminating corresponding function values
% % for i = zeros_matrix
% %     func_result(i) = 0;
% % end
% 
% % error matrices for CGAL and Matlab
% error_cgal = zeros(length(cgal_result), 1);
% % error_mtlb = zeros(length(func_result), 1);
% for i = 1 : length(cgal_result)
%     if cgal_result(i) ~= 0
%     error_cgal(i) = abs((cgal_result(i) - mtlb_result(i)) / cgal_result(i)) * 100;
%     % error_mtlb(i) = abs((func_result(i) - mtlb_result(i)) / func_result(i)) * 100;
%     end
% end
% 
% % average error values
% avg_error_cgal = mean(error_cgal);
% % avg_error_mtlb = mean(error_mtlb);

% M = readmatrix("..\build\Release\data_2\data3_scatter.csv");
% 
% figure(1)
% hold on
% plot(M(:,1),M(:,2),"LineWidth",1,"LineStyle","-","Color","b","Marker","+");
% plot(M(:,1),M(:,3),"LineWidth",1,"LineStyle","-","Color","r",Marker="+");
% % plot(M(:,1),M(:,6),"LineWidth",1,"LineStyle","-","Color","b",Marker="o");
% % plot(M(:,1),M(:,8),"LineWidth",1,"LineStyle","-","Color","r",Marker="o");
% grid on;
% legend("CGAL_scatter, MATLAB_scatter");
% xlabel("Number of query points");
% ylabel("Time elapsed (s)")
% title("Variation of time elapsed with number of query points (60000 data points)");
% hold off
% 
% figure(2)
% hold on
% plot(M(:,1),M(:,4),"*b",MarkerSize=10);
% % plot(M(:,1),M(:,5),"*r",MarkerSize=10);
% % plot(M(:,1),M(:,7),"ob",MarkerSize=10);
% % plot(M(:,1),M(:,9),"or",MarkerSize=10);
% grid on;
% % legend("Linear: CGAL","Linear: MATLAB","Quadratic: CGAL","Quadratic: MATLAB");
% xlabel("Number of query points");
% ylabel("Error (%)")
% title("Variation of Error with number of Query Points (60000 data points)");
% hold off

% 3D plot
M3 = readmatrix("..\build\Release\data_2\data5.csv");
M3_CGAL = M3(3:11,2:6);
M3_MTLB = M3(3:11,8:12);
sample = M3(3:11,1);
query = [1000;2000;3000;4000;5000];
figure(3)
hold on
surf(query,sample,M3_CGAL);
surf(query,sample,M3_MTLB);
legend("CGAL","MATLAB");
xlabel("Number of query points");
ylabel("Number of sample points");
zlabel("Computational time (s)");
hold off
view(3);