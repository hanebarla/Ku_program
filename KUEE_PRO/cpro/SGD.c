#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "nn.h"

#define epoch_time 50
#define batch_size 100
#define L_rate 0.1

// m_x_rows * m_x_colums, m_y_rows * m_y_colums　の行列としたとき
// m_x_colums = m_y_rows は前提とする
// X * Y = O

//入力→affine→Relu→affine→Relu→affine→softmax(出力)→cross_entropy_error

void int_swap(int *a, int *b);

void shuffle(int m_x_size, int *m_x);

void index_init(int m_x_size, int *m_x);

void rand_init(int size, float *matrix); // 乱数初期化

void con_init(int size, float init_num,float *bias); // 第2引数で初期化

void labtomatrix(int lab, float *t); // 正解ラベルを配列に

void matrixtolab(int *lab, float *y); // 最も高いスコアの添え字を答えとする

void Affine_layer_forward(int m_y_size, int m_x_colums, float *m_x, float *m_y, float *m_b, float *output); //順方向Affine

void Affine_layer_backward(int m_x_size, int m_w_size, int m_x_colums, float *d_o, float *m_x, float *m_w, float *m_b,float *dm_x, float *dm_w, float *dm_b);

void Mul_layer_forward(int m_y_size, int m_x_colums, float *m_x, float *m_y, float *output); // X * Y = output

void Mul_layer_backward(int m_x_size, int m_y_size, int m_x_colums, float *d_o, float *m_x, float *m_y, float *dm_x, float *dm_y);
// dm_x = d_o * m_y.T, dm_y = m_x.T * d_o

void Add_layer_forward(int m_y_size, int m_x_colums, float *m_x, float *m_y, float *output); // X + Y = output

void Add_layer_backward(int m_y_size, float *d_o, float *m_y, float *dm_y);

void Relu_layer_forward(int m_x_size, float *m_x, float *output);

void Relu_layer_backward(int m_x_size, float *d_o, float *m_x, float *dm_x);

void Softmax_layer_forward(int m_x_size, float *m_x, float *m_y);

void Cross_entropy_error(int m_x_size, float *m_y, int t, float *loss);

void Softmax_with_Loss_layer_backward(int m_x_size, float *m_y, float *m_t, float *dm_x);

void update(int x_size, float *m_x, float *dm_x); // SGD

void add_slope(int m_x_size, float *m_x, float *sum_x);

void Slope_Cal(int input_size, int hidden1_size, int hidden2_size, int output_size,
                 float *m_input, int label, float *W1, float *W2, float *W3, float *b1, float *b2, float *b3,
                 float *d_W1, float *d_W2, float *d_W3, float *d_b1, float *d_b2, float *d_b3);
// 勾配の計算

int predict(float *m_input, float *W1, float *W2, float *W3, float *b1, float *b2, float *b3, float *loss, int label);

void save(const char *filename, int m, int n, float *A, float *b);

void load(const char *filename, int m, int n, float *A, float *b);

void logger(const char *filename, int gyou, float *matrix);

void print(int size, float *matrix);

