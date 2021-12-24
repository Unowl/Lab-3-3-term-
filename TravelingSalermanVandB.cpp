#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <climits>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;
vector<vector<int>> d;
int inf = INT_MAX;
int BestWay = inf;
vector<pair<int,int>> Way;
vector<pair<int,int>> result;

void Show(vector<vector<int>> data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        for (int j = 0; j < data.size(); ++j)
        {
            if (data[i][j] == inf)
                cout << "  inf";
            else
                cout <<setw(4)<< data[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"----------------"<<endl;

}
int getResultSum()
{
	int sum = 0;
	for (int i = 0; i < result.size(); i++)
		sum += d[result[i].first - 1][result[i].second - 1];
	return sum;
}
int FindMinRow (vector<vector<int>> matrix, int sel)
{
    int Min = inf;
    for (int i = 0; i < matrix[sel].size() - 1; i++)
    {
        if (Min > matrix[sel][i])
            Min = matrix[sel][i];
    }
    return Min;
}

int FindMinCol (vector<vector<int>> matrix, int sel)
{
    int Min = inf;
    for (int i = 0; i < matrix[sel].size() - 1; i++)
    {
        if (Min > matrix[i][sel])
            Min = matrix[i][sel];
    }
    return Min;
}

void Answer (vector<vector<int>> matrix)
{
    //Определяем точку возврата и удаляем необходимое ребро

    if (matrix.size() - 1 > 2)
    {
		vector<int> vertexes;
		for (int i = 0; i < result.size(); i++) {
			vertexes.push_back(result[i].first);
			vertexes.push_back(result[i].second);
		}
		for (int i = 0; i < vertexes.size(); i++) {
			pair<int, int> elem(inf, inf), elem1(inf, inf);
			for (int j = 0; j < vertexes.size(); j++) {
				if (vertexes[i] != vertexes[j]) {
					for (int k = 0; k < matrix[matrix.size() - 1].size() - 1; k++) {
						if (vertexes[i] == matrix[k][matrix[k].size() - 1]) elem.first = k;
						if (vertexes[j] == matrix[k][matrix[k].size() - 1]) elem1.first = k;
					}
					for (int k = 0; k < matrix.size() - 1; k++) {
						if (vertexes[i] == matrix[matrix.size() - 1][k]) elem.second = k;
						if (vertexes[j] == matrix[matrix.size() - 1][k]) elem1.second = k;
					}
				}
			}
			for (int i = 0; i < matrix.size() - 1; i++)
				for (int j = 0; j<matrix.size() - 1; j++)
					if (i == elem1.first && j == elem1.second)
						matrix[elem1.first][elem1.second] = inf;
			for (int i = 0; i < matrix.size() - 1; i++)
				for (int j = 0; j < matrix.size() - 1; j++)
					if (i == elem.first && j == elem.second)
						matrix[elem.first][elem.second] = inf;
		}
	}

    //Вычитаем из каждой строки минимальное значение
    //Show(matrix);
    int Min = 0;
    for (int i = 0; i < matrix.size() - 1; i++)
    {
		int Min = FindMinRow(matrix, i);
		if (Min == inf)
		{
			//showMatrix(matrix);
			//std::cout << endl << "Bad road" << endl;
			return;
		}
		if (Min != 0)
		{
			for (int j = 0; j < matrix[i].size() - 1; j++)
			{
				if(matrix[i][j] != inf) matrix[i][j] = matrix[i][j] - Min;
            }
        }
	}
	Min = 0;
    //Вычитаем из каждого столбца минимальное значение
    for (int i = 0; i < matrix[matrix.size() - 1].size() - 1; i++)
    {
		int Min = FindMinCol(matrix, i);
		if (Min  == inf)
		{
			//showMatrix(matrix);
			//std::cout << endl << "Bad road" << endl;
			return;
		}
		if (Min != 0)
		{
			for (int j = 0; j < matrix.size() - 1; j++)
			{
				if (matrix[j][i] != inf) matrix[j][i] = matrix[j][i] - Min;
            }
        }
	}
	//Show(matrix);

	//Находим максимально оцененный ноль
    int Max = 0;
	for (int i = 0; i < matrix.size() - 1; i++)
		for (int j = 0; j < matrix[i].size() - 1; j++)
			if (matrix[i][j] == 0) {
				matrix[i][j] = inf;
				int max = (FindMinRow(matrix, i) == inf || FindMinCol(matrix, j) == inf)? inf: FindMinRow(matrix, i) + FindMinCol(matrix, j);
				if (max > Max) Max = max;
				matrix[i][j] = 0;
			}

    //Находим все нули максимальная оценка которых равна Max
	vector<pair<int, int>> Maxs;
	for (int i = 0; i < matrix.size() - 1; i++)
		for (int j = 0; j < matrix[i].size() - 1; j++)
			if (matrix[i][j] == 0)
			{
				matrix[i][j] = inf;
				int max = (FindMinRow(matrix, i) == inf || FindMinCol(matrix, j) == inf) ? inf : FindMinRow(matrix, i) + FindMinCol(matrix, j);
				if (max == Max) Maxs.push_back(pair<int, int>(matrix[i][matrix.size() - 1], matrix[matrix.size() - 1][j]));
				matrix[i][j] = 0;
			}

    //Завершаем выполнение данной ветви если нету нулей
    if (Maxs.size() == 0)
    {
		//std::cout << "Bad road." << endl;
		return;
	}
	//Show(matrix);

	for (int i = 0; i < Maxs.size(); i++)
	{
		//Добавляем вершину в массив с результатом
		result.push_back(Maxs[i]);
		//Если размер матрицы порядка 1, завершаем текущию ветвь
		if (matrix.size() - 1 == 1)
		{
		/*
			for (int i = 0; i < result.size(); i++)
				cout << "(" << result[i].first << ", " << result[i].second << ")\t";
			cout << endl;
			cout << "Result: " << getResultSum() << endl;  */
            if (getResultSum() < BestWay)
            {
                BestWay = getResultSum();
                Way = result;
            }
			result.pop_back();
			return;
		}

		//Создаем копию текущей матрицы и удаляем из нее строку и столбец выбранного нуля
		vector<vector<int>>  temp(matrix);
		pair<int, int> elem(inf, inf), elem1(inf, inf);
		for (int j = 0; j < temp[temp.size() - 1].size() - 1; j++) {
			if (Maxs[i].first == temp[j][temp[j].size() - 1]) elem.first = j;
			if (Maxs[i].second == temp[j][temp[j].size() - 1]) elem1.first = j;
		}
		for (int j = 0; j < temp.size() - 1; j++) {
			if (Maxs[i].second == temp[temp.size() - 1][j]) elem.second = j;
			if (Maxs[i].first == temp[temp.size() - 1][j]) elem1.second = j;
		}

		for(int i = 0; i < temp.size() - 1; i++)
			for(int j = 0;j<temp.size() - 1; j++)
				if(i == elem1.first && j == elem1.second)
					temp[elem1.first][elem1.second] = inf;

		for (int j = 0; j < temp[temp.size() - 1].size(); j++)
			temp[j].erase(temp[j].begin() + elem.second);
		temp.erase(temp.begin() + elem.first);
		//Вызываем рекурсивно эту же функцию для уже новой матрицы
		Answer(temp);
		//Удаляем последние значение из массива с результатом
		result.pop_back();
	}
}


int main()
{
int n;
cin>> n;
vector<vector<int>> data(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            //cin >> data[i][j];
            data[i][j] = rand() % 9 ;
            if (i == j) data[i][j] = inf;
            if (data[i][j] == 0) data[i][j] = inf;
         }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (data[i][j] == inf)
                cout << "  inf";
            else
                cout <<setw(4)<< data[i][j]<<" ";
        }
        cout<<endl;
    }

	for (int i = 0; i < data.size(); i++)
		data[i].push_back(i + 1);
	vector<int> numeration;
	for (int i = 0; i < data[0].size(); i++)
		numeration.push_back(i + 1);
	data.push_back(numeration);

d = data;
auto begin = std::chrono::steady_clock::now();
Answer(data);
if (BestWay == inf)
{

}
else
{
for (int i = 0; i < Way.size(); i++)
    cout << "(" << Way[i].first << ", " << Way[i].second << ")\t";
cout << endl;
	cout << "Result: " << BestWay << endl;
int sum = 0;
for (int i = 0; i < Way.size(); i++)
    sum += d[Way[i].first - 1][Way[i].second - 1];
if(sum == BestWay)
    cout<< "Test: Ok"<<endl;
else
    cout<< "Test: NO OK"<<endl;
}
auto end = std::chrono::steady_clock::now();
auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
int seconds = elapsed_ms.count();
cout <<"The time: "<< seconds<<" milliseconds" <<endl;
return 0;
}
