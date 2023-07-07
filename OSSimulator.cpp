#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

bool cmp(vector<int>&a,vector<int>&b)
{
    return a[1] < b[1];
}

class PageReplacement{
    int Frames,Pages;
    vector<int>pages;
    vector<int>frames;
    void printLRU_and_MRU(set<int>s , string res)
    {
        for(auto itr = s.begin() ; itr != s.end() ; itr++)
        {
            cout << *itr << "  " ;
        }

        int printHyphen = Frames-s.size();
        for(int i = 0 ; i < printHyphen ; i++)
        cout << "_" << "  ";
        
        cout << "      " << res << " " << endl;
    }
    public:
    PageReplacement(int n,int f)
    {
        Pages = n;
        pages.resize(n);
        Frames = f;
        frames.resize(f);
    }

    void printFrames(string res,set<int>s)
    {   
        
        for(int i = 0 ; i < Frames ; i++)
        {
            if(i < s.size())
            cout << frames[i] << "  " ;
            else
            cout << "_" << "  ";
        }

        cout << "      "<< res << " " << endl;
    }

    void insertData()
    {
        cout << "Please Enter the sequence of the Pages in which you want to access them . " << endl;

        for(int i = 0 ; i < Pages; i++)
        {
            int pageNo;
            cout << "Enter the pageNo : ";
            cin >> pageNo;

            pages[i] = pageNo;
        }
    }

    void Fifo()
    {   
        int start = 0,framePointer = 0,pageHit = 0,pageFault = 0;
        double hitRatio = 0.0;
        set<int>s;
        for(int i = 0 ; i < pages.size(); i++)
        {   
            
            if(s.find(pages[i]) == s.end())
            {
                if(s.size() == Frames)
                {   
                    s.erase(frames[start]);
                    start = (start+1)%Frames;
                }

                s.insert(pages[i]);

                frames[framePointer] = pages[i];
                framePointer = (framePointer+1) % Frames;

                printFrames("PageFault",s);
                pageFault++;
            }
            else
            {   
                printFrames("PageHit",s);
                pageHit++;
            }

            Sleep(2000);
        }

        cout << endl << endl;
        hitRatio = (double)pageHit/(double)Pages;
        cout << "Total pageFaults are : " << pageFault << endl ;
        cout << "Total pageHits are : " << pageHit << endl;
        cout << "The hit ratio is : " << hitRatio << endl;
        cout << "The hit percentage is : " << hitRatio * 100 << "%";
    }

    void LRU()
    {   int pageHit = 0,pageFault = 0,framePointer = 0;
        double hitRatio = 0.0;
        set<int>s;
        map<int,int>pageIndex; //map to store the index of every used page;
        for(int i = 0 ; i < pages.size() ; i++)
        {
            if(s.find(pages[i]) == s.end())
            {
                if(s.size() == Frames)
                {
                    int leastIndex = INT_MAX;
                    int elementToBeDeleted = -1;
                    for(auto itr = pageIndex.begin() ; itr != pageIndex.end() ; itr++)
                    {
                        if(itr->second < leastIndex)
                        {
                            leastIndex = itr->second;
                            elementToBeDeleted = itr->first;
                        }
                    }

                    s.erase(elementToBeDeleted);
                    pageIndex.erase(elementToBeDeleted);
                }

                s.insert(pages[i]);
                pageIndex[pages[i]] = i;
                printLRU_and_MRU(s,"PageFault");
                pageFault++;
            }
            else
            {
                pageIndex[pages[i]] = i;
                pageHit++;
                printLRU_and_MRU(s,"PageHit");
            }

            Sleep(2000);
        }

        cout << endl << endl;
        hitRatio = (double)pageHit/(double)Pages;
        cout << "Total pageFaults are : " << pageFault << endl;
        cout << "Total pageHits are : " << pageHit << endl;
        cout << "The hit ratio is : " << hitRatio << endl;
        cout << "The hit percentage is : " << hitRatio * 100 << "%";
    }

