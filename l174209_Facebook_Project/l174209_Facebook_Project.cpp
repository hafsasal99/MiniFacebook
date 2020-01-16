#include <iostream>
#include<fstream>
#include<string>
#include <stdlib.h>
using namespace std;
class object;
class users;
class pages;
class posts;
class comments;
class facebook;
class date;
class object
{
private:
	char* ID;
public:
	object()
	{
		ID = 0;
	}
	object(char* temp)//overloaded constructor
	{
		int length = 0;//computes length of given string
		for (length = 0; temp[length] != '\0'; length++);
		length++;

		ID = new char[length];

		for (int k = 0; k < length-1; k++)//explicitly copying the given string into ID on heap
		{
			ID[k] = temp[k];
		}
		ID[length - 1] = '\0';
	}
	virtual ~object()
	{
		if(ID!=0)
		delete[] ID;
	}
	void printID()
	{
		cout << ID;
	}
	char* getID()
	{
		return ID;
	}
	virtual void printdetails() = 0;
	virtual void printName() = 0;
	void setID(char* temp)
	{
		int length = 0;//computes length of given string
		for (length = 0; temp[length] != '\0'; length++);
		length++;

		ID = new char[length];

		for (int k = 0; k < length - 1; k++)//explicitly copying the given string into ID on heap
		{
			ID[k] = temp[k];
		}
		ID[length - 1] = '\0';
	
	}

};
class date
{
private:
	int day;
	int month;
	int year;
public:
	date(int d = 15, int m = 11, int y = 2017)
	{
		day = d;
		month = m;
		year = y;
	}
	void printDate()
	{
		cout << day << "/" << month << "/" << "/" << year ;
	}
	int getDay()
	{
		return day;
	}
	int getMonth()
	{
		return month;
	}
	int getYear()
	{
		return year;
	}
	bool within24Hrs(date currentDate)//checks whether *this date is within 24 hours of given date
	{
		if (currentDate.month == month && currentDate.year == year)
		{
			if (currentDate.day == day || currentDate.day == day + 1)
				return true;

		}
		return false;
	}
	void setDate(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;

	}

};
class comments :public object
{
private:
	posts* commentOn;
	object* commentBy;
	char* description;
public:
	comments(ifstream& fin, char* id) :object(id)
	{
		description = 0;
	}
	comments()
	{
		commentOn = 0;
		commentBy = 0;
		description = 0;
	}
	void setCommentOn(posts* ptr)
	{
		commentOn = ptr;
	}
	void setCommentBy(object* ptr)
	{
		commentBy = ptr;
	}
	void setDescription(char* string)
	{
		int length = strlen(string);
		length++;
		description = new char[length];
		for (int x = 0; string[x] != '\0'; x++)
		{
				description[x] = string[x];
					
		}
		description[length - 1] = '\0';
	
	}
	void printComment()
	{
		cout << "\t-";
		commentBy->printName();
		cout<< " wrote :" << description << endl;
	}
	void printName()
	{
		cout << description;
	}
	void printdetails()
	{
		cout << getID() << "-" << description << endl;
	}
	~comments()
	{
		if(description!=0)
			delete[] description;

	}
};
class posts :public object
{
private:
	date Date;
	char* description;
	object* sharedBy;
	object** likedBy;
	comments** Comments;
public:
	posts(ifstream& fin, char* id, date d) :object(id)
	{
		Date = d;
		char buffer[150];
		fin.getline(buffer, 150);
		fin.getline(buffer, 150);
		int length;
		for (length = 0; buffer[length] != '\0'; length++);//computing length of post description
		length++;

		description = new char[length];
		for (int k = 0; buffer[k] != '\0'; k++)//explicitly copying description of post
		{
			description[k] = buffer[k];
		}
		description[length - 1] = '\0';

		sharedBy = 0;
		Comments = 0;
	}

