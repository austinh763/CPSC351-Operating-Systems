#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<list>

using namespace std;


class process{
public:
  int id =0;
  int arrive=0;
  int done=0;
  int alive=0;
  int memory=0;
};
queue<process> setqueue(vector<process> b){
  vector<process> input =b;
  queue<process> l = {};

  for(int i=0;i<input.size();++i){
    process a;
    a.id = input.at(i).id;
    a.arrive = input.at(i).arrive;
    a.done = input.at(i).done;
    a.alive = input.at(i).alive;
    a.memory = input.at(i).memory;
    l.push(a);
  }

  return l;

}




vector<process> pop_front(vector<process> b){
    process a;
    vector<process> s = b;
    vector<process> d={};
    for(int i=1;i<s.size();i++){
      a.id = b.at(i).id;
      a.arrive = b.at(i).arrive;
      a.done = b.at(i).done;
      a.alive = b.at(i).alive;
      a.memory = b.at(i).memory;

      d.push_back(a);
    }
    return d;

}


void printinput(vector<process> a){
  vector<process> s = a;
  int num_pro = s.size();
      if(num_pro == 1){
      cout << "Input queue: [" << s.at(0).id << "]" << endl;
    }
    else if(num_pro == 2){
      cout << "Input queue: [" << s.at(0).id << " " << s.at(1).id << "]" << endl;
    }
    else if(num_pro == 3){
      cout << "Input queue: [" << s.at(0).id << " " << s.at(1).id << " "<< s.at(2).id << "]" << endl;
    }
    else if(num_pro == 0){
      cout << "Input queue: [   ]" << endl;
    }


}

vector<process> vectset(int a[],int size){
  vector<process> c;

  int increment =4;
    for(int i =1;i<size;i+=increment){
      process s;
      s.id = a[i];
      s.arrive = a[i+1];
      s.done = a[i+2];
      s.alive = -1; // was 0
      int n = a[i+3];
      int e =n;

        while(n > 0){
            s.memory += a[(i+3)+n];
            n--;
        }
        i = i+e;

        c.push_back(s);
      }

      return c;

}

int total_mem(){
  int tot_mem=0;
  cout << " how much mem needed " << endl;
  cin >> tot_mem;
  return tot_mem;

}

int selection(){
  int choice = 0;
  cout << " mem scheme " << endl;
  cin >> choice;
  if ( choice == 1){
    choice = 100;
  }
  else if(choice == 2){
    choice = 200;
  }
  else{
    choice = 400;
  }

  return choice;
}


vector<process> inputset(vector<process> a,int r,bool wait,vector<process> input){

  int time = r;
  vector<process> in = input;
  int start = in.size();

  bool w = wait;
  vector<process> b=a;
    vector<process> place = {};

    if(start == 0){
  for(int i = 0; i < b.size()-1;i++){
      process a;


      if(b.at(i).arrive == time){
        cout << "t = " << time << " Process " << b.at(i).id << " arrives " << endl;
        a.id = b.at(i).id;
        a.arrive = b.at(i).arrive;
        a.done = b.at(i).done;
        a.alive = b.at(i).alive;
        a.memory = b.at(i).memory;
        place.push_back(a);

        printinput(place);
      }
      else{}

}
}/////////
else if(start>0){
    for(int i =0;i<b.size()-1;i++){
      process a;

      if(b.at(i).arrive == time){

        cout << "t = " << time << "Process " << b.at(i).id << " arrives " << endl;
        a.id = b.at(i).id;
        a.arrive = b.at(i).arrive;
        a.done = b.at(i).done;
        a.alive = b.at(i).alive;
        a.memory = b.at(i).memory;
        place.push_back(a);
    }
  }
//  cout << " setting input " << endl;
  for(int i =0;i<place.size();i++){
    process val;
    val.id = place.at(i).id;
    val.arrive = place.at(i).arrive;
    val.done = place.at(i).done;
    val.alive = place.at(i).alive;
    val.memory = place.at(i).memory;
    in.push_back(val);

  }
  return in;
}

  return place;
}

bool check_mem(int a[],int mem,int choice,int size){
    int m = mem;
    int s = size;
    int c = choice;
    int hold =0 ;
    int tracker=0;
    if(mem%choice != 0){
      hold = choice - (mem%choice);
      m = m+hold;


    }
    else{ }


    for(int i =0; i < s;++i){
      if(a[i]==0){
        tracker++;
      }
      else{}

    }

    if(tracker>=m){
      return true;

    }
    else{
      return false;

    }


}

vector<process> update_alive(vector<process> a){

  vector<process> b = a;
  for(int i=0;i<b.size()-1;i++){

    if(b.at(i).alive>=0){
    b.at(i).alive +=100;

  }
  else{}
  }

  return b;
}

list<string> update_list(list<string> st,string f, int id){

  list<string> s=st;
  int keep_track = 0;
  string l=f;
  int d = id;
  string j = to_string(d);
  string g;
  list<string>:: iterator it;
  for (it=s.begin();it!=s.end();it++){
    g = *it;

    string a = g.substr(g.find("e")+4,j.length());

    if(a!=j){a="0";}
    int check = stoi(a);

    if(check == d && keep_track==0){
      s.insert(it,l);
      it = s.erase(it);
      it--;
      keep_track++;
    }

  }
  return s;
}

