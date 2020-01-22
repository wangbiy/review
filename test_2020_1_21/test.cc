#include <iostream>
using namespace std;
#include <vector>
#include <unordered_map>
#include <string>
class Solution 
{
	public:
		//移除掉所有为val的元素，不能创建新的数组，在原地移除，使用快慢指针
		int removeElement(vector<int>& nums, int val)
		{
			int i=0;
			for(int j=0;j<nums.size();++j)
			{
				if(nums[j]!=val)
				{
					nums[i]=nums[j];
					i++;
				}
			} 
			return i;
		}
		//搜索指定元素
		int searchInsert(vector<int>& nums, int target) 
		{
			int left=0;
			int right=nums.size()-1;
			while(left<=right)
			{
				int mid=left+(right-left)/2;
				if(nums[mid]==target)
					return mid;
				else if(target>nums[mid])
				{
					left=mid+1;
				}
				else
				{
					right=mid-1;
				}
			} 
			return left;  
		}
		//赎金信问题（杂志字符串是否可以组成ransomNote字符串）
		bool canConstruct(string ransomNote, string magazine)    
		{
			unordered_map<char,int> map(26);//int表示字符个数
			for(int i=0;i<magazine.size();++i)
			{
	            ++map[magazine[i]];
	        }
			for(int j=0;j<ransomNote.size();++j)
			{
				--map[ransomNote[j]];
				if(map[ransomNote[j]]<0)
					return false;
			} 
			return true;
		}
		//回文数问题
		bool isPalindrome(int x)
		{
			if(x<0)
				return false;
			long result=0;
			int ret=x;
			while(x!=0)
			{
				//逆转，判断与原数是否相同
				int tmp=x%10;
				x/=10;
				result=result*10+tmp;
			}
			if(result==ret)
				return true;
			else
				return false;
		}

};
int main()
{
	Solution s;
	vector<int> nums{3,1,1,3};
	int count=s.removeElement(nums,3);
	cout<<count<<endl;
	vector<int> arr{1,3,5,6};
	int ret=s.searchInsert(arr,5);
	cout<<ret<<endl;
	string ransomNote = "aa";
	string magazine = "aab";
	if(s.canConstruct(ransomNote,magazine))
		cout<<"可以找到"<<endl;
	else
		cout<<"不可以找到"<<endl;
	if(s.isPalindrome(121))
		cout<<"是回文数"<<endl;
	else
		cout<<"不是回文数"<<endl;	
	return 0;
}
