/*
    @����:CHH
    @�汾V1.0
    @����:chh_is_dog@163.com
    @��дʱ��:2019-7-29
    @����:ʹ�÷��򴫲�������ʶ����д����
    @ʹ�÷���:
        1.���ɵ��ļ����Զ���ͬһĿ¼��Ѱ��MNIST���ĸ���д�����
        2.��������ص�ַ:http://yann.lecun.com/exdb/mnist/
        3.DEBUGģʽ��ֻ��ʹ������ѵ������
        4.�����Ϊstdout
    @ģ�ͽṹ:
        1.�����:sigmod
        2.��ʧ����:��������ʧ����
        3.������ʽ:���򴫲�+�����ݶ��½�
        4.ѧϰ��=0.5
        5.������Ԫ,���ӷ�ʽ: ȫ����
            a.�����:28*28��
            b.���ز�:20��
            c.�����:10��
    @����ṹ:��Ϊ4��ģ��,������̻�
        1.ʵ�־������Լ�����Ļ�������
        2.����MNIST�����ݲ�������ϴ
        3.ʵ��FP->BP->GD
        4.ģ������
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

#define DEBUG

const int IMAGE_SIZE = 28 * 28;
const int LABEL_SIZE = 1;
const int OUT_SIZE = 10;
const double INF = 1.7e308;
const double EPS = 1e-6;
const double E = 2.718281828459;
#ifdef DEBUG
const int NUM_TRAIN = 100;
const int NUM_TEST = 10;
#else
const int NUM_TRAIN = 60000;
const int NUM_TEST = 10000;
#endif

//����
typedef vector<vector<double>> Matrix;
//������
void construct(Matrix &mat, int row, int col)
{
    mat.resize(row);
    for (int i = 0; i < row; i++)
        mat[i].resize(col);
}
void construct(Matrix &mat, int row, int col, double val)
{
    mat.resize(row);
    for (int i = 0; i < row; i++)
        mat[i].resize(col, val);
}
//����ӷ�
inline const Matrix addition(const Matrix &a, const Matrix &b)
{
    if (a.size() != b.size() || a[0].size() != b[0].size())
        throw "ERROR: Matrix addition format wrong";
    Matrix res;
    res.resize(a.size());
    for (int i = 0; i < a.size(); i++)
        res[i].resize(a[0].size());
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a[i].size(); j++)
            res[i][j] = a[i][j] + b[i][j];
    return res;
}
//�������
inline const Matrix subtract(const Matrix &a, const Matrix &b)
{
    if (a.size() != b.size() || a[0].size() != b[0].size())
        throw "ERROR: Matrix subtract format wrong";
    Matrix res;
    res.resize(a.size());
    for (int i = 0; i < a.size(); i++)
        res[i].resize(a[0].size());
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a[i].size(); j++)
            res[i][j] = a[i][j] - b[i][j];
    return res;
}
//����˷�
inline const Matrix multiply(const Matrix &a, const Matrix &b)
{
    if (a[0].size() != b.size())
        throw "ERROR: Matrix multiply format wrong";
    Matrix res;
    res.resize(a.size());
    for (int i = 0; i < a.size(); i++)
        res[i].resize(b[0].size(), 0);
    for (int i = 0; i < res.size(); i++)
        for (int j = 0; j < res[0].size(); j++)
            for (int k = 0; k < a[0].size(); k++)
                res[i][j] += a[i][k] * b[k][j];
    return res;
}
//������
inline const Matrix matmul(const Matrix &a, const Matrix &b)
{
    if (a.size() != b.size() || a[0].size() != b[0].size())
        throw "ERROR: Matrix matmul format wrong";
    Matrix res;
    res.resize(a.size());
    for (int i = 0; i < a.size(); i++)
        res[i].resize(a[0].size());
    for (int i = 0; i < res.size(); i++)
        for (int j = 0; j < res[0].size(); j++)
            res[i][j] = a[i][j] * b[i][j];
    return res;
}
//����Ա����ĳ˷�
inline const Matrix multiply(const Matrix &a, double val)
{
    Matrix res;
    res.resize(a.size());
    for (int i = 0; i < a.size(); i++)
        res[i].resize(a[0].size());
    for (int i = 0; i < res.size(); i++)
        for (int j = 0; j < res[0].size(); j++)
            res[i][j] = a[i][j] * val;
    return res;
}
//����Ա����ĳ���
inline const Matrix division(const Matrix &a, double val)
{
    Matrix res;
    res.resize(a.size());
    for (int i = 0; i < a.size(); i++)
        res[i].resize(a[0].size());
    for (int i = 0; i < res.size(); i++)
        for (int j = 0; j < res[0].size(); j++)
            res[i][j] = a[i][j] / val;
    return res;
}

//����ת��
inline const Matrix transpose(const Matrix &mat)
{
    Matrix res;
    res.resize(mat[0].size());
    for (int i = 0; i < res.size(); i++)
        res[i].resize(mat.size());
    for (int i = 0; i < res.size(); i++)
        for (int j = 0; j < res[0].size(); j++)
            res[i][j] = mat[j][i];
    return res;
}
//��ӡ����
void printMatrix(const Matrix &mat)
{
    cout << mat.size() << " * " << mat[0].size() << endl;
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

//��ӡͼƬ
inline void printImage(const Matrix &data)
{
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            printf("%.2lf ", data[28 * i + j][0]);
        }
        cout << '\n';
    }
}

//���ݵ�
struct Point
{
    //double image[IMAGE_SIZE];
    //bool label[OUT_SIZE];
    Matrix image;
    Matrix label;
    Point(char *image, uint8_t num)
    {
        this->image.resize(IMAGE_SIZE);
        for (int i = 0; i < IMAGE_SIZE; i++)
        {
            this->image[i].resize(1);
            this->image[i][0] = (uint8_t)image[i];
        }
        label.resize(OUT_SIZE);
        for (int i = 0; i < OUT_SIZE; i++)
        {
            label[i].resize(1);
            label[i][0] = 0;
        }
        label[num][0] = 1;
    }
};
vector<Point> TrainData, TestData;

//��������
void readALLData(vector<Point> &train, vector<Point> &test)
{
    char rubbish[16];
    ifstream train_images("./train-images.idx3-ubyte", ios::binary | ios::in);
    ifstream train_labels("./train-labels.idx1-ubyte", ios::binary | ios::in);
    train_images.read(rubbish, 16); //4*32bit_integer
    train_labels.read(rubbish, 8);  //2*32bit_integer
    for (int i = 0; i < NUM_TRAIN; i++)
    {
        char image[IMAGE_SIZE];
        uint8_t num;
        train_images.read(image, IMAGE_SIZE);
        train_labels.read((char *)(&num), LABEL_SIZE);
        train.push_back({image, num});
        // printImage(train[i].image);
    }

    ifstream test_images("./t10k-images.idx3-ubyte", ios::binary | ios::in);
    ifstream test_labels("./t10k-labels.idx1-ubyte", ios::binary | ios::in);
    test_images.read(rubbish, 16); //4*32bit_integer
    test_labels.read(rubbish, 8);  //2*32bit_integer
    for (int i = 0; i < NUM_TEST; i++)
    {
        char image[IMAGE_SIZE];
        uint8_t num;
        test_images.read(image, IMAGE_SIZE);
        test_labels.read((char *)(&num), LABEL_SIZE);
        test.push_back({image, num});
    }
    // printImage(test[0].image);
    // for(int i=0; i<10; i++)
    //     if(test[0].label[i])
    //         cout<<i;
}

//��һ��
void Normalize(vector<Point> &set)
{
    vector<Point>::iterator it;
    it = set.begin();
    while (it != set.end())
    {
        for (int i = 0; i < IMAGE_SIZE; i++)
        {
            it->image[i][0] /= 180.0; //ӳ�䵽[0, 1.4]֮��
        }

        it++;
    }
}

//������

//����ṹ
//���㣺����:28*28->����:20->���:10
const int LAYER_NUM = 3;
const int NEURE_NUM[LAYER_NUM] = {IMAGE_SIZE, 20, OUT_SIZE};

//�����
inline double sigmod(double x)
{
    return 1.0 / (1 + pow(E, -x)); //BUG,��ĸ���и�1+
}
inline const Matrix sigmod(const Matrix &mat)
{
    Matrix res;
    construct(res, mat.size(), mat[0].size());
    for (int i = 0; i < res.size(); i++)
        for (int j = 0; j < res[0].size(); j++)
            res[i][j] = sigmod(mat[i][j]);
    return res;
}

//��ر���
vector<Matrix> Weight;     //Ȩ��
vector<Matrix> Bias;       //ƫ����
vector<Matrix> Error;      //���
vector<Matrix> der_Weight; //Ȩ�ص�ƫ����
vector<Matrix> der_Bias;   //ƫ������ƫ����
vector<Matrix> receive;    //���ܵ�ֵ
vector<Matrix> activation; //�������ֵ
int iteration;             //��������
double step;               //ѧϰ��
//�����������ʼ��
void initialize(void)
{
    //������
    iteration = 200;
    step = 0.5;
    //Ȩ�س�ʼ��
    Weight.resize(LAYER_NUM);
    for (int i = 1; i < LAYER_NUM; i++)
    {
        //������״
        construct(Weight[i], NEURE_NUM[i], NEURE_NUM[i - 1]);
        //���������
        srand(time(0));
        for (int j = 0; j < Weight[i].size(); j++)
            for (int k = 0; k < Weight[i][0].size(); k++)
            {
                Weight[i][j][k] = ((double)(rand() % 1000) / 700 - 0.5) * sqrt(1.0 / NEURE_NUM[i - 1]);
                //cout << Weight[i][j][k] << endl;
            }
    }
    //ƫ������ʼ��
    Bias.resize(LAYER_NUM);
    for (int i = 1; i < LAYER_NUM; i++)
    {
        //������״
        //0��ʼ��
        construct(Bias[i], NEURE_NUM[i], 1, 0);
    }
    //����ʼ��
    Error.resize(LAYER_NUM);
    for (int i = 1; i < LAYER_NUM; i++)
    {
        //������״
        //0��ʼ��
        construct(Error[i], NEURE_NUM[i], 1, 0);
    }
    //Ȩ�ص�ƫ������ʼ��
    der_Weight.resize(LAYER_NUM);
    for (int i = 1; i < LAYER_NUM; i++)
    {
        //������״
        //0��ʼ��
        construct(der_Weight[i], NEURE_NUM[i], NEURE_NUM[i - 1], 0);
    }
    //ƫ������ƫ������ʼ��
    der_Bias.resize(LAYER_NUM);
    for (int i = 1; i < LAYER_NUM; i++)
    {
        //������״
        //0��ʼ��
        construct(der_Bias[i], NEURE_NUM[i], 1, 0);
    }
    //���ܵ�ֵ��ʼ��
    receive.resize(LAYER_NUM);
    for (int i = 1; i < LAYER_NUM; i++)
    {
        //������״
        //0��ʼ��
        construct(receive[i], NEURE_NUM[i], 1, 0);
    }
    //�������ֵ��ʼ��
    activation.resize(LAYER_NUM);
    for (int i = 0; i < LAYER_NUM; i++)
    {
        //������״
        //0��ʼ��
        construct(activation[i], NEURE_NUM[i], 1, 0);
    }
}

//����
inline void zeroClear(vector<Matrix> &mat)
{
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++)
            for (int k = 0; k < mat[i][0].size(); k++)
                mat[i][j][k] = 0;
}

//����������ǰ�򴫲�
inline void forwardPropagation(const Point &point)
{
    activation[0] = point.image;
    for (int i = 1; i < LAYER_NUM; i++)
    {
        receive[i] = multiply(Weight[i], activation[i - 1]);
        activation[i] = sigmod(receive[i]);
    }
}

//���������㷴�򴫲�
inline void backPropagation(const Point &point)
{
    Error[LAYER_NUM - 1] = subtract(activation[LAYER_NUM - 1], point.label);
    Matrix ONE;
    for (int i = LAYER_NUM - 2; i >= 1; i--) //ע���Ƿ��򴫲�
    {
        construct(ONE, activation[i].size(), activation[i][0].size(), 1);
        Error[i] = matmul(multiply(transpose(Weight[i + 1]), Error[i + 1]), matmul(activation[i], subtract(ONE, activation[i])));
    }
}
//ƫ�����ۼ�
inline void accumulateDerivate(void)
{
    for (int i = 1; i < LAYER_NUM; i++)
    {
        der_Weight[i] = addition(der_Weight[i], multiply(Error[i], transpose(activation[i - 1])));
        der_Bias[i] = addition(der_Bias[i], Error[i]);
    }
}
//����ƫ����
inline void calculateDerivate(void)
{
    for (int i = 1; i < LAYER_NUM; i++)
    {
        der_Weight[i] = division(der_Weight[i], NUM_TRAIN);
        der_Bias[i] = division(der_Bias[i], NUM_TRAIN);
    }
}
//�ݶ��½�
inline void gradientDescent(void)
{
    for (int i = 1; i < LAYER_NUM; i++)
    {
        Weight[i] = subtract(Weight[i], multiply(der_Weight[i], step));
        Bias[i] = subtract(Bias[i], multiply(der_Bias[i], step));
    }
}
//�������Ƿ���ȷ
inline bool match(const Matrix &res, const Matrix &label)
{
    int max_pos = 0;
    for (int i = 1; i < OUT_SIZE; i++)
        if (res[i][0] > res[max_pos][0])
            max_pos = i;
    return label[max_pos][0] == 1;
}
//������޴�������
inline bool mistake(void)
{
    for (int i = 0; i < NUM_TRAIN; i++)
    {
        const Point &point = TrainData[i];
        forwardPropagation(point);
        if (!match(activation[LAYER_NUM - 1], point.label))
            return true;
    }
    return false;
}
//����ѧϰ��
inline double evaluateStudy(void)
{
    int cnt = 0;
    for (int i = 0; i < NUM_TRAIN; i++)
    {
        const Point &point = TrainData[i];
        forwardPropagation(point);
        if (match(activation[LAYER_NUM - 1], point.label))
            cnt++;
    }
    return (double)cnt / NUM_TRAIN;
}
//��������Ч��
inline double evaluateModel(void)
{
    int cnt = 0;
    for (int i = 0; i < NUM_TEST; i++)
    {
        const Point &point = TestData[i];
        forwardPropagation(point);
        if (match(activation[LAYER_NUM - 1], point.label))
            cnt++;
    }
    return (double)cnt / NUM_TEST;
}
//�������
inline void showParameter(void)
{
    cout << "Ȩ��: " << endl;
    for (int i = 1; i < LAYER_NUM; i++)
        printMatrix(Weight[i]);
    cout << "ƫ����: " << endl;
    for (int i = 1; i < LAYER_NUM; i++)
        printMatrix(Bias[i]);
}
int main(void)
{
    freopen("out.txt", "w", stdout);
    clock_t start_time = clock();
    {
        readALLData(TrainData, TestData);
        Normalize(TrainData);
        Normalize(TestData);
        initialize();
        cout << "--------��ʼ������--------" << endl;
        cout << "ѧϰ��: " << step << endl;
        showParameter();
        cout << "--------��ʼ������--------" << endl
             << endl;
        int i = 0;
        while (i < iteration && mistake())
        {
            try
            {
                zeroClear(der_Weight);
                zeroClear(der_Bias);
                for (int j = 0; j < NUM_TRAIN; j++)
                {
                    forwardPropagation(TrainData[j]);
                    backPropagation(TrainData[j]);
                    accumulateDerivate();
                }
                calculateDerivate();

                gradientDescent();
            }
            catch (char const *message)
            {
                cout << message << endl;
            }
            i++;
        }
        //������
        cout << "--------ģ������--------" << endl;
        cout << "��������: " << i << endl;
        cout << "ѵ��������: " << NUM_TRAIN << endl;
        cout << "ѧϰ��: " << evaluateStudy() << endl;
        cout << "����������: " << NUM_TEST << endl;
        cout << "����Ч��: " << evaluateModel() << endl;
        cout << "����:" << endl;
        showParameter();
        cout << "--------ģ������--------" << endl
             << endl;
    }
    clock_t end_time = clock();
    cout << "--------ʱ��--------" << endl;
    cout << "��ʱ: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << 's' << endl;
    cout << "--------ʱ��--------" << endl
         << endl;
    return 0;
}