	void setSharedBy(object* ptr)
	{
		sharedBy = ptr;
	}
	void allocateLikedBy()
	{
		likedBy = new object*[10];
		for (int i = 0; i < 10; i++)
		{
			likedBy[i] = 0;
		}
	}
	void setLikedBy(object* ptr)
	{
		if (likedBy == 0)
		{
			allocateLikedBy();
		}
		for (int x = 0; x < 10; x++)//initialising likedBy list with nullptrs
		{
			if (likedBy[x] == 0)
			{
				likedBy[x] = ptr;
				break;
			}
		}
	}
	void setComment(comments* ptr)
	{
		if (Comments == 0) //allocation in case not done previously
		{
			Comments = new comments*[10];
			for (int y = 0; y < 10; y++)//initialising comments list with nullptrs
			{
				Comments[y] = 0;
			}
		}
		for (int x = 0; x < 10; x++)//setting comment
		{
			if (Comments[x] == 0)
			{
				Comments[x] = ptr;
				break;
			}
		}
		
	}
	date getDate()
	{
		return Date;
	}
	void printPost()//prints posts without date(for users' homepage)
	{
		cout << "--";
		sharedBy->printName();
		cout << " shared : '" << description << "'" << endl;
		if (Comments != 0)
		{
			for (int x = 0; Comments[x] != 0; x++)
			{
				Comments[x]->printComment();
			}
		}
	}
	void printdetails()
	{
		cout << description;

	}
	void printName()
	{
		cout << "--";
		printID();
		cout << "-";
		sharedBy->printName();
		cout << " shared: " << description << endl;
	}
	void viewLikedBy()
	{
		if (likedBy != 0)
		{
			cout << "Post Liked By:" << endl;
			for (int k = 0; likedBy[k] != 0; k++)
			{
				likedBy[k]->printdetails();
			}
		}
	}
	void printPostDetails()//prints posts and the date each was shared on for timelines
	{
		cout << "--";
		sharedBy->printName();
		cout << " shared : '" << description << "'" << "(";
		Date.printDate();
		cout << ")" << endl;
		if (Comments != 0)
		{
			for (int x = 0; Comments[x] != 0; x++)
			{
				Comments[x]->printComment();
			}
		}
	}
	posts(const posts& rhs)//copy constructor
	{
		int length;
		for (length = 0; rhs.description[length] != '\0'; length++);//computing length of post description
		length++;

		description = new char[length];
		for (int k = 0; rhs.description[k] != '\0'; k++)//explicitly copying description of post
		{
			description[k] = rhs.description[k];
		}
		description[length - 1] = '\0';
		Comments = 0;
		sharedBy = 0;
		likedBy = 0;
	}
	void setDate(date& rhs)
	{
		int day = rhs.getDay();
		int month = rhs.getMonth();
		int year = rhs.getYear();
		Date.setDate(day, month, year);
	
	}
	bool searchPosts(char* key)
	{

		int count = 0;
		for (int i = 0; description[i] != '\0'; i++)//checks whether a given post contains as substring the key
		{
			if (key[count] == description[i])
				count++;
			else
				count = 0;
			if (count == strlen(key))
				return true;
		}
		return false;
	}
	~posts()
	{
		delete[] description;
		if (likedBy != 0)
		{
			delete[] likedBy;
		}
		if (Comments != 0)
		{
			for (int k = 0; Comments[k] != 0; k++)
			{
				delete Comments[k];
			}
			delete[] Comments;
		}
	}
};
class pages :public object
{
private:
	char* title;
	posts** timeline;
	int numOfLikes;

public:
	pages(ifstream& fin, char* id) :object(id)//overloaded constructor
	{
		char buffer[80];
		fin.getline(buffer, 80);
		int length;
		for (length = 0;buffer [length] != '\0'; length++);//computing length of page title 

		title = new char[length];
		int count = 0;
		for (int k = 1; k < length; k++)//explicitly copying into title
		{
			title[count] = buffer[k];
			count++;
		}
		title[count] = '\0';

		
		numOfLikes = 0;
		timeline = 0;
	}
	void printLikedPages()
	{
		printID();
		cout << " - " << title << endl;
	}
	void setTimeline(posts* ptr)
	{
		if (timeline == 0)//allocation for likedPages in case not done previously
		{
			timeline = new posts*[10];
			for (int k = 0; k < 10; k++)
				timeline[k] = 0;
		}
		for (int x = 0; x < 10; x++)//setting timeline
		{
			if (timeline[x] == 0)
			{
				timeline[x] = ptr;
				break;
			}

		}

	}