    void MRU()
    {
        int pageHit = 0,pageFault = 0;
        double hitRatio = 0.0;
        set<int>s;
        map<int,int>pageIndex; //map to store the index of every used page;
        for(int i = 0 ; i < pages.size() ; i++)
        {
            if(s.find(pages[i]) == s.end())
            {
                if(s.size() == Frames)
                {
                    int leastIndex = INT_MIN;
                    int elementToBeDeleted = -1;
                    for(auto itr = pageIndex.begin() ; itr != pageIndex.end() ; itr++)
                    {
                        if(itr->second > leastIndex)
                        {
                            leastIndex = itr->second;
                            elementToBeDeleted = itr->first;
                        }
                    }

                    s.erase(elementToBeDeleted);
                    pageIndex.erase(elementToBeDeleted);
                }

                s.insert(pages[i]);
                pageIndex[pages[i]] = i;
                printLRU_and_MRU(s,"PageFault");
                pageFault++;
            }
            else
            {
                pageIndex[pages[i]] = i;
                pageHit++;
                printLRU_and_MRU(s,"PageHit");
            }

            Sleep(2000);
        }

        cout << endl << endl;
        hitRatio = (double)pageHit/(double)Pages;
        cout << "Total pageFaults are : " << pageFault << endl;
        cout << "Total pageHits are : " << pageHit << endl;
        cout << "The hit ratio is : " << hitRatio << endl;
        cout << "The hit percentage is : " << hitRatio * 100 << "%" << endl;
    }
};

class ProcessManagement{
    int n;
    vector<vector<int>>process;
    public:
    ProcessManagement(int numOfProcess)
    {
        n = numOfProcess;
    }

    void insertData()
    {   
        int arrivalTime,burstTime;
        for(int i = 0 ; i < n ; i++)
        {   
            int processId;
            cout << "Enter the process id : " ;
            cin >> processId;
            cout << "Enter the arrival and burst time of process (seperated by space) : ";
            cin >> arrivalTime >>burstTime;

            process.push_back({processId,arrivalTime,burstTime});
        }
    }

    void printAns(vector<vector<int>>res)
    {   sort(res.begin(),res.end());
        cout << "Process ID\t\tArrival Time\t\tBurst Time\t\tCompletion Time\t\tTurnAround Time\t\tWaiting Time" << endl;  
        for(int i = 0  ; i < n ; i++)
        {
            for(int j = 0 ; j < 6 ; j++)
            {
                cout << res[i][j] << "\t\t\t" ;
            }

            cout << endl;
            Sleep(2000);
        }
    }

    void FCFS()
    {   
        vector<vector<int>>processCopy = process;
        sort(processCopy.begin(),processCopy.end(),cmp);
        vector<vector<int>>ans;
        int timeCounter = 0;
        vector<int>temp;

        cout << "The Order in which processes are executed is : " ;
        for(int i = 0 ; i < n ; i++)
        {   
            temp = {processCopy[i][0],processCopy[i][1],processCopy[i][2]};
            int completionTime;

            cout << "P" << processCopy[i][0] << " ";
            if(processCopy[i][1] <= timeCounter)
            completionTime = timeCounter+processCopy[i][2];
            else
            {
                timeCounter += processCopy[i][1]-timeCounter;
                completionTime = timeCounter+processCopy[i][2];
            }
            timeCounter = completionTime;
            int turnAroundTime = completionTime-processCopy[i][1];
            int waitingTime = turnAroundTime - processCopy[i][2];

            temp.push_back(completionTime);
            temp.push_back(turnAroundTime);
            temp.push_back(waitingTime);

            ans.push_back(temp);
            Sleep(1000);
        }

        cout << endl << endl;
        printAns(ans);
    }

    void SJF()
    {
        vector<vector<int>>copy = process;
        sort(copy.begin(),copy.end(),cmp);

        vector<vector<int>>ans;
        int timerCounter = 0;
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>pq;
        int index = 0;

        cout << "The order in which processes are executed : " ;
        while(index < copy.size())
        {   
            if(pq.empty() && timerCounter < copy[index][1])
            {
                timerCounter += copy[index][1]-timerCounter;
            }
            else
            {   
                vector<int>temp;
                while(index < copy.size() && timerCounter >= copy[index][1])
                {
                    pq.push({copy[index][2],copy[index][1],copy[index][0]});
                    index++;
                }

                int burstTime = pq.top()[0];
                int arrivalTime = pq.top()[1];
                int id = pq.top()[2];
                temp = {id,arrivalTime,burstTime};

                cout << "P" << id << " ";

                int completionTime = timerCounter+burstTime;
                timerCounter = completionTime;
                int turnAroundTime = completionTime-arrivalTime;
                int waitingTime = turnAroundTime-burstTime;

                temp.push_back(completionTime);
                temp.push_back(turnAroundTime);
                temp.push_back(waitingTime);

                ans.push_back(temp);
                pq.pop();

                Sleep(1000);
            }
        }

        while(!pq.empty())
        {   
            vector<int>temp;
            int burstTime = pq.top()[0];
            int arrivalTime = pq.top()[1];
            int id = pq.top()[2];
            temp = {id,arrivalTime,burstTime};

            cout << "P" << id << " ";
            int completionTime = timerCounter+burstTime;
            timerCounter = completionTime;
            int turnAroundTime = completionTime-arrivalTime;
            int waitingTime = turnAroundTime-burstTime;

            temp.push_back(completionTime);
            temp.push_back(turnAroundTime);
            temp.push_back(waitingTime);

            ans.push_back(temp);
            pq.pop();
            Sleep(1000);
        }

        cout << endl << endl;
        printAns(ans);
    }

