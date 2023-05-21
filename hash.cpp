#include<iostream>
#include<bits/stdc++.h>
#include<cstdlib>
#include<cstring>
#include<cstdio>

//  key   : value
//ancient :   1
using namespace std;


const int cap = 10000;
int probe=0;
int col=0;
static const char pool[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";



class Hashdata {
   public:
      string k;
      int v;

      Hashdata(string k, int v)
      {
         this->k = k;
         this->v = v;
      }
};


class HashTable
{

      //Hashdata **t;
      vector<pair<string,int>> t;
      vector<vector<pair<string, int>>> chaint;

   public:
      HashTable()
      {
         /*t = new Hashdata* [cap];
         for (int i = 0; i< cap; i++)
         {
            t[i] = NULL;
         }*/
         //chaint = new vector<pair<string,int>> [cap];
         chaint.resize(cap);
         t.resize(cap);
      }

      string getrandomKey()
      {
            //cout<<t[rand()%cap]->k;
          return t[rand()%cap].first;

      }

      int Hashf(string str)
      {
          return Hash1(str);
          //return Hash2(str);
          //return auxHash(str);

      }

      int Hash1(string str)
      {
          unsigned long val = 0;

          for (int i = 0; i < str.length() ; i++)
            val = str[i] + (val << 6) + (val << 4) - val;

          //cout<<val;
          return val%cap;

      }

      int Hash2(string str)
      {
          unsigned long val = 0;

          for (int i = 0; i < str.length() ; i++)
             val ^= (val << 5) + (val >> 2) + str[i];

          return val%cap;


      }

      int auxHash(string str)
      {
          unsigned long val = 0;

          for(int i = 0; i< str.length(); i++)
            val = 3*val+str[i];

          val %= cap;

          if(val<0) val += cap;


          return val;
      }

      int DoubleHash(string k, int i)
      {
          return (Hashf(k) + i * auxHash(k)) % cap;
          //return (Hash2(k) + i * auxHash(k)) % cap;
      }

      int Customprobe(string k,int i)
      {
          return (Hashf(k) + 3 * i * auxHash(k) + 7 * i * i) % cap;
          //return (Hash2(k) + 3 * i * auxHash(k) + 7 * i * i) % cap;
      }

      void chain_insert(string key, int value)
      {

            int h = Hashf(key);


            if (!chaint[h].empty()) col++;

            for(auto i=chaint[h].begin() ; i!=chaint[h].end() ; i++)
            {
                if (i->first != key)
                {
                    chaint[h].push_back(make_pair(key, value));
                    return;
                }

            }

      }

      void Insert(string k, int v)
      {

         int h = Hashf(k);

         while (t[h].first!="")
         {
            col++;
            if(t[h].first != k)
                h = DoubleHash(k,v);
              h = Customprobe(k,v);
         }


         t.push_back(make_pair(k, v));

      }

      void chain_search(string k)
      {
        int h = Hashf(k);


        for(auto i=chaint[h].begin() ; i!=chaint[h].end() ; i++)
        {
            probe++;
            if (i->first == k )
            {
                cout<<"  Key  :  value "<<endl;
                cout<<i->first<<" "<<i->second;
                return;
            }


        }
      }


      int Search(string k)
      {
         int h = Hashf(k);

         while (t[h].first!="" && t[h].first!= k)
         {
            probe++;
            h = Hashf(t[h + 1].first);
         }

         if (t[h].first=="")
            return -1;
         else
            return t[h].second;

      }


     /* void Remove(string k)
      {
         int h = Hashf(k);

         while (t[h].first!="")
         {
            if (t[h].first == k)
               break;
            h = Hashf(t[h + 1].first);
         }
         if (t[h].first=="")
         {
            cout<<"No Element found at key "<<k<<endl;
            return;
         }
         else {
                auto i =t[h].begin();
         t.erase(i);}

      }
*/


};
int main() {

   HashTable hash;
   string k;
   int c, v;
   //cin>>c;
   for(int i=0 ; i< cap; i++)
   {  k="";

      for(int j=0 ; j< 7; j++)
        k += pool[rand()%(sizeof(pool)-1)];

      //cout<<k<<endl;
      hash.Insert(k,i+1);
      hash.chain_insert(k,i+1);
      //cout<<col<<endl;
   }

   cout<<col;

   for(int i=0 ; i< 1000; i++)
   {
       //cout<<col;

       k = hash.getrandomKey();
        //cout<<"rand "<<k<<endl;
       hash.Search(k);
       hash.chain_search(k);
   }

   cout<<probe;



   return 0;
}

