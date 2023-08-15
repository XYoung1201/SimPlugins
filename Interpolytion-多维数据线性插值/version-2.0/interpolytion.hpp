#pragma once
#include<stdlib.h>
#include<windows.h>
#include<string>
#include<fstream>
#include <iostream>
#include <math.h>

using namespace std;

class Interpolytion {
public:
    Interpolytion() {
        index_num=0;
        data_num=0;
        data=NULL;
        data_lockable=NULL;
        data_index_min = NULL;
        data_index_interval = NULL;
        data_temp = NULL;
        index_value = NULL;
        total_num=1;
        data_index_num = NULL;
    }
    ~Interpolytion(){
        free(data_index_num);
        free(data_index_min);
        free(data_index_interval);
        free(output);
        realse_data(data,0);

        for(int i=0;i<index_num;i++){
            free(data_temp[i][0]);
            free(data_temp[i][1]);
            free(data_temp[i]);
            free(index_value[i]);
        }
        free(data_temp);
        free(index_value);
        free(data_lockable);
    }

    void realse_data(void* index,int n){
        if(n != index_num)
            for(int i=0;i<data_index_num[i];i++)
                realse_data(((void**)index)[sizeof(void*)*i],n+1);
        free(index);
    }

    void mem_build(void*& index,int n){
        if(n==index_num){
            index=malloc(sizeof(double)*data_num);
            return;
        }
        index=malloc(data_index_num[n]*sizeof(void*));
        for(int i=0;i<data_index_num[n];i++)
            mem_build(((void**)(index))[i],n+1);
    }

    void config(int input_num, int output_num, double* minValue, double* maxValue, double* data_step) {
        index_num = input_num;
        index_value = (double**)malloc(sizeof(double*) * index_num);
        data_index_min = (double*)malloc(sizeof(double) * index_num);
        data_index_interval = (double*)malloc(sizeof(double) * index_num);
        data_index_num = (int*)malloc(sizeof(int) * index_num);
        data_temp = (double***)malloc(sizeof(double*) * index_num);
        for (int i = 0; i < index_num; i++) {
            data_index_min[i] = minValue[i];
            data_index_interval[i] = data_step[i];
            double max = maxValue[i];
            data_index_num[i] = ceil((max - data_index_min[i]) / data_index_interval[i])+1;
            total_num *= data_index_num[i];
            index_value[i] = (double*)malloc(sizeof(double) * data_index_num[i]);
            for (int j = 0; j < data_index_num[i]; j++)
                index_value[i][j] = data_index_min[i] + j * data_index_interval[i];
        }
        data_num = output_num;
        mem_build(data, 0);
        output = (double*)malloc(sizeof(double) * data_num);
        for (int i = 0; i < index_num; i++) {
            data_temp[i] = (double**)malloc(sizeof(double*) * 2);
            data_temp[i][0] = (double*)malloc(sizeof(double) * data_num);
            data_temp[i][1] = (double*)malloc(sizeof(double) * data_num);
        }
        data_lockable = (bool*)malloc(sizeof(bool) * data_num);
        for (int i = 0; i < data_num; i++) {
            data_lockable[i] = false;
        }
    }

    void boundryLimit(bool* limit) {
        if (data_num == 0)
            return;
        for (int i = 0; i < data_num; i++)
            data_lockable[i] = (bool*)calloc(index_num, sizeof(bool));
        double isornot;
        for (int i = 0; i < data_num; i++) {
            data_lockable[i] = limit[i];
        }
    }

    void read_file(string file_name){
        if (data_num == 0)
            return;
        ifstream file;
        file.open(file_name);
        double data_ = 0;
        while(file){
            void *index=data;
            double data_;
            for(int i=0;i<index_num;i++){
                file >> data_;
                index=((void**)index)[int(round((data_-data_index_min[i])/data_index_interval[i]))];
            }
            for(int i=0;i<data_num;i++){
                file >> data_;
                ((double*)index)[i]=data_;
            }
            total_num--;
            if (file.eof())
                break;
            if (total_num == 0)
                break;
        }
    }

    double* interpolyte(double* data_input){
        memcpy_s(output,data_num*sizeof(double),poly(data,0,data_input),data_num*sizeof(double));
        return output;
    }

    double* poly(void* index,int n,double* input_data){
        if(n==index_num)
            return (double*)index;
        double ratial=(input_data[n]-data_index_min[n])/data_index_interval[n];
        int n_=floor(ratial);
        bool over_limit;

        over_limit=(n_<0||n_+1>=data_index_num[n]);

        if(over_limit)
            n_=n_<0?0:data_index_num[n]-2;

        if(ratial-n_<data_index_interval[n]/1000 && !over_limit)
            return poly(((void**)index)[n_],n+1,input_data);
        if(n_+1-ratial<data_index_interval[n]/1000 && !over_limit)
            return poly(((void**)index)[n_+1],n+1,input_data);

        memcpy_s(data_temp[n][0],data_num*sizeof(double),poly(((void**)index)[n_],n+1,input_data),data_num*sizeof(double));
        memcpy_s(data_temp[n][1],data_num*sizeof(double),poly(((void**)index)[n_+1],n+1,input_data),data_num*sizeof(double));

        for(int i=0;i<data_num;i++)
            if(data_lockable[i] && over_limit)
                data_temp[n][0][i]=n_==0?data_temp[n][0][i]:data_temp[n][1][i];
            else
                data_temp[n][0][i]=((data_temp[n][0][i]-data_temp[n][1][i])*input_data[n]-
                data_temp[n][0][i]*index_value[n][n_+1]+data_temp[n][1][i]*index_value[n][n_])/
                (index_value[n][n_]-index_value[n][n_+1]);
        return data_temp[n][0];
    }
};
