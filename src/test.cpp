#include "hypothesis.h"
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define rep(i,a,b)	for(ll i=a;i<b;i++)

using namespace std;

vector<Hypothesis> general,specific;
vector< vector <string> > input_data[8]; 
vector< vector< string> > input_attr = readAttr();
const int num_attr = 16;
void find_target(ll k)
{
	general.clear();	specific.clear();
	general.pb(Hypothesis(num_attr,match_all));	
	specific.pb(Hypothesis(num_attr,match_none));
	//cout<<general[0]<<"          "<<specific[0]<<endl;
	for(vector<vector<string> >:: iterator it=input_data[k].begin();it!=input_data[k].end();it++)
	{
		vector<string> instance = *it,temp;	

		rep(i,0,instance.size())	if(i!=0 && i!=instance.size()-1)	temp.pb(instance[i]);
		ll target_val = atoi((instance[instance.size()-1]).c_str());
		
		//rep(i,0,temp.size())	cout<<temp[i]<<endl;
		
		if(target_val==1)
		{
			vector<Hypothesis> temp_hyp;
			
			rep(i,0,general.size())
				if(general[i].isSatisfy(temp) == target_val)		
					temp_hyp.pb(general[i]);

			general.clear();
			general=temp_hyp;
			temp_hyp.clear();

			rep(i,0,specific.size())
			{
				if(specific[i].isSatisfy(temp)== target_val)
					temp_hyp.pb(specific[i]);
				else 
				{
					vector<string> min_gen;
					rep(j,0,num_attr)
					{	
						string s= specific[i][j];
						if(s == match_none)		s=temp[j];
						else if(s!=temp[j])		s="?";
						min_gen.pb(s);
					}
					
					ll flag=0;
					if(Hypothesis(num_attr,min_gen).isSatisfy(temp)== target_val)
					{
						rep(j,0,general.size())		
							if(general[j] > Hypothesis(num_attr,min_gen)) 	
							{
								flag=1;
								break;
							}
					}
					if(flag==1)		temp_hyp.pb(Hypothesis(num_attr,min_gen));

				}
			}
			specific.clear();
			specific = temp_hyp;
		}

		else
		{
			vector<Hypothesis> temp_hyp;

			rep(i,0,specific.size())		
				if(specific[i].isSatisfy(temp) == target_val)	
					temp_hyp.pb(specific[i]);

			specific.clear();
			specific = temp_hyp;
			temp_hyp.clear();

			rep(i,0,general.size())
			{
				if(general[i].isSatisfy(temp) == target_val)	
					temp_hyp.pb(general[i]);
				else
				{
					vector<Hypothesis> temp_hyp_2;
					vector<string> min_spf;
					rep(j,0,num_attr)		min_spf.pb(general[i][j]);

					rep(j,0,num_attr)
					{
						if(min_spf[j]==match_all)
						{
							string s= temp[j];
							rep(k,0,input_attr[j].size())
							{
								if(input_attr[j][k]!=s)
								{
									min_spf[j]=input_attr[j][k];
									temp_hyp_2.pb(Hypothesis(num_attr,min_spf));
								}
							}
							min_spf[j]=match_all;
						}

						else
						{
							string s= min_spf[j];
							min_spf[j]=match_none;
							temp_hyp_2.pb(Hypothesis(num_attr,min_spf));	
							min_spf[j]=s;
						}
					}
					rep(j,0,temp_hyp_2.size())
					{
						if(temp_hyp_2[j].isSatisfy(temp) == target_val)
						{
							ll flag=0;
							rep(k,0,specific.size())
							{
								if(specific[k] < temp_hyp_2[j])
								{
									flag=1;
									break;
								}
							}
							if(flag==1)	temp_hyp.pb(temp_hyp_2[j]);
						}
					}
				}
			}
			general.clear();
			rep(i,0,temp_hyp.size())
			{
				ll flag=1;
				rep(j,0,temp_hyp.size())
				{
					if(temp_hyp[i]<temp_hyp[j])
					{
						flag=0;
						break;
					}
				}
				if(flag==1)	general.pb(temp_hyp[i]);
			}
		}
	}
}


int main()
{
	rep(i,1,8)	input_data[i]=readData();
	rep(i,1,8)	
	{
		for(vector<vector<string> >:: iterator it=input_data[i].begin();it!=input_data[i].end();it++)
		{
			ll z= atoi(((*it)[(*it).size()-1]).c_str());	
			if(z == i)	
				(*it)[(*it).size()-1]="1";
			else (*it)[(*it).size()-1]="0";
		}
	}
	rep(i,1,8)
	{	
		find_target(i);
		cout<<"Specific Hypothesis of version space "<<i<<endl;
		rep(i,0,specific.size())	cout<<specific[i]<<" ";	
		cout<<endl;
		cout<<"General Hypothesis of version space "<<i<<endl;
		rep(i,0,general.size())		cout<<general[i]<<" ";
		cout<<endl<<endl<<endl;
	}//cerr<<"Done";
	return 0;
}