#include<iostream>
#include<cmath>
class point{
public:
double x;
double y;
};
int getMatrixElimination(double ** matrix,int i,int j,int rows,int columns);
int getDeterminant(double ** matrix,int rows,int columns){
if(rows==2 && columns==2){
    return (matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]);
}
int sum=0;
for(int i=0;i<columns;i++){
   sum+=pow(-1,i)*matrix[0][i]*getMatrixElimination(matrix,0,i,rows,columns);
}
return sum;
}
int getMatrixElimination(double ** matrix,int rowEliminate,int columnEliminate,int rows,int columns){
    double **newMatrix=new double*[rows-1];
    for(int i=0;i<rows-1;i++){
        newMatrix[i]=new double[columns-1];
    }
    int newI=0;
    int newJ=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          if(i!=rowEliminate && j!=columnEliminate){
            newMatrix[newI][newJ]=matrix[i][j];
            newJ++;
            if(newJ==columns-1){
                newJ=0;
                newI++;
            }
          }
        }
    }
    return getDeterminant(newMatrix,rows-1,columns-1);
};
double ** substitude(double** A,int x,int rows,int columns,double* B){
double** Ai=new double*[rows];
for(int i=0;i<rows;i++){
    Ai[i]=new double[columns];
}
for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
        Ai[i][j]=A[i][j];
    }
}
for(int i=0;i<rows;i++){
    Ai[i][x]=B[i];
}
return Ai;
}
// the answers of xi is saved into 1D array that returned by function
//Xi=|Ai|/|A|
double * solveLinearSystemEquationsUsingCramersRule(double **A,double *B,
int rowsOfA,int columnsOfA){
    if(getDeterminant(A,rowsOfA,columnsOfA)==0){
        throw "this system doesnt have an answer or have an infinity naswers";
    }
    double* answers=new double[columnsOfA];

for(int i=0;i<columnsOfA;i++){
    double **Ai=substitude(A,i,rowsOfA,columnsOfA,B);
    answers[i]=getDeterminant(Ai,rowsOfA,columnsOfA)/
    getDeterminant(A,rowsOfA,columnsOfA);
}
return answers;
}
double * curveFitting(point * points,int size){
double** coefficients=new double*[size];
for(int i=0;i<size;i++){
    coefficients[i]=new double[size];
}
for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
        coefficients[i][j]=pow(points[i].x,size-j-1);
    }
}
double* B=new double[size];
for(int i=0;i<size;i++){
    B[i]=points[i].y;
}
double* answers=solveLinearSystemEquationsUsingCramersRule(coefficients,
B,size,size);
return answers;
}
int main(int length,char* args[]){
int numberOfPoints=0;
std::cout<<"enter number of points";
std::cin>>numberOfPoints;
point * points=new point[numberOfPoints];
int i=1;
while (i<=numberOfPoints)
{
    std::cout<<"enter point"<<i<<" its x and y respectively\n";
    std::cin>>points[i-1].x>>points[i-1].y;
    i++;
}
double *answers;
try{
 answers=curveFitting(points,numberOfPoints);
}catch(const char* x){
    std::cout<<x;
    return 0;
}
char x='a';
for(int i=0;i<numberOfPoints;i++){
    std::cout<<x<<"="<<answers[i]<<"\t";
    x++;
}
return 0;
}