int main(int argc, char *argv[]){

    if(argc == 4){

        float *train_x = NULL;
        unsigned char *train_y = NULL;
        int train_count = -1;

        float *test_x = NULL;
        unsigned char *test_y = NULL;
        int test_count = -1;

        int width = -1;
        int height = -1;

        load_mnist(&train_x, &train_y, &train_count, //MNISTのデータ読みこみ
                    &test_x, &test_y, &test_count,
                    &width, &height);

        // これ以降，３層NN の係数 A_784x10 および b_784x10 と，
        // 訓練データ train_x + 784*i (i=0,...,train_count-1), train_y[0]～train_y[train_count-1],
        // テストデータ test_x + 784*i (i=0,...,test_count-1), test_y[0]～test_y[test_count-1],
        // を使用することができる．

        // 重みパラメータの定義
        float *W1 = malloc(sizeof(float) * 39200); // 784 * 50
        float *W2 = malloc(sizeof(float) * 5000); // 50 * 100
        float *W3 = malloc(sizeof(float) * 1000); // 100 * 10
        rand_init(39200, W1);
        rand_init(5000, W2);
        rand_init(1000, W3);

        // バイアスの定義
        float *b1 = malloc(sizeof(float) * 50);
        float *b2 = malloc(sizeof(float) * 100);
        float *b3 = malloc(sizeof(float) * 10);
        con_init(50, 1, b1);
        con_init(100, 1, b2);
        con_init(10, 1, b3);

        // データの添え字
        int *index = malloc(sizeof(int) * train_count);
        index_init(train_count, index);
        shuffle(train_count, index);

        // 重みパラメータとバイアスの勾配
        float *d_W1 = malloc(sizeof(float) * 39200);
        float *d_b1 = malloc(sizeof(float) * 50);
        float *d_W2 = malloc(sizeof(float) * 5000);
        float *d_b2 = malloc(sizeof(float) * 100);
        float *d_W3 = malloc(sizeof(float) * 1000);
        float *d_b3 = malloc(sizeof(float) * 10);
        con_init(39200, 0, d_W1);
        con_init(50, 0, d_b1);
        con_init(5000, 0, d_W2);
        con_init(100, 0, d_b2);
        con_init(1000, 0, d_W3);
        con_init(10, 0, d_b3);

        // バッチで更新用の勾配の合計
        float *sum_d_W1 = malloc(sizeof(float) * 39200);
        float *sum_d_b1 = malloc(sizeof(float) * 50);
        float *sum_d_W2 = malloc(sizeof(float) * 5000);
        float *sum_d_b2 = malloc(sizeof(float) * 100);
        float *sum_d_W3 = malloc(sizeof(float) * 1000);
        float *sum_d_b3 = malloc(sizeof(float) * 10);

        // データログ保存場所
        float *logging = malloc(sizeof(float) * 3 * epoch_time);
        con_init(3 * epoch_time, 0, logging);

        // 時間計測
        clock_t e_start, e_end;

        int batch_num = train_count / batch_size;

        for (int n = 0; n < epoch_time;n++){

            printf("\n============================== Begin Epoch %d/%d ==============================\n\nNow begin trainig!\n", n + 1, epoch_time);
            float time;
            e_start = clock();

            int test_ac_count = 0;
            int train_ac_count = 0;
            int accuracy_conut = 0;
            float accuracy_rate = 0;
            float ave_loss = 0;

            for (int i = 0; i < batch_num;i++){

                con_init(39200, 0, sum_d_W1);
                con_init(50, 0, sum_d_b1);
                con_init(5000, 0, sum_d_W2);
                con_init(100, 0, sum_d_b2);
                con_init(1000, 0, sum_d_W3);
                con_init(10, 0, sum_d_b3);

                #pragma omp parallel for
                for (int k =i * batch_size; k < (i + 1) * batch_size; k++){

                    Slope_Cal(784, 50, 100, 10, train_x + 784 * index[k], train_y[index[k]], W1, W2, W3, b1, b2, b3, d_W1, d_W2, d_W3, d_b1, d_b2, d_b3);
                    add_slope(39200, d_W1, sum_d_W1);
                    add_slope(50, d_b1, sum_d_b1);
                    add_slope(5000, d_W2, sum_d_W2);
                    add_slope(100, d_b2, sum_d_b2);
                    add_slope(1000, d_W3, sum_d_W3);
                    add_slope(10, d_b3, sum_d_b3);
                }

                update(39200, W1, sum_d_W1);
                update(50, b1, sum_d_b1);
                update(5000, W2, sum_d_W2);
                update(100, b2, sum_d_b2);
                update(1000, W3, sum_d_W3);
                update(10, b3, sum_d_b3);

                // プログレスバー
                fprintf(stderr, "\r0%% |");
                for (int j = 0; j < i / 30 ;j++){
                    fprintf(stderr, "#");
                }
                for (int j = 0; j < 19 - (i / 30);j++){
                    fprintf(stderr, " ");
                }
                fprintf(stderr, "| 100%% [%.1f%%]", (float)(i + 1) / 6.0);

            }
            printf(" Trained!\n\nNow begin Testing!\n");

            for (int m = 0; m < test_count;m++){
                if( predict(test_x + 784 * m, W1, W2, W3, b1, b2, b3, &ave_loss, test_y[m])){
                    accuracy_conut += 1;
                    test_ac_count += 1;
                }
                // プログレスバー
                if(m % 500 == 0){
                    fprintf(stderr, "\rTest Data 0%% |");
                    for (int j = 0; j < m / 500 ;j++){
                        fprintf(stderr, "#");
                    }
                    for (int j = 0; j < 19 - ( m/ 500);j++){
                        fprintf(stderr, " ");
                    }
                    fprintf(stderr, "| 100%%");
                }
            }
            printf(" Acuuracy: %.3f%%\n", 100.0 * (float)test_ac_count / test_count);
            for (int o = 0; o < train_count;o++){
                if (predict(train_x + 784 * o, W1, W2, W3, b1, b2, b3, &ave_loss, train_y[o])){
                    accuracy_conut += 1;
                    train_ac_count += 1;
                }
                // プログレスバー
                if(o % 3000 == 0){
                    fprintf(stderr, "\rTrain Data 0%% |");
                    for (int j = 0; j < o / 3000;j++){
                        fprintf(stderr, "#");
                    }
                    for (int j = 0; j < 19 - (o / 3000);j++){
                        fprintf(stderr, " ");
                    }
                    fprintf(stderr, "| 100%%");
                }
            }
            printf(" Accuracy: %.3f%% Tested!\n", 100.0*(train_ac_count) / train_count);
            accuracy_rate = 100.0 * (float)accuracy_conut / (test_count + train_count);
            ave_loss /= (train_count + test_count);
            printf("Average Accracy: %f%%     Loss: %.8f\n", accuracy_rate, ave_loss);
            e_end = clock();
            time = (double)(e_end - e_start) / CLOCKS_PER_SEC;
            printf("Time: %f[s]\n", time);

            logging[3 * n] = accuracy_rate;
            logging[3 * n + 1] = ave_loss;
            logging[3 * n + 2] = time;
            printf("\n============================== End   Epoch %d ==============================\n\n\n", n+1);
        }
        logger("SGDlog2.csv", epoch_time, logging);
        save(argv[1], 784, 50, W1, b1);
        save(argv[2], 50, 100, W2, b2);
        save(argv[3], 100, 10, W3, b3);

    }else{
        printf("Arguments Error\n");
        exit(1);
    }

    return 0;
}