list<string> update_ls(list<string> st,string f,int id,int pages){

  list<string> a = st;
  list<string>:: iterator it;
  string g=f;
  int d=id;
  int page = pages;
  int mutex = 0;

        for(it=a.begin();it!=a.end();it++){
        string h = *it;

          string k = h.substr(h.find(" "));

          if((" Free Frames"==k)&&(mutex==0)){

          mutex++;
            string place = h;
            string t = g;
            string lo = place.erase(place.find(" "));
            lo = lo.erase(lo.find("-"));
            string hi = place.substr(place.find("-")+1);


            string low = t.erase(t.find(" "));
            low = low.erase(low.find("-"));
            string high = t.substr(t.find("-")+1);

            int l = stoi(lo);
            int h = stoi(hi);
            int hg = stoi(high);
            int lw = stoi(low);
            if(h == hg){

              string pro = to_string(lw)+"-"+to_string(hg)+" Process " + to_string(d)+", page " + to_string(d);
              a.insert(it,pro);
              it = a.erase(it);
              it--;
            }
            else{

              l = hg+1;
              string pro = to_string(lw)+"-"+to_string(hg)+" Process " + to_string(d)+", page " + to_string(d);
              string free = to_string(l)+"-"+to_string(h)+" Free Frames";
              a.insert(it,pro);
              a.insert(it,free);
              it= a.erase(it);
              it--;
            }
          }
        }

          return a;
}

int main(){

    int time = 0;
    double average = 0;
    int tot_mem = total_mem();
    int process_total = 0;

    int choice = selection();

    string filename;
    string line;

    int memory[tot_mem]={};

      cout << " which file " << endl;
      cin >> filename;

      int count = 0;
      int a[44]={};


      ifstream myf(filename);

      if(myf.is_open()){
        while(!myf.eof()){
          myf >> a[count];
          count++;
        }
        myf.close();
      }

      else
        cout << "can not open file " << endl;



      int pro_num = a[0];
      int size = *(&a+1)-a;


      vector<int> p = {};
      vector<process> b = vectset(a,size);
      vector<process> input;
      queue<process> l;
      int n = 0;
      int mem_size = 0;
      int ui =0;
      int lo=0;

      int complete_pro =0;
      list<string> st;
      st.push_back("0-1999 Free Frames");
      list<string> complete;
      list<string> free_frames;
      list<string>:: iterator it;
      bool in_wait = 1;///////////////////////////////////////////

      while(time<100000 && pro_num>1){
input= inputset(b,time,in_wait,input);

        l = setqueue(input);

        bool check=check_mem(memory,l.front().memory,choice,tot_mem);
        in_wait = check;/////////////////////////
        bool only_one = 1;


        if(check ==0){}
        else{
        while((only_one==true)&&(!l.empty())){ //!l.empty()
          int mem_copy =0;
          if(l.front().memory%choice !=0){
            mem_copy= l.front().memory + (choice - (l.front().memory%choice));
          }
          else{mem_copy=l.front().memory;}
          input = pop_front(input);
          b.at(l.front().id-1).arrive =0;

        cout << " MM moves process " << l.front().id << " into memory " << endl;
        b.at(l.front().id-1).alive =0;

        int lo=0;
        int hi=0;
        int pages = 1;

        while(pages<(mem_copy/choice)+1){
          int keep =0;

          for(int i =hi ; i < tot_mem+1;i++){
            if(keep==0 && memory[i]==0){
              memory[i]=l.front().id;


              lo = i;

              keep++;
            }
            else if(keep==choice){

              hi = i;
              string f = to_string(lo) + "-" + to_string(hi-1) + " process " + to_string(l.front().id) + ", Page " + to_string(pages);

              st=update_ls(st,f,l.front().id,pages);
              for(it=st.begin();it!=st.end();it++){
                cout << *it << endl;
              }


              break;
            }
            else if(memory[i]==0){
              memory[i]=l.front().id;
              keep++;
            }
          }
          pages++;

        }
        printinput(input);


        l.pop();
        only_one = check_mem(memory,l.front().memory,choice,tot_mem);

      }
    }

        pro_num++;
        time+=100;
        b=update_alive(b);

        for(int i =0;i < b.size()-1;++i){
          int page_done = 1;
          //  int low_bound = 0;
            int high_bound = 0;


          if(b.at(i).done == b.at(i).alive){
            process_total++;
            average += b.at(i).alive;
            cout << "t = " << time << " Process " << b.at(i).id << " done executing " << endl;
            int mem_done = 0;

            int id = b.at(i).id;

            if(b.at(i).memory%choice !=0){
              mem_done = b.at(i).memory + (choice - (b.at(i).memory%choice));
            }
            else{mem_done =b.at(i).memory;}

            while(page_done< (mem_done/choice)+1){
              int keep_done =0;
              int low_bound=0;

              for(int i = high_bound;i < tot_mem+1;i++){

                if(low_bound == 0 && memory[i]==id ){
                  memory[i]=0;
                  low_bound = i;
                  keep_done++;
                }
                else if(keep_done == choice){
                  high_bound = i;

                  break;
                }
                else if(memory[i] == id){
                  memory[i] =0;
                  keep_done++;

                }

              }
              string f = to_string(low_bound) + "-" + to_string(high_bound-1) + " Free Frames";
              st=update_list(st,f,id);
              page_done++;
            }

         for(it=st.begin();it!=st.end();it++){
            cout << *it << endl;
          }
          }

        }
        vector<process> place_holder = input;

      }

average = average / process_total;
cout << endl << endl << "Average Turnaround Time: " << average << endl;

return 0;
}