    void RoundRobin()
    {   
        int timeQuantum;
        cout << "Enter the timeQuantum " ;
        cin >> timeQuantum;

        vector<vector<int>>copy = process;
        vector<vector<int>>ans;
        sort(copy.begin(),copy.end());

        map<int,int>IDtoBurstTime;
        for(int i = 0 ; i < n ; i ++)
        {
            IDtoBurstTime[copy[i][0]] = copy[i][2];
        }

        int index = 0,timeCounter = 0;
        queue<vector<int>>ReadyQueue;
        vector<int>temp(6);
        bool pushLastProcess = false;
        cout << "The order in which tasks are executed is : ";
        while(!ReadyQueue.empty() || index < n)
        {
            if(ReadyQueue.empty() && timeCounter < copy[index][1])
            {
                timeCounter += copy[index][1]-timeCounter;
                continue;
            }
            else if(index < n && timeCounter >= copy[index][1])
            {
                while(index < n && timeCounter >= copy[index][1])
                {
                    ReadyQueue.push(copy[index]);
                    index++;
                }
            }

                if(pushLastProcess == true)
                ReadyQueue.push(temp);

                int processId = temp[0] = ReadyQueue.front()[0];
                int arrivalTime = temp[1] = ReadyQueue.front()[1];
                int burstTime = temp[2] = ReadyQueue.front()[2];
                ReadyQueue.pop();

                cout << "P" << processId << " ";
                if(burstTime <= timeQuantum)
                {
                    int completionTime = timeCounter+burstTime;
                    timeCounter = completionTime;
                    int turnAroundTime = completionTime-arrivalTime;
                    int waitingTime = turnAroundTime-IDtoBurstTime[processId];
                    temp[2] = IDtoBurstTime[processId];

                    temp[3] = completionTime ; temp[4] = turnAroundTime ; temp[5] = waitingTime ;

                    ans.push_back(temp);
                    pushLastProcess = false;
                }
                else
                {
                    temp[2] -= timeQuantum;
                    timeCounter += timeQuantum;

                    pushLastProcess = true;
                }

                Sleep(1000);  
        }

        while(pushLastProcess == true)
        {
              temp[3] = timeCounter+temp[2];
              temp[4] = temp[3]-temp[1];
              temp[5] = temp[4]-IDtoBurstTime[temp[0]];

              temp[2] = IDtoBurstTime[temp[0]];

              ans.push_back(temp);
              pushLastProcess = false;
        }
        cout << endl << endl;
        printAns(ans);
    }
};

class DiskScheduling{
    int n;
    vector<int>disks;
    public:
    DiskScheduling(int numOfDisks)
    {
        n = numOfDisks;
    }

    void insertData()
    {
        int i = 0 ,invalidInput = 0 ;
        while(i < n)
        {   
            int diskNo;
            cout << "Enter the disk number which you want to access (Between 0 and 100) : " ;
            cin >> diskNo;

            if(diskNo < 0 || diskNo > 200)
            {   
                if(invalidInput >= 10)
                {
                    cout << "You have exhausted your limit of invalid inputs." << endl;
                    cout << "Operation is terminating . " << endl;
                    return ;
                }
                cout << "Please enter a valid diskNo . " << endl;
                invalidInput++;
            }
            else
            {
                disks.push_back(diskNo);
                invalidInput = 0;
                i++;
            }


        }
    }

    void FCFS()
    {
        int totalDiskMovements = 0;
        cout << "Enter the initial position of HeadPointer : ";
        int initialPosition; 
        cin >> initialPosition ;

        cout << "The order of accessing the disks is : " ;
        for(int i = 0 ; i < n ; i++)
        {
            cout << disks[i] << " ";
            totalDiskMovements += abs(initialPosition-disks[i]);
            initialPosition = disks[i];
            Sleep(1000);
        }

        cout << endl;
        cout << "The total movement of headPointer is : " << totalDiskMovements << endl;
    }