	void printdetails()
	{
		cout <<getID()<<"-"<<title<<endl ;
	}
	void printName()
	{
		cout << title;
	}
	posts** getTimeline()
	{
		return timeline;
	}
	void printTimeline()
	{
		cout << title << endl;
		if (timeline != 0)
		{
			for (int x = 0; timeline[x] != 0; x++)
			{
				timeline[x]->printPostDetails();
			}
		}
	}
	bool searchPages(char* key)//traverses the title array to check whether it contains as substring the key
	{
		int count = 0;
		for (int k = 0; title[k] != '\0'; k++)
		{
			if (key[count] == title[k])
				count++;
			else
				count = 0;
			if (count == strlen(key))
				return true;
		}
		return false;
	}
	void printPostsForHome(date& currentDate)
	{
		if (timeline != 0)
		{
			for (int x = 0; timeline[x] != 0; x++)
			{
				date sharedDate = timeline[x]->getDate();
				if (sharedDate.within24Hrs(currentDate) == true)
				{
					timeline[x]->printPost();
					cout << endl;
				}


			}
		}
	}
	~pages()
	{
		delete[] title;
		if (timeline != 0)
		{
			for (int k = 0; timeline[k] != 0; k++)
			{
				delete timeline[k];
			}
			delete[] timeline;
		}
	}
};
class users :public object
{
private:
	char* name;
	users** friendList;
	pages** likedPages;
	posts** timeline;
	char** friendsId;

	
public:
	users(ifstream& fin, char* id) :object(id)
	{
		char fname[20];
		char lname[20];
		fin >> fname;
		fin >> lname;
		int length = 0;//computing length of first name
		for (length = 0; fname[length] != '\0'; length++);
		length++;

		int length2 = 0;//computing length of last name
		for (length2 = 0; lname[length2] != '\0'; length2++);
		length2++;

		name = new char[length + length2];
		int i;
		for (i = 0; fname[i] != '\0'; i++)//concatenating first and last name
		{
			name[i] = fname[i];
		}
		name[i] = ' ';
		i++;
		for (int k = 0; lname[k] != '\0'; k++)
		{
			name[i] = lname[k];
			i++;
		}
		name[i] = '\0';
		char temp[10];
		fin >> temp;
		int count = 0;
		if (strcmp(temp, "-1") != 0)
		{
			friendsId = new char*[10];
			friendList = new users*[10];
		}
			
		else
			friendsId = 0;
		for(count=0;count<10 && temp[0]!='-';count++)
		{
			for (length = 0; temp[length] != '\0'; length++);//computing length of friend's ID
			length++;

			friendsId[count] = new char[length];

			int x;
			for ( x = 0; x < length - 1; x++)//copying into friendsId
			{
				friendsId[count][x] = temp[x];
			}
			friendsId[count][x] = '\0';

			fin >> temp;

		}
		if (friendsId != 0)
		{
			for (count; count < 10; count++)
			{
				friendsId[count] = 0;
			}
		}
		if (friendsId != 0)
		{
			for (int i = 0; i < 10; i++)
			{

				friendList[i] = 0;

			}
		}
		likedPages = 0;
		timeline = 0;
	
	}
	void setLikedPage(pages* ptr)
	{
		if (likedPages == 0)//allocates page pointers if likedPages==0
		{
			likedPages = new pages*[10];
			for (int x = 0; x < 10; x++)
				likedPages[x] = 0;
		}
		for (int k = 0; k<10; k++)//stores likedPage pointer
		{
			if (likedPages[k] == 0)
			{
				likedPages[k] = ptr;
				break;
			}
				
		}
	}
	char* getName()
	{
		return name;
	}
	void printListView()
	{
		printID();
		cout << " - " << name << endl;
	}
	users** getFriendList()
	{
		return friendList;
	}
	char** getFriendsId()
	{
		return friendsId;
	}
	pages** getLikedPages()
	{
		return likedPages;
	}
	