void int_swap(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int m_x_size, int *m_x){
    int temp;
    for (int i = 0; i < m_x_size;i++){
        temp = rand() % m_x_size;
        int_swap(&m_x[i], &m_x[temp]);
    }
}

void index_init(int m_x_size, int *m_x){
    for (int i = 0; i < m_x_size;i++){
        m_x[i] = i;
    }
}

void rand_init(int size_y, float *y){
    srand(time(NULL));
    for (int i = 0; i < size_y;i++){
        int np = (rand() % 2) + 1;
        y[i] = pow(-1, np) * (rand() % 1000000) / 1000000;
    }
}

void con_init(int size_b, float init_num, float *bias){
    for (int i = 0; i < size_b;i++){
        bias[i] = init_num;
    }
}

void labtomatrix(int lab, float *t){
    for (int i = 0; i < 10;i++){
        if(lab == i){
            t[i] = 1;
        }else{
            t[i] = 0;
        }
    }
}

void matrixtolab(int *lab, float *y){
    *lab = 0;
    for (int i = 0; i < 9;i++){
        if(y[i]>y[*lab]){
            *lab = i;
        }
    }
}

void Affine_layer_forward(int m_w_size, int m_x_colums, float *m_x, float *m_w, float *m_b, float *output){
    Mul_layer_forward(m_w_size, m_x_colums, m_x, m_w, output);
    int m_b_size = m_w_size / m_x_colums;
    Add_layer_forward(m_b_size, m_b_size, m_b, output, output);
}