    void SSTF()
    {
        int totalDiskMovements = 0;
        cout << "Enter the initail position of HeadPointer : ";
        int initialPosition ;
        cin >> initialPosition ;
        vector<int>seeksequence;

        set<int>usedIndex;
        while(usedIndex.size() != n)
        {
            //find minimum for initialPosition
            int minDiff = INT_MAX , currIndex;
            vector<int>copy = disks;
            sort(copy.begin(),copy.end());
            for(int i = 0 ; i < n ; i++)
            {
                if(abs(initialPosition - copy[i]) <= minDiff && usedIndex.find(i) == usedIndex.end())
                {
                    currIndex = i;
                    minDiff = abs(initialPosition-copy[i]);
                }
            }

            seeksequence.push_back(copy[currIndex]);
            usedIndex.insert(currIndex);
            totalDiskMovements += minDiff;
            initialPosition = copy[currIndex];
        }

        cout << "The order of accessing disks is : " ;
        for(int i = 0 ; i < n ;i++)
        {
            cout << seeksequence[i] << " " ;
            Sleep(1000);
        }

        cout << endl;
        cout << "The total number of disk movements are : " << totalDiskMovements << endl;
    }

    void SCAN()
    {
        vector<int>copy = disks;
        sort(copy.begin(),copy.end());

        int totalDiskMovement = 0 , initialHead;
        cout << "Enter the position of the head : " ;
        cin >> initialHead;
        
        int index = -1;
        //find the just smaller element then the initial Head Pointer
        for(int i = 0 ; i < n ; i++)
        {
            if(copy[i] <= initialHead)
            index = i;
            else
            break;
        }

        //now print the order
        cout << "The order in which disk are accessed is : ";
        for(int i = index ; i >= 0 ; i--)
        {
            cout << copy[i] << " ";
            totalDiskMovement += abs(initialHead-copy[i]);
            initialHead = copy[i];

            Sleep(1000);
        }

        totalDiskMovement += abs(initialHead-0);
        initialHead = 0;
        cout << initialHead << " " ;
        Sleep(1000) ;

        //now print the rest of disks
        for(int i = index+1 ; i < n ; i++)
        {
            cout << copy[i] << " ";
            totalDiskMovement += abs(initialHead-copy[i]);
            initialHead = copy[i];

            Sleep(1000);
        }

        cout << endl;
        cout << "Total Disk Movements are : " << totalDiskMovement << endl;
    }

    void LOOK()
    {
        vector<int>copy = disks;
        sort(copy.begin(),copy.end());

        int totalDiskMovement = 0 , initialHead;
        cout << "Enter the position of the head : " ;
        cin >> initialHead;
        
        int index = -1;
        //find the just smaller element then the initial Head Pointer
        for(int i = n-1 ; i >= 0 ; i--)
        {
            if(copy[i] >= initialHead)
            index = i;
            else
            break;
        }

        //now print the order
        cout << "The order in which disk are accessed is : ";
        for(int i = index ; i < n ; i++)
        {
            cout << copy[i] << " ";
            totalDiskMovement += abs(initialHead-copy[i]);
            initialHead = copy[i];

            Sleep(1000);
        }

        //now print the rest of disks
        for(int i = index-1 ; i >= 0 ; i--)
        {
            cout << copy[i] << " ";
            totalDiskMovement += abs(initialHead-copy[i]);
            initialHead = copy[i];

            Sleep(1000);
        }

        cout << endl;
        cout << "Total Disk Movements are : " << totalDiskMovement << endl;
    }
};