	void viewFriendList()
	{
		cout << "\n\nCommand:\t\tView Friend List" << endl;
		cout << "---------------------------------------------------" << endl;
		cout <<name;
		cout << "- Friend List" << endl << endl << endl;
		for (int x = 0; x <10; x++)
		{
			if (friendList[x]!= 0)
				friendList[x]->printListView();
			else
				break;
		}
		cout << "---------------------------------------------------------------------" << endl;
	}
	void viewLikedPages()
	{
		cout << "\n\nCommand:\t\tView Liked Pages" << endl;
		cout << "---------------------------------------------------" << endl;
		cout <<name;
		cout << "- Liked Pages" << endl << endl << endl;
		for (int x = 0; x < 10; x++)
		{
			if (likedPages[x] != 0)
				likedPages[x]->printLikedPages();
			else
				break;
		}
		cout << "---------------------------------------------------------------------" << endl;
	}
	void allocateLikedPages()
	{
		likedPages = new pages*[10];
		for (int i = 0; i < 10; i++)//initialising list of likedPages to nullptrs
		{
			likedPages[i] = 0;
		}

	}
	void setTimeline(posts* ptr)
	{
		if (timeline == 0)//allocation of timeline in case not done previously
		{
			timeline = new posts*[10];
			for (int k = 0; k < 10; k++)//initialising timeline with nullptrs 
				timeline[k] = 0;
		}
		for (int x = 0; x < 10; x++)//setting posts on timeline
		{
			if (timeline[x] == 0)
			{
				timeline[x] = ptr;
				break;
			}
				
		}
			
	}
	posts** getTimeline()
	{
		return timeline;
	}
	void printdetails()
	{
		cout << getID() << "-" << name << endl;

	}
	void printName()
	{
		cout << name;
	}
	void printTimeline()
	{
		if (timeline != 0)
		{
			for (int x = 0; timeline[x] != 0; x++)
			{
				timeline[x]->printPostDetails();
				cout << endl;
			}

		}
	}
	bool searchUser(char* key)//traverses array for user's name to see whether it contains key as substring
	{
	
		int count = 0;
		for (int i = 0; name[i] != '\0'; i++)
		{
			if (key[count] == name[i])
				count++;
			else
				count = 0;
			if (count == strlen(key))
				return true;
		}
		
		return false;
	}
	void printHome(users* currentUser,date& currentDate)
	{
		for (int k = 0; friendList[k] != 0; k++)//printing posts shared by friends in the past 24 hours
		{
			if (friendList[k]->timeline != 0)
			{
				for (int x = 0; timeline[x] != 0; x++)
				{
					date sharedDate = timeline[x]->getDate();
					if (sharedDate.within24Hrs(currentDate) == true)
					{
						friendList[k]->timeline[x]->printPost();
						cout << endl;
					}


				}
			}
		}
		
		for (int k = 0; likedPages[k] != 0; k++)//printing posts shared by liked pgs in the past 24 hours
		{
			
			likedPages[k]->printPostsForHome(currentDate);
		}
	}
	~users()
	{
		if (friendList != 0)
			delete[] friendList;
		if (likedPages != 0)
			delete[] likedPages;
		if (timeline != 0)
		{
			for (int k = 0; timeline[k] != 0; k++)
			{
				delete timeline[k];
			}
			delete[] timeline;
		}
		if (name != 0)
			delete[] name;
	}
};



class Facebook
{
private:
	static int  totalUsers;
	static  int totalPages;
	static int totalPosts;
	static int totalComments;
	static int AllPosts;
	users** Users;
	pages** Pages;
	posts** Posts;
	users* currentUser;
static 	date currentDate;
public:

