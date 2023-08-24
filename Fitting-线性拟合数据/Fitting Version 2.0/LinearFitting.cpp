#include "LinearFitting.h"
LinearFitting::LinearFitting(const std::string fileName,const int input_dim,const int output_dim):m(input_dim),n(output_dim) {
    std::ifstream file(fileName);

    N = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++N;
    }

    Eigen::MatrixXd X(N, m + 1);
    Eigen::MatrixXd Y(N, n);

    y_out = (double*)malloc(sizeof(double) * n);

    x.resize(m + 1);
    y.resize(n);

    file.clear();
    file.seekg(0, std::ios::beg);

    int row = 0;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string value;
        for (int i = 0; i < m; ++i) {
            std::getline(ss, value, ',');
            X(row,i) = std::stod(value);
        }
        X(row, m) = 1.0;
        for (int i = 0; i < n; ++i) {
            std::getline(ss, value, ',');
            Y(row,i) = std::stod(value);
        }
        ++row;
    }

    getW(X, Y);
}
LinearFitting::~LinearFitting() {
    free(y_out);
}
void LinearFitting::getW(const Eigen::MatrixXd& X, const Eigen::MatrixXd& Y) {
    Eigen::MatrixXd XTX = X.transpose() * X;
    Eigen::MatrixXd XTY = X.transpose() * Y;
    W = XTX.ldlt().solve(XTY);
}

double* LinearFitting::Predicting(double* x) {
    for (int i = 0; i < m; i++)
        this->x(i) = x[i];
    this->x(m) = 1.0;
    this->y = this->x.transpose() * W;
    for (int i = 0; i < n; i++)
        this->y_out[i] = this->y(i);
    return this->y_out;
}