void executeProcessManagement()
{
    cout << endl << endl << endl << setw(90) << "WELCOME TO THE PROCESS MANAGEMENT SECTION " << endl;
    cout << "Please Enter the number of processes you want to manage : ";
    int noOfProcess;
    cin >> noOfProcess;

    ProcessManagement PM(noOfProcess);
    PM.insertData();
    
    cout << endl << endl << "Select which Algorithm you want to perform : " << endl;
    cout << "1. First Come First Serve \t\t" ;
    cout << "2. Shortest Job Next \t\t";
    cout << "3. Round Robin Scheduling \t\t";
    cout << endl << "Enter your choice : ";

    start:
    int choice;
    cin >> choice;
    switch(choice)
    {
        case 1:  PM.FCFS();
                break;
        case 2:  PM.SJF();
                break;
        case 3:  PM.RoundRobin();
                break;
        default:    cout << "Wrong Choice Entered."<< endl;
                    cout << "Press 1 to ReEnter your choice." << endl;
                    cout << "Press 0 to exit the program." << endl;
                    int ch;
                    cin >> ch;

                    if(ch) goto start;
                    else
                    exit(0);
    }            
}
void executePageReplacement()
{
    cout << endl << endl << endl << setw(90) << "WELCOME TO THE PAGE REPLACEMENT SECTION " << endl;
    cout << "Please Enter the number of pages you want to insert : ";
    int noOfPages,noOfFrames;
    cin >> noOfPages;
    cout << "Please Enter the number of frames you want to have : ";
    cin >> noOfFrames;

    PageReplacement PR(noOfPages,noOfFrames);
    PR.insertData();
    
    cout << endl << endl << "Select which Algorithm you want to perform : " << endl;
    cout << "1. First In First Out \t\t" ;
    cout << "2. Least Recently Used \t\t";
    cout << "3. Most Recently Used \t\t";
    cout << endl << "Enter your choice : ";

    start:
    int choice;
    cin >> choice;
    switch(choice)
    {
        case 1:  PR.Fifo();
                break;
        case 2:  PR.LRU();
                break;
        case 3:  PR.MRU();
                break;
        default:    cout << "Wrong Choice Entered."<< endl;
                    cout << "Press 1 to ReEnter your choice." << endl;
                    cout << "Press 0 to exit the program." << endl;
                    int ch;
                    cin >> ch;

                    if(ch) goto start;
                    else
                    exit(0);
    }            

}
void executeDiskAccessing()
{
    cout << endl << endl << endl << setw(90) << "WELCOME TO THE DISK SCHEDULING ALGORITHM SECTION " << endl;
    cout << "Please Enter the total number of disk request : ";
    int noOfDisksRequest;
    cin >> noOfDisksRequest;

    DiskScheduling DS(noOfDisksRequest);
    DS.insertData();
    
    cout << endl << endl << "Select which Algorithm you want to perform : " << endl;
    cout << "1. First Come First Serve \t\t" ;
    cout << "2. Shortes Seek Time First \t\t";
    cout << "3. SCAN Algorithm \t\t";
    cout << "4. LOOK Algorithm \t\t";
    cout << endl << "Enter your choice : ";

    start:
    int choice;
    cin >> choice;
    switch(choice)
    {
        case 1:  DS.FCFS();
                break;
        case 2:  DS.SSTF();
                break;
        case 3:  DS.SCAN();
                break;
        case 4: DS.LOOK();
                break;
        default:    cout << "Wrong Choice Entered."<< endl;
                    cout << "Press 1 to ReEnter your choice." << endl;
                    cout << "Press 0 to exit the program." << endl;
                    int ch;
                    cin >> ch;

                    if(ch) goto start;
                    else
                    exit(0);
    }            
}
int main()
{
    cout << setw(75) << "WELCOME TO THE OS SIMULATOR" << endl;
    cout << setw(130) << "This project demonstrates the working of the various algorithms used in Opearting System for the following tasks : ";
    cout << endl << endl;

    doitAgain:
    cout << setw(65) << "MAIN MENU " << endl;
    cout << setw(76) << "1. Process Management" << endl;
    cout << setw(86) << "2. Page Replacement Algorithms " << endl;
    cout << setw(84) << "3. Disk Accessing Algorithms " << endl;

    start:
    int choice ;
    cout << setw(100) << "Please Enter the serial number of the task you want to perform : ";
    cin >> choice ;

    switch(choice)
    {
        case 1: executeProcessManagement();
                break;

        case 2: executePageReplacement();
                break;
        
        case 3: executeDiskAccessing();
                break;
        
        default:    cout << "Wrong Choice " << endl;
                    cout << "Press 1 to make choice Again" << endl;
                    cout << "Press 0 to terminate the Progarm" << endl;
                    int ch ;
                    cout << "Enter your choice : " ;
                    cin >> ch; 

                    if(ch == 1) goto start;
                    else
                    exit(0);
                    break;
    }

    cout << endl;
    cout << "Do you want to perfom more operations ?" << endl;
    cout<< "Press Y for YES or N for No :  " << endl;
    char var ;
    cin >> var ;

    if(var == 'Y' || var == 'y')
    goto doitAgain;
    else
    {
        cout << "THANK YOU FOR CHECKING THIS OUT.";
        exit(0);
    }
    return 0;
}