#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

ifstream fin("TextFile1.txt");

void sortareCorecta(int const v[], int const nrElemente)
{
    for (int i = 0; i < nrElemente - 1; i++)
        if (v[i] > v[i + 1])
        {
            cout << "Sortare incorecta! :(" << endl;
            return;
        }
    cout << "Sortare corecta! :)" << endl;


}

//MergeSort
void merge(int vector[], int const st, int const mij, int const dr)
{
    int const miniVector1 = mij - st + 1;
    int const miniVector2 = dr - mij;

    int* vectorDr = new int[miniVector1],
        * vectorSt = new int[miniVector2];

    for (auto i = 0; i < miniVector1; i++)
        vectorDr[i] = vector[st + i];
    for (auto j = 0; j < miniVector2; j++)
        vectorSt[j] = vector[mij + 1 + j];

    int pozitieVector1 = 0, pozitieVector2 = 0, pozitieVectorFinal = st; 

    
    while (pozitieVector1 < miniVector1 && pozitieVector2 < miniVector2) {
        if (vectorDr[pozitieVector1] <= vectorSt[pozitieVector2]) {
            vector[pozitieVectorFinal] = vectorDr[pozitieVector1];
            pozitieVector1++;
        }
        else {
            vector[pozitieVectorFinal] = vectorSt[pozitieVector2];
            pozitieVector2++;
        }
        pozitieVectorFinal++;
    }
    
    while (pozitieVector1 < miniVector1) {
        vector[pozitieVectorFinal] = vectorDr[pozitieVector1];
        pozitieVector1++;
        pozitieVectorFinal++;
    }
    
    while (pozitieVector2 < miniVector2) {
        vector[pozitieVectorFinal] = vectorSt[pozitieVector2];
        pozitieVector2++;
        pozitieVectorFinal++;
    }
}


void mergeSort(int vector[], int const inc, int const sf)
{
    if (inc >= sf)
        return; 

    auto mij = inc + (sf - inc) / 2;
    mergeSort(vector, inc, mij);
    mergeSort(vector, mij + 1, sf);
    merge(vector, inc, mij, sf);
}

auto timp_MergeSort(int const vector[], int const nrElemente)
{

    int *vectorSortat = new int[nrElemente]; 
    for (int i = 0; i < nrElemente; i++)
        vectorSortat[i] = vector[i]; 
    
    auto begin = std::chrono::high_resolution_clock::now();

    mergeSort(vectorSortat, 0, nrElemente - 1);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    sortareCorecta(vectorSortat, nrElemente); 

    delete[] vectorSortat; 

    return elapsed.count(); 
}

//ShellSort
void shellSort(int vector[], int nrElemente)
{
    for (int interval = nrElemente / 2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < nrElemente; i += 1)
        {
            int aux = vector[i];

            int j;
            for (j = i; j >= interval && vector[j - interval] > aux; j -= interval)
                vector[j] = vector[j - interval];

            vector[j] = aux;
        }
    }
}

auto timp_ShellSort(int const vector[], int const nrElemente)
{
    int* vectorSortat = new int[nrElemente];
    for (int i = 0; i < nrElemente; i++)
        vectorSortat[i] = vector[i];

    auto begin = std::chrono::high_resolution_clock::now();

    shellSort(vectorSortat, nrElemente);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    sortareCorecta(vectorSortat, nrElemente);

    delete[] vectorSortat;

    return elapsed.count();
}
//RadixSort
int valoareBit(int const nr, int const bit)
{
    int masca = 1 << bit; 
    if ((nr & masca) != 0)
        return 1; 
    return 0; 
}

void countingSort(int vector[], int const nrElemente, int bit)
{
    int numarare[2] = { 0, 0 };
    for (int i = 0; i < nrElemente; i++)
        numarare[valoareBit(vector[i], bit)]++;

    int indici[2] = { 0, numarare[0] };
    int* vectorSortat = new int[nrElemente];

    for (int i = 0; i < nrElemente; i++)
    {
        int valoareBitElement = valoareBit(vector[i], bit);
        vectorSortat[indici[valoareBitElement]] = vector[i];
        indici[valoareBitElement]++;
    }

    for (int i = 0; i < nrElemente; i++)
        vector[i] = vectorSortat[i];

    delete[] vectorSortat;


}

void radixSort(int vector[], int const nrElemente)
{
    for (int iBit = 0; iBit < 64; iBit++)
        countingSort(vector, nrElemente, iBit);
}