	Facebook()
	{
		Users=0;
		Pages=0;
		Posts = 0;
		currentUser=0;
		currentDate=0;
		
	}
	void loading()
	{
		ifstream fin;

		fin.open("Project-SocialNetworkPages.txt");//loading Pages
		int total;
		fin >> totalPages;
		
		char id[10];
		char buffer[80];
		fin.getline(buffer, 80);
		Pages = new pages*[totalPages];
		for (int i = 0; i < totalPages; i++)
		{
			fin >> id;
			Pages[i] = new pages(fin,id);
		}
		fin.close();

		fin.open("Project-SocialNetworkUers.txt");//loading Users
		fin >> totalUsers;
		
		char temp[9];
		Users = new users*[totalUsers];
		fin.getline(buffer, 80);

		for (int i = 0; i < totalUsers; i++)
		{
			fin >> id;
			Users[i] = new users(fin, id);
			char pageID[10];
			for (int k = 0; k < 10; k++)
			{
				fin >> pageID;
				if (k == 0 && strcmp(pageID, "-1") != 0)
				{
					Users[i]->allocateLikedPages();
				}
				if ((strcmp(pageID, "-1") == 0))
				{	
					break;

				}
					
				int y = 0;
				for (int x = 1; pageID[x] != '\0'; x++)//storing only the numerical value of ID in a temp array
				{
					temp[y] = pageID[x];
					y++;
				}
				temp[y] = '\0';
				int index = atoi(temp);
				Users[i]->setLikedPage(Pages[index-1]);
			
				
			}
			//fin.getline(buffer, 80);
		}
		fin.close();
		fin.open("Project-SocialNetworkPosts.txt");//loading Posts
		fin >> totalPosts;

		for (int k = 0; k < 8; k++) //skipping comments
		{
			fin.getline(buffer, 80);
		}
		Posts = new posts*[totalPosts];
		AllPosts = totalPosts;
		for (int i = 0; i < totalPosts; i++)
		{
			fin >> id;
			fin.getline(buffer, 80);
			int d, m, y;
			fin >> d;
			fin >> m;
			fin >> y;
			date Date(d, m, y);
			Posts[i] = new posts(fin,id,Date);
			fin >> buffer;
			if (strcmp(buffer, "-1") != 0)
			{
				char tempArray[10];
				int count = 0;
				for (int x = 1; buffer[x] != '\0'; x++)//storing the numerical value of object's ID
				{
					tempArray[count] = buffer[x];
					count++;
				}
				tempArray[count] = '\0';
				int index = atoi(tempArray);
				if (buffer[0] == 'u')
				{
					Posts[i]->setSharedBy(Users[index - 1]);
					Users[index - 1]->setTimeline(Posts[i]);
				}
					
				else
				{
					Posts[i]->setSharedBy(Pages[index - 1]);
					Pages[index - 1]->setTimeline(Posts[i]);
				}
					

			}
			fin.getline(buffer, 80);

			for (int a = 0; a < 10; a++)
			{
				fin >> id;
				if (strcmp(id, "-1") != 0 && a == 0)
				{
					Posts[i]->allocateLikedBy();
				}
				if (strcmp(id, "-1") == 0)
					break;
				int count = 0;
				char tempArray[10];
				for (int x = 1; id[x] != '\0'; x++)//storing the numerical value of object's ID
				{
					tempArray[count] = id[x];
					count++;
				}
				tempArray[count] = '\0';
				int index = atoi(tempArray);
				if (id[0] == 'u')
				{
					Posts[i]->setLikedBy(Users[index - 1]);
					
				}
					
				else
				{
					Posts[i]->setLikedBy(Pages[index - 1]);
				
				}
					
			
				
			}
			fin.getline(buffer, 80);
			fin.getline(buffer, 80);
		}
		fin.close();
		fin.open("Project-SocialNetworkComments.txt");//loading comments
		fin >> totalComments;
		char buffer1[150];
		comments** Comments=new comments*[totalComments];
		for (int k = 0; k < 3; k++)//skipping comments in file
		{
			fin.getline(buffer1, 150);
		}
		for (int i = 0; i < totalComments; i++)
		{
			fin >> id;
			Comments[i] = new comments(fin, id);
			fin >> buffer;
			int count = 0;
			for (int x = 4; buffer[x] != '\0'; x++)//retrieving post number
			{
				temp[count] = buffer[x];
				count++;
			}
			temp[count] = '\0';
			int index = atoi(temp);
			Posts[index - 1]->setComment(Comments[i]);
			Comments[i]->setCommentOn(Posts[index-1]);
			fin >> id;
			count = 0;
			for (int x = 1; id[x] != '\0'; x++)//retrieving user/page number who commented
			{
				temp[count] = id[x];
				count++;
			}
			temp[count] = '\0';
			index = atoi(temp);
			if (id[0] == 'u')
				Comments[i]->setCommentBy(Users[index - 1]);
			else
				Comments[i]->setCommentBy(Pages[index - 1]);
			
			fin.getline(buffer1, 150);
			char space;
			fin >> space;
			Comments[i]->setDescription(buffer1);
		}
		fin.close();
		delete[] Comments;
	}
	