void Affine_layer_backward(int m_x_size, int m_w_size, int m_x_colums, float *d_o, float *m_x, float *m_w, float *m_b,float *dm_x, float *dm_w, float *dm_b){
    Mul_layer_backward(m_x_size, m_w_size, m_x_colums, d_o, m_x, m_w, dm_x, dm_w);
    int m_b_size = m_w_size / m_x_colums;
    Add_layer_backward(m_b_size, d_o, m_b, dm_b);
}

void Mul_layer_forward(int m_y_size, int m_x_colums, float *m_x, float *m_y, float *output){
    for (int i = 0; i < m_y_size;i++){
        int x_sub_scr = i % m_x_colums;
        int o_sub_scr = i / m_x_colums;
        output[o_sub_scr] += m_x[x_sub_scr] * m_y[i];
    }
}

void Mul_layer_backward(int m_x_size, int m_y_size, int m_x_colums, float *d_o, float *m_x, float *m_y, float *dm_x, float *dm_y){
    int m_y_colums = m_y_size / m_x_colums; // m_y_colums = d_o_colums となるのは明らか
    for (int i = 0; i < m_x_colums;i++){
        for (int j = 0; j < m_y_colums;j++){
            dm_x[i] += d_o[j] * m_y[i + j * m_x_colums];
        }
    }
    // ここがだめだった。まだ間違っている可能性あり。
    for (int i = 0; i < m_y_colums;i++){
        for (int j = 0; j < m_x_colums;j++){
            dm_y[j + i * m_x_colums] = m_x[j] * d_o[i];
        }
    }
}

void Add_layer_forward(int m_y_size, int m_x_colums, float *m_x, float *m_y, float *output){
    for (int i = 0; i < m_y_size;i++){
        output[i] = m_x[i] + m_y[i];
    }
}

void Add_layer_backward(int m_y_size, float *d_o, float *m_y, float *dm_y){
    for (int i = 0; i < m_y_size;i++){
        dm_y[i] = d_o[i];
    }
}

void Relu_layer_forward(int m_x_size, float *m_x, float *output){
    for (int i = 0; i < m_x_size;i++){
        if(m_x[i]<0){
            output[i] = 0;
        }else{
            output[i] = m_x[i];
        }
    }
}

void Relu_layer_backward(int m_x_size, float *d_o, float *m_x, float *dm_x){
    for (int i = 0; i < m_x_size;i++){
        if(m_x[i]>0){
            dm_x[i] = d_o[i];
        }else{
            dm_x[i] = 0;
        }
    }
}

void Softmax_layer_forward(int m_x_size, float *m_x, float *m_y){
    float sum = 0;
    for (int i = 0; i < m_x_size;i++){
        sum += exp(m_x[i]);
    }
    for (int j = 0; j < m_x_size;j++){
        m_y[j] = exp(m_x[j]) / (sum);
    }
}

void Cross_entropy_error(int m_y_size, float *m_y, int t, float *loss){
    *loss = -log(m_y[t]);
}

void Softmax_with_Loss_layer_backward(int m_y_size, float *m_y, float *m_t, float *dm_x){
    for (int i = 0; i < m_y_size;i++){
        dm_x[i] = m_y[i] - m_t[i];
    }
}

void update(int x_size, float *m_x, float *dm_x){
    for (int i = 0; i < x_size;i++){
        m_x[i] -= L_rate * dm_x[i] / batch_size;
    }
}

