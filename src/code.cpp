#include "hypothesis.h"
#include <bits/stdc++.h>


using namespace std;

vector<Hypothesis> general,specific;
pair< vector<Hypothesis>, vector<Hypothesis> > boundary[8];
vector< vector <string> > input_data[8]; 
vector< vector< string> > input_attr = readAttr();
const int num_attr = 16;

void find_target(int idx)
{
	general.clear();	specific.clear();
	general.push_back(Hypothesis(num_attr,match_all));	
	specific.push_back(Hypothesis(num_attr,match_none));
	//cout<<general[0]<<"          "<<specific[0]<<endl;
	for(vector<vector<string> >:: iterator it=input_data[idx].begin();it!=input_data[idx].end();it++)
	{
		vector<string> instance = *it,temp;	

		for(int i=0;i<instance.size();i++)	if(i!=0 && i!=instance.size()-1)	temp.push_back(instance[i]);
		int target_val = atoi((instance[instance.size()-1]).c_str());
		
		//rep(i,0,temp.size())	cout<<temp[i]<<endl;
		
		if(target_val==1)
		{
			vector<Hypothesis> temp_hyp;
			
			for(int i=0;i<general.size();i++)
				if(general[i].isSatisfy(temp) == target_val)		
					temp_hyp.push_back(general[i]);

			general.clear();
			general=temp_hyp;
			temp_hyp.clear();

			for(int i=0;i<specific.size();i++)
			{
				if(specific[i].isSatisfy(temp)== target_val)
					temp_hyp.push_back(specific[i]);
				else 
				{
					vector<string> min_gen;
					for(int j=0;j<num_attr;j++)
					{	
						string s= specific[i][j];
						if(s == match_none)		s=temp[j];
						else if(s!=temp[j])		s="?";
						min_gen.push_back(s);
					}
					
					int flag=0;
					if(Hypothesis(num_attr,min_gen).isSatisfy(temp)== target_val)
					{
						for(int j=0;j<general.size();j++)		
							if(general[j] > Hypothesis(num_attr,min_gen)) 	
							{
								flag=1;
								break;
							}
					}
					if(flag==1)		temp_hyp.push_back(Hypothesis(num_attr,min_gen));

				}
			}
			specific.clear();
			specific = temp_hyp;
		}

		else
		{
			vector<Hypothesis> temp_hyp;

			for(int i=0;i<specific.size();i++)		
				if(specific[i].isSatisfy(temp) == target_val)	
					temp_hyp.push_back(specific[i]);

			specific.clear();
			specific = temp_hyp;
			temp_hyp.clear();

			for(int i=0;i<general.size();i++)
			{
				if(general[i].isSatisfy(temp) == target_val)	
					temp_hyp.push_back(general[i]);
				else
				{
					vector<Hypothesis> temp_hyp_2;
					vector<string> min_spf;
					for(int j=0;j<num_attr;j++)		min_spf.push_back(general[i][j]);

					for(int j=0;j<num_attr;j++)
					{
						if(min_spf[j]==match_all)
						{
							string s= temp[j];
							for(int k=0;k<input_attr[j].size();k++)
							{
								if(input_attr[j][k]!=s)
								{
									min_spf[j]=input_attr[j][k];
									temp_hyp_2.push_back(Hypothesis(num_attr,min_spf));
								}
							}
							min_spf[j]=match_all;
						}

						else
						{
							string s= min_spf[j];
							min_spf[j]=match_none;
							temp_hyp_2.push_back(Hypothesis(num_attr,min_spf));	
							min_spf[j]=s;
						}
					}
					for(int j=0;j<temp_hyp_2.size();j++)
					{
						if(temp_hyp_2[j].isSatisfy(temp) == target_val)
						{
							int flag=0;
							for(int k=0;k<specific.size();k++)
							{
								if(specific[k] < temp_hyp_2[j])
								{
									flag=1;
									break;
								}
							}
							if(flag==1)	temp_hyp.push_back(temp_hyp_2[j]);
						}
					}
				}
			}
			general.clear();
			for(int i=0;i<temp_hyp.size();i++)
			{
				int flag=1;
				for(int j=0;j<temp_hyp.size();j++)
				{
					if(temp_hyp[i]<temp_hyp[j])
					{
						flag=0;
						break;
					}
				}
				if(flag==1)	general.push_back(temp_hyp[i]);
			}
		}
	}
	boundary[idx]= make_pair(specific,general);
}


int main()
{
	for(int i=1;i<8;i++)	input_data[i]=readData();
	for(int i=1;i<8;i++)
	{
		for(vector<vector<string> >:: iterator it=input_data[i].begin();it!=input_data[i].end();it++)
		{
			int z= atoi(((*it)[(*it).size()-1]).c_str());	
			if(z == i)	
				(*it)[(*it).size()-1]="1";
			else (*it)[(*it).size()-1]="0";
		}
	}
	for(int i=1;i<8;i++)
	{	
		find_target(i);
		cout<<"Specific Hypothesis of version space "<<i<<endl;
		for(int i=0;i<specific.size();i++)	cout<<specific[i]<<" ";	
		cout<<endl;
		cout<<"General Hypothesis of version space "<<i<<endl;
		for(int i=0;i<general.size();i++)		cout<<general[i]<<" ";
		cout<<endl<<endl<<endl;
	}
	return 0;
}