	void linking()
	{
		
		for (int i = 0; i < totalUsers; i++)
		{
			users** friendList=Users[i]->getFriendList();
			char** friendsId = Users[i]->getFriendsId();

			if (friendsId != 0)
			{
				for (int k = 0; k < 10; k++)
				{
					if (friendsId[k] != 0)
					{
						char tempId[5];
						int count = 0;
						for (int x = 1; friendsId[k][x] != '\0'; x++)//storing the numerical value of friend ID in a temp array
						{
							tempId[count] = friendsId[k][x];
							count++;
						}
						tempId[count] = '\0';
						int index = atoi(tempId);
						friendList[k] = Users[index - 1];
					}
					else
						break;
				}
				for (int i = 0; i < 10; i++)//de-allocating friendsID
				{
					delete[] friendsId[i];
				}
				delete[] friendsId;
				friendsId = 0;
			}
		}

	}
	void setCurrentUser(char* id)
	{
		cout << "Command: Set Current User " << id << endl;
		char temp[4];
		int count = 0;
		for (int i = 1; id[i] != '\0'; i++)//storing the numerical value of the user's ID
		{
			temp[count] = id[i];
			count++;
		}
		temp[count] = '\0';
		int index = atoi(temp);
		if (index < totalUsers)
		{
			currentUser = Users[index - 1];
			cout << currentUser->getName() << " successfully set as current user." << endl;
		}
		else
		{
			cout << "User not Found" << endl;
			currentUser = 0;
		}
		
	}

	static void setCurrentDate(int d, int m, int y)
	{
		cout << "\n \n Command:\t\tSet current system date "<<d<<" " <<m<<" "<<y << endl;
		currentDate.setDate(d, m, y);
		cout << "System Date:\t\t";
		currentDate.printDate();
		
	}
	void Run()
	{
	
		setCurrentUser("u7");
		if (currentUser != 0)
		{
			setCurrentDate(15, 11, 2017);
			currentUser->viewFriendList();
			currentUser->viewLikedPages();

		}
	
		
	}
	void viewHome()
	{
		users** friendList=currentUser->getFriendList();
		cout << "Command:\t\t View Home" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << currentUser->getName() << "--Home Page " << endl<<endl;
		currentUser->printHome(currentUser,currentDate);
		cout << "---------------------------------------------------------------" << endl;
	}

