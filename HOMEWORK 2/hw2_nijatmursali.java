
public class hw2_nijatmursali  
{ 
	
	static int RoundRobin(int[] processes) 
	{
		//your implementation goes here
		int quantum = 10; // quantum should be initialized to 10 		
		int sumofQuantums = 0;
		int n = processes.length; 
		int timeArr[] = new int[n];
		
		int totalTurnAroundTime = 0;
		
		int loop = 0;

		for(int i = 0; i < n ; i++) {
			loop += processes[i];
		}
		
		for (int j = 0; j < loop; j++) {
			for (int i = 0; i < n; i++) {
				if (processes[i] == 0) { //
					continue;
				}else if (processes[i] <= quantum) { //case when process less than quantum
					quantum = processes[i];
					System.out.print(i + " ");
					processes[i] = 0;
				}else if (processes[i] >= quantum) { //case when one process is more than quantum
					System.out.print(i + " ");
					processes[i] = processes[i] - quantum;
				}
				sumofQuantums = sumofQuantums + quantum;
				timeArr[i] = sumofQuantums;
			}
			
		}
		for(int i = 0; i < n; i++) {
			totalTurnAroundTime = totalTurnAroundTime + timeArr[i];
		}
		System.out.println();
		
		return totalTurnAroundTime;
	}
	
    public static void main(String[] args) 
    { 
        // process id's 
        int processes[] = {100, 20, 50}; 
        int result = RoundRobin(processes); 
        System.out.println(result);
    } 
} 