auto timp_RadixSort(int const vector[], int const nrElemente)
{
    int* vectorSortat = new int[nrElemente];
    for (int i = 0; i < nrElemente; i++)
        vectorSortat[i] = vector[i];

    auto begin = std::chrono::high_resolution_clock::now();

    radixSort(vectorSortat, nrElemente);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    sortareCorecta(vectorSortat, nrElemente);

    delete[] vectorSortat;

    return elapsed.count();
}



//QuickSort
void swap(int &a, int &b)
{
    int aux = a;
    a = b;
    b = aux;
}

int partition(int vector[], int low, int high)
{
    int pivot = vector[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++)
    {
        if (vector[j] < pivot)
        {
            i++; 
            swap(vector[i], vector[j]);
        }
    }
    swap(vector[i + 1], vector[high]);
    return (i + 1);
}

void quickSort(int vector[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(vector, low, high);

        quickSort(vector, low, pivot - 1);
        quickSort(vector, pivot + 1, high);
    }
}

auto timp_QuickSort(int const vector[], int const nrElemente)
{
    int* vectorSortat = new int[nrElemente];
    for (int i = 0; i < nrElemente; i++)
        vectorSortat[i] = vector[i];

    auto begin = std::chrono::high_resolution_clock::now();

    quickSort(vectorSortat, 0, nrElemente - 1);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    sortareCorecta(vectorSortat, nrElemente);

    delete[] vectorSortat;

    return elapsed.count();
}

//HeapSort 
void heapify(int vector[], int nrElemente, int i)
{
    int mx = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 

    if (l < nrElemente && vector[l] > vector[mx])
        mx = l;

    if (r < nrElemente && vector[r] > vector[mx])
        mx = r;

    if (mx != i) {
        swap(vector[i], vector[mx]);

        heapify(vector, nrElemente, mx);
    }
}

void heapSort(int vector[], int nrElemente)
{
   
    for (int i = nrElemente / 2 - 1; i >= 0; i--)
        heapify(vector, nrElemente, i);

    for (int i = nrElemente - 1; i > 0; i--) {
        swap(vector[0], vector[i]);
        heapify(vector, i, 0);
    }
}

auto timp_HeapSort(int const vector[], int const nrElemente)
{
    int* vectorSortat = new int[nrElemente];
    for (int i = 0; i < nrElemente; i++)
        vectorSortat[i] = vector[i];

    auto begin = std::chrono::high_resolution_clock::now();

    heapSort(vectorSortat, nrElemente);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    sortareCorecta(vectorSortat, nrElemente);

    delete[] vectorSortat;

    return elapsed.count();
}


int main()
{
	srand(time(0));

	int nrTeste;
	fin >> nrTeste;

	for (int test = 1; test <= nrTeste; test++)
	{
		int nrNumere, nrMaxim;
		fin >> nrNumere >> nrMaxim;

		cout << "Testul " << test << " -------------------------------------------------------------------" << endl << "Numarul de numere este " << nrNumere << "      " << "Numarul maxim este " << nrMaxim << endl;

		int* numereRandom = new int[nrNumere]; 
		for (int i = 0; i < nrNumere; i++)
			numereRandom[i] = rand() % nrMaxim; 

        //MergeSort
        cout << endl << "MergeSort: " << endl;
        if (nrNumere >= 100000000) 
            cout << "Numarul de elemente este prea mare. Nu poate sorta!" << endl; 
        else
            cout << "Timpul de executie a fost " << timp_MergeSort(numereRandom, nrNumere) << " ns" << endl;

		//ShellSort
        cout << endl << "ShellSort: " << endl;
        cout << "Timpul de executie a fost " << timp_ShellSort(numereRandom, nrNumere) << " ns" << endl;

         //RadixSort
        cout << endl << "RadixSort: " << endl;
        cout << "Timpul de executie a fost " << timp_RadixSort(numereRandom, nrNumere) << " ns" << endl;

        //QuickSort 
        cout << endl << "QuickSort: " << endl;
        if(nrNumere >= 10000000)
            cout << "Numarul de elemente este prea mare. Nu poate sorta!" << endl;
        else
            cout << "Timpul de executie a fost " << timp_QuickSort(numereRandom, nrNumere) << " ns" << endl;

        //HeapSort
        cout << endl << "HeapSort: " << endl;
        cout << "Timpul de executie a fost " << timp_HeapSort(numereRandom, nrNumere) << " ns" << endl << endl << endl; 
        
		delete[] numereRandom;
	

	} 
}