	void viewTimeline()
	{
		cout << "Command:\t\t View Timeline" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << currentUser->getName() << "--Timeline " << endl << endl;
		currentUser->printTimeline();
		cout << "---------------------------------------------------------------" << endl;
	}
	void viewLikedList(char* id )
	{
		char temp[4]; int count = 0;
		cout << "Command:\tView Liked List (" << id << ")" << endl;
		cout << endl << endl;
		for (int i = 4; id[i] != '\0'; i++)//retrieving post number(ie numerical value of id)
		{
			temp[count] = id[i];
			count++;
		}
		temp[count] = '\0';
		int index = atoi(temp);
		posts* requiredPost = Posts[index - 1];
		requiredPost->viewLikedBy();
		cout << "---------------------------------------------------------" << endl;
	}
	void likePost(char* id)
	{
		char temp[4]; int count = 0;
		cout << "Command:\t\tLike Post(" << id << ")";
		cout << endl << endl;
		for (int i = 4; id[i] != '\0'; i++)//retrieving numerical value of post ID
		{
			temp[count] = id[i];
			count++;
		}
		temp[count] = '\0';
		int index = atoi(temp);
		posts* requiredPost = Posts[index - 1];
		requiredPost->setLikedBy(currentUser);
	}
	void postComment(char* id, char* content)
	{
		cout << "Command:\t\tPost Comment(" << id << "," << content << ")" << endl;
		char temp[4]; int count = 0;
		for (int i = 4; id[i] != '\0'; i++)//retrieving numerical value of postID
		{
			temp[count] = id[i];
			count++;
		}
		temp[count] = '\0';
		int index = atoi(temp);
		posts* requiredPost = Posts[index - 1];
		comments* ptr=new comments;
		totalComments++;
		ptr->setDescription(content);
		ptr->setCommentBy(currentUser);
		ptr->setCommentOn(requiredPost);
		char temp2[20];//setting comment ID
		_itoa_s(totalComments, temp2, 10);
		int x = strlen(temp2);
		for (x ;x>=0; x--)//concatenating 'c' and numerical value of ID
		{
			temp2[x+1] = temp2[x];
		}
		temp2[0] = 'c';

		ptr->setID(temp2);
		requiredPost->setComment(ptr);

	}
	void viewPost(char* id)
	{
		cout << "Command:\t\tView Post(" << id << ")" << endl;
		char temp[4]; int count = 0;
		for (int i = 4; id[i] != '\0'; i++)//retrieving numerical value of post ID
		{
			temp[count] = id[i];
			count++;
		}
		temp[count] = '\0';
		int index = atoi(temp);
		posts* requiredPost = Posts[index - 1];
		requiredPost->printPost();
		cout << "---------------------------------------------------------------" << endl;
	}
	void sharePost(char* id)
	{
		cout << "Command:\t\tShare Post(" << id << ")" << endl;
		char temp[4]; int count = 0;
		for (int i = 4; id[i] != '\0'; i++)//retrieving numerical value of post ID
		{
			temp[count] = id[i];
			count++;
		}
		temp[count] = '\0';
		int index = atoi(temp);
		posts* ptr = new posts(*Posts[index - 1]);
		ptr->setSharedBy(currentUser);
		ptr->setDate(currentDate);
		AllPosts++;
		char temp2[20];//setting post ID
		char ID[20];
		_itoa_s(AllPosts, temp2, 10);
		count = 4;
		ID[0] = 'p'; //concatenating "post" and numerical value of id
		ID[1] = 'o';
		ID[2] = 's';
		ID[3] = 't';
		for (int x = 0; temp2[x] != '\0'; x++)
		{
			ID[count] = temp2[x];
			count++;
		}
		ID[count] = '\0';
		ptr->setID(ID);
		currentUser->setTimeline(ptr);
	}
	void viewPage(char* id)
	{
		cout << "Command:\t\tView Page(" << id << ")" << endl << endl;
		char temp[4]; int count = 0;
		for (int i = 1; id[i] != '\0'; i++)//retrieving numerical value of page id
		{
			temp[count] = id[i];
			count++;
		}
		temp[count] = '\0';
		int index = atoi(temp);
		pages* requiredPage = Pages[index - 1];
		requiredPage->printTimeline();
		cout << "-----------------------------------------------------------------" << endl;
	}
	void Search(char* key)
	{
		cout << "Command :\t\tSearch (" << key << ")" << endl << endl;
		int count = 0;
		for (int i = 0; i < totalUsers; i++)
		{
			bool found=Users[i]->searchUser(key);
			
			if (found == true && count == 0)
			{
				cout << "Users: " << endl;
			}
			if (found == true)
			{
				count++;
				cout << "--";
				Users[i]->printListView();
			}
				
		}
		cout << endl;
		count = 0;
		for (int i = 0; i < totalPosts; i++)
		{
			bool found = Posts[i]->searchPosts(key);

			if (found == true && count == 0)
			{
				cout << "Posts: " << endl;
			}
			if (found == true)
			{
				count++;
				Posts[i]->printName();
			}

		}
		cout << endl;
		count = 0;
		for (int i = 0; i < totalPages; i++)
		{
			bool found = Pages[i]->searchPages(key);

			if (found == true && count == 0)
			{
				cout << "Pages: " << endl;
			}
			if (found == true)
			{
				count++;
				cout << "--";
				Pages[i]->printID() ;
				cout << "-";
				Pages[i]->printName();
			}

		}
		cout << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
	}
	~Facebook()
	{
		for (int i = 0; i < totalUsers; i++)
		{
			delete Users[i];
		}
		delete[] Users;
		for (int i = 0; i < totalPages; i++)
		{
			delete Pages[i];
		}
		delete[] Pages;
	}
};
int Facebook::totalUsers=0;
int Facebook::totalPages = 0;
int Facebook::totalPosts = 0;
int Facebook::totalComments = 0;
date Facebook::currentDate = 0;
int Facebook::AllPosts = 0;
void main()
{
	Facebook f1;
	f1.loading();
	f1.linking();
	f1.Run();
	f1.viewHome();
	f1.viewTimeline();
	f1.viewLikedList("post5");
	f1.likePost("post5");
	f1.viewLikedList("post5");
	f1.postComment("post4", "Good Luck for your Result");
	f1.viewPost("post4");
	f1.postComment("post8", "Thanks for the wishes");
	f1.viewPost("post8");
	f1.sharePost("post5");
	f1.viewTimeline();
	f1.viewPage("p1");
	f1.Search("Birthday");
	f1.Search("Ali");
	system("pause");
}