void add_slope(int m_x_size, float *m_x, float *sum_x){
    for (int i = 0; i < m_x_size;i++){
        sum_x[i] += m_x[i];
    }
}

void Slope_Cal(int input_size, int hidden1_size, int hidden2_size, int output_size, float *m_input, int label, float *W1, float *W2, float *W3, float *b1, float *b2, float *b3, float *d_W1, float *d_W2, float *d_W3, float *d_b1, float *d_b2, float *d_b3){
    // 活性化関数の入力部
    float *ReLu1_input = malloc(sizeof(float) * 50);
    float *ReLu1_output = malloc(sizeof(float) * 50);
    float *ReLu2_input = malloc(sizeof(float) * 100);
    float *ReLu2_output = malloc(sizeof(float) * 100);
    float *softmax_input = malloc(sizeof(float) * 10);
    float *softmax_output = malloc(sizeof(float) * 10); // cross_entropy_error_inputと同じ
    float *Cross_entropy_error_output = malloc(sizeof(float) * 10);
    con_init(50, 0, ReLu1_input);
    con_init(50, 0, ReLu1_output);
    con_init(100, 0, ReLu2_input);
    con_init(100, 0, ReLu2_output);
    con_init(10, 0, softmax_input);
    con_init(10, 0, softmax_output);
    con_init(10, 0, Cross_entropy_error_output);

    // その他の勾配
    float *d_ReLu1_in = malloc(sizeof(float) * 50);
    float *d_ReLu1_out = malloc(sizeof(float) * 50);
    float *d_ReLu2_in = malloc(sizeof(float) * 100);
    float *d_ReLu2_out = malloc(sizeof(float) * 100);
    float *d_soft = malloc(sizeof(float) * 10);
    float *d_input = malloc(sizeof(float) * 784);
    con_init(50, 0, d_ReLu1_in);
    con_init(50, 0, d_ReLu1_out);
    con_init(100, 0, d_ReLu2_in);
    con_init(100, 0, d_ReLu2_out);
    con_init(10, 0, d_soft);
    con_init(784, 0, d_input);

    // 正解ラベルに基づいた配列
    float *train_m_t = malloc(sizeof(float) * 10);
    // 誤り率
    float loss = 0;

    con_init(39200, 0, d_W1);
    con_init(50, 0, d_b1);
    con_init(5000, 0, d_W2);
    con_init(100, 0, d_b2);
    con_init(1000, 0, d_W3);
    con_init(10, 0, d_b3);

    labtomatrix(label, train_m_t);

    Affine_layer_forward(39200, 784, m_input, W1, b1, ReLu1_input);
    Relu_layer_forward(50, ReLu1_input, ReLu1_output);
    Affine_layer_forward(5000, 50, ReLu1_output, W2, b2, ReLu2_input);
    Relu_layer_forward(100, ReLu2_input, ReLu2_output);
    Affine_layer_forward(1000, 100, ReLu2_output, W3, b3, softmax_input);
    Softmax_layer_forward(10, softmax_input, softmax_output);
    // print(10, softmax_output);
    Cross_entropy_error(10, softmax_output, label, &loss);
    Softmax_with_Loss_layer_backward(10, softmax_output, train_m_t, d_soft);
    Affine_layer_backward(100, 1000, 100, d_soft, ReLu2_output, W3, b3, d_ReLu2_out, d_W3, d_b3);
    Relu_layer_backward(100, d_ReLu2_out, ReLu2_input, d_ReLu2_in);
    Affine_layer_backward(50, 5000, 50, d_ReLu2_in, ReLu1_output, W2, b2, d_ReLu1_out, d_W2, d_b2);
    Relu_layer_backward(50, d_ReLu1_out, ReLu1_input, d_ReLu1_in);
    Affine_layer_backward(784, 39200, 784, d_ReLu1_in, m_input, W1, b1, d_input, d_W1, d_b1);

    free(ReLu1_input);
    free(ReLu1_output);
    free(ReLu2_input);
    free(ReLu2_output);
    free(softmax_input);
    free(softmax_output);
    free(Cross_entropy_error_output);
    free(d_ReLu1_in);
    free(d_ReLu1_out);
    free(d_ReLu2_in);
    free(d_ReLu2_out);
    free(d_input);
    free(d_soft);
}

