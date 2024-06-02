
#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;

#define edge pair<int, int>



//Finding the source node - finding the nearest hospital from the patient
int findShort(double userPoint_x, double userPoint_y, vector<double> listLocation_x,vector<double> listLocation_y, int n)
{
    int i, dist=0, min=10000, min_Index;
    for(i=0;i<n; i++){
        dist=sqrt((pow((listLocation_x[i] - userPoint_x),2)) + (pow((listLocation_y[i] - userPoint_y),2)));
        if(dist<min){
            min=dist;
            min_Index=i;
            //cout<<dist<<"\n";
        }
    }
    //return 
    //cout<<min<<"\n";
    return min_Index;
}



//kruskal algorithm- creating graph 
class Graph {
   private:
  vector<pair<double, edge> > G;  // graph
  vector<pair<double, edge> > T;  // mst
  int *parent;
  int V;  // number of vertices/nodes in graph
  public:
  Graph(int V);
  void AddWeightedEdge(int u, int v, double w);
  int find_set(int i);
  void union_set(int u, int v);
  void kruskal();
  void print();
};
Graph::Graph(int V) {
  parent = new int[V];

  //i 0 1 2 3 4 5
  //parent[i] 0 1 2 3 4 5
  for (int i = 0; i < V; i++)
    parent[i] = i;
 
  G.clear();
  T.clear();
}
void Graph::AddWeightedEdge(int u, int v, double w) {
  G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
  // If i is the parent of itself
  if (i == parent[i])
    return i;
  else
    // Else if i is not the parent of itself
    // Then i is not the representative of his set,
    // so we recursively call Find on its parent
    return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
  parent[u] = parent[v];
}
void Graph::kruskal() {
  int i, uRep, vRep;
  sort(G.begin(), G.end());  // increasing weight
  for (i = 0; i < G.size(); i++) {
    uRep = find_set(G[i].second.first);
    vRep = find_set(G[i].second.second);
    if (uRep != vRep) {
      T.push_back(G[i]);  // add to tree
      union_set(uRep, vRep);
    }
  }
}
void Graph::print() {
  cout << "Edge :"
     << " Weight" << endl;
  for (int i = 0; i < T.size(); i++) {
    cout << T[i].second.first << " - " << T[i].second.second << " : "
       << T[i].first;
    cout << endl;
    //cout<<T[i].first;
  }
}


//Finding the distance between the two hospitals to make weighted Graph
double distancePoint(double x1,double y1,double x2,double y2)
{
    double d=0.0;
    d=sqrt((pow((x2-x1),2)) + (pow((y2 - y1),2)));
    return d;
}


//Alloting bed according to the financial condition
class Bed {
    public:
    Bed(vector<int> b);
    vector<int> availableBed;
    string finance(int amount);
    void available_Bed(int amt,vector<int> bedCount);
    
};
Bed :: Bed(vector<int> b){
}
string Bed::finance(int amount)
{
    if(amount > 16)
        return "Rich";
    else if(amount>7 && amount<=16)
        return "Middle";
    else if(amount>2 && amount <= 7)
        return "Lower_Middle";
    else
        return "Poor";
}
void Bed :: available_Bed(int amt,vector<int> bedCount){
    cout<<"\n No of Beds available for the patient \n";
    cout<<"\n Hospital Id - Bed Count"<<"\n";
    for(int i=0;i<bedCount.size();i++)
    {
        if(finance(amt)=="Poor"){
          cout<<i<<"                   "<< int(.4*(bedCount[i]))<<"\n";
          //availableBed.insert(availableBed.begin()+i,int(.4*(bedCount[i])));
        }
        if(finance(amt)=="Lower_Middle")
        {
          cout<<i<<"                   "<< int(.3*(bedCount[i]))<<"\n";
          //availableBed.insert(availableBed.begin()+i,int(.3*(bedCount[i])));
        }
        if(finance(amt)=="Middle")
        {
          cout<<i<<"                   "<< int(.2*(bedCount[i]))<<"\n";
          //availableBed.insert(availableBed.begin()+i,int(.2*(bedCount[i])));
        }
        if(finance(amt)=="Rich")
        {
          cout<<i<<"                   "<< int(.1*(bedCount[i]))<<"\n";
          //availableBed.insert(availableBed.begin()+i,int(.1*(bedCount[i])));
        }
    }
}

//specialization of Hospital available
int specification(vector<vector<int>> v, int n){
    cout<<"Hospital id with this specializations are \n";
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            if(v[i][j]==n)
            {
                cout<<i<<"\n";
            }
        } 
    }	
}

//printing all specializations of Hospital
int prints(){
    vector<string> st={" ","ENT","Cancer","Cardiologist","Oncology","Neurosurgery","Colorectal_Surgery","ICU","Accident","Orthopedics","Emergency_Medicine","Gastroenterology","Urology","Dermatology","Neuroradiology","Osteology","Rheumatology","Radiology","Pulmonology","Geriatrics","Endocrinology","Hepatology","Cardio_oncologists"};
    cout<<"The list for specializations are as follows \n";
    for(int i=0;i<st.size();i++){
        cout<<i<<"  -  "<<st[i]<<"\n";
    }
}

//main
int main() {
  vector<double> a={24.4768525,25.4803247,26.4800535,27.5138178,28.5200737,29.512659,21.5126734,22.5230754,21.5260363,30.5237496,31.5710205,33,33.5396709,34.5395592,35.5391902,36.5397473,37.4942466,25.59756};
  vector<double> b={89.4014977,87.3971269,87.3979611,87.3750175,87.3555012,87.3532501,87.3508145,87.3395323,92.3421313,91.3405603,90.337153,96,87.3051791,87.3002118,87.2984089,87.2893106,87.2952444,90.7837913};
  vector<int> bedCount={96,45,87,56,12,77,88,54,66,98,32,78,12,45,85,32,74,55};
  vector<vector<int>> special={ {1,5,7,9,22},{9,6,8,7,3},{21,19,17,15},{13,11,9,7},{5,3,1,7},{2,4,6,8},{10,12,14,16},{18,20,22,13},{9,5,7,8},{3,4,6,1,15},{11,22,15,13,19},{21,3,4,6,4},{1,4,5,6},{7,5,6,3,1},{11,2,7,18},{13,15,17,19},{22,1,21,20},{7,8,5,4} };
  //double x=25.5612, y= 87.7897;
  double x,y;
  int amt, q;
  cout<<"Enter the latitude of patient manually \n";
  cin>>x;
  cout<<"Enter the latitude of patient manually \n";
  cin>>y;
  cout<<"Enter your average income per annum in lakhs in digit  ";
  cin>>amt;
  int i,j, n=18;
  int ind;
  auto start = high_resolution_clock::now();
  // calling graph 
  Graph g(n);
  ind=findShort(x,y,a,b,n);
  for(i=0;i<=17;i++){
      for(j=1;j<=17;j++){
        if(i==0){
            g.AddWeightedEdge(ind,j,distancePoint(a[ind],b[ind],a[j],b[j]));
        }
        else{
            //cout<<a[i]<<"  "<<a[j]<<distancePoint(a[i],b[i],a[j],b[j])<<"\n";;
            g.AddWeightedEdge(i,j,distancePoint(a[i],b[i],a[j],b[j]));
        }
      }
  }
  g.kruskal();
  g.print();
  Bed v(bedCount);
  v.available_Bed(amt,bedCount);
  prints();
  cout<<"\n What specialization you are searching for? Enter the specialization no from list  ";
  cin>>q;
  specification(special,q);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout<<"\n HOPE YOU FOUND YOUR BED... STAY WITH US FOR MORE UPCOMING RESEARCH PAPERWORK \n  All these code is done with C++ and the Output shows how hospital bed is alloted in step by step";
  cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
  return 0;
}