int predict(float *m_input, float *W1, float *W2, float *W3, float *b1, float *b2, float *b3, float *sum_loss, int label){

    float max = 0;
    int max_index = 0;
    int count_flag = 0;
    float loss = 0;

    float *ReLu1_input = malloc(sizeof(float) * 50);
    float *ReLu1_output = malloc(sizeof(float) * 50);
    float *ReLu2_input = malloc(sizeof(float) * 100);
    float *ReLu2_output = malloc(sizeof(float) * 100);
    float *softmax_input = malloc(sizeof(float) * 10);
    float *softmax_output = malloc(sizeof(float) * 10); // cross_entropy_error_inputと同じ
    float *Cross_entropy_error_output = malloc(sizeof(float) * 10);
    con_init(50, 0, ReLu1_input);
    con_init(50, 0, ReLu1_output);
    con_init(100, 0, ReLu2_input);
    con_init(100, 0, ReLu2_output);
    con_init(10, 0, softmax_input);
    con_init(10, 0, softmax_output);
    con_init(10, 0, Cross_entropy_error_output);

    Affine_layer_forward(39200, 784, m_input, W1, b1, ReLu1_input);
    Relu_layer_forward(50, ReLu1_input, ReLu1_output);
    Affine_layer_forward(5000, 50, ReLu1_output, W2, b2, ReLu2_input);
    Relu_layer_forward(100, ReLu2_input, ReLu2_output);
    Affine_layer_forward(1000, 100, ReLu2_output, W3, b3, softmax_input);
    Softmax_layer_forward(10, softmax_input, softmax_output);
    Cross_entropy_error(10, softmax_output, label, &loss);
    *sum_loss += loss;
    max = softmax_input[0];
    for (int i = 0; i < 10;i++){
        if(max < softmax_input[i]){
            max = softmax_input[i];
            max_index = i;
        }
    }

    if(max_index == label){
        count_flag = 1;
    }

    free(ReLu1_input);
    free(ReLu1_output);
    free(ReLu2_input);
    free(ReLu2_output);
    free(softmax_input);
    return count_flag;
}

void load(const char *filename, int m, int n, float *A, float *b){
    FILE *fp;
    fp = fopen(filename, "rb");
    if(!fp){
        printf("FILE CANNOT OPEN");
    }
    for (int i = 0; i < m;i++){
        for (int j = 0; j < n;j++){
            fread(&A[i*j+j], sizeof(float), 1, fp);
        }
    }
    for (int j = 0; j < n; j++){
        fread(&b[j], sizeof(float), 1, fp);
    }
    fclose(fp);
}

void save(const char *filename, int m, int n, float *A, float *b){
    FILE *fp;
    fp = fopen(filename , "wb");
    fwrite(A, sizeof(float), m*n, fp);
    fwrite(b, sizeof(float), n, fp);
    fclose(fp);
}

void logger(const char *filename, int gyou, float *matrix){
    FILE *fp;
    fp = fopen(filename, "w");
    for (int i = 0; i < gyou;i++){
        fprintf(fp, "%d,%f,%.8f,%f\n", i + 1, matrix[3 * i], matrix[3 * i + 1], matrix[3 * i + 2]);
    }
    fclose(fp);
}

void print(int size, float *matrix){
    for (int i = 0; i < size;i++){
        printf("%lf ", matrix[i]);
    }
    printf("\n\n");
}